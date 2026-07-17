English | [简体中文](README.zh-Hans.md)

# VLC Protocol Handler for macOS

A VLC protocol handler for macOS that supports opening videos in VLC by clicking `vlc://` links.

## Features

- Supports standard format: `vlc://http://example.com/video.mp4`
- Supports Chrome 130+ format (auto-fix): `vlc://http//example.com/video.mp4`
- Supports weblink format: `vlc://weblink?url=http%3A%2F%2Fexample.com%2Fvideo.mp4`

## Build and Install

The build script (`build.sh`) supports the following parameters:

| Parameter | Description |
| --- | --- |
| `--plist` | Generate a new Info.plist file (can be omitted if configuration does not need changing) |
| `--install` | Install to the user's Applications folder (~/Applications) |
| `--install-to <path>` | Install to a specified directory (e.g., to install to the system Applications folder) |

### Build

The simplest build command:
```bash
cd mac
./build.sh
```

### Install

1. Install to the user's Applications folder:
   ```bash
   ./build.sh --install
   ```

2. Install to the system Applications folder:
   ```bash
   ./build.sh --install-to /Applications
   ```

3. If you need to modify the app configuration, you can use the `--plist` parameter at the same time:
   ```bash
   ./build.sh --plist --install
   ```

## First Use

On first run, macOS will ask whether to allow opening this app. Select "Open" to proceed.

## Testing

1. Open the `test.html` file
2. Click a test link, and VLC should automatically launch to play the corresponding video

## System Requirements

- macOS 10.15 or later
- VLC media player
