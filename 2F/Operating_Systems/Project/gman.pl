#!/usr/bin/perl -w
use strict;

if (@ARGV != 2) {
  print <<_EOF_;
Content-type: text/html

<html><head><title>gman.pl: invalid use</title></head>
<body>
<h1>gman.pl cannot be used without arguments.</h1>
</body></html>
_EOF_
  die;
}

my $section = $ARGV[0]; # should also have some sanity check
my $name = $ARGV[1];
my $man2html = "/usr/lib/cgi-bin/man/man2html";
my $path = `man -w $section $name`; chomp $path; $path =~ s/\s*$//;

unless (-s "$path") {
  warn "not -s $path\n";
  $name = lc $name;
  $path = `man -w $section $name`; chomp $path; $path =~ s/\s*$//;
}
unless (-s "$path") {
  warn "not -s $path\n";
	print <<end_of_line;
Content-type: text/html

<!DOCTYPE HTML PUBLIC "-//IETF//DTD HTML 2.0//EN">
<HTML><HEAD>
<TITLE>404 Not Found</TITLE>
</HEAD><BODY>
<H1>Not Found</H1>
The requested man page $name($section) was not found on this server.
</BODY></HTML>
end_of_line
	die;
}

unless (-e "$man2html") {
  warn "$man2html missing\n";
	print <<end_of_line;
Content-type: text/html

<!DOCTYPE HTML PUBLIC "-//IETF//DTD HTML 2.0//EN">
<HTML><HEAD>
<TITLE>man2html missing</TITLE>
</HEAD><BODY>
<H1>man2html missing</H1>

<p>You have to install <tt>man2html</tt> in order to use this mode in gman.

</BODY></HTML>
end_of_line
	die;
}

my $page = `$man2html $path`;

# $page =~ s/^Content-type: text\/html\n\n// if (not run as cgi...);

$page =~ s/(This document was created by\n<a HREF=\".*\">man2html<\/a>)(,\nusing the manual pages.<br>)/$1 for <a href=\"\/cgi-bin\/gman.pl?1+gman\">gman<\/a>$2/io;

print $page;
