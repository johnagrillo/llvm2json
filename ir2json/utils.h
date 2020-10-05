#ifndef __UTILS_H__
#define __UTILS_H__

#include "llvm/IR/Instructions.h"
unsigned getAlignment(llvm::Instruction *ins);
#endif
