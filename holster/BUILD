config_setting(
    name = "pi",
    values = {"cpu": "armeabihf"},
)

cc_library(
  name = "lib",
  srcs = glob([]),
  hdrs = glob(["include/*.h", "include/*.hpp"]),
  deps = select({
		  ":pi": ["@boost//:iostreams", "@org_llvm_libcxx//:libcxx"],
  		  "//conditions:default":["@boost//:iostreams" ]}),
  copts = ["-lrt"],
  visibility = ["//visibility:public"],
)

cc_binary(
  name="platform",
  srcs = glob(["src/main.cc"]),
  deps = [":lib"],
  linkopts = ["-lrt"],
  visibility = ["//visibility:public"],
)

cc_binary(
  name="client",
  srcs = glob(["src/client.cc"]),
  deps = [":lib"],
  linkopts = ["-lrt"],
  visibility = ["//visibility:public"],
)

cc_binary(
  name="server",
  srcs = glob(["src/server.cc"]),
  deps = [":lib"],
  linkopts = ["-lrt"],
  visibility = ["//visibility:public"],
)
