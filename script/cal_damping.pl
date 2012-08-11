#!/usr/bin/perl -w

###
### perl cal_damping.pl dblp.hashed conf.cate conf.map out_dir
###

my %conf_cate;
my %conf_map;

## load conf.cate file.
sub load_conf_cate {
	open CONF_CATE, "<$ARGV[1]" or die "open $ARGV[1] failed.\n";
	while(<CONF_CATE>) {
		chomp;
		my ($cate, $call) = split /\t/;
		for my $cn (split /,/, $call) {

			$conf_cate{ $conf_map{$cn} || "null" } = $cate;
			#print ">$cn<\n" unless $conf_map{$cn};
			#print ">$cn< $conf_map{$cn}\n" if $conf_map{$cn};
		}
	}
	close CONF_CATE;
}

## load conf.map file.
sub load_conf_map {
	open CONF_MAP, "<$ARGV[2]" or die "open $ARGV[2] failed.\n";
	while(<CONF_MAP>) {
		chomp;
		my ($cn, $id) = split /\s+/;
		$cn =~ tr{A-Z}{a-z};
		$conf_map{$cn} = $id;
	}
	close CONF_MAP;
}

sub cal_cate_damping {
	my $node_num = 0;

	my %au_conf_cate;
	my %au_sum;

	my $out_dir = $ARGV[3];

	open EDGE, "<$ARGV[0]" or die "open $ARGV[0] failed.\n";

	while(<EDGE>) {
		chomp;
		my ($aus, $conf) = split /\s+/;

		my @aulist = split /,/, $aus;

		for my $au (@aulist) {
			$node_num = $au if $au > $node_num;
			$au_sum{$au} += (@aulist == 1) ? 1 : 2.0 / ((@aulist - 1) * @aulist);

			#$au_conf{$au}++ if $conf eq $conf_id;

			$au_conf_cate{$conf_cate{$conf} || "null" }->{$au} += (@aulist == 1) ? 1 : 2.0 / ((@aulist - 1) * @aulist);
		}
	}

	for my $cate (keys %au_conf_cate) {
		my $fname = $cate;
		$fname =~ s{\s}{_}g;
		$fname =~ tr{A-Z}{a-z};

		open CATE, ">$out_dir/$fname.damping" or die "open $out_dir/$fname.damping failed.\n";
		print CATE $node_num+1, "\n";

		my $confs = $au_conf_cate{$cate};
		for my $k (sort { $confs->{$b} * $confs->{$b} / $au_sum{$b} <=> $confs->{$a} * $confs->{$a} / $au_sum{$a} } keys %{$confs}) {
			#print CATE $k, " ", $confs->{$k}, " ", $au_sum{$k}, " ", $confs->{$k} * $confs->{$k} / $au_sum{$k}, "\n";
			#print CATE $k, " ", $confs->{$k} * $confs->{$k} / $au_sum{$k}, "\n";
			print CATE $k, " ", $confs->{$k}, "\n";
		}
		close CATE;
	}

	close EDGE;
}

sub main {
	if($#ARGV <= 2) {
		die "perl cal_damping.pl dblp.hashed conf.cate conf.map out_dir\n";
	}
	&load_conf_map;
	&load_conf_cate;
	&cal_cate_damping;
}

&main;
