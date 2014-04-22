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
my %refs;
while(<VA>) {
	chomp;
	my ($cited, $citing, $num) = split /,/;
	$refs{$map{$cited}}->{$map{$citing}}++;
	#print "$map{$cited}\t$map{$citing}\n";
}

for my $cd (sort { $a <=> $b } keys %refs) {
	my @citings = sort { $a <=> $b } keys %{$refs{$cd}};
	print "$cd\t", $#citings + 1, "\t", join("\t", @citings);
}
close VA;
close MAP;
