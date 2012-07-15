#!/usr/bin/perl -w


### 计算autor之间的边的权重.
my %eds;
my $e_num = 0;
my $node_num = 0;

while(<>) {
	chomp;

	my @parts = split /\s+/;
	
	my @auths = split /,/, $parts[0];

	my $anum = @auths;

	for my $x (@auths) {
		$node_num = $x if $x > $node_num;

		for my $y (@auths) {
			next if $x eq $y;

#		print "$x $y\n";
			if($x > $y) {
				$eds{$y}->{$x}->[0] += 0.0;
				$eds{$y}->{$x}->[1] += 2.0 / (($anum - 1) * $anum );
			}
			else {
				$eds{$x}->{$y}->[0] += 2.0 / (($anum - 1) * $anum );
				$eds{$x}->{$y}->[1] += 0.0;
			}
		}
	}
}

for my $x (keys %eds) {
	for my $y (keys %{$eds{$x}}) {
		++$e_num; #print "$x $y $eds{$x}->{$y}->[0] $eds{$x}->{$y}->[1]\n";
	}
}

print $node_num+1, " ", $e_num, "\n";

for my $x (keys %eds) {
	for my $y (keys %{$eds{$x}}) {
		#print "$x $y $eds{$x}->{$y}\n";
		print "$x $y $eds{$x}->{$y}->[0] $eds{$x}->{$y}->[1]\n";
	}
}
