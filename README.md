English | [简体中文](README.zh-Hans.md)

# VLC Protocol Handler

A cross-platform VLC protocol handler that supports opening videos in VLC by clicking `vlc://` links.

## Features

- Supports multiple URL formats:
  - Standard format: `vlc://http://example.com/video.mp4`
  - Chrome 130+ format (auto-fix): `vlc://http//example.com/video.mp4`
  - Weblink format: `vlc://weblink?url=http%3A%2F%2Fexample.com%2Fvideo.mp4`
- Cross-platform support:
  - Windows: Supports PowerShell, batch script, and executable installation methods
  - macOS: Supports command-line and GUI installation
  - Linux: Supports command-line installation

## Platform Support

### Windows
- Supports Windows 10 and above
- Provides three installation methods:
  1. PowerShell script: Recommended
  2. Batch script: Simple and straightforward, does not support weblink format yet
  3. Executable: Best performance
- See [windows/README.md](windows/README.md) for detailed instructions

### macOS
- Supports macOS 10.15 and above
- Installation: After downloading the archive, extract the app directory to `/Applications`
- See [mac/README.md](mac/README.md) for detailed instructions

### Linux
- Supports most Linux desktop distributions, such as Ubuntu, Debian
- See [linux/README.md](linux/README.md) for installation instructions

## Browser Configuration

### Firefox
1. Open `about:config`
2. Search for `network.protocol-handler.expose.vlc`
3. Create it as a boolean and set it to `false`

### Chrome
- Chrome 130 and earlier: Click the link directly to use
- Chrome 130 and later: New URL format is automatically fixed

### Safari
- macOS: Click the link directly to use
- Other platforms: Not supported

## Related Projects

- [Open with VLC](https://github.com/stefansundin/open-with-vlc) - Browser extension for opening videos via right-click menu

## Security

- Only supports http:// and https:// links; on Linux, ftp://, udp://, mms://, and file:// links are also supported
- Does not support executing arbitrary commands

## Acknowledgements

This project is based on [stefansundin/vlc-protocol](https://github.com/stefansundin/vlc-protocol). Thanks to the original project developers for their contributions.

## Contributing

Pull requests and issues are welcome!

## License

GPLv3
