bb() {
    CC=clang CXX=clang++ bazel build $1
}

bt() {
    CC=clang CXX=clang++ bazel test $1
}

[[ -r "/usr/local/etc/profile.d/bash_completion.sh" ]] && . "/usr/local/etc/profile.d/bash_completion.sh"
