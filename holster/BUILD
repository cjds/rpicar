config_setting(
    name = "pi",
    values = {"cpu": "armeabihf"},
)

cc_library(
  name = "lib",
  srcs = glob(["src/*.cc"]),
  hdrs = glob(["include/*.h", "include/*.hpp"]),
  deps = select({
		  ":pi": ["@boost//:iostreams", "@org_llvm_libcxx//:libcxx"],
  		  "//conditions:default":["@boost//:iostreams" ]}),
  visibility = ["//visibility:public"],
)

cc_binary(
  name="platform",
  srcs = glob(["src/main.cc"]),
  deps = [":lib"],
  visibility = ["//visibility:public"],
)
