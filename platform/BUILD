config_setting(
    name = "pi",
    values = {"cpu": "armeabihf"},
)

cc_binary(
  name = "platform",
  srcs = glob(["src/*.cc"]),
  deps = [
      ":lib",
      "//holster:lib",
  ]
)

cc_library(
  name = "lib",
  hdrs = glob(["include/*.h", "include/*.hpp"]),
  visibility = ["//visibility:public"],
  linkopts = ["-lgpiod"],
  copts = ["-Ilib/gpiod"],
  deps = select({
		  ":pi": ["@org_llvm_libcxx//:libcxx"],
  		  "//conditions:default":[]}),
)
