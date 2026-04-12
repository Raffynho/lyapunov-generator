# lyapunov-generator
 
# Programma CPU 

## Compilatore 

Il Makefile e' configurato con compilatore di default con **g++** quindi per compilare su Windows bisona installare [Mingw](https://github.com/msys2/msys2-installer/releases/download/2026-03-22/msys2-x86_64-20260322.exe).

Una volta installato si puo' controllare che sia andato tutto a buon fine tramite il comando:

```{bash}
g++ --version
```

## Compilare il programma 

Se si e' su windoe all'interno della cartella `src-openmp` bisogna eliminare il documento chiamato `Makefile` e rinominare quello chiamato `Makefile_windows` in `Makefile` (documento Makefile non ha estesione)

Muoversi in `src-openmp` con il comando `cd` ed eseguere 

```{bash}
mingw32-make
```

per compilare.

# Test 

Ci sono due test da fare `thread_count_bentchmark` e `scale_compute_benchmark` (per piu' informazioni leggere report.pdf) ogni test all'interno dei benchmark viene eseguita un default di 100 volte modificabili tramite il flag `RUNS` ad esempio si puo' fare:

```{bash}
mingw32-make thread_count_benchmark RUNS=50
```
e dopo aver salvato il csv contenente il risultato 

```{bash}
mingw32-make scale_compute_benchmark RUNS=50
```


