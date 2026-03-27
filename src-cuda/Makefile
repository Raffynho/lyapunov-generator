# --- COMPILATORE E FLAG ---
NVCC = nvcc
NVCCFLAGS = -O3 -std=c++17

# --- TARGET E SORGENTI ---
TARGET = lyapunov_cuda
SRCS = main.cu lyapunov.cu

# --- REGOLE ---
all: $(TARGET)

# Passiamo tutti i file sorgente a nvcc, che li compilerà insieme
$(TARGET): $(SRCS)
	$(NVCC) $(NVCCFLAGS) -o $(TARGET) $(SRCS)

run: $(TARGET)
	@echo "Esecuzione di $(TARGET)..."
	./$(TARGET) 800 800 AB 400 400

clean:
	@echo "Pulizia dei file generati..."
	rm -f $(TARGET) *.ppm