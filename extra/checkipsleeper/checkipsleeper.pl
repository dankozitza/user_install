#!/usr/bin/perl
#
# checkipsleeper.pl
#
# used to email myself my external ip. you'll need to set up an email account
# for your machine or host an email server on it. check out userhome/.msmtprc.
# you will also want to place the checkipsleeper dir somewhere and modify
# extra/checkipsleeper.service to have it executed by systemctl on init.
#

use strict;
use Sys::Hostname;

my $filepath = "/var/local/externalip";
my @sites = qw'ifconfig.me myexternalip.com/raw ip.appspot.com';

for (my $i = 0; $i < $#ARGV; $i++) {
	if ($ARGV[$i] eq "-f" || $ARGV[$i] eq "--filepath") {
		print "setting filepath to $ARGV[$i+1]\n";
		$filepath = $ARGV[$i+1];
	}
	if ($ARGV[$i] eq "-s" || $ARGV[$i] eq "--site") {
		print "adding site $ARGV[$i+1] to list of websites\n";
		my @newsites;
		push(@newsites, $ARGV[$i+1], @sites);
		print "sites: @newsites\n";
		@sites = @newsites;
	}
}

while (1) {
	my $h = hostname;

	my $newip;
	my $i = -1;
	while ($newip !~ /^\d+\.\d+\.\d+\.\d+$/) {
		sleep(30) if $i >= 0;
		$i++;
		$i = 0 if $i > $#sites;

#		print "checking site $sites[$i]\n";
		$newip = `curl -m 10 $sites[$i] 2> /dev/null`;
		chomp($newip);
	}

	my $ip = "<nil>";
	if (-f "$filepath") {
		$ip = `cat $filepath`;
		chomp($ip);
	}

	if ($newip ne $ip) {
		print "old ip $ip has changed to new ip $newip\n";
		system("rm -f $filepath; echo '$newip' >> $filepath");
		system("mail -s '$h external ip change' UserName\@email.com < $filepath");
	}

	sleep(1000);
}
