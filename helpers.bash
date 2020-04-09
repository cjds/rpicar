bb() {
    bazel build --config=pi --spawn_strategy=local //...
}

bt() {
    bazel test --config=pi --spawn_strategy=local //...
}

bbx86() {
    bazel build //... --config x86
}

btx86() {
    bazel test //... --config x86
}

[[ -r "/usr/local/etc/profile.d/bash_completion.sh" ]] && . "/usr/local/etc/profile.d/bash_completion.sh"
