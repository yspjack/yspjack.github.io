---
title: Compiling Android kernel
date: 2023-09-23 20:50:30
tags:
---

## FAQ

### undefined reference to `stpcpy'

- https://github.com/nathanchance/android-kernel-clang/issues/16
- https://github.com/ClangBuiltLinux/linux/issues/1126
- https://github.com/ClangBuiltLinux/linux/issues/416

clang 原因。可以自己实现相应函数：

`stpcpy`

https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/commit/?id=1e1b6d63d6340764e00356873e5794225a2a03ea

`bcmp`

https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/commit/?id=5f074f3e192f10c9fade898b9b3b8812e3d83342

或者将 `-fno-builtin` 添加 `KBUILD_CFLAGS`

### Clang 无法编译汇编代码

将 `-no-integrated-as` 添加 `KBUILD_CFLAGS`

