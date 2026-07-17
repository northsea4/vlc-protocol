[English](README.md) | 简体中文

# VLC Protocol Handler for Windows

这是一个 Windows 下的 VLC 协议处理程序，支持通过点击 `vlc://` 链接来用 VLC 播放视频。

## 功能特性

- 支持标准格式：`vlc://http://example.com/video.mp4`
- 支持 Chrome 130+ 格式（自动修复）：`vlc://http//example.com/video.mp4`
- 支持 weblink 格式：`vlc://weblink?url=http%3A%2F%2Fexample.com%2Fvideo.mp4`

## 安装方式

### 方式一：PowerShell 脚本安装（推荐）

这种方式安装简单，且不会出现命令行窗口。

1. 将 `ps` 目录下的文件复制到 VLC 安装目录（通常是 `C:\Program Files\VideoLAN\VLC`）
2. 以管理员身份运行 `vlc-protocol-register.ps1`（右键点击文件，选择"以管理员身份运行"）

### 方式二：批处理脚本安装

这种方式安装简单，但在点击 `vlc://` 链接时会短暂出现命令行窗口。

1. 将 `bat` 目录下的文件复制到 VLC 安装目录
2. 以管理员身份运行 `vlc-protocol-register.bat`

### 方式三：可执行文件安装

这种方式不会出现命令行窗口，且性能最好。

#### 直接下载安装
1. 从 [Releases](https://github.com/northsea4/vlc-protocol/releases/latest) 页面下载最新的 [vlc-protocol-windows-exe.zip](https://github.com/northsea4/vlc-protocol/releases/latest/download/vlc-protocol-windows-exe.zip) 文件
2. 将下载的 zip 文件解压后把里面的文件复制到 VLC 安装目录
3. 以管理员身份运行 `vlc-protocol-register.bat`

#### 自行编译
1. 安装 MinGW-w64 工具链
   - Windows: 使用 [MSYS2](https://www.msys2.org/) 安装
   - macOS: 使用 Homebrew 安装 `brew install mingw-w64`
   - Linux: 使用包管理器安装，如 `sudo apt install gcc-mingw-w64`
2. 克隆仓库：`git clone https://github.com/northsea4/vlc-protocol.git`
3. 进入目录：`cd vlc-protocol/windows/exe/`
4. 编译：`./build.sh`

## 测试

1. 打开 `test.html` 文件
2. 点击测试链接，应用会自动启动 VLC 播放相应的视频

## 卸载

### PowerShell 脚本卸载
以管理员身份运行 `vlc-protocol-deregister.ps1`

### 批处理脚本卸载
以管理员身份运行 `vlc-protocol-deregister.bat`

### 可执行文件卸载
以管理员身份运行 `vlc-protocol-deregister.bat`

## 系统要求

- Windows 10 或更高版本
- VLC media player 2.0.0 或更高版本

## 故障排除

如果遇到问题：

1. 确保以管理员身份运行注册脚本
2. 检查 VLC 是否已正确安装
3. PowerShell 版本的日志文件位置：
   - 正常日志：`%TEMP%\vlc-protocol.log`
   - 错误日志：`%TEMP%\vlc-protocol-error.log`
4. 如果链接点击无反应，请检查浏览器是否允许打开外部协议

## 安全说明

- 程序会验证 URL 格式，只允许 http:// 和 https:// 链接
- 不支持执行任意命令，仅支持打开视频链接

## 开发说明

提供了三种实现方式：
1. PowerShell 脚本（ps）：功能完整，易于维护
2. 批处理脚本（bat）：简单直接，暂不支持 weblink 格式
3. 可执行文件（exe）：性能最好，支持 x86_64 和 arm64 架构

选择建议：
- 一般用户：使用 PowerShell 版本
- 追求性能：使用可执行文件版本
- 系统兼容性要求高：使用批处理脚本版本
