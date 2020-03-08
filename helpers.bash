bb() {
    CC=clang CXX=clang++ bazel build $1
}

bt() {
    CC=clang CXX=clang++ bazel test $1
}

