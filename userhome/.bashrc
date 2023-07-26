#
# ~/.bashrc
#

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

PS1="\w) "

#export GOPATH=$HOME/go
#export PATH=$PATH:$GOPATH/bin

alias ls='ls --color=auto'
#alias sc='systemctl'
alias cpueat="while true; do date; ps auxf | awk '{if(\$8==\"D\") print $0;}\'; sleep 1; done"
alias save_vms="echo 'shutting down running vms'; VBoxManage list runningvms | sed -r 's/\"//' | sed -r 's/\".*$//' | xargs -i VBoxManage controlvm '{}' savestate"

alias vim="vim --cmd 'set noloadplugins'";
alias vip="vim --cmd 'set loadplugins'";

function off {
	save_vms
	sleep 1

	echo
	echo "running vms:"
	echo
	if ps -ef | grep -v "grep" | grep "startvm"
	then
		echo
		echo "there are still vms running"
		
	else
		echo "no vms running, shutting down"
		echo
		#su -c 'shutdown'
		shutdown now
	fi
}

#PS1='[\u@\h \W]\$ '
