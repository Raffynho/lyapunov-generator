CXX = g++
CXXFLAGS = -fopenmp 

TARGET_MAIN = lyapunov_gen
SRCS_MAIN = main.cpp lyapunov.cpp

# Flag per salvare l'immagine su disco (1 = Salva, 0 = Non salvare)
SAVE_IMG ?= 0
RUNS ?= 50

THREADS ?= 8
THREAD_LIST ?= 2 4 6 8

all: $(TARGET_MAIN)

$(TARGET_MAIN): $(SRCS_MAIN)
	$(CXX) $(CXXFLAGS) -o $(TARGET_MAIN) $(SRCS_MAIN)

run: $(TARGET_MAIN)
	./$(TARGET_MAIN) 

clean:
	rm -f $(TARGET_MAIN) *.ppm benchmark_results.csv


.PHONY: thread_count_benchmark scale_compute_benchmark chunk_benchmark clean schedule_benchmark

# Test problema costante al variare del nuemro di threads 
thread_count_benchmark: all
	@echo "======================================================="
	@echo "   Starting constant size benchmark..."
	@echo "   Risoluzione: 2048x2048 | Ripetizioni: $(RUNS)"
	@echo "======================================================="
	
	@for threads in $(THREAD_LIST); do \
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
	
# Varia risoluzione dell'immagine con numero basso di iterazioni per testare la cache
cache_wss_benchmark: all
	@echo "======================================================="
	@echo "   Starting Working (Cache) Benchmark"
	@echo "   Threads: $(THREADS) | Ripetiizoni: $(RUNS)"
	@echo "======================================================="
	@rm -f benchmark_results.csv
	
	@# Dimensioni crescenti per occupare la cache
	@# 512x512 = ~768 KB 
	@# 1024x1024 = ~3 MB 
	@# 4096x4096 = ~50 MB 
	@# 8192x8192 = ~200 MB 
	@for size in 512 1024 2048 4096 8192; \
	do \
		echo "\n---> Test Dimensione: $$size x $$size..."; \
		for i in `seq 1 50`; \
		do \
			OMP_NUM_THREADS=8 ./$(TARGET_MAIN) "Cache_Size_$$size" $$size $$size ABBA 10 10 0 > /dev/null; \
		done; \
	done
	
	@echo "\n======================================================="
	@echo "   Benchmark completato! Dati in benchmark_results.csv"
	@echo "======================================================="

# Varia la dimensione dei chunk
chunk_benchmark: all
	@echo "======================================================="
	@echo "   BENCHMARK DIMENSIONE CHUNK (Static Schedule)"
	@echo "   Risoluzione: 2000x2000 | Thread: $(THREADS) | Ripetizioni: $(RUNS)"
	@echo "======================================================="
	@rm -f benchmark_results.csv
	
	@for chunk in 1 16 64 256 512; do \
			echo "\n---> Test con Chunk Size: $$chunk..."; \
			for i in `seq 1 $(RUNS)`; do \
				./$(TARGET_MAIN) "Chunk_$$chunk" 2048 2048 ABBA 800 800 0 > /dev/null; \
			done; \
		done
	
	@echo "\n======================================================="
	@echo "   Benchmark completato! Dati in benchmark_results.csv"
	@echo "======================================================="

# Come thread_count_benchmark solo che varia tipo di schedule
schedule_benchmark: all
	@echo "======================================================="
	@echo "   Starting SCHEDULE TYPE Benchmark"
	@echo "   Risoluzione: 2000x2000 | Threads: $(THREADS) | Ripetizioni: $(RUNS)"
	@echo "======================================================="
	@rm -f benchmark_results.csv
	
	@# Iteriamo tra i tre tipi principali (senza specificare il chunk per usare il default)
	@for sched in static dynamic guided; do \
		echo "\n---> Test Scheduling: $$sched..."; \
		for i in `seq 1 $(RUNS)`; do \
			OMP_SCHEDULE="$$sched" ./$(TARGET_MAIN) "Sched_$$sched" 2000 2000 ABBA 2000 2000 0 > /dev/null; \
		done; \
	done
	
	@echo "\n======================================================="
	@echo "   Benchmark completato! Dati in benchmark_results.csv"
	@echo "======================================================="

# Comando che permette di vedere il numero di cache miss
cache_hardware_test: all
	@echo "Misurazione hardware dei Cache Misses"
	perf stat -e L1-dcache-load-misses,LLC-load-misses,LLC-store-misses ./$(TARGET_MAIN) "Perf_HighIter" 2048 2048 ABBA 800 800 0
	perf stat -e L1-dcache-load-misses,LLC-load-misses,LLC-store-misses ./$(TARGET_MAIN) "Perf_LowIter" 8192 8192 ABBA 10 10 0