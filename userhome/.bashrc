#
# ~/.bashrc
#

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

export GOPATH=$HOME/go
export PATH=$PATH:$GOPATH/bin

alias ls='ls --color=auto'

#PS1='[\u@\h \W]\$ '
