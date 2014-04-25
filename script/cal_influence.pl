#!/usr/bin/perl -w

my $dir = $ARGV[0];
my %si;

for my $f (`ls $dir/*.si`) {
	chomp $f;
	print "$f\n";
	open IN, "<$f" or die "open $f failed...\n";
	while(<IN>) {
		my ($u, @tk) = split /\s+/;
		for my $p (@tk) {
			my ($v, $tsi) = split /:/, $p;
			$si{$u}->{$v} = $tsi;
			print "($u,$v,$tsi)\n";
		}
	}
	close IN;
}

for my $u (sort { $a <=> $b } keys %si) {
	for my $v (sort {$a <=> $b} keys %{$si{$u}}) {
		print "($u,$v,$si{$u}->{$v})\n";
	}
}
