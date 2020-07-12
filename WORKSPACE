workspace(name = 'rpicar')

BAZEL_VERSION = "3.0.0"
BAZEL_VERSION_SHA = "3efb903ef885339a271445a9940642df704f97297fbe268f131d4fe36b02ea80"

load("//build-tools/workspace:default.bzl", "add_default_repositories")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

add_default_repositories()

load("@rpi_bazel//tools/workspace:default.bzl",
     rpi_bazel_add = "add_default_repositories")
rpi_bazel_add()

