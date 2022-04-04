---
title: Multi(Dual)-booting
date: 2022-04-01 01:04:58
tags:
---

## Windows 修复ESP分区

```cmd
bcdboot C:\Windows
```

## Multi-boot Windows(EFI) via GRUB

https://wiki.archlinux.org/title/GRUB#Windows_installed_in_UEFI/GPT_mode

<!--more-->

```shell
if [ "${grub_platform}" == "efi" ]; then
	menuentry "Microsoft Windows Vista/7/8/8.1 UEFI/GPT" {
		insmod part_gpt
		insmod fat
		insmod chain
		search --no-floppy --fs-uuid --set=root $hints_string $fs_uuid
		chainloader /EFI/Microsoft/Boot/bootmgfw.efi
	}
fi
# grub-probe --target=fs_uuid /boot/efi/EFI/Microsoft/Boot/bootmgfw.efi
# grub-probe --target=hints_string /boot/efi/EFI/Microsoft/Boot/bootmgfw.efi
```

## os-prober bug: 找不到ESP分区(MBR)

```diff
--- /usr/lib/os-probes/mounted/05efi	2017-01-21 23:43:28.000000000 +0800
+++ /tmp/05efi	2021-10-06 22:11:02.332865995 +0800
@@ -39,9 +39,9 @@
 	debug "$partition partition type is $ID_PART_ENTRY_TYPE"
 
 	if [ -z "$ID_PART_ENTRY_TYPE" -o -z "$ID_PART_ENTRY_SCHEME" -o \
-		\( "$ID_PART_ENTRY_SCHEME" != gpt -a "$ID_PART_ENTRY_SCHEME" != msdos \) -o \
+		\( "$ID_PART_ENTRY_SCHEME" != gpt -a "$ID_PART_ENTRY_SCHEME" != dos \) -o \
 		\( "$ID_PART_ENTRY_SCHEME" = gpt -a "$ID_PART_ENTRY_TYPE" != c12a7328-f81f-11d2-ba4b-00a0c93ec93b \) -o \
-		\( "$ID_PART_ENTRY_SCHEME" = msdos -a "$ID_PART_ENTRY_TYPE" != 0xef \) ]; then
+		\( "$ID_PART_ENTRY_SCHEME" = dos -a "$ID_PART_ENTRY_TYPE" != 0xef \) ]; then
 		debug "$partition is not a ESP partition: exiting"
 		exit 1
 	fi

```

## Time standard(Timezone)

### Linux use localtime

```bash
timedatectl set-local-rtc 1
```

### UTC in Microsoft Windows(recommended)

```
Windows Registry Editor Version 5.00

[HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\TimeZoneInformation]
     "RealTimeIsUniversal"=dword:00000001
```

## Reference

https://wiki.archlinux.org/title/GRUB

https://docs.microsoft.com/zh-cn/windows-hardware/manufacture/desktop/bcdboot-command-line-options-techref-di
