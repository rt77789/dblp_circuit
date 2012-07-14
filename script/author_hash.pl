#!/usr/bin/perl -w

my %hash;
my %conf;
my $hindex = 0;
my $cindex = 0;

my $lnum = 1;
while(<>) {
	chomp;
	my @parts = split /\t/, $_, 3;
	die "parts number != 3, line num: $lnum\n" if $#parts != 2;

	my @auths = split /,/, $parts[0];
	my @ah;

	for my $au (@auths) {
		if(defined $hash{$au}) {
			push @ah, $hash{$au};
		}
		else {
			++$hindex;
			$hash{$au} = $hindex;
			push @ah, $hindex;
		}
		$hash{$au}++;
	}
	if(defined $conf{$parts[1]}) {
		print join(',', @ah), "\t$conf{$parts[1]}\n";
	}
	else {
		++$cindex;
		$conf{$parts[1]} = $cindex;
		print join(',', @ah), "\t$cindex\n";
	}
	++$lnum;
}

open HMAP, ">author.map" or die "open author.map fail.\n";
print HMAP "$_\t$hash{$_}\n" for sort {$hash{$a} <=> $hash{$b}} keys %hash;
close HMAP;

open CMAP, ">conf.map" or die "open conf.map fail.\n";
print CMAP "$_\t$conf{$_}\n" for sort {$conf{$a} <=> $conf{$b}} keys %conf;
close CMAP;

#print "$_, $hash{$_}\n" for sort { $hash{$b} <=> $hash{$a} } keys %hash;
