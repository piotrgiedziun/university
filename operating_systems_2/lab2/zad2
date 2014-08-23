#!/bin/bash
# ============================
# Kopia zadango katalogu w zadanym miejscu tak, aby wszytkie dowiazania
# symbloiczne w kopii wskazywały na te same obiekty co w katalogu pierwotnym
# ============================
# example:
# ./zad2 .
# ============================

if [ $# -ne 2 ]; then
    echo Błędna ilość argumetów
    exit
fi

if [ ! -d $1 ]; then
    echo Błędny katalog pierwotny
    exit
fi

if [ ! -d $2 ]; then
    echo Błędny katalog docelowy
    exit
fi

for file in $1/*; do
    if [ -h $file ]; then
        echo copied link $file
         filepath=$(readlink -f $file)
           ln -sf $filepath $2/$file
    elif [ -f $file ]; then
        echo coppied $file
        cp $file $2/$file
    fi
done
