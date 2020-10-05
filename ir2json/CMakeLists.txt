set(LLVM_LINK_COMPONENTS
  BitReader
  IRReader
  Core
  Support
  )

add_llvm_tool(ir2json
  ir2json.cpp
  utils.cpp
  tostring.cpp
  DEPENDS
  )


