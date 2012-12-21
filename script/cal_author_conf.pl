#!/usr/bin/perl -w

###
### Compute author per conf.
###

my %conf;

while(<>) {
	chomp;

	my @parts = split /\s+/;
	
	my @auths = split /,/, $parts[0];

	my $anum = @auths;

	for my $x (@auths) {
		$conf{$parts[1]}->{$x}->[0] += 2.0 / $anum;
		$conf{$parts[1]}->{$x}->[1]++;
	}
}
my $mapp = 0;

for my $x (keys %conf) {
	for my $y (sort {$conf{$x}->{$b}->[1] <=> $conf{$x}->{$a}->[1] } keys %{$conf{$x}}) {
		$mapp = $conf{$x}->{$y}->[1] if $conf{$x}->{$y}->[1] > $mapp;
		print "$x $y $conf{$x}->{$y}->[1] $conf{$x}->{$y}->[0]\n";
	}
}


print STDERR $mapp, "\n";
