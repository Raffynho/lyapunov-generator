#ifndef LYAPUNOV_CUDA_H
#define LYAPUNOV_CUDA_H

#include <vector>
#include <string>
#include <cstdint>

// Struttura colore
struct Color {
    uint8_t r, g, b;
};

// Funzione principale che gestisce la memoria GPU e lancia il calcolo
void runLyapunovCUDA(std::vector<Color>& h_image, int width, int height, 
                     int iterations, int lyap_steps, const std::string& sequence,
                     double min_a, double max_a, double min_b, double max_b,
                     double& timeCudaMs);

// Funzione per salvare l'immagine
void saveToPPM(const std::string& filename, const std::vector<Color>& image, int width, int height);

#endif // LYAPUNOV_CUDA_H