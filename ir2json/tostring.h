
#include <string.h>
#include "llvm/Support/JSON.h"
#include "llvm/IR/Function.h"

#ifndef __TOSTRING_H__
#define __TOSTRING_H__

#include <string>

template <typename T> inline std::string toString(T *t)
{
  std::string str;
  llvm::raw_string_ostream rso(str);
  t->print(rso);
  return rso.str();
}

template <> std::string inline toString<llvm::Type>(llvm::Type *t)
{
  std::string str;
  llvm::raw_string_ostream rso(str);
  t->print(rso);
  return rso.str();
}


template <typename T> inline
std::string toStringOperand(T *t, bool printWithout = false)
{
  std::string str;
  llvm::raw_string_ostream rso(str);
  t->printAsOperand(rso, printWithout);
  return rso.str();
}
std::string toString(const llvm::json::Value v);


std::string visibilityToString(llvm::GlobalValue::VisibilityTypes Vis);
std::string linkageToString(llvm::GlobalValue::LinkageTypes LT);
std::string callingConvToString(llvm::CallingConv::ID CC);
std::string storageToString(llvm::GlobalValue::DLLStorageClassTypes SCT);


#endif
