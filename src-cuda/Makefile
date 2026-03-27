# --- COMPILATORE E FLAG ---
NVCC = nvcc
NVCCFLAGS = -O3 -std=c++17 -allow-unsupported-compiler

TARGET = lyapunov_cuda.exe
SRCS = main.cu lyapunov.cu

# --- VARIABILI CONFIGURABILI ---
# Usiamo solo RUNS, i THREADS sono gestiti dai blocchi CUDA nel codice C++
RUNS = 5

all: $(TARGET)

$(TARGET): $(SRCS)
	$(NVCC) $(NVCCFLAGS) -o $(TARGET) $(SRCS)

run: $(TARGET)
	$(TARGET) "Test_Manuale" 800 800 AB 400 400

clean:
	del /Q /F $(TARGET) *.ppm benchmark_results.csv 2>NUL

benchmark: all
	@echo =======================================================
	@echo    BENCHMARK SCALABILITA' CUDA
	@echo    Ripetizioni: $(RUNS)
	@echo =======================================================
	
	@echo.
	@echo ---> TEST 1: Molto Leggero (10 iterazioni)
	@FOR /L %%i IN (1, 1, $(RUNS)) DO @( echo      Esecuzione %%i di $(RUNS)... & $(TARGET) "test1" 2000 2000 AB 10 10 > NUL )
	@if exist lyapunov_cuda.ppm move /Y lyapunov_cuda.ppm bench_1.ppm > NUL
	
	@echo.
	@echo ---> TEST 2: Leggero (200 iterazioni)
	@FOR /L %%i IN (1, 1, $(RUNS)) DO @( echo      Esecuzione %%i di $(RUNS)... & $(TARGET) "test2" 2000 2000 AB 200 200 > NUL )
	@if exist lyapunov_cuda.ppm move /Y lyapunov_cuda.ppm bench_2.ppm > NUL

	@echo.
	@echo ---> TEST 3: Medio (2.000 iterazioni)
	@FOR /L %%i IN (1, 1, $(RUNS)) DO @( echo      Esecuzione %%i di $(RUNS)... & $(TARGET) "test3" 2000 2000 ABBA 2000 2000 > NUL )
	@if exist lyapunov_cuda.ppm move /Y lyapunov_cuda.ppm bench_3.ppm > NUL

	@echo.
	@echo ---> TEST 4: Pesante (4.000 iterazioni)
	@FOR /L %%i IN (1, 1, $(RUNS)) DO @( echo      Esecuzione %%i di $(RUNS)... & $(TARGET) "test4" 2000 2000 ABBBABAA 4000 4000 > NUL )
	@if exist lyapunov_cuda.ppm move /Y lyapunov_cuda.ppm bench_4.ppm > NUL

	@echo.
	@echo ---> TEST 5: Molto Pesante (8.000 iterazioni)
	@FOR /L %%i IN (1, 1, $(RUNS)) DO @( echo      Esecuzione %%i di $(RUNS)... & $(TARGET) "test5" 2000 2000 ABBBABAA 8000 8000 > NUL )
	@if exist lyapunov_cuda.ppm move /Y lyapunov_cuda.ppm bench_5.ppm > NUL

	@echo.
	@echo ---> TEST 6: GPU STRESS TEST (4K - 15.000 iterazioni)
	@FOR /L %%i IN (1, 1, $(RUNS)) DO @( echo      Esecuzione %%i di $(RUNS)... & $(TARGET) "test6_stress" 4000 4000 ABBA 15000 15000 > NUL )
	@if exist lyapunov_cuda.ppm move /Y lyapunov_cuda.ppm bench_6_stress.ppm > NUL

	@echo.
	@echo ---> TEST 7: GPU EXTREME (8K - 30.000 iterazioni)
	@FOR /L %%i IN (1, 1, $(RUNS)) DO @( echo      Esecuzione %%i di $(RUNS)... & $(TARGET) "test7_extreme" 8000 8000 ABBBABAA 30000 30000 > NUL )
	@if exist lyapunov_cuda.ppm move /Y lyapunov_cuda.ppm bench_7_extreme.ppm > NUL
	
	@echo.
	@echo =======================================================
	@echo    BENCHMARK COMPLETATO! Dati accodati in benchmark_results.csv
	@echo =======================================================