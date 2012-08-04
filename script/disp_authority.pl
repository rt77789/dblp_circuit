#!/usr/bin/perl 

##
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
		my ($id, $score) = split /\s+/;
		$authority{$id} = $score;	
	}

	for my $id (sort { $authority{$b} <=> $authority{$a} } keys %authority) {
		print $au_id2name{$id}, " ", $id, " ", $authority{$id}, "\n";
	}
}
&main;
