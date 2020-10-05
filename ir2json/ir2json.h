#ifndef __IR2JSON_H__
#define __IR2JSON_H__

#include "tostring.h"
#include "utils.h"

llvm::json::Value getBasicBlock(llvm::BasicBlock *);
llvm::json::Value getFunction(llvm::Function *);
llvm::json::Value getGlobal(llvm::GlobalVariable *);

#endif
