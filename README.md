# Floe TinyEMU archive

[English](#english) | [简体中文](#简体中文)

## English

This repository preserves Fabrice Bellard's official **TinyEMU 2019-12-21** source and Floe's former RISC-V Linux integration. It is a source archive, not a new Floe App release or an ARM64 runtime.

The author distributes an archive at <https://bellard.org/tinyemu/>. We imported that official archive as the first commit and tagged it `upstream-2019-12-21`. This is not represented as a GitHub fork of an author-owned repository. The archive SHA-256 is `be8351f2121819b3172fcedce5cb1826fa12c87da1b7ed98f269d3e802a05555`. Original copyright and license notices are retained.

### Floe changes

- An embeddable C lifecycle: bounded execution slices, console input/output, stop, power-off observation and repeatable destruction without terminating the host.
- Recoverable allocation, image-size and guest-device errors; modern Linux firmware, CSR and FENCE compatibility.
- Multi-hart execution and explicit shared-device synchronization.
- Per-machine networking, port forwards and SIGPIPE-safe sends.
- File-descriptor based 9P containment, rename/unlink metadata and directory handling.
- Apple build shims, a reviewed SwiftPM source layout, guest-image recipes and focused lifecycle/network/filesystem/SMP qualification sources.

Exact patches and their scope are in `FloeAgent/ThirdParty/TinyEMU/patches/`, `PROVENANCE.json` and `LICENSE-INVENTORY.md`. `FLOE-SOURCE.json` binds every copied file to the original Floe source commit and digest. The historical Swift caller in `integration-reference/` requires Floe modules and is not a standalone executable. Qualification material retains its original assumptions; this extraction does not re-certify old benchmarks or physical-device behavior.

### Layout and licensing

- Root source files: unmodified official TinyEMU archive baseline.
- `FloeAgent/ThirdParty/TinyEMU/`: Floe adapter, patches, vendored build sources and guest build recipes.
- `FloeAgent/Qualification/TinyEMULinux/` and `FloeAgent/Tests/FloeTinyEMUTests/`: historical focused qualification sources.
- TinyEMU core: MIT. slirp and other upstream files retain their own notices. Floe adapter changes retain their MPL-2.0 headers; the MPL text is in `LICENSE-FLOE-MPL-2.0`. Linux guest and firmware licensing remains separate.

No user files, pairing records, credentials, local VM disks or prebuilt App packages are included. Floe is moving to a separate ARM64 runtime; this repository preserves the retired implementation for attribution and independent study.

## 简体中文

本仓库保存 Fabrice Bellard 官方 TinyEMU 2019-12-21 源码及 Floe 过去使用的 RISC-V Linux 集成。作者通过官网归档发布源码，因此这里从官方归档导入并标记上游基线，不冒称作者 GitHub 仓库的 fork。

Floe 的改进包括嵌入式生命周期与错误恢复、多核、独立网络及端口转发、9P 文件访问约束与元数据修复、Apple 编译适配和相关验证源码。逐项差异以补丁、来源文件和摘要清单为准。保留原作者署名、MIT/BSD 等上游许可及 Floe 自有代码的 MPL-2.0 边界；客体系统和固件另按其各自许可处理。

本仓库是退役实现的独立源码保存，不是新的 App 安装包，也不是 ARM64 引擎。未包含用户文件、凭据、配对数据或本地虚拟机磁盘。原验证源码保留历史上下文，不代表此次抽取重新完成了全部运行或真机验证。
