#include "MatlabUnparser.h"

#include <boost/format.hpp>
#include <boost/filesystem.hpp>
#include <sstream>

std::string MatlabUnparserBottomUpTraversal::handleDoubleVal(SgNode *node, SynthesizedAttributesList childAttributes)
  {
    double value  = isSgDoubleVal(node)->get_value();

    std::ostringstream ss;

    ss << boost::format("%g") %  value;
    
    return ss.str();
  }

std::string MatlabUnparserBottomUpTraversal::handleExprListExp(SgNode *node, SynthesizedAttributesList childAttributes)
  {
    std::string listString;
    
    for(SynthesizedAttributesList::iterator i = childAttributes.begin(); i != childAttributes.end(); i++)
      {
	listString += *i;

	if( (i + 1) != childAttributes.end())
	  {
	    listString += ", ";
	  }
      }

    return listString;
  }

std::string MatlabUnparserBottomUpTraversal::handleMagicColonExp(SgNode *node, SynthesizedAttributesList childAttributes)
{
  return ":";
}

std::string MatlabUnparserBottomUpTraversal::handleMatrixExp(SgNode *node, SynthesizedAttributesList childAttributes)
  {
    std::string matrixString = "[";

    for(SynthesizedAttributesList::iterator i = childAttributes.begin(); i != childAttributes.end(); i++)
      {
	matrixString += *i;

	if( (i + 1) != childAttributes.end())
	  {
	    matrixString += "; ";
	  }
      }

    matrixString += "]";
    return matrixString;
  }

std::string MatlabUnparserBottomUpTraversal::handleRangeExp(SgNode *node, SynthesizedAttributesList childAttributes)
{
  SgRangeExp *rangeExp = isSgRangeExp(node);

  std::string rangeString;
  
  if(rangeExp->get_start())
    {
      rangeString += childAttributes[SgRangeExp_start];
    }

  if(rangeExp->get_stride())
    {
      rangeString += ":" + childAttributes[SgRangeExp_stride];
    }

  if(rangeExp->get_end())
    {
      rangeString += ":" + childAttributes[SgRangeExp_end];
    }

  return rangeString;
}

std::string MatlabUnparserBottomUpTraversal::handleVarRefExp(SgNode *node, SynthesizedAttributesList childAttributes)
{
  return isSgVarRefExp(node)->get_symbol()->get_name().getString();
}

std::string MatlabUnparserBottomUpTraversal::handleFunctionCallExp(SgNode *node, SynthesizedAttributesList childAttributes)
{
  std::string functionName = childAttributes[SgFunctionCallExp_function];
  std::string args = childAttributes[SgFunctionCallExp_args];

  return functionName + "(" + args + ")";
}

std::string MatlabUnparserBottomUpTraversal::handlePrefixOp(SgNode *node, SynthesizedAttributesList childAttributes, std::string operatorString)
{
  return operatorString + childAttributes[SgUnaryOp_operand_i];
}

std::string MatlabUnparserBottomUpTraversal::handleInitializedName(SgNode *node, SynthesizedAttributesList childAttributes)
{
  return isSgInitializedName(node)->get_name().getString();
}

std::string MatlabUnparserBottomUpTraversal::handleAssignOp(SgNode *node, SynthesizedAttributesList childAttributes)
{
  std::string lhs = childAttributes[SgAssignOp_lhs_operand_i];
  std::string rhs = childAttributes[SgAssignOp_rhs_operand_i];

  SgAssignOp *assignOp = isSgAssignOp(node);

  /*
   * Handle cases like [a, b] = [2 , 3]
   * Here a, b is an ExprListExp
  */
  if(isSgExprListExp(assignOp->get_lhs_operand()))
    {
     lhs = "[" + lhs + "]";
    }
  
  return lhs + "=" + rhs;
}

std::string MatlabUnparserBottomUpTraversal::handleBinaryOp(SgNode *node, SynthesizedAttributesList childAttributes, std::string operatorString)
{
  std::string lhs = childAttributes[SgBinaryOp_lhs_operand_i];
  std::string rhs = childAttributes[SgBinaryOp_rhs_operand_i];

  return lhs + operatorString + rhs;
}

std::string MatlabUnparserBottomUpTraversal::handleMatrixTransposeOp(SgNode *node, SynthesizedAttributesList childAttributes)
{
  SgMatrixTransposeOp *transposeOp = isSgMatrixTransposeOp(node);

  std::string transposeString = childAttributes[SgMatrixTransposeOp_operand_i];
  
  if(transposeOp->get_is_conjugate())
    {
      transposeString += "'"; //conjugate transpose
    }
  else
    {
      transposeString +=  ".'"; //normal transpose
    }

  return transposeString;
}

std::string MatlabUnparserBottomUpTraversal::handleExprStatement(SgNode *node, SynthesizedAttributesList childAttributes)
{
  std::string expressionString = childAttributes[SgExprStatement_expression];

  return expressionString + "\n";
}

std::string MatlabUnparserBottomUpTraversal::handleReturnStmt(SgNode *node, SynthesizedAttributesList childAttributes)
{
  SgFunctionDeclaration *enclosingFunctionDecl = SageInterface::getEnclosingFunctionDeclaration(node, false);

  std::string returnStmtString = "[" + childAttributes[SgReturnStmt_expression] + "]";

  ReturnStmtAttribute *returnStmtAttribute = new ReturnStmtAttribute();
  returnStmtAttribute->returnStmtString = returnStmtString;

  returnStmtAttribute->attach_to(enclosingFunctionDecl);
  
  return "";
}

std::string MatlabUnparserBottomUpTraversal:: handleBasicBlock(SgNode *node, SynthesizedAttributesList childAttributes)
{
  std::string blockString;

    for(SynthesizedAttributesList::iterator i = childAttributes.begin(); i != childAttributes.end(); i++)
      {
	blockString += *i;
      }

    return blockString;
}

std::string MatlabUnparserBottomUpTraversal::handleFunctionDefinition(SgNode *node, SynthesizedAttributesList childAttributes)
  {
    return childAttributes[SgFunctionDefinition_body];
  }

std::string MatlabUnparserBottomUpTraversal::handleFunctionParameterList(SgNode *node, SynthesizedAttributesList childAttributes)
{
  std::string parameterListString;
  
  for(SynthesizedAttributesList::iterator i = childAttributes.begin(); i != childAttributes.end(); i++)
  {
    parameterListString += *i;
      
    if((i + 1) != childAttributes.end())
    {
      parameterListString += ", ";
    }     
  }

  return parameterListString;
}

std::string MatlabUnparserBottomUpTraversal::handleFunctionDeclaration(SgNode *node, SynthesizedAttributesList childAttributes)
{
  std::string functionString = "function ";

  if(ReturnStmtAttribute *returnStmtAttribute = ReturnStmtAttribute::get_attribute(node))
  {
    std::string returnList = returnStmtAttribute->returnStmtString;

    functionString += returnList + " = ";
  }

  SgFunctionDeclaration *functionDeclaration = isSgFunctionDeclaration(node);
  functionString += functionDeclaration->get_name().getString();
  
  
  std::string parameterList = childAttributes[SgFunctionDeclaration_parameterList];

  functionString += "(" + parameterList + ")";

  std::string functionBody = childAttributes[SgFunctionDeclaration_definition];

  functionString += "\n" + functionBody + "end\n\n";

  return functionString;
}

std::string MatlabUnparserBottomUpTraversal::handleMatlabForStatement(SgNode *node, SynthesizedAttributesList childAttributes)
{
  std::string index = childAttributes[SgMatlabForStatement_index];
  std::string range = childAttributes[SgMatlabForStatement_range];
  std::string body = childAttributes[SgMatlabForStatement_body];

  std::string forString = "for " + index + " = " + range + "\n" + body + "end\n";

  return forString; 
}

std::string MatlabUnparserBottomUpTraversal::handleIfStmt(SgNode *node, SynthesizedAttributesList childAttributes)
  {
    SgIfStmt *ifStmt = isSgIfStmt(node);
    
    std::string conditional = childAttributes[SgIfStmt_conditional];
    std::string true_body = childAttributes[SgIfStmt_true_body];

    std::string ifString = "if " + conditional + true_body;
    
    if(ifStmt->get_false_body())
      {
	ifString += "else";

	std::string elseString = childAttributes[SgIfStmt_false_body];
	
	if(isSgBasicBlock(ifStmt->get_false_body()))
	  {
	    ifString += "\n" + elseString + "end\n";
	  }
	else
	  {
	    ifString += elseString;
	  }
	  

      }
    else
      {
	ifString += "end\n";
      }

    return ifString;
  }

std::string MatlabUnparserBottomUpTraversal::handleGlobal(SgNode *node, SynthesizedAttributesList childAttributes)
{
  std::string scriptString;
  
  for(SynthesizedAttributesList::iterator i = childAttributes.begin(); i != childAttributes.end(); i++)
  {
    scriptString += *i;
  }

  return scriptString;
}

std::string MatlabUnparserBottomUpTraversal::handleSourceFile(SgNode *node, SynthesizedAttributesList childAttributes)
{
  std::string scriptString = childAttributes[SgSourceFile_globalScope];

  SgSourceFile *sourceFile = isSgSourceFile(node);

  boost::filesystem::path sourceFilePath(sourceFile->getFileName());
  printf(("UNPARSER: source file: " + sourceFilePath.string()).c_str());
  std::string unparsedFileName = "rose_" + sourceFilePath.stem().string();

  printf(("UNPARSER: output file = " + unparsedFileName).c_str());
  
  std::ofstream unparsedFile(unparsedFileName.c_str());

  unparsedFile << scriptString;

  unparsedFile.flush();
  unparsedFile.close();

  return "";
}
