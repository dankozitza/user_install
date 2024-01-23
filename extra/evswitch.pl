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
my $wd = $ENV{PWD} . "/";
my $init_wd = $wd;
my $pcheck = 1;
my @cmd_list = ();
my $chdirl = "";
my $post_chdirl = "";
my $sc_msg = "EVSwitch system call ";
my $prompt_msg = "_Enter_Command> ";
my $unknown_cmd = "/usr/bin/sh -c";
my $task_management = 0;
my $verbose =  0;
my @cpids  = ();
my $cmdi   = 0;
my $cmd    = "";
my $in     = "";
my $msf    = "";
my $script = "";
my $stpath = "";
my $pid    = 0;
my $idx = -1;
my $eval_print = 1;

my $collectverbose = 0;
foreach my $arg (@ARGV) {

   if ($collectverbose) {
      $verbose = $arg;
      $collectverbose = 0;
      next;
   }

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

   if ($arg eq "-v") {
      $collectverbose = 1;
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
      $msf = $arg;
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

if ($verbose > 4) {
   print "EVSwitch environment: $0\n";
   my @keys = keys %ENV;
   foreach my $key (@keys) {
      print "   $key -> $ENV{$key}\n";
   }
}

$cmdi = 0;
foreach my $cmdp (@cmd_list) {
   $cmd = $cmdp;
   fcall_cmd();
   $cmdi++;
}

print "EVSwitch entering interactive mode.";
print "\n";

my $prompt = 0;
while (1) {

   if ($prompt) {
      check_children();
      print $prompt_msg;
      $prompt = 0;
   }

   $in = "";
   $in = readline(STDIN);
   chomp $in;

   if ($in eq "help" || $in eq "h" || $in eq "?") {
      print "\nEVSwitch commands:\n
   <index><s|n> [options] - Run system call at index.
   <size><s|n> [command]  - Define new system call.
   list                   - List system calls.
   lf                     - List functions.
   lc                     - List comments.
   eval [index]           - Evaluate and print one or all system calls.
   export [filename.sh]   - Evaluate system calls, write functions and bash profile to file system.
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
            my $func = $1;
            my $l = $line;
            $l =~ s/ ?#EVSA#//g;
            $l =~ s/ ?#EVSF_\w+#//g;
            print "\[$ii\]\[$func\]> $l\n";
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
         $cmd =~ s/^#\s+//;
         $eval_print = 0;
         evaluate(); $eval_print = 1;
         print "$arg> $cmd\n";
      }
      else {
         my $ii = 0;
         foreach my $tc (@cmd_list) {
            $cmdi = $ii;
            $cmd = $cmd_list[$cmdi];
            my $fname = "";

            if ($cmd =~ /#EVSF_(\w+)#/) { $fname = $1; $cmd =~ s/^#\s+//; }

            $eval_print = 0;
            if (evaluate() == 0 && $cmd ne "") {
               if ($fname ne "") { print "\[$ii\]\[$fname\]> $cmd\n"; }
               else              { print "\[$ii\]> $cmd\n"; }
            }
            $eval_print = 1;
            $ii++;
         }
      }

   }
   elsif ($in =~ /^expor(t.*)$/) { # export a bash environment #_cmddef
      my $arg = $1;
      my $filename = "";
      if ($arg =~ /^t\s+/) {
         $arg =~ s/^t\s+//;

         if ($arg =~ /^\//) {
            $filename = $arg;
         }
         else {
            $filename = $stpath . $arg;
         }
      }
      else {
         $filename = $stpath . $script;
      }

      if ($filename eq "") {
         print "EVSwitch export Usage: export [script.evss]\n";
      }
      else {
         if ( ! -d "$filename" ) {
            print "$sc_msg\'mkdir $filename\'.\n";
            system("mkdir $filename");
         }

         if ($wd ne $filename) {
            print "EVSwitch moving into directory $filename\n";
            chdir($filename) or die "EVSwitch cannot enter directory '$filename'.";
            $wd = $filename;
         }

         # export directory is cwd begin building bash scripts
      }

      $prompt = 1;
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
   elsif ($in =~ /^evs-clear(.*)$/) { # delete system calls #_cmddef

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
   elsif ($in =~ /^restar(t.*)$/) { #_cmddef
      print "Restarting...\n";
      my $arg = $1;

      if ($arg ne "t") {
         $arg =~ s/^t\s+//;
      }
      else {
         $arg = $stpath . $script . ".evss";
      }

      wait_for_children();

      chdir($init_wd);
      print "$sc_msg\'perl $0 $arg':\n";
      exec("perl $0 $arg");
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
            if ($in =~ /^(.*) $tc /) { $start = $1; }
            if ($in =~ /^(.*) $tc$/) { $start = $1; }
            if ($in =~ / $tc (.*)$/) { $end = $1; }
            if ($in =~ /^$tc (.*)$/) { $end = $1; }

            if ($tc eq $in || $start ne "" || $end ne "") {
               $cmdi = $ii;
               $cmd = $start . $line . $end;
               $cmd =~ s/^\s*#\s+//;
               fcall_cmd();
               $found = 1;
               break;
            }
         }
         $ii++;
      }

      if (!$found) {

         if ( -f $in ) {
            system("cat $in");
         }
         else {
            system($unknown_cmd . " \"" . $in . "\"");
         }
         $prompt = 1;
      }
   }
   else {
      check_children();
      print $prompt_msg;
   }


}

# Return 0 if command can be executed, 1 if some other action is taken.
sub evaluate {

   if ($cmd =~ /^#( |\!)(.++)/) { # comment syntax #_cmddef
      if ($eval_print == 0) { $cmd = ""; return; }
      my $prefix = "$cmdi> ";
      my $comment = $2;
      $comment =~ s/\\n/\n$prefix/g;
      print "$prefix$comment\n";
      return 1;
   }

   if ($cmd =~ /#EVSP_(\w+|_+|\/+)#/) {
      if ($1 =~ /cd_(\w+|_+|\/+)/) { # internal cd symbol #_cmddef
         $chdirl = $1;
      }
      if ($1 =~ /cdp_(\w+|_+|\/+)/) { # internal post system call cd symbol #_cmddef
         $post_chdirl = $1;
      }
      $cmd =~ s/ ?#EVSP_(\w+|_+|\/+)#//;
   }

   while ($cmd =~ /^(.+)( # \S.*)$/) {
      $cmd = $1;
   }

   my $symbol = "";
   my $last_i = $cmdi;

   my $T = 1;
   while ($T) {

      my $tci = "";
      my $fname = "";

      if ($cmd =~ /#EVSP_(\w+|_+|\/+)#/) { # duplicate above
         if ($1 =~ /cd_(\w+|_+|\/+)/) {
            $chdirl = $1;
         }
         if ($1 =~ /cdp_(\w+|_+|\/+)/) {
            $post_chdirl = $1;
         }
         $cmd =~ s/ ?#EVSP_(\w+|_+|\/+)#//;
      }

      if ($cmd =~ /#(\-?\+?\d+)#/) { $tci = $1; $symbol = "index"; }
      elsif ($cmd =~ /#EVSC_(\w+)#/) { $fname = $1; $symbol = "function"; }
      else { $T = 0; $symbol = "exit"; }

      if ($symbol eq "index") {

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


         if ($tcmd =~ /^(.+)( # \S.*)$/) { # trailing comments must have spaces surrounding #_cmddef
            $tcmd = $1;
         }

         if ($tcmd =~ /^# /) {
            $tcmd =~ s/^#\s+//; # line combiner treats commented lines like system calls #_cmddef
         }
         $cmd =~ s/#(\+?\-?\d+)#/$tcmd/; # line combination #_cmddef

         if ($tcmd =~ /#(\+|\-)\d+#/) {$last_i = $tci;} # line combiner enters line if + or - symbols are found
      }
      elsif ($symbol eq "function") {

	    my $found = 0;
	    foreach my $line (@cmd_list) {
	       my $tcmd = "";
	       if ($line =~ /#EVSF_$fname\#/) {
	          $tcmd = $line;

               if ($tcmd =~ /^(.+)( # \S.*)$/) {
                  $tcmd = $1;
               }

               if ($tcmd =~ /^# /) {
                  $tcmd =~ s/^#\s+//;
               }

	          $cmd =~ s/#EVSC_$fname\#/$tcmd/;
	          $found = 1;
	       }
	    }
	    if (!$found) { die "Command $fname has not been defined.\n"; }
      }
      else {
         $T = 0;
      }
   }

   $cmd =~ s/ ?#EVSA#//g;
   $cmd =~ s/ ?#EVSF_\w+#//g;
   $cmd =~ s/ ?#EVSC_\w+#//g;

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

   if ($chdirl ne "") {
      chdir($chdirl) or print "EVSwitch cannot enter directory '$chdirl'.\n";
      $chdirl = "";
   }

   print "$sc_msg\[ix:$cmdi\]: $cmd\n";

   my $ppid = open(my $outfh, "-|", "$cmd 2>&1")
                       || die "can't fork: $!";

   push(@cpids, $ppid);

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

   if ($post_chdirl ne "") {
      while (!chdir($post_chdirl)) {
         print "$post_chdirl...\n";
         sleep(1);
      }
      $post_chdirl = "";
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

      my $arg = $1;
      my $name = $2;

      if ($msf eq "") { $msf = $2; }

      if ($msf =~ /^\/\w+$/) {
         $msf = "/" . $msf;
      }

      if ($msf =~ /^\/(\/|\w+)\/(.+)$/) {
         $stpath = $1 . "/";
         $script = $2;
         $script =~ s/\.evss$//; # evss file descriptor is stripped during export #_cmddef
         $script =~ s/\.\///;
         if ($stpath eq "") { $stpath = $wd; }
      }
      else {
         $script = $name;
         $script =~ s/\.evss$//;
         $script =~ s/\.\///;
         $stpath = $wd;
      }

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
