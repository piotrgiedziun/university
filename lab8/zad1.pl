#!/usr/bin/perl
# W zadanym pliku zastąpić liczby naturalne przez liczby postaci L.0
# Nie zast. liczb ujemnych, liczb. sklejonych z tesktsem.
# Założyć, że pomiędzy liczbą a znakiem przystankowym zawsze jest spacja.

my $file_path = $ARGV[0];

open FILE, "<", $file_path or die $!;

while (<FILE>) {
	while($_ =~ s/(\s|^)(\d+)(\s|$)/$1$2.0$3/o){};
	print $_; 
}

close FILE;