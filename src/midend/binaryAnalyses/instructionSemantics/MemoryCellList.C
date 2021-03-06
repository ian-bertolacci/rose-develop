#include <sage3basic.h>
#include <MemoryCellList.h>

namespace rose {
namespace BinaryAnalysis {
namespace InstructionSemantics2 {
namespace BaseSemantics {

void
MemoryCellList::clear() {
    cells.clear();
    MemoryCellState::clear();
}

SValuePtr
MemoryCellList::readMemory(const SValuePtr &addr, const SValuePtr &dflt, RiscOperators *addrOps, RiscOperators *valOps) {
    CellList::iterator cursor = get_cells().begin();
    CellList cells = scan(cursor /*in,out*/, addr, dflt->get_width(), addrOps, valOps);
    SValuePtr retval = mergeCellValues(cells, dflt, addrOps, valOps);
    updateReadProperties(cells);
    if (cells.empty()) {
        // No matching cells
        insertReadCell(addr, retval);
    } else if (cursor == get_cells().end()) {
        // No must_equal match and at least one may_equal match. We must merge the default into the return value and save the
        // result back into the cell list.
        retval = retval->createMerged(dflt, merger(), valOps->solver());
        AddressSet writers = mergeCellWriters(cells);
        InputOutputPropertySet props = mergeCellProperties(cells);
        insertReadCell(addr, retval, writers, props);
    } else if (cells.size() == 1) {
        // Exactly one must_equal match (no additional may_equal matches)
    } else {
        // One or more may_equal matches with a final must_equal match.
        AddressSet writers = mergeCellWriters(cells);
        InputOutputPropertySet props = mergeCellProperties(cells);
        insertReadCell(addr, retval, writers, props);
    }
    return retval;
}

void
MemoryCellList::writeMemory(const SValuePtr &addr, const SValuePtr &value, RiscOperators *addrOps, RiscOperators *valOps)
{
    ASSERT_not_null(addr);
    ASSERT_require(!byteRestricted() || value->get_width() == 8);
    MemoryCellPtr newCell = protocell->create(addr, value);

    if (addrOps->currentInstruction() || valOps->currentInstruction()) {
        newCell->ioProperties().insert(IO_WRITE);
    } else {
        newCell->ioProperties().insert(IO_INIT);
    }

    // Prune away all cells that must-alias this new one since they will be occluded by this new one.
    if (occlusionsErased_) {
        for (CellList::iterator cli=cells.begin(); cli!=cells.end(); /*void*/) {
            MemoryCellPtr oldCell = *cli;
            if (newCell->must_alias(oldCell, addrOps)) {
                cli = cells.erase(cli);
            } else {
                ++cli;
            }
        }
    }

    // Insert the new cell
    cells.push_front(newCell);
    latestWrittenCell_ = newCell;
}

bool
MemoryCellList::merge(const MemoryStatePtr &other_, RiscOperators *addrOps, RiscOperators *valOps) {
    MemoryCellListPtr other = boost::dynamic_pointer_cast<MemoryCellList>(other_);
    ASSERT_not_null(other);
    bool changed = false;

    BOOST_REVERSE_FOREACH (const MemoryCellPtr &otherCell, other->get_cells()) {
        // Is there some later-in-time (earlier-in-list) cell that occludes this one? If so, then we don't need to process this
        // cell.
        bool isOccluded = false;
        BOOST_FOREACH (const MemoryCellPtr &cell, other->get_cells()) {
            if (cell == otherCell) {
                break;
            } else if (otherCell->get_address()->must_equal(cell->get_address(), addrOps->solver())) {
                isOccluded = true;
            }
        }
        if (isOccluded)
            continue;

        // Read the value, writers, and properties without disturbing the states
        SValuePtr address = otherCell->get_address();

        CellList::iterator otherCursor = other->get_cells().begin();
        CellList otherCells = other->scan(otherCursor /*in,out*/, address, 8, addrOps, valOps);
        SValuePtr otherValue = mergeCellValues(otherCells, valOps->undefined_(8), addrOps, valOps);
        AddressSet otherWriters = mergeCellWriters(otherCells);
        InputOutputPropertySet otherProps = mergeCellProperties(otherCells);

        CellList::iterator thisCursor = get_cells().begin();
        CellList thisCells = scan(thisCursor /*in,out*/, address, 8, addrOps, valOps);

        // Merge cell values
        if (thisCells.empty()) {
            writeMemory(address, otherValue, addrOps, valOps);
            latestWrittenCell_->setWriters(otherWriters);
            latestWrittenCell_->ioProperties() = otherProps;
            changed = true;
        } else {
            bool cellChanged = false;
            SValuePtr thisValue = mergeCellValues(thisCells, valOps->undefined_(8), addrOps, valOps);
            SValuePtr mergedValue = thisValue->createOptionalMerge(otherValue, merger(), valOps->solver()).orDefault();
            if (mergedValue)
                cellChanged = true;

            AddressSet thisWriters = mergeCellWriters(thisCells);
            AddressSet mergedWriters = otherWriters | thisWriters;
            if (mergedWriters != thisWriters)
                cellChanged = true;

            InputOutputPropertySet thisProps = mergeCellProperties(thisCells);
            InputOutputPropertySet mergedProps = otherProps | thisProps;
            if (mergedProps != thisProps)
                cellChanged = true;

            if (cellChanged) {
                if (!mergedValue)
                    mergedValue = thisValue->copy();
                writeMemory(address, mergedValue, addrOps, valOps);
                latestWrittenCell_->setWriters(mergedWriters);
                latestWrittenCell_->ioProperties() = mergedProps;
                changed = true;
            }
        }
    }
    return changed;
}

SValuePtr
MemoryCellList::mergeCellValues(const CellList &cells, const SValuePtr &dflt, RiscOperators *addrOps, RiscOperators *valOps) {
    SValuePtr retval;
    BOOST_FOREACH (const MemoryCellPtr &cell, cells) {
        // Get the cell's value. If the cell value is not the same width as the desired return value then we've go more work to
        // do. This isn't implemented yet. [Robb P. Matzke 2015-08-17]
        SValuePtr cellValue = valOps->unsignedExtend(cell->get_value(), dflt->get_width());

        if (!retval) {
            retval = cellValue;
        } else {
            retval = retval->createMerged(cellValue, merger(), valOps->solver());
        }
    }

    return retval ? retval : dflt;
}

MemoryCellList::AddressSet
MemoryCellList::mergeCellWriters(const CellList &cells) {
    AddressSet writers;
    BOOST_FOREACH (const MemoryCellPtr &cell, cells)
        writers |= cell->getWriters();
    return writers;
}

InputOutputPropertySet
MemoryCellList::mergeCellProperties(const CellList &cells) {
    InputOutputPropertySet props;
    BOOST_FOREACH (const MemoryCellPtr &cell, cells)
        props |= cell->ioProperties();
    return props;
}

void
MemoryCellList::updateReadProperties(CellList &cells) {
    BOOST_FOREACH (MemoryCellPtr &cell, cells) {
        cell->ioProperties().insert(IO_READ);
        if (cell->ioProperties().exists(IO_WRITE)) {
            cell->ioProperties().insert(IO_READ_AFTER_WRITE);
        } else {
            cell->ioProperties().insert(IO_READ_BEFORE_WRITE);
        }
        if (!cell->ioProperties().exists(IO_INIT))
            cell->ioProperties().insert(IO_READ_UNINITIALIZED);
    }
}

MemoryCellPtr
MemoryCellList::insertReadCell(const SValuePtr &addr, const SValuePtr &value) {
    MemoryCellPtr cell = protocell->create(addr, value);
    cell->ioProperties().insert(IO_READ);
    cell->ioProperties().insert(IO_READ_BEFORE_WRITE);
    cell->ioProperties().insert(IO_READ_UNINITIALIZED);
    cells.push_front(cell);
    return cell;
}

MemoryCellPtr
MemoryCellList::insertReadCell(const SValuePtr &addr, const SValuePtr &value,
                               const AddressSet &writers, const InputOutputPropertySet &props) {
    MemoryCellPtr cell = protocell->create(addr, value);
    cell->setWriters(writers);
    cell->ioProperties() = props;
    cells.push_front(cell);
    return cell;
}

MemoryCell::AddressSet
MemoryCellList::getWritersUnion(const SValuePtr &addr, size_t nBits, RiscOperators *addrOps, RiscOperators *valOps) {
    MemoryCell::AddressSet retval;
    CellList::iterator cursor = get_cells().begin();
    BOOST_FOREACH (const MemoryCellPtr &cell, scan(cursor, addr, nBits, addrOps, valOps))
        retval |= cell->getWriters();
    return retval;
}

MemoryCell::AddressSet
MemoryCellList::getWritersIntersection(const SValuePtr &addr, size_t nBits, RiscOperators *addrOps, RiscOperators *valOps) {
    MemoryCell::AddressSet retval;
    CellList::iterator cursor = get_cells().begin();
    size_t nCells = 0;
    BOOST_FOREACH (const MemoryCellPtr &cell, scan(cursor, addr, nBits, addrOps, valOps)) {
        if (1 == ++nCells) {
            retval = cell->getWriters();
        } else {
            retval &= cell->getWriters();
        }
        if (retval.isEmpty())
            break;
    }
    return retval;
}

// [Robb P. Matzke 2015-08-10]: deprecated; use getWritersUnion instead.
std::set<rose_addr_t>
MemoryCellList::get_latest_writers(const SValuePtr &addr, size_t nbits, RiscOperators *addrOps, RiscOperators *valOps) {
    AddressSet writers = getWritersUnion(addr, nbits, addrOps, valOps);
    std::set<rose_addr_t> retval;
    BOOST_FOREACH (rose_addr_t va, writers.values())
        retval.insert(va);
    return retval;
}

void
MemoryCellList::print(std::ostream &stream, Formatter &fmt) const
{
    for (CellList::const_iterator ci=cells.begin(); ci!=cells.end(); ++ci)
        stream <<fmt.get_line_prefix() <<(**ci+fmt) <<"\n";
}

// [Robb P. Matzke 2015-08-18]: deprecated
MemoryCellList::CellList
MemoryCellList::scan(const BaseSemantics::SValuePtr &addr, size_t nbits, RiscOperators *addrOps, RiscOperators *valOps,
                     bool &short_circuited/*out*/) const {
    CellList::const_iterator cursor = get_cells().begin();
    CellList retval = scan(cursor, addr, nbits, addrOps, valOps);
    short_circuited = cursor != get_cells().end();
    return retval;
}

std::vector<MemoryCellPtr>
MemoryCellList::matchingCells(const MemoryCell::Predicate &p) const {
    std::vector<MemoryCellPtr> retval;
    BOOST_FOREACH (const MemoryCellPtr &cell, cells) {
        if (p(cell))
            retval.push_back(cell);
    }
    return retval;
}

std::vector<MemoryCellPtr>
MemoryCellList::leadingCells(const MemoryCell::Predicate &p) const {
    std::vector<MemoryCellPtr> retval;
    BOOST_FOREACH (const MemoryCellPtr &cell, cells) {
        if (!p(cell))
            break;
        retval.push_back(cell);
    }
    return retval;
}

void
MemoryCellList::eraseMatchingCells(const MemoryCell::Predicate &p) {
    CellList::iterator ci = cells.begin();
    while (ci != cells.end()) {
        if (p(*ci)) {
            ci = cells.erase(ci);
        } else {
            ++ci;
        }
    }
}

void
MemoryCellList::eraseLeadingCells(const MemoryCell::Predicate &p) {
    CellList::iterator ci = cells.begin();
    while (ci != cells.end()) {
        if (p(*ci)) {
            ci = cells.erase(ci);
        } else {
            return;
        }
    }
}

void
MemoryCellList::traverse(MemoryCell::Visitor &v) {
    BOOST_FOREACH (MemoryCellPtr &cell, cells)
        v(cell);
}

} // namespace
} // namespace
} // namespace
} // namespace

#ifdef ROSE_HAVE_BOOST_SERIALIZATION_LIB
BOOST_CLASS_EXPORT_IMPLEMENT(rose::BinaryAnalysis::InstructionSemantics2::BaseSemantics::MemoryCellList);
#endif
