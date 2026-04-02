# --- COMPILATORE E FLAG ---
NVCC = nvcc
NVCCFLAGS = -O3 -std=c++17

TARGET = lyapunov_cuda.exe
SRCS = main.cu lyapunov.cu

# Variabili Configurabili
RUNS = 100

all: $(TARGET)

$(TARGET): $(SRCS)
	$(NVCC) $(NVCCFLAGS) -o $(TARGET) $(SRCS)

run: $(TARGET)
	$(TARGET) "Test_Manuale" 800 800 AB 400 400

clean:
	del /Q /F $(TARGET) *.ppm benchmark_results.csv 2>NUL



scale_compute_benchmark: all
	@echo =======================================================
	@echo    Starting variable size benchmark...
	@echo    Risoluzione: 2048x2048 ^| Ripetizioni: $(RUNS)
	@echo =======================================================
	@del /Q /F benchmark_results.csv 2>NUL
	
	@FOR %%k IN (500 1000 2000 4000 8000 16000 32000) DO @( \
		echo ---> Test con densita' matematica: %%k iterazioni... & \
		FOR /L %%i IN (1, 1, $(RUNS)) DO @( \
			echo      Esecuzione %%i di $(RUNS)... & \
			$(TARGET) "Iter_%%k" 2048 2048 ABBA %%k %%k > NUL \
		) \
	)
	
	@echo =======================================================
	@echo    Benchmark completato! Dati in benchmark_results.csv
	@echo =======================================================