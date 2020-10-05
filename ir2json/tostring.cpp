#include "tostring.h"

std::string toString(const llvm::json::Value v)
{
  std::string Context;
  llvm::raw_string_ostream OS(Context);
  OS << v;
  return OS.str();
}


std::string visibilityToString(llvm::GlobalValue::VisibilityTypes Vis)
{
  switch (Vis) {
  case llvm::GlobalValue::DefaultVisibility:
    return "";
    break;
  case llvm::GlobalValue::HiddenVisibility:
    return "hidden ";
    break;
  case llvm::GlobalValue::ProtectedVisibility:
    return "protected ";
    break;
  }
  llvm_unreachable("invalid visibility");
}

// borrowed from ASMWriter
std::string linkageToString(llvm::GlobalValue::LinkageTypes LT) {
  switch (LT) {
  case llvm::GlobalValue::ExternalLinkage:
    return "external";
  case llvm::GlobalValue::PrivateLinkage:
    return "private";
  case llvm::GlobalValue::InternalLinkage:
    return "internal";
  case llvm::GlobalValue::LinkOnceAnyLinkage:
    return "linkonce";
  case llvm::GlobalValue::LinkOnceODRLinkage:
    return "linkonce_odr";
  case llvm::GlobalValue::WeakAnyLinkage:
    return "weak";
  case llvm::GlobalValue::WeakODRLinkage:
    return "weak_odr";
  case llvm::GlobalValue::CommonLinkage:
    return "common";
  case llvm::GlobalValue::AppendingLinkage:
    return "appending";
  case llvm::GlobalValue::ExternalWeakLinkage:
    return "extern_weak";
  case llvm::GlobalValue::AvailableExternallyLinkage:
    return "available_externally";
  }
  llvm_unreachable("invalid linkage");
}


std::string callingConvToString(llvm::CallingConv::ID CC)
{
  switch (CC) {
  default:                               return "cc" ; break;
  case llvm::CallingConv::Fast:          return "fastcc"; break;
  case llvm::CallingConv::Cold:          return "coldcc"; break;
  case llvm::CallingConv::WebKit_JS:     return "webkit_jscc"; break;
  case llvm::CallingConv::AnyReg:        return "anyregcc"; break;
  case llvm::CallingConv::PreserveMost:  return "preserve_mostcc"; break;
  case llvm::CallingConv::PreserveAll:   return "preserve_allcc"; break;
  case llvm::CallingConv::CXX_FAST_TLS:  return "cxx_fast_tlscc"; break;
  case llvm::CallingConv::GHC:           return "ghccc"; break;
  case llvm::CallingConv::Tail:          return "tailcc"; break;
  case llvm::CallingConv::CFGuard_Check: return "cfguard_checkcc"; break;
  case llvm::CallingConv::X86_StdCall:   return "x86_stdcallcc"; break;
  case llvm::CallingConv::X86_FastCall:  return "x86_fastcallcc"; break;
  case llvm::CallingConv::X86_ThisCall:  return "x86_thiscallcc"; break;
  case llvm::CallingConv::X86_RegCall:   return "x86_regcallcc"; break;
  case llvm::CallingConv::X86_VectorCall:return "x86_vectorcallcc"; break;
  case llvm::CallingConv::Intel_OCL_BI:  return "intel_ocl_bicc"; break;
  case llvm::CallingConv::ARM_APCS:      return "arm_apcscc"; break;
  case llvm::CallingConv::ARM_AAPCS:     return "arm_aapcscc"; break;
  case llvm::CallingConv::ARM_AAPCS_VFP: return "arm_aapcs_vfpcc"; break;
  case llvm::CallingConv::AArch64_VectorCall: return "aarch64_vector_pcs"; break;
  case llvm::CallingConv::AArch64_SVE_VectorCall:
    return "aarch64_sve_vector_pcs";
    break;
  case llvm::CallingConv::MSP430_INTR:   return "msp430_intrcc"; break;
  case llvm::CallingConv::AVR_INTR:      return "avr_intrcc "; break;
  case llvm::CallingConv::AVR_SIGNAL:    return "avr_signalcc "; break;
  case llvm::CallingConv::PTX_Kernel:    return "ptx_kernel"; break;
  case llvm::CallingConv::PTX_Device:    return "ptx_device"; break;
  case llvm::CallingConv::X86_64_SysV:   return "x86_64_sysvcc"; break;
  case llvm::CallingConv::Win64:         return "win64cc"; break;
  case llvm::CallingConv::SPIR_FUNC:     return "spir_func"; break;
  case llvm::CallingConv::SPIR_KERNEL:   return "spir_kernel"; break;
  case llvm::CallingConv::Swift:         return "swiftcc"; break;
  case llvm::CallingConv::X86_INTR:      return "x86_intrcc"; break;
  case llvm::CallingConv::HHVM:          return "hhvmcc"; break;
  case llvm::CallingConv::HHVM_C:        return "hhvm_ccc"; break;
  case llvm::CallingConv::AMDGPU_VS:     return "amdgpu_vs"; break;
  case llvm::CallingConv::AMDGPU_LS:     return "amdgpu_ls"; break;
  case llvm::CallingConv::AMDGPU_HS:     return "amdgpu_hs"; break;
  case llvm::CallingConv::AMDGPU_ES:     return "amdgpu_es"; break;
  case llvm::CallingConv::AMDGPU_GS:     return "amdgpu_gs"; break;
  case llvm::CallingConv::AMDGPU_PS:     return "amdgpu_ps"; break;
  case llvm::CallingConv::AMDGPU_CS:     return "amdgpu_cs"; break;
  case llvm::CallingConv::AMDGPU_KERNEL: return "amdgpu_kernel"; break;
  }
}

std::string storageToString(llvm::GlobalValue::DLLStorageClassTypes SCT)
{
  switch (SCT) {
  default : return "";break;
  case llvm::GlobalValue::DefaultStorageClass: return ""; break;
  case llvm::GlobalValue::DLLImportStorageClass: return "dllimport "; break;
  case llvm::GlobalValue::DLLExportStorageClass: return "dllexport "; break;
  }
}




  

