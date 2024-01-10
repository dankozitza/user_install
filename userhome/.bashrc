# .bashrc

# Source global definitions
if [ -f /etc/bashrc ]; then
	. /etc/bashrc
fi

# User specific environment
if ! [[ "$PATH" =~ "$HOME/.local/bin:$HOME/cmd:" ]]
then
    PATH="$HOME/.local/bin:$HOME/cmd:$PATH"
fi
export PATH

# Uncomment the following line if you don't like systemctl's auto-paging feature:
# export SYSTEMD_PAGER=

# User specific aliases and functions
if [ -d ~/.bashrc.d ]; then
	for rc in ~/.bashrc.d/*; do
		if [ -f "$rc" ]; then
			. "$rc"
		fi
	done
fi

unset rc

#PS1="[\u@\h \W]\$"

cb1="\[\033[01;";
cb2="m\]";
ce="\[\033[00m\]";

user_color=$((31 + $RANDOM % 7));
pid_color=36;
bar_color=$user_color;

#PS1="[\[\033[01;"$user_color"m\]\u-"$$"\[\033[00m\]@\h \W]\$ ";
#PS1="[\[\033[01;"$user_color"m\]\u\[\033[00m\]#\[\033[01;"$pid_color"m\]"$$"\[\033[00m\]@\h \W]\$ ";
#PS1="[\[\033[01;"$user_color"m\]\u\[\033[00m\]@\h#\[\033[01;"$pid_color"m\]"$$"\[\033[00m\] \W]\$ ";
#PS1="["$cb1$user_color$cb2"\u"$ce"@\h#"$cb1$pid_color$cb2$$$ce" \W]\$ ";

# colored bar, user, host, pid, pwd
#PS1=$cb1$bar_color$cb2"["$ce$cb1$user_color$cb2"\u"$ce"@\h#"$cb1$pid_color$cb2$$$ce" \W"$cb1$bar_color$cb2"]"$ce"\$ ";

# pid, pwd
#PS1=$cb1$user_color$cb2$$$ce" \W"$cb1$bar_color$cb2")"$ce" ";

# user, pwd
PS1=$cb1$user_color$cb2"\u"$ce" \W"$cb1$bar_color$cb2")"$ce" ";

