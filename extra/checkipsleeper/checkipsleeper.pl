#!/usr/bin/perl
#
# checkipsleeper.pl
#
# used to email myself my external ip. you'll need to set up an email account
# for your machine or host an email server on it. check out userhome/.msmtprc.
# you will also want to place the checkipsleeper dir somewhere and modify
# extra/checkipsleeper.service to have it executed by systemctl on init.
#

use Sys::Hostname;

while (1) {
	$h = hostname;

	$newip = `curl ipecho.net/plain 2> /dev/null`;
	chomp($newip);
	$ip = `cat ip`;
	chomp($ip);

	if ($newip ne $ip) {
		print "old ip $ip has changed to new ip $newip\n";
		system("rm ip; echo '$newip' >> ip");
		system("mail -s '$h external ip change' YourUserName\@email.com < ip");
	}

	sleep(1000);
}
