Laboratorium 3
=========


app1
----
Aplikacja pokazująca działanie mechanizmu FIFO.
Należy pokazać:
- ile danych należy wysłać, aby byfor się przepełnił,
- po jakim czasie bufor się odblokuje,
- czy można pisać do zakmniętego deskryptora

Aplikacja została zaimplementowana na sygnałach.
W celu użycia sygnału należy znając PID procesu wysłać sygnał SIGUSR1

**example usage:**
> make app1

> ./app1

> kill -10 [PID]

app2
----
Implementacja odpowiednika "|" (pipe) z bash'a.
    
**example usage:**
> make app2

> ls | wc | cat

> ./app2 -p ls -p wc -p cat

> ls

> ./app2 -p ls
