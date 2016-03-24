#!/usr/bin/perl

my @lines = `systemctl --no-pager status rsnapshot_daily`;
my $msg = "";
my $stat = "WARN";
my $st = "rsnapshot_daily";

foreach my $line (@lines) {
   if ($line =~ /SUCCESS/) {
      $stat = "PASS";
   }
   $line =~ s/&/and/g;
   $line =~ s/;//g;
   $line =~ s/\n/<br>/g;
   $msg .= $line;
}

print $msg;

system(
      "curl -d \"id=777&message=$msg&short_stack=" . $st . "&status="
      . $stat . "&program=systemctl&stack=\" dankozitza.com/post_stat");
