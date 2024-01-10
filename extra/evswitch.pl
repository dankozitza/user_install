#!/usr/bin/perl
# (((* switcher)speaker)screen) DKMagic_EVSWITCH
#
#    evswitch.pl
#
# This program is a general purpose on/off switch for scripts
# that interoperate with artificial intelligence.
#
# Copyright (c) 2024 Daniel Kozitza
#

BEGIN {
   $SIG{__DIE__} = sub{ print STDERR "Perl: ", @_; wait_for_children(); exit 0; };
}

sub print_help {
   print "
evswitch.pl

   This script is a general purpose on/off switch for a list of system calls.

   The use of this script as a tool for interacting with AI requires an
   interactive shell be configured for each job/session.

Description:

   EVSwitch.pl accepts -index arguments that indicate the following arguments
   are passed to the corresponding system call defined in cmd_list. if an
   index is not yet defined lines are added to cmd_list and a new system call
   is defined at index.

   Default index: 0

Usage:

   perl evswitch.pl [script.evss] -0 [arguments] -1 [arguments] -l [system call]

";
   return;
}

print STDOUT "EVSwitch Starting...\n";
my $pcheck = 1;
my @cmd_list = ();
my $chdirl = "";
my $sc_msg = "EVSwitch system call ";
my $unknown_cmd = "/usr/bin/sh -c";
my $task_management = 0;
my @cpids  = ();
my $cmdi   = 0;
my $cmd    = "";
my $in     = "";
my $msf    = "";
my $pid    = 0;
my $idx = -1;
my $eval_print = 1;

foreach my $arg (@ARGV) {

   if ($arg eq "help" || $arg eq "-h" || $arg eq "--help") {
      print_help();
      exit 0;
   }

   if ($arg =~ /^evs\-(c|clear)$/) { # evs clear all system calls #_cmddef
      @cmd_list = ();
      next;
   }

   if ($arg eq "-t") {
      $task_management = 1;
      next;
   }

   if ($arg eq "-l") { # evs add new system call #_cmddef
      if ($#cmd_list == 0 && $cmd_list[0] eq "") {
         $idx = 0;
         $cmd_list[0] = "";
         next;
      }
      else {
         $arg = "-" . ($#cmd_list + 1);
      }
   }

   if ($arg =~ /-(\d+)/) { # evs usage #_cmddef
      $idx = $1;
      if ($idx > $#cmd_list) {
         my @new_lines = ("") x ($idx - $#cmd_list);
         push(@cmd_list, @new_lines);
      }
      next;
   }

   if ($idx == -1) {
      $in = "script ra $arg";
      script();
   }
   elsif ($cmd_list[$idx] =~ /^(.*)( #EVSA#.*)$/) {
      $cmd_list[$idx] = $1 . " " . $arg . $2;
   }
   else {
      if ($cmd_list[$idx] eq "") {
         $cmd_list[$idx] = $arg;
      }
      else {
         $cmd_list[$idx] .= " " . $arg;
      }
   }
}

$cmdi = 0;
foreach my $cmdp (@cmd_list) {
   $cmd = $cmdp;
   fcall_cmd();
   $cmdi++;
}

my $prompt = 0;
while (1) {

   $in = "";
   $in = readline(STDIN);
   chomp $in;

   if ($in eq "help" || $in eq "h" || $in eq "?") {
      print "\nEVSwitch commands:\n
   <index><s|n> [options] - Run system call at index.
   <size><s|n> [command]  - Define new system call.
   list                   - List system calls.
   lhk                    - List system calls that begin with an index symbol.
   lc                     - List comments.
   eval [index]           - Evaluate and print one or all system calls.
   script <r|w|ra|wa> <filename.evss>  - Read/Write/Append script from file system.
   rpl(a) <index> <m>/[r] - Run a regular expression replacement at index.
   evs [options]          - Start an EVSwitch instance within this one.
   evs-clear [index]      - Clear one or all system calls.
   restart [options]      - Restart the program.
   exit                   - Exit this instance.\n\n";
      $prompt = 1;
   }
   elsif ($in =~ /^(\d+)/) { # cli run/modify/add system call at index #_cmddef

      my $ci = $1;
      my $run = "T";
      my $args = "";

      if ($in =~ /^\d+(n |s | )(.++)/) {
         $run  = $1;
         $args = $2;
      }
      elsif ($in =~ /^\d+(n|s)$/) { # do not run and strip comment symbols #_cmddef
         $run = $1;
      }

      if ($ci > $#cmd_list) {
         my @new_lines = ("") x ($ci - $#cmd_list);
         push(@cmd_list, @new_lines);
      }

      if ($args ne "") {

         if ($cmd_list[$ci] =~ /^(.*)#EVSA#(.*)$/) {
            $cmd_list[$ci] = $1 . $args . $2;
         }
         elsif ($cmd_list[$ci] =~ /\s$/) {
            $cmd_list[$ci] .= $args;
         }
         else {
            $cmd_list[$ci] .= " " . $args;
         }
      }

      if ($run =~ /\S/) {
         $run =~ s/\s+//g;
      }
      else {
         $run = " ";
      }

      $cmdi = $ci;
      $cmd = $cmd_list[$ci];

      if ($run eq "T" || $run ne "n") {

         if ($run eq "s") {
            if ($cmd =~ /^\s*#(\D.++)/ && $cmd !~ /^\s*#[\+\-]/) {
               $cmd = $1;
               $cmd =~ s/^\s++//;
               $cmd =~ s/\s+$/ /;
            }
         }

         fcall_cmd();
      }
   }
   elsif ($in eq "list" || $in eq "l") { # list system calls #_cmddef
      print "EVSwitch system calls:\n";
      my $i = 0;
      foreach my $sc (@cmd_list) {
         print "$i> $sc\n";
         $i++;
      }
   }
   elsif ($in =~ /^cd(.*)$/) {
      my $arg = "";
      if ($1 ne "") { $arg = $1; $arg =~ s/^\s+//;}
      chdir($arg) or print "EVSwitch cannot enter directory '$arg'.\n";
      $prompt = 1;
   }
   elsif ($in =~ /^(rpla?) (\d+) (.+)\/.*$/) { # rpl(a) <line> <m>/[r] # regex #_cmddef
      my $c = $1; my $i = $2;
      my $match = $3;
      my $repl = "";

      if ($in =~ /^(rpla?) (\d+) (.+)\/(.+)$/) {
         $repl = $4;
      }

      if ($c eq "rpl") {
         $cmd_list[$i] =~ s/$match/$repl/;
      }
      else {
         $cmd_list[$i] =~ s/$match/$repl/g;
      }
      $prompt = 1;
   }
   elsif ($in =~ /^move (\d+) (\d+)$/) { #_cmddef
      $cmd_list[$2] = $cmd_list[$1];
      $cmd_list[$1] = "";
      $prompt = 1;
   }
   elsif ($in =~ /^script (r|w|ra|wa) (.++)/) { # read/write/append script #_cmddef
      script();
      $prompt = 1;
   }
   elsif ($in eq "reload") { # clear buffer and read script from fs #_cmddef
      if ($msf ne "") {
         $in = "script r $msf";
         script();
      }
      else {
         print "No script loaded.\n";
      }
      $prompt = 1;
   }
   elsif ($in eq "lp") { # list processes #_cmddef
      print "Running processes: ";
      foreach my $cp (@cpids) {
         print $cp . " ";
      }
      print "\n";
      $prompt = 1;
   }
   elsif ($in eq "lhk") { # list hot keys #_cmddef
      my $li = 0;
      foreach my $line (@cmd_list) {
         if ($line =~ /^\s*(#?\s*#)(\+?\-?\d+)#/) {
            my $msg = "$li> ";
            if ($1 =~ /##/) { $msg = "$li\s> "; }
            my $tl = $line;
            if ($tl =~ /#EVSF_(\w+)#/) { $msg .= $1; }
            if ($tl =~ / #( .+)$/) { $msg .= " -" . $1; }
            print $msg . "\n";
         }
         $li++;
      }
      $prompt = 1;
   }
   elsif ($in eq "lc") { # list comments #_cmddef
      my $ii = 0;
      foreach my $line (@cmd_list) {
         if ($line =~ /(# \S.*)$/) {
            print $ii . "> $1\n";
         }
         $ii++;
      }
   }
   elsif ($in eq "lf") { # list functions #_cmddef {
      my $ii = 0; my $found = 0;
      foreach my $line (@cmd_list) {
         if ($line =~ /#EVSF_(\w+)#/) {
            print "$ii> $line\n";
         }
         $ii++;
      }
   }
   elsif ($in =~ /^eval(.*)$/) { # evaluate #_cmddef
      my $arg = "";
      if ($1 ne "") { $arg = $1; $arg =~ s/^\s+//; }

      if ($arg ne "") {
         $cmdi = $arg;
         $cmd = $cmd_list[$cmdi];
         $cmd =~ s/^\s*#\s+//;
         $eval_print = 0;
         evaluate(); $eval_print = 1;
         print "$arg> $cmd\n";
      }
      else {
         my $ii = 0;
         foreach my $tc (@cmd_list) {
            $cmdi = $ii;
            $cmd = $cmd_list[$cmdi];
            $eval_print = 0;
            if (evaluate() == 0) { print "$ii> $cmd\n"; }
            $eval_print = 1;
            $ii++;
         }
      }

   }
   elsif ($in =~ /^end (.+)$/) { #_cmddef

      my $cargs = $1;
      while ($cargs =~ /\s*(\d+)(.*)/) {
         print "Stopping $1.\n";
         my $ci = $1;
         $cargs = $2;
         if ($cmd_list[$ci] =~ /^([\w|\/|\.|_|-]+)(.*)$/) {
            print "$sc_msg\'pkill $1':\n";
            system("pkill $1");
         }
      }
      $prompt = 1;
   }
   elsif ($in =~ /^clear(.*)$/) { # delete system calls #_cmddef

      if ($1 eq "") { # clear all #_cmddef
         print "Clearing all system calls.\n";
         @cmd_list = ();
      }
      if ($1 =~ /(\d+) ?- ?(\d+)/) { # clear range #_cmddef
         print "Clearing " . ($2 - $1 + 1) . " lines.\n";
         for (my $index = $1; $index <= $2; $index++) {
            $cmd_list[$index] = "";
         }
      }
      else {
         my $cargs = $1;
         while ($cargs =~ /\s*(\d+)(.*)/) { # clear list #_cmddef
            print "Clearing $1.\n";
            $cmd_list[$1] = "";
            $cargs = $2;
         }
      }
      $prompt = 1;
   }
   elsif ($in eq "exit" || $in eq "quit" || $in eq "leave" || $in eq "return") { #_cmddef
      print "Exiting...\n";
      $pcheck = 1;
      wait_for_children();
      exit 0;
   }
   elsif ($in =~ /^restart(.*)$/) { #_cmddef
      print "Restarting...\n";
      wait_for_children();
      print "$sc_msg\'perl $0$1':\n";
      exec("perl $0$1");
   }
   elsif ($in =~ /^evs(.*)$/) { #_cmddef

      my $env_args = $1;

      my $ea_ap = "";
      if ($env_args =~ /^(.*)evs\-(s|send)\s+(.*)$/) { #_cmddef
         $env_args = $1;
         my $line = $3;
         while ($line =~ /^\s*(\d+)(.*)/) {
            my $sidx = $1;
            $line = $2;
            $ea_ap .= "-l \"" . $cmd_list[$sidx] . "\" ";
         }

         $env_args .= $ea_ap . $line;
      }

      print "$sc_msg\'perl $0$env_args':\n";
      system("perl $0$env_args");
      wait_for_children();
   }
   elsif ($in ne "") {

      my $ii = 0; my $found = 0;
      foreach my $line (@cmd_list) {
         if ($line =~ /#EVSF_(\w+)#/) { # function syntax #_cmddef
            my $tc = $1;
            my $start = ""; my $end = "";
            if ($in =~ /^(.*)$tc/) { $start = $1; }
            if ($in =~ /$tc(.*)$/) { $end = $1; }

            if ($tc eq $in || $start ne "" || $end ne "") {
               $cmdi = $ii;
               $cmd = $start . $line . $end;
               $cmd =~ s/^\s*#\s*//;
               fcall_cmd();
               $found = 1;
               break;
            }
         }
         $ii++;
      }

      if (!$found) {
         system($unknown_cmd . " \"" . $in . "\"");
         $prompt = 1;
      }
   }
   else {
      check_children();
      print "_Enter_Command> ";
   }

   if ($prompt) {
      check_children();
      print "_Enter_Command> ";
      $prompt = 0;
   }
}

# Return 0 if command can be executed, 1 if some other action is taken.
sub evaluate {

   if ($cmd =~ /^\s*#(\D)(.++)/ && $cmd !~ /^\s*#[\+\-]/) { # comment syntax #_cmddef
      if ($eval_print = 0) { $cmd = ""; return; }
      my $arg = $1;
      my $prefix = "$cmdi> ";
      my $comment = $2;
      if ($arg eq "#") { $prefix = ""; }
      elsif ($arg ne " ") { $comment = $arg . $comment; }
      $comment =~ s/\\n/\n$prefix/g;
      if ($eval_print) { print "$prefix$comment\n"; }
      return 1;
   }

   if ($cmd =~ /#EVSP_(\w+|_+|\/+)#/) {
      if ($1 =~ /cd_(\w+|_+|\/+)/) { # internal cd symbol #_cmddef
         $chdirl = $1;
      }
   }

   if ($cmd =~ /^(.+)( # \S.*)$/) {
      $cmd = $1;
   }

   while ($cmd =~ /#EVSC_(\w+)#/) {
      my $fname = $1;
      my $found = 0;
      foreach my $line (@cmd_list) {
         my $tcmd = "";
         if ($line =~ /#EVSF_$fname\#/) {
            $tcmd = $line;

            if ($tcmd =~ /^\s*#(.)/) {
               if ($1 !~ /^[\+\-\d]/ && $1 !~ /^EVS/) {
                  $tcmd =~ s/^\s*#\s*//;
               }
            }

            $cmd =~ s/#EVSC_$fname\#/$tcmd/;
            $found = 1;
            break;
         }
      }
      if (!$found) { break; }
   }

   my $last_i = $cmdi;
   while ($cmd =~ /#(\-?\+?\d+)#/) {
      my $tci = $1;
      my $mode = "index";
      if ($tci =~ /^\+/) { $mode = "inc"; }
      if ($tci =~ /^\-/) { $mode = "dec"; }

      $tci =~ s/[\-\+]//g;

      if ($mode eq "inc") {
         $tci = $last_i + $tci;
      }
      if ($mode eq "dec") {
         $tci = $last_i - $tci;
      }

      my $tcmd = $cmd_list[$tci];

      if ($tcmd =~ /#EVSP_(\w+|_+|\/+)#/) {
         if ($1 =~ /cd_(\w+|_+|\/+)/) { # internal cd symbol #_cmddef
            $chdirl = $1;
         }
      }

      if ($tcmd =~ /^(.+)( # \S.*)$/) { # trailing comments must have spaces surrounding #_cmddef
         $tcmd = $1;
      }

      if ($tcmd =~ /^\s*#(.)/) {
         if ($1 !~ /^[\+\-\d]/ && $1 !~ /^EVS/) {
            $tcmd =~ s/^\s*#\s*//; # line combiner treats comments like a system call #_cmddef
         }
      }
      $cmd =~ s/#(\+?\-?\d+)#/$tcmd/; # line combination #_cmddef

      if ($tcmd =~ /#(\+|\-)\d+#/) {$last_i = $tci;} # line combiner enters line if symbols are found
   }

   $cmd =~ s/ ?#EVSA#//g; # argument placement #_cmddef
   $cmd =~ s/ ?#EVSF_\w+#//g;
   $cmd =~ s/ ?#EVSC_\w+#//g;
   $cmd =~ s/ ?#EVSP_(\w+|_+|\/+)#//g;

   if ($cmd =~ /^\s*$/) {
      return 1;
   }
   return 0;
}

sub fcall_cmd {

   if (evaluate()) { return; }

   if ($task_management) {
      $pid = 0;
      $pid = fork();
      if ($pid != 0) {
         push(@cpids, $pid);
         #print "EVSwitch started process $pid.\n";
         return;
      }
   }

   my $ppid = open(my $outfh, "-|", "$cmd 2>&1")
                       || die "can't fork: $!";

   push(@cpids, $ppid);

   print "$sc_msg\[id:$ppid\]\[ix:$cmdi\]: $cmd\n";

   if ($chdirl ne "") {
      sleep 1;
      chdir($chdirl) or print "EVSwitch cannot enter directory '$chdirl'.\n";
      $chdirl = "";
   }

   if (!$task_management) {
      $pid = 0;
      $pid = fork();
      if ($pid != 0) {
         push(@cpids, $pid);
         while (<$outfh>) { print; }
         close $outfh       || die "process exited: $! $?";
         $task_management = 1;
         $pcheck = 0;
         wait_for_children();
         exit 0;
      }
   }
   else {
      while (<$outfh>) { print; }
      close $outfh       || die "process exited: $! $?";
      exit 0;
   }

   return;
}

sub check_children {
   my $msg = "EVSwitch process ";
   my @tcpids = @cpids;
   my $cdidx = 0;
   foreach my $cpid (@tcpids) {
      my $rn = waitpid($cpid, WNOHANG);
      if ($rn > 0 || $rn == -1) {
         $msg .= "$cpid ";
         splice(@cpids, $cdidx, 1);
      }
      else {
         $cdidx++;
      }
   }
   $msg .= "exited. Waiting for " . ($#cpids + 1) . ".\n";

   if ($pcheck && length($msg) > 46) { print $msg; }

   return $#cpids + 1;
}

sub wait_for_children {

   while (check_children() > 0) {
      if ($pcheck) { print "EVSwitch waiting for children.\n"; }
      sleep(1);
   }
   return;
}

sub script {
   if ($in =~ /^script (r|w|ra|wa) (.++)/) { # read/write/append script #_cmddef

      if ($msf eq "") { $msf = $2; }

      my $arg = $1;
      my $name = $2;
      my $mode = "";
      if ($arg eq "w")                 { $mode = ">"; }
      if ($arg eq "r" || $arg eq "ra") { $mode = "<"; }
      if ($arg eq "wa")                { $mode = ">>"; }
      open(my $stfh, $mode, $name) or die "EVSwitch could not open $name. $!\n";

      if ($arg eq "w" || $arg eq "wa") {
         print "EVSwitch writing script to file system '$name'.\n";
         foreach my $l (@cmd_list) {
            print $stfh $l . "\n";
         }
      }
      else {
         if ($arg eq "r") { @cmd_list = (); }
         print "EVSwitch reading script from file system '$name'.\n";
         while (<$stfh>) {
            chomp $_;
            push(@cmd_list, $_);
         }
      }

      close $stfh or die "EVSwitch failed while closing $name. $!\n";
   }
   return;
}

__END__
