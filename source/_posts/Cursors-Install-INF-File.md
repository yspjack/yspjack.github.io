---
title: 自定义鼠标指针安装文件
date: 2024-01-31 01:49:58
tags:
---

# 自定义鼠标指针安装文件

我们从网上下载自定义鼠标指针后，通常会按照教程，右键安装 INF 文件。本文分析 INF 文件的内容和安装鼠标指针的原理。

<!-- more -->

## INF 文件解析

安装 INF 文件，实际上执行了以下操作：

- 复制鼠标指针文件到指定目录
- 写入注册表 `HKEY_CURRENT_USER\Control Panel\Cursors\Schemes`
- 写入注册表 `HKEY_CURRENT_USER\Control Panel\Cursors`
- 执行一次性命令，打开控制面板--鼠标

`Strings` 指定了每个 `%strkey%` 字符串键对应的值，例如

```ini
[Strings]
strkey1 = "some string"
```

`DefaultInstall` 部分指定了安装 INF 所执行的指令：复制文件 `CopyFiles` 、写入注册表 `AddReg`

```ini
[DefaultInstall]
CopyFiles = Scheme.Cur
AddReg    = Scheme.Reg,Wreg
```

### 复制鼠标指针文件

`Scheme.Cur` 对应后面的 `Scheme.Cur` 部分，指定需要复制的文件。

`DestinationDirs` 部分指定了目标文件夹。这里 `10,"%CUR_DIR%"` 说明将文件复制到 `Windows` 目录下的文件夹，即 `%SystemRoot%\"%CUR_DIR%"`。`%SystemRoot%` 通常是 `C:\windows`。`"%CUR_DIR%"` 代表一个字符串，假设是`Cursors\Example` 。展开后，目标文件夹就是 `C:\windows\Cursors\Example`。

### 添加鼠标指针方案

鼠标指针方案存储在 `HKEY_CURRENT_USER\Control Panel\Cursors\Schemes`，内容是用逗号分隔的字符串。例如，Windows 默认的方案为

```
%SystemRoot%\cursors\aero_arrow.cur,%SystemRoot%\cursors\aero_helpsel.cur,%SystemRoot%\cursors\aero_working.ani,%SystemRoot%\cursors\aero_busy.ani,,,%SystemRoot%\cursors\aero_pen.cur,%SystemRoot%\cursors\aero_unavail.cur,%SystemRoot%\cursors\aero_ns.cur,%SystemRoot%\cursors\aero_ew.cur,%SystemRoot%\cursors\aero_nwse.cur,%SystemRoot%\cursors\aero_nesw.cur,%SystemRoot%\cursors\aero_move.cur,%SystemRoot%\cursors\aero_up.cur,%SystemRoot%\cursors\aero_link.cur,%SystemRoot%\cursors\aero_pin.cur,%SystemRoot%\cursors\aero_person.cur
```

注意，由于 Windows 版本不同，`Schemes` 的内容也要修改，否则会出现应用方案时报错、鼠标指针对应顺序错乱等问题。

### 修改鼠标指针

`HKEY_CURRENT_USER\Control Panel\Cursors` 保存每种光标对应的图片路径。`(默认)` 条目保存当前的鼠标指针方案。


| 注册表项    | 含义               |
| ----------- | ------------------ |
| AppStarting | 后台运行           |
| Arrow       | 正常选择           |
| Crosshair   | 精确选择           |
| Hand        | 链接选择           |
| Help        | 帮助选择           |
| IBeam       | 文本选择           |
| No          | 不可用             |
| NWPen       | 手写               |
| SizeAll     | 移动               |
| SizeNESW    | 沿对角线调整大小 1 |
| SizeNS      | 垂直调整大小       |
| SizeNWSE    | 沿对角线调整大小 2 |
| SizeWE      | 水平调整大小       |
| UpArrow     | 候选               |
| Wait        | 忙                 |
| Pin         | 位置选择           |
| Person      | 个人选择           |

### 执行一次性命令

将命令添加到 RunOnce 注册表项 `HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Runonce\Setup\` ，会使系统运行一次命令，然后删除刚刚添加的注册表项。这里的命令是 `rundll32.exe shell32.dll,Control_RunDLL main.cpl @0` ，就是打开控制面板--鼠标属性。

## 注意事项

如果文件包含了非ASCII字符，安装错误信息有乱码，则文件编码需要改成当前代码页（编码 ANSI）。为了避免乱码，建议 INF 文件中只出现基本 ASCII 字符。

## INF 文件示例

来源：B 站视频 [BV1Rt4y1K7Z8](https://www.bilibili.com/video/BV1Rt4y1K7Z8/)

> \(C\) 2015-2023 SAM TOKI STUDIO
> https://github.com/SamToki/IconDesign---Sam-Toki-Mouse-Cursors
> 遵循 CC BY-NC-SA 3.0 协议

```ini
[Version]
signature = "$CHICAGO$"

[DefaultInstall]
CopyFiles = Scheme.Cur
AddReg    = Scheme.Reg,Wreg

[DestinationDirs]
Scheme.Cur = 10,"%CUR_DIR%"

[Scheme.Reg]
HKCU,"Control Panel\Cursors\Schemes","%SCHEME_NAME%",,"%10%\%CUR_DIR%\%CurArrow%,%10%\%CUR_DIR%\%CurHelp%,%10%\%CUR_DIR%\%CurAppStarting%,%10%\%CUR_DIR%\%CurWait%,%10%\%CUR_DIR%\%CurCrosshair%,%10%\%CUR_DIR%\%CurIBeam%,%10%\%CUR_DIR%\%CurNWPen%,%10%\%CUR_DIR%\%CurNo%,%10%\%CUR_DIR%\%CurSizeNS%,%10%\%CUR_DIR%\%CurSizeWE%,%10%\%CUR_DIR%\%CurSizeNWSE%,%10%\%CUR_DIR%\%CurSizeNESW%,%10%\%CUR_DIR%\%CurSizeAll%,%10%\%CUR_DIR%\%CurUpArrow%,%10%\%CUR_DIR%\%CurHand%"

[Wreg]
HKCU,"Control Panel\Cursors",,0x00020000,"%SCHEME_NAME%"
HKCU,"Control Panel\Cursors",AppStarting,0x00020000,"%10%\%CUR_DIR%\%CurAppStarting%"
HKCU,"Control Panel\Cursors",Arrow,0x00020000,"%10%\%CUR_DIR%\%CurArrow%"
HKCU,"Control Panel\Cursors",Crosshair,0x00020000,"%10%\%CUR_DIR%\%CurCrosshair%"
HKCU,"Control Panel\Cursors",Hand,0x00020000,"%10%\%CUR_DIR%\%CurHand%"
HKCU,"Control Panel\Cursors",Help,0x00020000,"%10%\%CUR_DIR%\%CurHelp%"
HKCU,"Control Panel\Cursors",IBeam,0x00020000,"%10%\%CUR_DIR%\%CurIBeam%"
HKCU,"Control Panel\Cursors",No,0x00020000,"%10%\%CUR_DIR%\%CurNo%"
HKCU,"Control Panel\Cursors",NWPen,0x00020000,"%10%\%CUR_DIR%\%CurNWPen%"
HKCU,"Control Panel\Cursors",SizeAll,0x00020000,"%10%\%CUR_DIR%\%CurSizeAll%"
HKCU,"Control Panel\Cursors",SizeNESW,0x00020000,"%10%\%CUR_DIR%\%CurSizeNESW%"
HKCU,"Control Panel\Cursors",SizeNS,0x00020000,"%10%\%CUR_DIR%\%CurSizeNS%"
HKCU,"Control Panel\Cursors",SizeNWSE,0x00020000,"%10%\%CUR_DIR%\%CurSizeNWSE%"
HKCU,"Control Panel\Cursors",SizeWE,0x00020000,"%10%\%CUR_DIR%\%CurSizeWE%"
HKCU,"Control Panel\Cursors",UpArrow,0x00020000,"%10%\%CUR_DIR%\%CurUpArrow%"
HKCU,"Control Panel\Cursors",Wait,0x00020000,"%10%\%CUR_DIR%\%CurWait%"
HKLM,"SOFTWARE\Microsoft\Windows\CurrentVersion\Runonce\Setup\","",,"rundll32.exe shell32.dll,Control_RunDLL main.cpl @0"

[Scheme.Cur]
"STMC_GenshinNahida_01_Normal.cur"
"STMC_Genshin_02_Help.cur"
"STMC_GenshinNahida_03_Working.ani"
"STMC_GenshinNahida_04_Busy.ani"
"STMC_GenshinNahida_05_Cross.cur"
"STMC_GenshinNahida_06_Beam.cur"
"STMC_Standard_01_Normal(red).cur"
"STMC_Common_08_Unavailable.cur"
"STMC_GenshinNahida_09_NS.cur"
"STMC_GenshinNahida_10_EW.cur"
"STMC_GenshinNahida_11_NWSE.cur"
"STMC_GenshinNahida_12_NESW.cur"
"STMC_Common_13_Hand.cur"
"STMC_GenshinNahida_14_Mirror.cur"
"STMC_Common_15_Finger.cur"

[Strings]
CUR_DIR         = "Cursors\STMC"
SCHEME_NAME     = "STMCS-401-GenshinNahida"

CurArrow        = "STMC_GenshinNahida_01_Normal.cur"
CurHelp         = "STMC_Genshin_02_Help.cur"
CurAppStarting  = "STMC_GenshinNahida_03_Working.ani"
CurWait         = "STMC_GenshinNahida_04_Busy.ani"
CurCrosshair    = "STMC_GenshinNahida_05_Cross.cur"
CurIBeam        = "STMC_GenshinNahida_06_Beam.cur"
CurNWPen        = "STMC_Standard_01_Normal(red).cur"
CurNo           = "STMC_Common_08_Unavailable.cur"
CurSizeNS       = "STMC_GenshinNahida_09_NS.cur"
CurSizeWE       = "STMC_GenshinNahida_10_EW.cur"
CurSizeNWSE     = "STMC_GenshinNahida_11_NWSE.cur"
CurSizeNESW     = "STMC_GenshinNahida_12_NESW.cur"
CurSizeAll      = "STMC_Common_13_Hand.cur"
CurUpArrow      = "STMC_GenshinNahida_14_Mirror.cur"
Curhand         = "STMC_Common_15_Finger.cur"
```

## 参考

- [Overview of INF Files - Windows drivers | Microsoft Learn](https://learn.microsoft.com/en-us/windows-hardware/drivers/install/overview-of-inf-files)
- [Run and RunOnce Registry Keys - Win32 apps | Microsoft Learn](https://learn.microsoft.com/en-us/windows/win32/setupapi/run-and-runonce-registry-keys)
