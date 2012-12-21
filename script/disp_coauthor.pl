#!/usr/bin/perl 


#
# A script which disp the (degree, edge weight 1, edge weight 2) of current node w.r.t input author name.
# perl disp_coauthor.pl auth.map edges.info 'yi zheng'
#

my %au2id;
my %id2au;

sub load_author {
	open IN, "<$_[0]" or die "open $_[0] fail.";
	while(<IN>) {
		chomp;
		my ($au, $id) = split /\t/;
		$au2id{$au} = $id;
		$id2au{$id} = $au;
	}
	close IN;
}

sub main {
	die "usage: perl disp_coauthor.pl auth.map edges.info 'yi zheng' " if $#ARGV < 2;
	#print "<$_>\n" for @ARGV;

	&load_author($ARGV[0]);
	open EDGE, "<$ARGV[1]" or die "open $ARGV[1] failed.\n";

	<EDGE>;
	while(<EDGE>) {
		chomp;
		my ($u, $v, $w1, $w2) = split /\s+/;
		if($u eq $au2id{$ARGV[2]}) {
			print "$id2au{$v}\t$w1\t$w2\n";
		}
		#$edges{$u} = "$id2au{$v} $w1 $w2";
	}
}

&main;
