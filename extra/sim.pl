#!/usr/bin/perl
#
# sim.pl
#
# Compare two files
#
# Copyright (c) 2024 Daniel Kozitza

BEGIN {
   $SIG{__DIE__} = sub{ print STDERR "Perl: ", @_; exit 0; die 0;};
}

$| = 1;
my @stra1 = ();
my $first_done = 0;
my @stra2 = ();
my @outfl = ();
my $v = 0;
my $total = 0;
my $min = 0;

foreach my $arg (@ARGV) {

   if ($arg eq "help" || $arg eq "-h" || $arg eq "--help") {
      exit 0;
   }

   elsif ($arg eq "exit" || $arg eq "quit" || $arg eq "leave" || $arg eq "return") { #_cmddef
      print "Exiting...\n";
      exit 0;
   }

   elsif ($arg =~ /^-v=(\d+)$/) {
      $v = $1;
   }

   elsif ($arg eq "-v") {
      $v = 5;
   }

   elsif ($arg =~ /^-m=(\d+)$/) {
      $min = $1;
   }

   elsif ($arg =~ /^-file-(r|w|rb-\d+|wa)=(\S++)/) { # read/write/append script #_cmddef
      my $sarg = $1;
      my $name = $2;
      my $mode = "";
      my $rbs  = 0;

      if ($sarg =~ /rb-(\d++)/) { $rbs = $1; $sarg = "rb"; }

      if ($sarg eq "w")  { $mode = ">";    }
      if ($sarg eq "r")  { $mode = "<";    }
      if ($sarg eq "rb") { $mode = "<:raw";}
      if ($sarg eq "wa") { $mode = ">>";   }

      if ($sarg eq "w" || $sarg eq "wa") {
         push(@outfl, $mode . " " . $name);
      }
      elsif ($sarg eq "r") {
         my $fh;
         open($fh, $mode, $name) or die "$0 could not open $name. $!\n";
         while (<$fh>) {
            my $line = $_;
            chomp $line;
            if (length($line) < $min) { next; }

            if ($first_done == 0) {
               push(@stra1, $line);
            }
            else {
               push(@stra2, $line);
            }
         }
         close $fh or die "$0 failed while closing $name. $!\n";
         $first_done = 1;
      }
      elsif ($sarg eq "rb") {
         my $fh;
         open($fh, $mode, $name) or die "$0 could not open $name. $!\n";
         my $read = 1;
         while ($read > 0) {
            my $bytes;
            $read = read $fh, $bytes, $rbs;

            if ($bytes ne '') {

               $bytes =~ s/\W/ /ug;
               if ($bytes =~ /^\s+$/aa) {
                  next;
               }
               if (length($bytes) < $rbs) {
                  next;
               }

               if ($first_done == 0) {
                  push(@stra1, $bytes);
               }
               else {
                  push(@stra2, $bytes);
               }
            }
            else { $read = 0; }
         }
         close $fh or die "$0 failed while closing $name. $!\n";
         $first_done = 1;
      }
   }
}

if ($v >= 4) {
   print "$0 buffer 1:\n";

   my $i = 0;
   foreach my $line (@stra1) {
      print "$i|$line|\n";
      $i++;
   }
}

if ($v >= 5) {
   print "$0 buffer 2:\n";

   $i = 0;
   foreach my $line (@stra2) {
      print "$i|$line|\n";
      $i++;
   }
}

my $i2 = 0;
foreach my $line2 (@stra2) {

   if (length($line2) == 0 || $line2 eq '') { next; }

   my $i1 = 0;
   foreach my $line1 (@stra1) {

      if (length($line1) == 0 || $line1 eq '') { next; }

      if (length($line1) == length($line2) && $line1 eq $line2) {
         $total++;
         if ($v == 1) {
            print $line1 . ' ';
         }
         elsif ($v == 2) {
            print "line $i1 matches line $i2\n";
         }
         elsif ($v >= 3) {
            print "string:\n  $i1|$line1|\n    found in file 2 line $i2\n";
         }
      }
      elsif (length($line1) < length($line2)) {
         my $l1l = length($line1);
         my $dif = length($line2) - $l1l;
         for (my $si = 0; $si <= $dif; $si++) {
            my $ls = substr($line2, $si, $l1l);
            if ($line1 eq $ls) {
               $total++;
               if ($v == 1) {
                  print $line1 . ' ';
               }
               elsif ($v == 2) {
                  print "line $i1 matches line $i2\n";
               }
               elsif ($v >= 3) {
                  print "string at:\n  $i1|$line1|\n    found at:\n";
                  print "      $i2|$line2|\n";
               }
               $si = $dif;
            }
         }
      }

      $i1++;
   }

   if ($v == 1) {
      print "\n";
   }

   $i2++;
}

if ($v >= 2) {
   print "total matches: $total\n";
}

foreach my $file (@outfl) {
   print $file . "\n";
}

my $msg = "Process ";
my $cpcidx = 0;
while ($cpcidx != -1) {
   $cpcidx = waitpid(-1, WNOHANG);
   if ($cpcidx > 0) {
      $msg .= "$cpcidx ";
   }
   else {
      $msg .= "exited.\n";
   }
}
if (length($msg) > 16) { print $msg; }

exit 0;

__END__
