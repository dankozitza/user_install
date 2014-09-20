#!/usr/bin/perl

my $url = $ARGV[0];

my $search = "https://duckduckgo.com";

if (!$url) {
   $url = $search;
}

if (@ARGV[1] || ($url !~ /\./ && $url ne "localhost")) {
   $url = $search . "/?q=";
   foreach my $arg (@ARGV) {
      $arg =~ s/\s/+/g;
      $url .= $arg . "+";
   }
   $url =~ s/\+$//;
}

print "s: going to [$url]\n";

if (!-d $ENV{"HOME"} . "/downloads") {
	system("mkdir ~/downloads")
}

exec("dwb $url 2> ~/.d_dwb_log &");
