include $(top_srcdir)/config/Makefile.for.ROSE.includes.and.libs

# noinst_PROGRAMS = globalVariablesInLambdas

# globalVariablesInLambdas_SOURCES = globalVariablesInLambdas.C

AM_CPPFLAGS = $(ROSE_INCLUDES)
LDADD    = $(LIBS_WITH_RPATH) $(ROSE_LIBS)



# globalVariablesInLambdas_TESTS = test_1.C


EXAMPLE_TESTCODES_REQUIRED_TO_PASS = \
test2012_01.C \
test2012_02.C \
test2012_05.C \
test2014_02.C \
test2014_04.C \
test2014_05.C \
test2014_06.C \
test2014_07.C \
test2014_08.C \
test2014_09.C \
test2014_11.C \
test2014_12.C \
test2014_13.C \
test2014_14.C \
test2014_15.C \
test2014_16.C \
test2014_17.C \
test2014_18.C \
test2014_19.C \
test2014_20.C \
test2014_21.C \
test2014_22.C \
test2014_23.C \
test2014_27.C \
test2014_29.C \
test2014_30.C \
test2014_32.C \
test2014_33.C \
test2014_34.C \
test2014_36.C \
test2014_37.C \
test2014_38.C \
test2014_39.C \
test2014_40.C \
test2014_41.C \
test2014_42.C \
test2014_43.C \
test2014_44.C \
test2014_45.C \
test2014_47.C \
test2014_48.C \
test2014_49.C \
test2014_50.C \
test2014_51.C \
test2014_52.C \
test2014_54.C \
test2014_55.C \
test2014_56.C \
test2014_57.C \
test2014_58.C \
test2014_70.C \
test2014_71.C \
test2014_72.C \
test2014_73.C \
test2014_74.C \
test2014_75.C \
test2014_76.C \
test2014_77.C \
test2014_78.C \
test2014_79.C \
test2014_80.C \
test2014_81.C \
test2014_83.C \
test2014_84.C \
test2014_86.C \
test2014_87.C \
test2014_89.C \
test2014_90.C \
test2015_01.C \
test2015_02.C \
test2015_03.C \
test2015_04.C \
test2015_05.C \
test2015_06.C \
test2015_07.C \
test2015_08.C \
test2015_09.C \
test2015_10.C \
test2015_12.C \
test2015_13.C \
test2015_14.C \
test2016_01.C \
test2016_03.C \
test2016_04.C \
test2016_06.C \
test2016_07.C \
test2016_10.C \
test2016_11.C \
test2016_13.C \
test2016_14.C \
test2016_15.C \
test2016_16.C \
test2016_17.C \
test2016_18.C \
test2016_19.C \
test2016_21.C \
test2016_22.C \
test2016_25.C \
test2016_29.C \
test2016_30.C \
test2016_37.C \
test2016_39.C \
test2016_42.C \
test2016_91.C \
test2016_92.C \
test2016_93.C \
test2017_03.C \
test2017_04.C \
test2017_07.C \
test2017_08.C \
test2017_09.C \
last.C

# DQ (2/21/2017): This fails due to missing builtin functions (still to be addressed).
if !USING_CLANG_COMPILER
# EXAMPLE_TESTCODES_REQUIRED_TO_PASS += 
# test2015_08.C 
endif

# DQ (11/19/2016): This test is failing in the unparsed code (a RAJA example) at least for the GNU 6.1 compiler and using EDG 4.11).
# test2016_40.C 
if ROSE_USE_EDG_VERSION_4_9
EXAMPLE_TESTCODES_REQUIRED_TO_PASS += \
   test2014_25.C \
   test2014_28.C \
   test2015_11.C \
   test2016_40.C
endif

if !OS_MACOSX
EXAMPLE_TESTCODES_REQUIRED_TO_PASS += \
   test2016_12.C \
   test2016_20.C \
   test2016_23.C \
   test2016_24.C \
   test2016_33.C \
   test2016_34.C \
   test2016_35.C \
   test2016_36.C \
   test2016_90.C 
endif

# DQ (7/9/2016): This test is inconsistatn with what I understand to be the most recent fixes.
# test2016_41.C (expression templates example)

# DQ (5/8/2016): Demonstration of bug in GNU 4.9.2 header files (test2016_31.C)
# test2016_26.C
# test2016_27.C
# test2016_28.C
# test2016_31.C

# New test codes not yet tested in regression tests.
# test2015_15.C 
# test2015_16.C 

# Failing tests:
# test2014_10.C
# test2014_24.C
# test2014_26.C
# test2014_31.C 
# test2014_35.C 
# test2014_46.C 
# test2014_53.C 

# These are incomplete non-compilable code fragments
TESTCODE_CURRENTLY_FAILING = \
test2012_03.C \
test2012_04.C \
test2012_06.C \
test2012_07.C \
test2012_08.C \
test2012_09.C \
test2012_10.C \
test2012_11.C \
test2012_12.C \
test2012_13.C \
test2012_14.C \
test2012_15.C \
test2012_16.C \
test2012_17.C \
test2012_18.C \
test2012_19.C \
test2012_20.C \
test2012_21.C \
test2012_22.C \
test2012_23.C \
test2012_24.C \
test2012_25.C \
test2012_26.C \
test2012_27.C \
test2012_28.C \
test2012_29.C \
test2012_30.C \
test2012_31.C \
test2012_32.C \
test2012_33.C \
test2012_34.C \
test2014_03.C \
test2014_82.C \
test2014_85.C \
test2014_88.C \
test2017_10.C \
last.C

# Note: last.C just simplifies the Makefile.am it
# avoids common makefle errors in adding new files.

# This is the long test of ROSE (takes a while!)
TESTCODES_REQUIRED_TO_PASS = $(EXAMPLE_TESTCODES_REQUIRED_TO_PASS)

# Automake's testing mechanism (which defines the "make check" rule) requires passing tests.
TESTCODES = \
$(TESTCODES_REQUIRED_TO_PASS) 

# QMTest allows both passing and failing tests.
ALL_TESTCODES = \
$(TESTCODES_REQUIRED_TO_PASS) \
$(TESTCODE_CURRENTLY_FAILING)

SKIP_UNPARSE_C_ASM_STATEMENTS = -rose:skip_unparse_asm_commands

# Use options to turn on C++11 and process using just the frontend for now.
# CXX11_OPTIONS = -rose:Cxx11 -rose:skip_translation_from_edg_ast_to_rose_ast
CXX11_OPTIONS = -rose:Cxx11 

# DQ (5/8/2011): Adding -rose:skipfinalCompileStep so that we can test the new name qualification support that is not yet hooked up to the unparser.
# ROSE_FLAGS = $(CXX11_OPTIONS) --edg:no_warnings -w -rose:verbose 0 $(SKIP_UNPARSE_C_ASM_STATEMENTS)
ROSE_FLAGS = $(CXX11_OPTIONS) -rose:verbose 0 $(SKIP_UNPARSE_C_ASM_STATEMENTS)
# ROSE_FLAGS = --edg:no_warnings -w -rose:verbose 0 -rose:skipfinalCompileStep $(SKIP_UNPARSE_C_ASM_STATEMENTS)

TESTCODE_INCLUDES =

PASSING_TEST_Objects = ${TESTCODES:.C=.o}
TEST_Objects = ${ALL_TESTCODES:.C=.o}

# DQ (9/18/2011): Added testing for new option to use folded constants or the original express trees.
TEST_Objects_FoldedConstants = ${EXAMPLE_TESTCODES_REQUIRED_TO_PASS_FOLDED_CONSTANTS:.C=.foldedConstants-o}
TEST_Objects_UnfoldedConstants = ${ALL_TESTCODES:.C=.unfoldedConstants-o}

# VALGRIND_OPTIONS = -v --num-callers=12 --leak-check=yes --error-limit=no --show-reachable=yes
VALGRIND_OPTIONS = --tool=memcheck -v --num-callers=30 --leak-check=no --error-limit=no --show-reachable=yes --trace-children=yes --suppressions=$(top_srcdir)/scripts/rose-suppressions-for-valgrind
# VALGRIND = valgrind $(VALGRIND_OPTIONS)
# VALGRIND =

# DQ (11/5/2016): Adding support for address sanitizer (borrowing the VALGRIND variable to support 
# this, this implementation needs review).  It might be better to prepend the information to the 
# CC and CXX variables. I think that the purify support uses this approach.
if ROSE_USE_SANITIZER
VALGRIND = $(NON_RTH_ADDRESS_SANITIZER_OPTIONS)
else
VALGRIND =
endif

# A number of tests require the path to the A++ include directory 
# and a number of other tests require a path to the source directory.
# Add the dependence upon the source file to trigger recompilation each time the makefile is run!
# $(TEST_Objects): ../../testTranslator $(srcdir)/$(@:.o=.C)
$(TEST_Objects): ../../testTranslator
if !ROSE_USE_INSURE
	$(VALGRIND) ../../testTranslator $(ROSE_FLAGS) $(TESTCODE_INCLUDES) -I$(srcdir) -c $(srcdir)/$(@:.o=.C)
#	$(VALGRIND) ../../testParser $(ROSE_FLAGS) $(TESTCODE_INCLUDES) -I$(srcdir) -c $(srcdir)/$(@:.o=.C)
#	$(VALGRIND) ../../testFrontEnd $(ROSE_FLAGS) $(TESTCODE_INCLUDES) -I$(srcdir) -c $(srcdir)/$(@:.o=.C)
else
#	DQ (4/22/2011): For Insure++ we want to get the filename into the names used for the report files.
#	@if test ! -f "../../.libs/lt-testTranslator"; then echo "Can NOT find ../../.libs/lt-testTranslator"; ../../testTranslator --help > /dev/null; echo "Fixed"; fi
#	cp ../../.libs/lt-testTranslator testTranslator_$(@:.o=)
#	./testTranslator_$(@:.o=) $(ROSE_FLAGS) $(TESTCODE_INCLUDES) -I$(srcdir) -c $(srcdir)/$(@:.o=.C)
#	echo "Removing the just built copy of lt-testTranslator to save space..."
#	rm -f testTranslator_$(@:.o=)
	$(VALGRIND) ../../testTranslator $(ROSE_FLAGS) $(TESTCODE_INCLUDES) -I$(srcdir) -c $(srcdir)/$(@:.o=.C)
endif

# DQ (9/18/2011): This is testing the option to process the AST to use the constant folded values (contained in the AST).
$(TEST_Objects_FoldedConstants): ../../testTranslatorFoldedConstants
	$(VALGRIND) ../../testTranslatorFoldedConstants $(ROSE_FLAGS) $(TESTCODE_INCLUDES) -I$(srcdir) -c $(srcdir)/$(@:.foldedConstants-o=.C) && touch $@
#	$(VALGRIND) ../../testFrontEnd $(ROSE_FLAGS) $(TESTCODE_INCLUDES) -I$(srcdir) -c $(srcdir)/$(@:.o=.C)

# DQ (9/18/2011): This is the equivalent to the default using testTranslator (so not critical to run this).
$(TEST_Objects_UnfoldedConstants): ../../testTranslatorUnfoldedConstants
	$(VALGRIND) ../../testTranslatorUnfoldedConstants $(ROSE_FLAGS) $(TESTCODE_INCLUDES) -I$(srcdir) -c $(srcdir)/$(@:.unfoldedConstants-o=.C) && touch $@

# DQ (4/6/2010): Added test for parsing only (tested here for C++ code)
testParser:../../testParser
	$(VALGRIND) ../../testParser $(ROSE_FLAGS) $(TESTCODE_INCLUDES) -I$(srcdir) -c $(srcdir)/test2001_01.C

../../testTranslator:
	cd ../..; $(MAKE) testTranslator

../../testTranslatorFoldedConstants:
	cd ../..; $(MAKE) testTranslatorFoldedConstants

../../testTranslatorUnfoldedConstants:
	cd ../..; $(MAKE) testTranslatorUnfoldedConstants


CURRENT_DIRECTORY = `pwd`
QMTEST_Objects = ${ALL_TESTCODES:.C=.qmt}

$(QMTEST_Objects): ../../testTranslator
	qm.sh f rose.RoseTest $(CURRENT_DIRECTORY)/../../testTranslator NULL $(ROSE_FLAGS) $(TESTCODE_INCLUDES) -I$(srcdir) -c $(srcdir)/$(@:.qmt=.C)

# Include makefile rules specific to QMTest
include $(top_srcdir)/config/QMTest_makefile.inc

# Make sure that all the test codes end up in the distribution
EXTRA_DIST = $(EXAMPLE_TESTCODES_REQUIRED_TO_PASS) $(TESTCODE_CURRENTLY_FAILING)

print_testcodes:
	echo $(TESTCODES)

globalVariablesInLambdas_test: globalVariablesInLambdas
	./globalVariablesInLambdas -std=c++11 --edg:no_warnings -c $(srcdir)/globalVariablesInLambdas_test_01.C


check-local:
# DQ (2/19/2017): NEW VERSION OF LOGIC
# DQ (2/18/2017): More specific logic required for portability.
# When using EDG 4.9 these files don't compile on later versions of GNU, CLANG, and Intel compilers 
# but we still want them tests as we transition to EDG 4.12 (where they all work fine independent of 
# the compiler vendor and GNU compiler version).
if ROSE_USE_EDG_VERSION_4_9
	@echo "ROSE_USE_EDG_VERSION_4_9 == true"
if USING_GNU_COMPILER
	@echo "USING_GCC_COMPILER == true"
if ROSE_USING_GCC_VERSION_LATER_4_8
	@echo "ROSE_USING_GCC_VERSION_LATER_4_8 == true"
#	@echo "C++11 tests using EDG 4.9 and GNU version 4.9 backend compiler are disabled."
if ROSE_USING_GCC_VERSION_LATER_4_9
	@echo "C++11 tests using EDG 4.9: GNU 4.9 backend compiler NOT allowed with the EDG 4.9 frontend (reconfigure with EDG 4.12)."
else  # NOT ROSE_USING_GCC_VERSION_LATER_4_9
	@echo "C++11 tests using EDG 4.9 and GNU version 4.8 backend compiler are allowed."
	@$(MAKE) $(PASSING_TEST_Objects)
endif # ROSE_USING_GCC_VERSION_LATER_4_9
# Exclude these tests on GNU 4.9 and later compilers).
else  # NOT ROSE_USING_GCC_VERSION_LATER_4_8
# If this is not the CLANG or Intel compilers and an earlier version of GNU than GNU 4.9 compiler, so include these files.
	@echo "ROSE_USING_GCC_VERSION_LATER_4_8 == false"
endif # ROSE_USING_GCC_VERSION_LATER_4_8
else  # NOT USING_GNU_COMPILER
	@echo "USING_GCC_COMPILER == false"
if USING_CLANG_COMPILER
# Exclude this list of files in the case of CLANG compiler.
#	@echo "USING_CLANG_COMPILER == true"
	@echo "C++11 tests using EDG 4.9: Clang backend compiler are NOT allowed with the EDG 4.9 frontend."
else # NOT USING_CLANG_COMPILER
#	@echo "USING_CLANG_COMPILER == false"
if USING_INTEL_COMPILER
# Exclude this list of files in the case of Intel compiler.
#	@echo "USING_INTEL_COMPILER == true"
	@echo "C++11 tests using EDG 4.9 Intel backend compiler are NOT allowed."
#	@$(MAKE) $(PASSING_TEST_Objects)
else # NOT USING_INTEL_COMPILER
# This is an unknown compiler.
#	@echo "USING_INTEL_COMPILER == false"
endif # USING_INTEL_COMPILER
endif # USING_CLANG_COMPILER
endif # USING_GNU_COMPILER
else  # NOT ROSE_USE_EDG_VERSION_4_9
# Using EDG 4.12 or later (run all tests independent of the compiler).
#	@echo "ROSE_USE_EDG_VERSION_4_9 == false"
if USING_GNU_COMPILER
if ROSE_USING_GCC_VERSION_LATER_4_8
	@echo "C++11 tests require configuration with either EDG version 4.9 and GNU version 4.8 or backend compiler or EDG 4.12 and 4.8 or any later GNU compiler."
	@echo "C++11 tests using EDG 4.12 and any supported backend compiler are allowed."
	@$(MAKE) $(PASSING_TEST_Objects)
endif # ROSE_USING_GCC_VERSION_LATER_4_8
else
	@echo "ROSE_USE_EDG_VERSION_4_9 == false"
if USING_CLANG_COMPILER
# Exclude this list of files in the case of CLANG compiler.
	@echo "USING_CLANG_COMPILER == true"
	@echo "C++11 tests using EDG 4.9: Clang backend compiler using EDG 4.12 frontend."
# DQ (2/21/2017): Too many failing files due to builtin functions that are missing.
#	@$(MAKE) $(PASSING_TEST_Objects)
else # NOT USING_CLANG_COMPILER
	@echo "USING_CLANG_COMPILER == false"
if USING_INTEL_COMPILER
# Exclude this list of files in the case of Intel compiler.
	@echo "USING_INTEL_COMPILER == true"
	@echo "C++11 tests using EDG 4.12 Intel backend compiler are allowed."
	@$(MAKE) $(PASSING_TEST_Objects)
else # NOT USING_INTEL_COMPILER
# This is an unknown compiler.
	@echo "USING_INTEL_COMPILER == false"
endif # USING_INTEL_COMPILER
endif # USING_CLANG_COMPILER
endif # USING_GNU_COMPILER
endif # ROSE_USE_EDG_VERSION_4_9
	@echo "*********************************************************************************************************************"
	@echo "****** ROSE/tests/nonsmoke/functional/CompileTests/Cxx11_tests: make check rule complete (terminated normally) ******"
	@echo "*********************************************************************************************************************"


clean-local:
	rm -f a.out *.o rose_*.[cC] roseTestProgram.C *.dot
	rm -f *.foldedConstants-o
	rm -f *.unfoldedConstants-o
	rm -rf QMTest
	rm -f *.int.c
