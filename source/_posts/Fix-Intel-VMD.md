---
title: Fix Intel VMD or RST
date: 2022-06-14 18:26:17
tags:
- Windows
- Intel
---

# 修复 Intel VMD(Intel RST) 导致的问题

## 问题描述

最新一代Intel CPU的笔记本电脑默认开启Intel Volume Management Device (VMD)，导致以下问题：

- 安装Windows 10时找不到磁盘驱动器
- Windows启动时蓝屏（错误代码：Inaccessible_Boot_Device）

## 修复

### 获取驱动程序

个人推荐从笔记本电脑的品牌官方网站下载驱动，而不是从Intel下载。
以华硕笔记本为例：

![华硕笔记本的下载页面](asus.png)

### 安装驱动

#### 正在安装Windows

在安装过程中加载相对应的Intel VMD驱动程序即可。网络上已经有很多详细教程。

![Intel的教程](57787_image2.png)
(图片来自 [www.intel.com/content/www/us/en/support/articles/000057787/memory-and-storage/intel-optane-memory.html](https://www.intel.com/content/www/us/en/support/articles/000057787/memory-and-storage/intel-optane-memory.html))

#### 已安装Windows

使用Dism++（图形化界面，推荐使用），或者以**管理员权限**运行DISM命令，离线安装驱动：

```powershell
DISM.exe /Image:X:\Windows /Add-Driver /Driver:D:\Drivers /recurse
```

### 修改驱动加载设置

打开`regedit`

选择`HKEY_LOCAL_MACHINE`，菜单选择文件-加载配置单元。

![](regedit-load.png)

选择`X:\Windows\System32\config\SYSTEM`文件，项名称输入`win10`

定位到`HKEY_LOCAL_MACHINE\win10\ControlSet001\Services\iaStorVD`，
把`Start`值(类型为REG_DWORD)改成0，如果有`StartOverride`项，则删掉该项。

定位到`HKEY_LOCAL_MACHINE\win10\ControlSet001\Services\iaStorAVC`和
把`Start`值改成0，添加`StartOverride`项，设置如下。

![](iaStorAVC.png)

`HKEY_LOCAL_MACHINE\win10\ControlSet001\Services\stornvme`设置如下。

![](stornvme.png)

修改后，卸载配置单元。
