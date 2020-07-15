cc_library(
  name = "lib",
  srcs = glob(["src/*.cc"]),
  hdrs = glob(["include/*.h", "include/*.hpp"]),
  deps = ["@boost//:iostreams", "@org_llvm_libcxx//:libcxx"],
  visibility = ["//visibility:public"],
)

cc_binary(
  name="platform",
  srcs = glob(["src/main.cc"]),
  deps = [":lib"],
  visibility = ["//visibility:public"],
)
