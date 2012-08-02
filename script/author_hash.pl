#!/usr/bin/perl -w

#
# perl author_hash.pl author.map conf.map < dblp.raw > dblp.hashed
#
my %hash;
my %conf;
my $hindex = 0;
my $cindex = 0;

my $lnum = 1;
my @lines;

while(<stdin>) {
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
			$hash{$au} = $hindex;
			push @ah, $hindex;
			++$hindex;
		}
#		$hash{$au}++;
	}
	if(defined $conf{$parts[1]}) {
		print join(',', @ah), "\t$conf{$parts[1]}\n";
		#push @lines, join(',', @ah)."\t$conf{$parts[1]}\n";
	}
	else {
		$conf{$parts[1]} = $cindex;
		print join(',', @ah), "\t$cindex\n";
		#push @lines, join(',', @ah)."\t$cindex\n";
		++$cindex;
	}
	++$lnum;
}

#print "$hindex ", $lnum - 1, "\n";
#print $_ for @lines;

## author.map, conf.map.
open HMAP, ">$ARGV[0]" or die "open $ARGV[0] fail.\n";
print HMAP "$_\t$hash{$_}\n" for sort {$hash{$a} <=> $hash{$b}} keys %hash;
close HMAP;

open CMAP, ">$ARGV[1]" or die "open $ARGV[1] fail.\n";
print CMAP "$_\t$conf{$_}\n" for sort {$conf{$a} <=> $conf{$b}} keys %conf;
close CMAP;

#print "$_, $hash{$_}\n" for sort { $hash{$b} <=> $hash{$a} } keys %hash;
