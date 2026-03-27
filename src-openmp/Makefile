CXX = g++
CXXFLAGS = -O3 -Wall -std=c++17 -fopenmp -pthread

TARGET_MAIN = lyapunov_gen
SRCS_MAIN = main.cpp lyapunov.cpp

# --- VARIABILI CONFIGURABILI DA TERMINALE ---
RUNS ?= 5
THREADS ?= 8
# Flag per salvare l'immagine su disco (1 = Salva, 0 = Non salvare)
SAVE_IMG ?= 0

all: $(TARGET_MAIN)

$(TARGET_MAIN): $(SRCS_MAIN)
	$(CXX) $(CXXFLAGS) -o $(TARGET_MAIN) $(SRCS_MAIN)

run: $(TARGET_MAIN)
	./$(TARGET_MAIN)

clean:
	rm -f $(TARGET_MAIN) *.ppm benchmark_results.csv


benchmark: all
	@echo "======================================================="
	@echo "   BENCHMARK SCALABILITA' (RISOLUZIONE FISSA 2000x2000)"
	@echo "   Thread: $(THREADS) | Ripetizioni: $(RUNS) | Salva Immagine: $(SAVE_IMG)"
	@echo "======================================================="
	
	@echo "\n---> TEST 1"
	@for i in `seq 1 $(RUNS)`; do \
		echo "     Esecuzione $$i di $(RUNS) con $(THREADS) thread..."; \
		OMP_NUM_THREADS=$(THREADS) ./$(TARGET_MAIN) "test1" 2000 2000 AB 10 10 $(SAVE_IMG) > /dev/null; \
	done
	@mv lyapunov.ppm bench_1.ppm 2>/dev/null || true
	
	@echo "\n---> TEST 2"
	@for i in `seq 1 $(RUNS)`; do \
		echo "     Esecuzione $$i di $(RUNS) con $(THREADS) thread..."; \
		OMP_NUM_THREADS=$(THREADS) ./$(TARGET_MAIN) "test2" 2000 2000 AB 200 200 $(SAVE_IMG) > /dev/null; \
	done
	@mv lyapunov.ppm bench_2.ppm 2>/dev/null || true

	@echo "\n---> TEST 3"
	@for i in `seq 1 $(RUNS)`; do \
		echo "     Esecuzione $$i di $(RUNS) con $(THREADS) thread..."; \
		OMP_NUM_THREADS=$(THREADS) ./$(TARGET_MAIN) "test3" 2000 2000 ABBA 2000 2000 $(SAVE_IMG) > /dev/null; \
	done
	@mv lyapunov.ppm bench_3.ppm 2>/dev/null || true

	@echo "\n---> TEST 4"
	@for i in `seq 1 $(RUNS)`; do \
		echo "     Esecuzione $$i di $(RUNS) con $(THREADS) thread..."; \
		OMP_NUM_THREADS=$(THREADS) ./$(TARGET_MAIN) "test4" 2000 2000 ABBBABAA 4000 4000 $(SAVE_IMG) > /dev/null; \
	done
	@mv lyapunov.ppm bench_4.ppm 2>/dev/null || true

	@echo "\n---> TEST 5"
	@for i in `seq 1 $(RUNS)`; do \
		echo "     Esecuzione $$i di $(RUNS) con $(THREADS) thread..."; \
		OMP_NUM_THREADS=$(THREADS) ./$(TARGET_MAIN) "test5" 2000 2000 ABBBABAA 8000 8000 $(SAVE_IMG) > /dev/null; \
	done
	@mv lyapunov.ppm bench_4.ppm 2>/dev/null || true
	
	@echo "\n======================================================="
	@echo "   BENCHMARK COMPLETATO! Dati accodati in benchmark_results.csv"
	@echo "======================================================="


.PHONY: full_benchmark

full_benchmark: all
	@echo "Cleaning up old benchmark results..."
	@rm -f benchmark_results.csv
	@echo "Test_Name,Threads,Width,Height,Sequence,Iterations,Time_ms" > benchmark_results.csv

	@echo "Starting full benchmark..."
	@for threads in 1 2 3 4 5 6 7 8; do \
	  for resolution in 500 1000 2000; do \
	    for iterations in 1000 2000 4000; do \
	      test_name="res$${resolution}_iter$${iterations}"; \
	      echo "Running test: res $${resolution}, iter $${iterations}, threads $${threads}"; \
	      for i in `seq 1 3`; do \
	        OMP_NUM_THREADS=$${threads} ./lyapunov_gen "$${test_name}" $${resolution} $${resolution} "AAB" $${iterations} $${iterations} 0 > /dev/null; \
	      done; \
	    done; \
	  done; \
	done

	@echo "Benchmark finished. Results are in benchmark_results.csv"