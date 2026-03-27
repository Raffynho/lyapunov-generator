# lyapunov-generator
 
# Programma CPU 

## Compilatore 

Il Makefile e' configurato con compilatore di default con **g++** 

## Compilare il programma 

All'interno del Makefile sono configurati tutti i comandi di compilazione quindi, se configurato il compilatore, una volta navigato all'interno della giusta directory tramite il comando 

```{bash}
cd C:/Users/.../lyapunov-generator/src-cpu
```

basta usare il comando 

```{bash}
make
```

se non funziona si Windowa potrebbe essere 

```{bash}
mingw32-make
```

## Bentchmark 

Il comando Bentchmark permette di eseguire una serie di comandi per automatizzare l'esecuzione del programma 

```{bash}
make bentchmark
```

# Test 

All'interno del makefile sono presenti dei flag per modificare in numero di thread usati per l'esecuzione quindi per fare il test ne varieremo il numero per vedere come cambiano le prestazioni

```{bash}
make bentchmark THREADS=1
make bentchmark THREADS=2
make bentchmark THREADS=4
make bentchmark THREADS=6
make bentchmark THREADS=8
```

o 

```{bash}
make bentchmark THREADS=1
make bentchmark THREADS=2
make bentchmark THREADS=4
make bentchmark THREADS=6
make bentchmark THREADS=8
```

i risultati dei test verranno salvati in un file scv chiamato `betchmark_results.csv`