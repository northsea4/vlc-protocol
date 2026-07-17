[English](README.md) | 简体中文

# VLC Protocol Handler for Linux

### 安装：
```shell
curl -LO https://github.com/northsea4/vlc-protocol/releases/latest/download/vlc-protocol-linux.zip
unzip vlc-protocol-linux.zip -d ./vlc-protocol-linux/
cd ./vlc-protocol-linux
sudo cp vlc-protocol /usr/local/bin/
sudo chmod +x /usr/local/bin/vlc-protocol
xdg-desktop-menu install vlc-protocol.desktop
update-desktop-database ~/.local/share/applications
```
然后**重启**系统使安装生效。

### 卸载：
```shell
xdg-desktop-menu uninstall vlc-protocol.desktop
sudo rm /usr/local/bin/vlc-protocol
```

### 测试：
```shell
# 标准格式
xdg-open vlc://https://pbs.twimg.com/tweet_video/Cx5L_3FWgAAxzpM.mp4

# Chrome 130+ 格式
xdg-open vlc://https//pbs.twimg.com/tweet_video/Cx5L_3FWgAAxzpM.mp4

# Weblink 格式
xdg-open vlc://weblink?url=https://pbs.twimg.com/tweet_video/Cx5L_3FWgAAxzpM.mp4

# URL 编码的 Weblink 格式
xdg-open vlc://weblink?url=https%3a%2f%2fpbs.twimg.com%2ftweet_video%2fCx5L_3FWgAAxzpM.mp4
```
