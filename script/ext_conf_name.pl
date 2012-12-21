#!/usr/bin/perl -w

####
### Create the category of conf.
### 
### perl ext_conf_name.pl < cs_conf_rank.html > conf.cate
####
sub remove_br {
	$_[0] =~ s{^\s*<br>}{}i;
	$_[0] =~ s{\s*<br>$}{}i;
	$_[0];
}

sub ext_conf_name {
	my @res = split /<br>/, $_[0];

	## 去掉nbsp,以及前后空白.
	map {
	$_ =~ s{&nbsp;}{}ig;
	$_ =~ s{^\s+}{};
	$_ =~ s{\s+$}{};
#	print "in map: $_\n";
	} @res;
	
	## 过滤前缀不是\da-zA-Z的会议名字.
	@res = grep {
	$_ =~ m{^([\da-zA-Z]+):}i;
	} @res;

	## 只保留简写名字.
	map {
	$_ =~ s{^([\da-zA-Z]+):.*$}{$1}i;
	$_ =~ tr{A-Z}{a-z};
	} @res;
	return @res;
}

my $data = "";

while(<>) {
	s{\n$}{}g;
	s{\r$}{}g;
	chomp;
	$data .= $_;
}

#print $data, "\n";

my $rc = ".*?</i>(.*?)</font>.*?";

while($data =~ s@AREA:\s*(.*?)<.*?Rank\s*1:${rc}Rank\s*2:${rc}Rank\s*3:${rc}@@is) {
	my ($area, $r1, $r2, $r3) = ($1, $2, $3, $4);
	$r1 = &remove_br($r1);
	$r2 = &remove_br($r2);
	$r3 = &remove_br($r3);

	$area =~ s{\t}{ }g;

	my $confs = join ",", &ext_conf_name($r1); #, &ext_conf_name($r2), &ext_conf_name($r3);

	print $area, "\t", $confs, "\n";
#
#	for my $cn (&ext_conf_name($r1)) {
#		print "\t$1\n" if $cn =~ m{^([\da-zA-Z]+):}i;
#	}
#
#	for my $cn (&ext_conf_name($r2)) {
#		print "\t$1\n" if $cn =~ m{^([\da-zA-Z]+):}i;
#	}
#
#	for my $cn (&ext_conf_name($r3)) {
#		print "\t$1\n" if $cn =~ m{^([\da-zA-Z]+):}i;
#	}

	#print "\t$_\n" for (&ext_conf_name($r1));
	#print "\t$_\n" for (&ext_conf_name($r2));
	#print "\t$_\n" for (&ext_conf_name($r3));

	#print "$1, $2, $3, $4\n";
}
