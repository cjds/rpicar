cc_binary(
  name = "platform",
  srcs = glob(["src/*.cc"]),
  deps = [
      ":lib",
      "//holster:lib",
      "@org_llvm_libcxx//:libcxx",
  ]
)

cc_library(
  name = "lib",
  hdrs = glob(["include/*.h", "include/*.hpp"]),
  visibility = ["//visibility:public"]
)
