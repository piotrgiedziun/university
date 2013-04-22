#!/usr/bin/perl
# w zadanym drzewie katalogów znajdź pliki regularne
# do których ktokolwiek ma atrybut wykonywania
# przynajmniej 10kb wielkości
# plik ma makysymalnie jedno rozszerzenie ( jedna kropke - jesli zaczyna sie od kropki - to nie jest ona rozszerzeniem)

use File::Find;
use File::stat;

$dir_path = $ARGV[0];

find(\&file, $dir_path);

sub size_in_kb {
    my $size_in_bytes = shift;
    return $size_in_bytes / 1024;
}

sub file {
    local $st = stat($_);
    if( $_ =~ /^?(\.|.)[^.]+$/ && $st->mode & 0111 && size_in_kb($st->size) > 10) {
        print $File::Find::name, "\n";    
    }
}