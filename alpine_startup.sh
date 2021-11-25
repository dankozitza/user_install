# alpine_startup.sh

if [  yes ]; then
	echo "script must be configured";
	exit;
fi

echo "Installing applications"
#sudo apk add screen
#sudo apk add vim
#sudo apk add git
#sudo apk add make
#sudo apk add gcc

if [ ! yes ]; then
echo "Configuring git"
git config --system user.name "dankozitza"
git config --system user.email "dankoz@gmx.us"
git config --system color.diff always
git config --system color.status true
git config --system credential.helper store
fi

if [ ! yes ]; then
echo "Installing mechanizm libs"
sudo apk add freeglut-dev
sudo apk add jsoncpp-dev
sudo apk add glm-dev
fi

if [ ! yes ]; then
echo "Installing mechanizm"
git clone https://github.com/dankozitza/mechanizm ~/m;
fi

# xfce and vnc
# https://www.amitnepal.com/alpine-linux-with-xfce-and-vnc-on-a-virtual-machine/
if [ ! yes ]; then
# uncomment community in /etc/apk/repositories
sudo apk update
sudo apk add setup-xorg-base xfce4 xfce4-terminal lightdm-gtk-greeter xfce4-screensaver dbus-x11 open-vm-tools-gtk faenza-icon-theme xf86-video-vmware xf86-input-mouse xf86-input-keyboard
sudo Xorg -configure
cp /root/xorg.conf.new /etc/X11/xorg.conf
rc-service lightdm start
rc-update add lightdm
rc-update add open-vm-tools
apk add --no-cache ca-certificates curl openssl sudo xvfb x11vnc xfce4 faenza-icon-theme bash
# start at boot
#rc-update add local default
# write following to /etc/local.d/vnc.start
##!/bin/sh
#nohup x11vnc -xkb -noxrecord -noxfixes -noxdamage -display :0 -loop -shared -forever -bg -auth /var/run/lightdm/root/:0 -rfbport 5900 -o /var/log/vnc.log > /dev/null 2>&1 &
#chmod +x /etc/local.d/vnc.start
fi
