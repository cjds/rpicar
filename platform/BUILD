cc_binary(
  name = "platform",
  srcs = glob(["src/*.cc"]),
  deps = [":platform_lib", "//holster:lib"]
)

cc_library(
  name = "platform_lib",
  hdrs = glob(["include/*.h", "include/*.hpp"])
)
