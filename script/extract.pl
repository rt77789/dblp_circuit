#!/usr/bin/perl -w

my $paper = '';

sub dblper {
	my $data = $_[0];
	my $res;
	while($data =~ s{<author>(.*?)</author>}{}) {
		$res .= "," if $res;
		$res .= "$1";
	}

	## 没有作者 的跳过!
	return unless $res;

	$res .= "\t";

	if($data =~ m{<journal>(.*?)</journal>}is) {
		$res .= $1;
	}
	#elsif($data =~ m{<booktitle>(.*?)</booktitle>}is) {
	elsif($data =~ m{<inproceedings\s+.*?\s+key="conf/([^/]+).*?">}is) {
		$res .= $1;
	}

	$res .= "\t";
	if($data =~ m{<title>(.*?)</title>}is) {
		$res .= $1; 
	}

	print $res, "\n";
}

sub main {

	while(<>) {
		chomp;
		#if(m{</article>} || m{</inproceedings>}) {
		if(m{<article}) {
			$paper = $_;
		}
		elsif(m{<inproceedings}) {
			$paper = $_;
		}
		elsif(m{</article>}) {
			&dblper($paper);
			$paper = '';
		}
		elsif(m{</inproceedings>}) {
			### 
			#	print $paper, "--\n";	
			&dblper($paper);
			$paper = '';
		}
		else {
			$paper .= $_;
		}
	}
}

&main;


