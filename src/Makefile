CXX = g++
CXXFLAGS = -O3 -Wall -std=c++17 -fopenmp -pthread

# Definiamo i nomi dei due eseguibili
TARGET_MAIN = lyapunov_gen
TARGET_TOOL = config_tool

# Definiamo i file sorgente per ciascuno
SRCS_MAIN = main.cpp lyapunov.cpp
SRCS_TOOL = config_tool.cpp

# Regola principale: compila ENTRAMBI i programmi
all: $(TARGET_MAIN) $(TARGET_TOOL)

$(TARGET_MAIN): $(SRCS_MAIN)
	$(CXX) $(CXXFLAGS) -o $(TARGET_MAIN) $(SRCS_MAIN)

$(TARGET_TOOL): $(SRCS_TOOL)
	$(CXX) $(CXXFLAGS) -o $(TARGET_TOOL) $(SRCS_TOOL)

run: $(TARGET_MAIN)
	./$(TARGET_MAIN)

# Regola per pulire tutto
clean:
	rm -f $(TARGET_MAIN) $(TARGET_TOOL) *.ppm config_backup.txt

benchmark: all
	@echo "======================================================="
	@echo "   BENCHMARK SCALABILITA' E LEGGE DI AMDAHL"
	@echo "======================================================="
	@cp config.txt config_backup.txt 2>/dev/null || true
	
	@echo "\n---> TEST 1: I/O Bound (Poco calcolo, tanto salvataggio)"
	@echo "Obiettivo: Mostrare l'overhead dei thread e il collo di bottiglia del disco."
	@./$(TARGET_TOOL) 2000 2000 AB 10 10
	@time ./$(TARGET_MAIN)
	
	@echo "\n---> TEST 2: Compute Bound Leggero (Equilibrio)"
	@echo "Obiettivo: Il calcolo inizia a superare il tempo di I/O."
	@./$(TARGET_TOOL) 1000 1000 AB 400 400
	@time ./$(TARGET_MAIN)

	@echo "\n---> TEST 3: Compute Bound Pesante (Dominanza della CPU)"
	@echo "Obiettivo: Stessa risoluzione del Test 2, ma carico matematico 10x."
	@echo "Qui il parallelismo mostrera' il suo vero potenziale."
	@./$(TARGET_TOOL) 1000 1000 ABBA 4000 4000
	@time ./$(TARGET_MAIN)

	@echo "\n---> TEST 4: Stress Test Estremo (Cache e Memoria)"
	@echo "Obiettivo: Saturare tutti i core con una sequenza complessa."
	@./$(TARGET_TOOL) 3840 2160 ABBBABAA 2000 2000
	@time ./$(TARGET_MAIN)
	
	@echo "\n======================================================="
	@echo "   BENCHMARK COMPLETATO! RIPRISTINO CONFIG "
	@echo "======================================================="
	@mv config_backup.txt config.txt || true