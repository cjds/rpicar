# -*- python -*-

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

def rpi_bazel_repository(name):
    commit = "8e81769f2f0ab5de3ae22977082d4814e9f27204"
    git_repository(
       name = name,
       remote = "https://github.com/cjds/rpi_bazel.git",
       commit = commit,
#       strip_prefix = "rpi_bazel-{}".format(commit),
    )
