English | [简体中文](README.zh-Hans.md)

# VLC Protocol Handler for Windows

A VLC protocol handler for Windows that supports opening videos in VLC by clicking `vlc://` links.

## Features

- Supports standard format: `vlc://http://example.com/video.mp4`
- Supports Chrome 130+ format (auto-fix): `vlc://http//example.com/video.mp4`
- Supports weblink format: `vlc://weblink?url=http%3A%2F%2Fexample.com%2Fvideo.mp4`

## Installation

### Method 1: PowerShell Script (Recommended)

This method is easy to install and does not show a command prompt window.

1. Copy the files from the `ps` directory to the VLC installation directory (usually `C:\Program Files\VideoLAN\VLC`)
2. Run `vlc-protocol-register.ps1` as administrator (right-click the file and select "Run as administrator")

### Method 2: Batch Script

This method is easy to install, but a command prompt window will briefly appear when clicking a `vlc://` link.

1. Copy the files from the `bat` directory to the VLC installation directory
2. Run `vlc-protocol-register.bat` as administrator

### Method 3: Executable

This method does not show a command prompt window and offers the best performance.

#### Download and Install
1. Download the latest [vlc-protocol-windows-exe.zip](https://github.com/northsea4/vlc-protocol/releases/latest/download/vlc-protocol-windows-exe.zip) from the [Releases](https://github.com/northsea4/vlc-protocol/releases/latest) page
2. Extract the downloaded zip file and copy its contents to the VLC installation directory
3. Run `vlc-protocol-register.bat` as administrator

#### Build from Source
1. Install the MinGW-w64 toolchain
   - Windows: Use [MSYS2](https://www.msys2.org/) to install
   - macOS: Install via Homebrew `brew install mingw-w64`
   - Linux: Install via package manager, e.g., `sudo apt install gcc-mingw-w64`
2. Clone the repository: `git clone https://github.com/northsea4/vlc-protocol.git`
3. Navigate to the directory: `cd vlc-protocol/windows/exe/`
4. Build: `./build.sh`

## Testing

1. Open the `test.html` file
2. Click a test link, and VLC should automatically launch to play the corresponding video

## Uninstallation

### PowerShell Script
Run `vlc-protocol-deregister.ps1` as administrator

### Batch Script
Run `vlc-protocol-deregister.bat` as administrator

### Executable
Run `vlc-protocol-deregister.bat` as administrator

## System Requirements

- Windows 10 or later
- VLC media player 2.0.0 or later

## Troubleshooting

If you encounter issues:

1. Make sure to run the registration script as administrator
2. Verify that VLC is properly installed
3. Log file locations for the PowerShell version:
   - Normal log: `%TEMP%\vlc-protocol.log`
   - Error log: `%TEMP%\vlc-protocol-error.log`
4. If clicking links has no effect, check if your browser allows opening external protocols

## Security

- The program validates URL formats and only allows http:// and https:// links
- Does not support executing arbitrary commands; only supports opening video links

## Development Notes

Three implementations are provided:
1. PowerShell script (ps): Full-featured, easy to maintain
2. Batch script (bat): Simple and straightforward, does not support weblink format yet
3. Executable (exe): Best performance, supports x86_64 and arm64 architectures

Recommendations:
- General users: Use the PowerShell version
- Performance seekers: Use the executable version
- High system compatibility needs: Use the batch script version
