bb() {
    bazel build --config=pi --spawn_strategy=local --compilation_mode=dbg //...
}

bt() {
    bazel test --config=pi --spawn_strategy=local --compilation_mode=dbg //...
}

bbx86() {
    bazel build //... --config x86
}

btx86() {
    bazel test //... --config x86
}

bcp() {
    ssh cjds@pi 'rm -rf /tmp/bazel-bin'
    scp -r bazel-bin cjds@pi:/tmp
}

s() {
    ssh cjds@pi
}
[[ -r "/usr/local/etc/profile.d/bash_completion.sh" ]] && . "/usr/local/etc/profile.d/bash_completion.sh"
