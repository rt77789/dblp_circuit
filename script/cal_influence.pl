#!/usr/bin/perl -w

my $dir = $ARGV[0];
my %si;
my %refs;
my %paper_author;
my %map;
my $algo_type = "si";

sub read_socail_influence {

	for my $f (`ls $dir/*.si`) {
		chomp $f;
		open IN, "<$f" or die "open $f failed...\n";
		while(<IN>) {
			my ($u, @tk) = split /\s+/;
			for my $p (@tk) {
				my ($v, $tsi) = split /:/, $p;
				$si{$u}->{$v} = $tsi;
				#print "($u,$v,$tsi)\n";
			}
		}
		close IN;
	}

}

sub read_citation {
	open C, "<$dir/citation.data" or die "open $dir/citation.data failed...\n";
	while(<C>) {
		chomp;
		my ($id, $line, $num) = split /\t/;
		my @tk = split /,/, $line;
		for my $k (@tk) {
			if(defined $refs{$k}) {
				push @{$refs{$k}}, $id;
			}
			else {
				$refs{$k} = [$id];
			}
			#$refs{$k} = $id;
		}
		#$refs{$id} = \@tk;
	}
	close C;
}

sub read_author_map {

	open MAP, "<$dir/acm_author.map" or die "open $dir/acm_author.map failed.\n";
	while(<MAP>) {
		chomp;
		my ($user, $id) = split /\t/;
		$map{$user} = $id;
	}

	close MAP;
}

sub read_paper_author {
	open PA, "<$dir/paper.authors" or die "open $dir/paper.authors failed...\n";
	while(<PA>) {
		chomp;
		my ($pid, $line) = split /\t/;
		my @tk = split /,/, $line;
		
		for my $au (@tk) {
			$paper_author{$pid}->{$map{$au}}++; # = $map{$au};
		}
	}
	close PA;
}

sub cal_si_dfs {
	
	for my $k (sort {$a <=> $b} keys %refs) {
		my %temp;
		my $flag = 0;
		for my $rf (@{$refs{$k}}) {
			my $si = 0;
			my $max_author = 0;

			if($algo_type eq "dfs") {
				$si = 100000000;
				for my $pu1 (keys %{$paper_author{$rf}}) {
					my $ssi = 100000000;
					for my $pu2 (keys %{$paper_author{$k}}) {
#					print STDERR "$pu1,$pu2,$si{$pu2}->{$pu1}\n";
						my $tsi = $si{$pu2}->{$pu1};
						if($tsi < $si) {
							$si = $tsi;
							$max_author = $pu1;
						}
					}
				}
			}
			elsif($algo_type eq "si") {
				$si = 0;
				$max_author = 0;

				#print STDERR "$k,$rf\n";
				for my $pu1 (keys %{$paper_author{$rf}}) {
					my $ssi = 0;
					for my $pu2 (keys %{$paper_author{$k}}) {
#					print STDERR "$pu1,$pu2,$si{$pu2}->{$pu1}\n";
						$ssi += $si{$pu2}->{$pu1};
					}
					if($ssi > $si) {
						$si = $ssi;
						$max_author = $pu1;
					}
				}
			}
			$temp{$rf}->[0] = $si;
			$temp{$rf}->[1] = $max_author;
		}
		for my $rf (sort { $temp{$b} <=> $temp{$a} } keys %temp) {
			#print "$k,$rf,$temp{$rf}->[0],$temp{$rf}->[1]\n";
			print "$k,$rf,$temp{$rf}->[0]\n"; #,$temp{$rf}->[1]\n";
		}
	}
}

sub main {
	print STDERR "read_citation\n";
	&read_citation;
	print STDERR "read_author_map\n";
	&read_author_map;
	print STDERR "read_paper_author\n";
	&read_paper_author;
	print STDERR "read_socail_influence\n";
	&read_socail_influence;

	print STDERR "cal_si_dfs\n";	
	&cal_si_dfs;
}

&main;
