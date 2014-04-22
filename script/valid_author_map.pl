#!/usr/bin/perl -w

#
# perl valid_author_map.pl build2/data/dblp_author.map build2/data/valid_authors.data
#


open MAP, "<$ARGV[0]" or die "open $ARGV[0] failed.\n";
open VA, "<$ARGV[1]" or die "open $ARGV[1] failed.\n";
while(<MAP>) {
	chomp;
	my ($user, $id) = split /\t/;
	$map{$user} = $id;
}
while(<VA>) {
	chomp;
	my ($user, $num) = split /,/;
	print "$map{$user}\n";
}
close VA;
close MAP;
