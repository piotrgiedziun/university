#!/usr/bin/perl
# W zadanym drzewie katalogów znajdź dowiazania symboliczne 
# wkazujące na obiekty w tym drzewie i przerobić jest
# w ten sposób, żeby ścieżka wskazująca na obiekt w dowiązaniu
# była ścieżką względną

use File::Find;
use Cwd 'realpath';
use Cwd;
use File::Basename;

$dir_path = $ARGV[0];

find(\&file, $dir_path);

sub max ($$) { $_[$_[0] < $_[1]] }

sub common_substr {
	my @path1 = split('/', $_[0]);
	my @path2 = split('/', $_[1]);
	my $loop_to = max($#path1, $#path2);
	my $length = 0;

	foreach (my $i = 1; $i < $loop_to; $i++) {
		last if ($path1[$i] ne $path2[$i]);
		$length += length($path1[$i])+1;
	}
	return substr($_[0], 0, $length);
}


sub file {
	if (-l $_) {
		my $file_name = basename(ralpath($_));
		my $to = dirname(realpath($_));
		my $from = getcwd();

		my $common_part = common_substr($from, $to);
		my $sub_to = substr($to, length($common_part), length($to));
		my $sub_from = substr($from, length($common_part), length($from));
		
		my @up_array = split('/', $sub_from);

		my $out_path = ".";
	 
		foreach (my $i = 0; $i < $#up_array; $i++) {
			 $out_path .= "/..";
		}

		$out_path .= $sub_to.'/'.$file_name;

		print "$to - $from\n";
		print "new = $out_path\n";
	}
}