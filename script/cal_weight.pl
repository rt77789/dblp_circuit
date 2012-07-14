#!/usr/bin/perl -w


### 计算autor之间的边的权重.
my %eds;

while(<>) {
	chomp;

	my @parts = split /\s+/;
	
	my @auths = split /,/, $parts[0];

	my $anum = @auths;

	for my $x (@auths) {
		for my $y (@auths) {
			next if $x eq $y;
#		print "$x $y\n";
			$eds{$x}->{$y} += 2.0 / (($anum - 1) * $anum );
		}
	}
}


for my $x (keys %eds) {
	for my $y (keys %{$eds{$x}}) {
		print "$x $y $eds{$x}->{$y}\n";
	}
}
