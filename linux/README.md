### Install:
```shell
curl -LO https://github.com/northsea4/vlc-protocol/releases/latest/download/vlc-protocol-linux.zip
unzip vlc-protocol-linux.zip -d ./vlc-protocol-linux/
cd ./vlc-protocol-linux
sudo cp vlc-protocol /usr/local/bin/
sudo chmod +x /usr/local/bin/vlc-protocol
xdg-desktop-menu install vlc-protocol.desktop
update-desktop-database ~/.local/share/applications
```
Then **restart** the system for the installation to take effect.

### Uninstall:
```shell
xdg-desktop-menu uninstall vlc-protocol.desktop
sudo rm /usr/local/bin/vlc-protocol
```

### Test:
```shell
xdg-open vlc://https://pbs.twimg.com/tweet_video/Cx5L_3FWgAAxzpM.mp4
```
