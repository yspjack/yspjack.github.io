---
title: Enable Nvidia driver on ubuntu 17.10
date: 2018-01-25 09:37:23
tags: [nvidia driver,ubuntu]
---

{% note warning %}
# Update

Since Ubuntu 18.04 LTS is released, this article may be out of date.
{% endnote %}

## 原文

Ubuntu 17.10更新使用了Wayland作为默认显示服务器，并用gdm3代替了lightdm。但这些更新可能导致Intel+Nvidia显卡的电脑（例如笔者的电脑）不能使用nvidia驱动进入桌面。本文简要介绍了如何重新启用nvidia驱动进入桌面。

<!--more-->

### 写在前面

首先进入BIOS设置，关闭安全启动(Secure Boot)
打开终端模拟器的快捷键一般是`Ctrl+Alt+T`

### 卸载之前安装的nvidia驱动

```bash
sudo apt purge nvidia-*
```

### 安装驱动nvidia-384

```bash
sudo apt update
sudo apt install nvidia-384
```

### 选择使用nvidia显卡

```bash
sudo prime-select nvidia
```

### 重启桌面环境

首先注销(logout)当前用户，然后进入tty(例如tty3 `Ctrl+Alt+F3`)，登录（注意小键盘此时没有num lock）。

```bash
sudo service gdm3 restart
```

接着电脑可能会卡死1分钟左右，然后出现登录界面。
登录后，打开终端模拟器，验证nvidia驱动是否正常工作。

```bash
nvidia-smi
```

如果正常，结果应该是类似这样的：

```
Thu Jan 25 10:00:31 2018
+-----------------------------------------------------------------------------+
| NVIDIA-SMI 384.111                Driver Version: 384.111                   |
|-------------------------------+----------------------+----------------------+
| GPU  Name        Persistence-M| Bus-Id        Disp.A | Volatile Uncorr. ECC |
| Fan  Temp  Perf  Pwr:Usage/Cap|         Memory-Usage | GPU-Util  Compute M. |
|===============================+======================+======================|
|   0  GeForce GTX 1050    Off  | 00000000:01:00.0 Off |                  N/A |
| N/A   46C    P8    N/A /  N/A |    437MiB /  1999MiB |      6%      Default |
+-------------------------------+----------------------+----------------------+
                                                                               
+-----------------------------------------------------------------------------+
| Processes:                                                       GPU Memory |
|  GPU       PID   Type   Process name                             Usage      |
|=============================================================================|
|    0      1427      G   /usr/lib/xorg/Xorg                            29MiB |
|    0      3830      G   /usr/bin/gnome-shell                           8MiB |
|    0      6663      G   /usr/lib/xorg/Xorg                           148MiB |
|    0      6857      G   /usr/bin/gnome-shell                         134MiB |
|    0      7207      G   fcitx-qimpanel                                48MiB |
|    0     14693      G   ...-token=CF289DEABC3E3E58C43168E984D2BFFE    64MiB |
+-----------------------------------------------------------------------------+
```
