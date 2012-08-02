#!/usr/bin/perl -w


my $node_num = 0;
my $conf_id = 4284;

my %au_conf;
my %au_sum;

while(<>) {
	chomp;
	my ($aus, $conf) = split /\s+/;

	for my $au (split /,/, $aus) {
		$node_num = $au if $au > $node_num;
		$au_sum{$au}++;			
		#print "<${conf}> <${conf_id}>";
		$au_conf{$au}++ if $conf eq $conf_id;
	}
}

print $node_num+1, "\n";
#for my $k (sort { $a <=> $b } keys %au_conf) {
for my $k (sort { $au_conf{$b} * $au_conf{$b} / $au_sum{$b} <=> $au_conf{$a} * $au_conf{$a} / $au_sum{$a} } keys %au_conf) {
	#print $k, " ", $au_conf{$k} / $au_sum{$k}, "\n";
	print $k, " ", $au_conf{$k}, " ", $au_sum{$k}, " ", $au_conf{$k} * $au_conf{$k} / $au_sum{$k}, "\n";
}
