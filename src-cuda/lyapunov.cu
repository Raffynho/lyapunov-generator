#include "lyapunov.h"

using namespace std;

// Inizializzazione Kernel di Cuda
__global__ void lyapunovKernel(Color* d_image, int width, int height, 
                               int iterations, int lyap_steps, 
                               const char* d_seq, int seq_len,
                               double min_a, double max_a, double min_b, double max_b) {
    
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x < width && y < height) {
        double a = min_a + (max_a - min_a) * x / width;
        double b = min_b + (max_b - min_b) * (height - y) / height;
        double x_val = 0.5;
        double sum_log = 0.0;

        for (int i = 0; i < iterations + lyap_steps; ++i) {
            char step_type = d_seq[i % seq_len];
            double r = (step_type == 'A' || step_type == 'a') ? a : b;
            double next_x = r * x_val * (1.0 - x_val);
            
            if (i >= iterations) {
                double deriv = fabs(r * (1.0 - 2.0 * next_x));
                if (deriv > 0) sum_log += log2(deriv);
            }
            x_val = next_x;
        }

        double lambda = sum_log / lyap_steps;

        Color c;
        if (lambda >= 0) {
            c = {0, 0, 0};
        } else {
            double val = fabs(lambda) * 50.0;
            uint8_t intensity = (uint8_t)(fmin(fmax(val, 0.0), 255.0));
            c = {intensity, (uint8_t)(intensity / 2), (uint8_t)(255 - intensity)};
        }

        d_image[y * width + x] = c;
    }
}

// Funzione per 
void runLyapunovCUDA(vector<Color>& h_image, int width, int height, 
                     int iterations, int lyap_steps, const string& sequence,
                     double min_a, double max_a, double min_b, double max_b,
                     double& timeCudaMs) {
    
    size_t img_size = width * height * sizeof(Color);
    size_t seq_size = sequence.length() * sizeof(char);

    Color* d_image;
    char* d_seq;
    cudaMalloc(&d_image, img_size);
    cudaMalloc(&d_seq, seq_size);

    cudaMemcpy(d_seq, sequence.c_str(), seq_size, cudaMemcpyHostToDevice);

    dim3 blockSize(16, 16);
    dim3 gridSize((width + blockSize.x - 1) / blockSize.x, 
                  (height + blockSize.y - 1) / blockSize.y);

    auto startCuda = chrono::high_resolution_clock::now();

    lyapunovKernel<<<gridSize, blockSize>>>(d_image, width, height, 
                                            iterations, lyap_steps, 
                                            d_seq, sequence.length(), 
                                            min_a, max_a, min_b, max_b);

    cudaDeviceSynchronize();
    
    auto endCuda = chrono::high_resolution_clock::now();
    timeCudaMs = chrono::duration_cast<chrono::microseconds>(endCuda - startCuda).count() / 1000.0;

    cudaMemcpy(h_image.data(), d_image, img_size, cudaMemcpyDeviceToHost);

    cudaFree(d_image);
    cudaFree(d_seq);
}

// Funzione per salvare l'immagine in formato PPM
void saveToPPM(const string& filename, const vector<Color>& image, int width, int height) {
    ofstream ofs(filename);
    if (!ofs) {
        cerr << "Errore nel salvataggio del file!" << endl;
        return;
    }
    ofs << "P3\n" << width << " " << height << "\n255\n";
    for (const auto& c : image) {
        ofs << (int)c.r << " " << (int)c.g << " " << (int)c.b << " ";
    }
    cout << "Immagine salvata in '" << filename << "'" << endl;
}