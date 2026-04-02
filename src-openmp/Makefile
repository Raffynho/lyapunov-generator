CXX = g++
CXXFLAGS = -O3 -Wall -std=c++17 -fopenmp -pthread
# -fopenmp
TARGET_MAIN = lyapunov_gen
SRCS_MAIN = main.cpp lyapunov.cpp

# Flag per iporre il numero di thread da usare
THREADS ?= 8
# Flag per salvare l'immagine su disco (1 = Salva, 0 = Non salvare)
SAVE_IMG ?= 0
RUNS ?= 100

all: $(TARGET_MAIN)

$(TARGET_MAIN): $(SRCS_MAIN)
	$(CXX) $(CXXFLAGS) -o $(TARGET_MAIN) $(SRCS_MAIN)

run: $(TARGET_MAIN)
	./$(TARGET_MAIN)

clean:
	rm -f $(TARGET_MAIN) *.ppm benchmark_results.csv

.PHONY: full_benchmark




thread_cout_benchmark: all
	@echo "======================================================="
	@echo "   Starting constant size benchmark..."
	@echo "   Risoluzione: 2048x2048 | Ripetizioni: $(RUNS)"
	@echo "======================================================="
	@rm -f benchmark_results.csv
	@# Nota: ho rimosso l'echo dell'intestazione perché il tuo main.cpp 
	@# è già programmato per scriverla automaticamente se il file è vuoto!

	@for threads in 2 4 6 8; do \
		echo "\n---> Test con $$threads thread logici..."; \
		for i in `seq 1 $(RUNS)`; do \
			echo "     Esecuzione $$i di $(RUNS)..."; \
			OMP_NUM_THREADS=$$threads ./$(TARGET_MAIN) "ConstSize_$$threads_Core" 2048 2048 ABBA 800 800 0 > /dev/null; \
		done; \
	done
	
	@echo "\n======================================================="
	@echo "   Benchmark completato! Dati in benchmark_results.csv"
	@echo "======================================================="


# Test con risoluzione fissa e aumento del numero di iterazioni
scale_compute_benchmark: all
	@echo "======================================================="
	@echo "   Starting variable size benchmark..."
	@echo "   Risoluzione: 2048x2048 | Ripetizioni: $(RUNS)"
	@echo "======================================================="
	@rm -f benchmark_results.csv
	
	@for iter in 500 1000 2000 4000 8000; do \
		echo "\n---> Test con densità matematica: $$iter iterazioni..."; \
		for i in `seq 1 $(RUNS)`; do \
			OMP_NUM_THREADS=$(THREADS) ./$(TARGET_MAIN) "Iter_$$iter" 2048 2048 ABBA $$iter $$iter 0 > /dev/null; \
		done; \
	done

	@echo "\n======================================================="
	@echo "   Benchmark completato! Dati in benchmark_results.csv"
	@echo "======================================================="