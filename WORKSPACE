workspace(name = 'rpicar')

BAZEL_VERSION = "3.0.0"
BAZEL_VERSION_SHA = "3efb903ef885339a271445a9940642df704f97297fbe268f131d4fe36b02ea80"

load("//build-tools/workspace:default.bzl", "add_default_repositories")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

add_default_repositories()


################
#     RPI      #
################
load("@rpi_bazel//tools/workspace:default.bzl",
     rpi_bazel_add = "add_default_repositories")
rpi_bazel_add()

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

################
#     BOOST    #
################
git_repository(
    name = "com_github_nelhage_rules_boost",
    commit = "ccc90b00c2fae7267cc25b77199fb992acd5e799",
    remote = "https://github.com/nelhage/rules_boost",
)

load("@com_github_nelhage_rules_boost//:boost/boost.bzl", "boost_deps")
boost_deps()


################
#    NODEJS    #
################

http_archive(
    name = "build_bazel_rules_nodejs",
    urls = ["https://github.com/bazelbuild/rules_nodejs/releases/download/2.0.3/rules_nodejs-2.0.3.tar.gz"],
)

load("@build_bazel_rules_nodejs//:index.bzl", "node_repositories", "yarn_install", "npm_install")

node_repositories(package_json = ["//:package.json"])

npm_install(
    name = "npm",
    package_json = "//:package.json",
    package_lock_json = "//:package-lock.json",
)
