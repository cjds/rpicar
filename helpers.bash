bb() {
    CC=clang++-10 CXX=clang++-10 bazel build $@
}

bt() {
    CC=clang++-10 CXX=clang++-10 bazel test $@
}

[[ -r "/usr/local/etc/profile.d/bash_completion.sh" ]] && . "/usr/local/etc/profile.d/bash_completion.sh"
