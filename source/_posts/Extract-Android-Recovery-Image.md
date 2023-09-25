---
title: 生成 Android recovery 镜像
date: 2023-08-26 01:49:30
tags:
- Android
---

某些版本的Android系统更新后，正常情况下会调用 `/system/bin/install-recovery.sh` 更新Recovery。
如果使用TWRP等第三方Recovery，`recovery-from-boot.p`会被重命名为`recovery-from-boot.bak`，导致该过程无法正常进行。
而官方ROM只有Boot镜像，没有直接提供Recovery镜像，需要手动生成。

根据 `/system/bin/install-recovery.sh` 的内容，我们可以用 `boot.img`，`recovery-resource.dat`，`recovery-from-boot.p` 生成Recovery镜像。

<!--more-->

## 提取文件

如果ROM包括 `system.transfer.list`, `system.new.dat`文件，在电脑端安装 Python 3，使用[sdat2img](https://github.com/xpirt/sdat2img) 提取 `system.img`

```sh
python sdat2img.py system.transfer.list system.new.dat system.img
```

如果只有 `payload.bin`，则使用 [payload-dumper-go](https://github.com/ssut/payload-dumper-go) 提取 `system.img`。

```sh
payload-dumper-go payload.bin
```

{% note info %}
新设备的 `payload.bin` 可能已经包含了 Recovery 镜像 `recovery.img`，无需进行后续操作。
{% endnote %}

接下来从 `system.img` 提取 `/bin/install-recovery.sh`，`/etc/recovery-resource.dat`，`/recovery-from-boot.p`。Windows 可使用 7-Zip 打开`system.img`文件进行提取。

最后将以下得到的4个文件，复制到 Android 设备的目录（例如`/data/local/tmp`）：

- install-recovery.sh
- recovery-resource.dat
- recovery-from-boot.p
- boot.img

## 调用 applypatch

提取出的`install-recovery.sh`内容为：

```sh
#!/system/bin/sh
if ! applypatch -c EMMC:/dev/block/bootdevice/by-name/recovery:32871724:07c2d811e95df920577ff4e3970f1c361c0c26df; then
  applypatch -b /system/etc/recovery-resource.dat EMMC:/dev/block/bootdevice/by-name/boot:22328616:6dbc3aa6037b6a27239ed9602902b823a9e055da EMMC:/dev/block/bootdevice/by-name/recovery 07c2d811e95df920577ff4e3970f1c361c0c26df 32871724 6dbc3aa6037b6a27239ed9602902b823a9e055da:/system/recovery-from-boot.p && log -t recovery "Installing new recovery image: succeeded" || log -t recovery "Installing new recovery image: failed"
else
  log -t recovery "Recovery image already installed"
fi
```

### applypatch 帮助信息

```
usage: applypatch [-b <bonus-file>] <src-file> <tgt-file> <tgt-sha1> <tgt-size> [<src-sha1>:<patch> ...]
   or  applypatch -c <file> [<sha1> ...]
   or  applypatch -s <bytes>
   or  applypatch -l

Filenames may be of the form
  EMMC:<partition>:<len_1>:<sha1_1>:<len_2>:<sha1_2>:...
to specify reading from or writing to an EMMC partition.

```

### 生成 `recovery.img`

根据上述内容，可以推测 `install-recovery.sh` 刷入 Recovery 的流程：

- 脚本先检查 `recovery` 分区中 Recovery 镜像的 SHA-1
- 如果检查通过，说明已经刷入正确的 Recovery 镜像
- 否则，使用 `/system/etc/recovery-resource.dat`, `/system/recovery-from-boot.p` 对 Boot 镜像进行修补，得到 Recovery 镜像刷入 `recovery` 分区。如果得到的 Recovery 镜像大小或 SHA-1 不一致，则刷入失败。

修改相关命令，使 `applypatch` 只对镜像文件进行操作，避免破坏当前 `recovery` 分区。

```sh
applypatch -b recovery-resource.dat EMMC:boot.img:22328616:6dbc3aa6037b6a27239ed9602902b823a9e055da EMMC:recovery.img 07c2d811e95df920577ff4e3970f1c361c0c26df 32871724 6dbc3aa6037b6a27239ed9602902b823a9e055da:recovery-from-boot.p
```

{% note info %}
注意：由于 `applypatch` 会将临时文件存储在 `/cache`，可能需要在已经获取 root 权限的 Android 设备执行命令。
{% endnote %}

如果成功生成`recovery.img`，输出：

```
patch EMMC:boot.img:22328616:6dbc3aa6037b6a27239ed9602902b823a9e055da: LoadPartitionContents called with bad filename "EMMC:recovery.img"
partition read matched size 22328616 SHA-1 6dbc3aa6037b6a27239ed9602902b823a9e055da
98988032 bytes free on /cache (22328616 needed)
now 07c2d811
  caches dropped
verification read succeeded (attempt 1)
```

### 检查`recovery.img`的校验和

```sh
applypatch -c EMMC:recovery.img:32871724:07c2d811e95df920577ff4e3970f1c361c0c26df
```

如果校验通过，输出：

```
partition read matched size 32871724 SHA-1 07c2d811e95df920577ff4e3970f1c361c0c26df
```
