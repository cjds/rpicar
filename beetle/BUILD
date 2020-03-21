cc_binary(
  name = "move_with_input",
  srcs = glob(["src/move_with_input.cc"]),
  deps = [":beetle_lib", "//holster:lib", "//platform:lib"],
  linkopts = ["-lpthread"],
)

cc_library(
  name = "beetle_lib",
  hdrs = glob(["include/*.h", "include/*.hpp"]),
)
