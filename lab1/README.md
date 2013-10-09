Laboratorium 1
=========


app1
----
Utworzenie procesu potomnego oraz użycie flagi -D w gcc.

**example usage:**
> make app1

> ./app1

app2
----
Aplikacja w dwóch wariantach. Pierwsza otwiera podaną liczbę procesów szeregowo, druga równolegle.
Parametry aplikacji mają być przekazane funkcją getopt (c - ilość procesów (count), r - tryb działania aplikacji (z parametrem "-r" wersja rekurencyjna))
    
**example usage:**
> make app2

> ./app2 -c 10 -r
> ./app2 -c 10