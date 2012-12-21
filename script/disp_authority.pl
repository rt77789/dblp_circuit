#!/usr/bin/perl 

##
## A script which display 
## perl disp_authority.pl authority.info author.map
##

my %au_id2name;
my %authority;

## load author.map file.
sub load_author_map {
	open AU_MAP, "<$_[0]" or die "open $_[0] failed.\n";
	while(<AU_MAP>) {
		chomp;
		my ($cn, $id) = split /\t/;
		$au_id2name{$id} = $cn;
	}
	close AU_MAP;
}

sub main {
	if($#ARGV != 0) {
		die "perl disp_authority.pl authority.info author.map\n";
	}
	#print $#ARGV, "\n";

	&load_author_map($ARGV[0]);

	while(<stdin>) {
		chomp;
		my ($id, $score, $degree) = split /\s+/;
		$authority{$id}->[0] = $score;	
		$authority{$id}->[1] = $degree;	
	}

	for my $id (sort { $authority{$b}->[0] <=> $authority{$a}->[0] } keys %authority) {
		print $au_id2name{$id}, "\t", $id, "\t", $authority{$id}->[1], "\t", $authority{$id}->[0], "\n";
	}
}
&main;
