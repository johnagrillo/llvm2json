//===-- ir2json.cpp - convertr ir to yaml --------------------===//
//
//===----------------------------------------------------------------------===//
//
// This utility may be invoked in the following manner:
//  ir2json [options]      - Read LLVM bitcode from stdin, write asm to stdout
//  ir2json [options] x.bc - Read LLVM bitcode from the x.bc file, write yaml
//                            to the x.yaml file.
//  Options:
//      --help   - Output information about command line switches
//
//===----------------------------------------------------------------------===//

#include "llvm/IR/DiagnosticInfo.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/JSON.h"
#include "ir2json.h"

int main(int argc, char **argv) {

  llvm::LLVMContext context;
  llvm::SMDiagnostic Err;
  std::unique_ptr<llvm::Module> mod = llvm::parseIRFile(argv[1], Err, context);

  llvm::json::Object module = llvm::json::Object{};
  llvm::json::Array globals = llvm::json::Array{};
  llvm::json::Array functions = llvm::json::Array{};
  
  for (llvm::GlobalVariable &g : mod->getGlobalList()) {
    globals.emplace_back(getGlobal(&g));    
  }
  module.try_emplace("globals", std::move(globals));    

  for (llvm::Function &f : mod->getFunctionList()) {
    functions.emplace_back(getFunction(&f));
  }
  module.try_emplace("functions", std::move(functions));
  
  llvm::outs() << toString(std::move(module)) << "\n";
  return 0;
}

llvm::json::Value getGlobal(llvm::GlobalVariable * g)
{
  llvm::json::Object global = llvm::json::Object{};
  global.try_emplace("name", g->getName().str());
  global.try_emplace("type", toString(g->getType()));
  if (g->hasInitializer()) {
    global.try_emplace("init", toString(g->getInitializer()));
  }
  return std::move(global);
}
  

#include <type_traits>

llvm::json::Value getFunction(llvm::Function * f)
{
  llvm::json::Object function = llvm::json::Object{};
  std::string name = f->getName().str();
  function.try_emplace("name",    name);
  function.try_emplace("linkage",  linkageToString(f->getLinkage()));
  function.try_emplace("visibility", visibilityToString(f->getVisibility()));
  function.try_emplace("cconv", callingConvToString(f->getCallingConv()));
  function.try_emplace("returnType", toString(f->getReturnType()));
  function.try_emplace("dllstorage", storageToString(f->getDLLStorageClass()));

  llvm::json::Array args = llvm::json::Array{};
  for (auto arg_iter = f->arg_begin(); arg_iter != f->arg_end();  arg_iter++)
  {
    llvm::json::Object arg = llvm::json::Object{};
    arg.try_emplace("type",toString(arg_iter->getType()));
    arg.try_emplace("value",toStringOperand(arg_iter, false));
    args.emplace_back(std::move(arg));    
  }
  function.try_emplace("args", std::move(args));

  llvm::json::Array attrs = llvm::json::Array{};  
  for (llvm::AttributeSet attr : f->getAttributes()) {
    attrs.emplace_back(attr.getAsString());
  }
  function.try_emplace("attrs", std::move(attrs));
  
  llvm::json::Array blocks = llvm::json::Array{};  
  for (llvm::BasicBlock &bb : f->getBasicBlockList()) {
    blocks.emplace_back(getBasicBlock(&bb));
  }
  function.try_emplace("blocks", std::move(blocks));
  return std::move(function);
}

llvm::json::Value getBasicBlock(llvm::BasicBlock * bb)
{
  llvm::json::Object block = llvm::json::Object{};
  std::string name = toStringOperand(bb, false);
  block.try_emplace("name", name);    
  
  llvm::json::Array instructions = llvm::json::Array{};        
  for (auto &ins : bb->getInstList()) {
    
    llvm::json::Object instruction = llvm::json::Object{};    
    auto align = getAlignment(&ins);
    if (align > 0) {
      instruction.try_emplace("align", 0);
    }

    // get bundles
    
    if (llvm::CallInst *ci = llvm::dyn_cast<llvm::CallInst>(&ins)) {
      if (ci->hasOperandBundles()) {
	for (unsigned i = ci->getBundleOperandsStartIndex(); i < ci->getBundleOperandsEndIndex(); i++) {
	  auto &b = ci->getBundleOpInfoForOperand(i);
	  auto tag = b.Tag;
	}
      }
    }
      
    instruction.try_emplace("opcode", ins.getOpcodeName());

    //if ((opcode != "store") && (opcode != "ret") && (opcode != "br")) {
    //  instruction.try_emplace("reg", toStringOperand(&ins));
    //}
    llvm::json::Array args = llvm::json::Array{};      
    for (auto arg_iter = ins.op_begin(); arg_iter != ins.op_end();  arg_iter++) {
      args.emplace_back(toString(arg_iter->get()->getType()));
      args.emplace_back(toStringOperand(arg_iter->get()));
    }
    instruction.try_emplace("args",std::move(args));          
    instructions.emplace_back(std::move(instruction));      
  }
  block.try_emplace("instructions",std::move(instructions));
  return std::move(block);
}

