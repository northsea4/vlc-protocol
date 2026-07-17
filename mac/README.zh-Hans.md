[English](README.md) | 简体中文

# VLC Protocol Handler for macOS

这是一个macOS下的VLC协议处理程序，支持通过点击 `vlc://` 链接来用VLC播放视频。

## 功能特性

- 支持标准格式：`vlc://http://example.com/video.mp4`
- 支持Chrome 130+格式（自动修复）：`vlc://http//example.com/video.mp4`
- 支持weblink格式：`vlc://weblink?url=http%3A%2F%2Fexample.com%2Fvideo.mp4`

## 构建和安装

构建脚本（`build.sh`）支持以下参数：

参数 | 说明
--- | ---
`--plist` | 生成新的 Info.plist 文件（如果不需要修改配置，可以不用此参数）
`--install` | 安装到用户的 Applications 文件夹（~/Applications）
`--install-to <path>` | 安装到指定目录（比如要安装到系统的 Applications 文件夹）

### 构建

最简单的构建命令：
```bash
cd mac
./build.sh
```

### 安装

1. 安装到用户的 Applications 文件夹：
   ```bash
   ./build.sh --install
   ```

2. 安装到系统的 Applications 文件夹：
   ```bash
   ./build.sh --install-to /Applications
   ```

3. 如果需要修改应用配置，可以同时使用 `--plist` 参数：
   ```bash
   ./build.sh --plist --install
   ```

## 首次使用

首次运行时，macOS会询问是否允许打开此应用，选择"打开"即可。

## 测试

1. 打开 `test.html` 文件
2. 点击测试链接，应用会自动启动VLC播放相应的视频

## 系统要求

- macOS 10.15 或更高版本
- VLC media player
