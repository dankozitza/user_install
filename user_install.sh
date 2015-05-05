#!/bin/bash

USER_NAME=$1

USER_HOME="/home/$USER_NAME/"
if [[ "$USER_NAME" == "root" ]]; then
	USER_HOME="/$USER_NAME/"
	echo "set user home to $USER_HOME"
fi

### set git name and email ###
#
git config --global user.name "Dan Kozitza"
git config --global user.email "dankoz@gmx.us"
#
###

### root+program configuration ###
#
find userhome/ -maxdepth 1 -mindepth 1 -exec cp -r {} ~ \;
find usr/ -maxdepth 1 -mindepth 1 -exec cp -r {} /usr/ \;
find etc/ -maxdepth 1 -mindepth 1 -exec cp -r {} /etc/ \;
#
###

### network setup ***
#
#ip addr
#
#echo "\n!--- configure network.service ---!\n"
#sleep 5
#
#vim network.service
#
#cp extra/network.service /etc/systemd/system/
#
#systemctl daemon-reload
#systemctl start network.service
#
#echo "\n!--- if ping fails network setup failed! ---!\n"
#sleep 2
#
#ping google.com
#
###

### virtualbox guest setup ###
#
#pacman --noconfirm -S virtualbox-guest-modules
#pacman --noconfirm -S virtualbox-guest-utils
#
#modprobe -a vboxguest vboxsf vboxvideo
#cp extra/virtualboxguest.conf /etc/modules-load.d/
#cp extra/mount_vboxshared.service /etc/systemd/system/
#systemd start mount_vboxshared.service
#
#systemctl daemon-reload
#systemctl enable vboxservice
#
###

### program download+installation ***
#
#echo "\n!--- Now going to install a few programs ---!\n"
#sleep 2
#
#pacman --noconfirm -S vim
#pacman --noconfirm -S wget
#pacman --noconfirm -S rsnapshot
#pacman --noconfirm -S openbox
#pacman --noconfirm -S xorg
#pacman --noconfirm -S xorg-xinit
#pacman --noconfirm -S xfce4-terminal
#pacman --noconfirm -S xfce4
#pacman --noconfirm -S arandr
#pacman --noconfirm -S git
#pacman --noconfirm -S go
#pacman --noconfirm -S mpc
#pacman --noconfirm -S ncmpcpp
#pacman --noconfirm -S alsa-utils
#pacman --noconfirm -S htop
#pacman --noconfirm -S surf
#pacman --noconfirm -S dwb
#pacman --noconfirm -S gst-plugins-good
#pacman --noconfirm -S dmenu
#pacman --noconfirm -S figlet
#pacman --noconfirm -S flashplugin
#pacman --noconfirm -S transmission-gtk
#pacman --noconfirm -S scrot
#pacman --noconfirm -S gimp
#pacman --noconfirm -S epdfview
#
###

### user setup ###
#
echo "\n!--- Now going to set up user $USER_NAME ---!\n"
sleep 2

useradd -m -s /bin/bash $USER_NAME
passwd $USER_NAME
#
###

### user+program configuration ***
#
echo "\n!--- Now going to configure programs ---!\n"
sleep 2

# copy config files
find userhome/ -maxdepth 1 -mindepth 1 -exec cp -r {} $USER_HOME \;

openbox --reconfigure

#mkdir -p $USER_HOME/go/src/github.com/dankozitza
#mkdir $USER_HOME/go/pkg

# make sure user owns all their files
chown -R $USER_NAME $USER_HOME
#
###

echo "\n!--- Done ---!\n"

### virtualbox host setup ###
#
#pacman --noconfirm -S virtualbox
#pacman --noconfirm -S qt4
#pacman --noconfirm -S virtualbox-guest-iso
#
#depmod -a
#modprobe vboxdrv
#modprobe vboxpci
#cp extra/virtualboxhost.conf /etc/modules-load.d/
#
###
