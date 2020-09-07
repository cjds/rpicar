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


#################
#     SASS      #
#################
# sass setup
http_archive(
    name = "io_bazel_rules_sass",
    sha256 = "36e2442b2e9e986d8ac709bcc8fffb9d66363c1f3bba2459906c9f3eb744c069",
    strip_prefix = "rules_sass-1.24.3",
    # Make sure to check for the latest version when you install
    url = "https://github.com/bazelbuild/rules_sass/archive/1.24.3.zip",
)

# Fetch required transitive dependencies. This is an optional step because you
# can always fetch the required NodeJS transitive dependency on your own.
load("@io_bazel_rules_sass//:package.bzl", "rules_sass_dependencies")

rules_sass_dependencies()

# Setup repositories which are needed for the Sass rules.
load("@io_bazel_rules_sass//:defs.bzl", "sass_repositories")

sass_repositories()

