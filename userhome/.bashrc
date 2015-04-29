#
# ~/.bashrc
#

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

export GOPATH=$HOME/go
export PATH=$PATH:$GOPATH/bin

alias ls='ls --color=auto'
alias sc='systemctl'
alias cpueat="while true; do date; ps auxf | awk '{if(\$8==\"D\") print $0;}\'; sleep 1; done"
alias save_vms="VBoxManage list runningvms | sed -r 's/\"//' | sed -r 's/\".*$//' | xargs -i VBoxManage controlvm '{}' savestate"
alias off="save_vms; sudo shutdown now"
alias offon="save_vms; reboot"

#PS1='[\u@\h \W]\$ '
