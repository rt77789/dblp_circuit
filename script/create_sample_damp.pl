#!/usr/bin/perl -w

my %user;

while(<>) {
	chomp;
	my ($u, $id) = split/\t/;
	$user{$id} = $u;
}

my @tu = keys %user;

print @tu + 0, "\n";

for my $k (sort {$a <=> $b} keys %user) {
	print "$k 1\n";
}
