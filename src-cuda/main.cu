#include "lyapunov.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    int width        = (argc > 1) ? stoi(argv[1]) : 800;
    int height       = (argc > 2) ? stoi(argv[2]) : 800;
    string sequence  = (argc > 3) ? argv[3] : "AB";
    int iterations   = (argc > 4) ? stoi(argv[4]) : 400;
    int lyap_steps   = (argc > 5) ? stoi(argv[5]) : 400;
    
    double min_a = 2.0, max_a = 4.0;
    double min_b = 2.0, max_b = 4.0;

    cout << "=== Generatore Lyapunov CUDA Modulare ===" << endl;
    cout << "Risoluzione: " << width << "x" << height << " | Sequenza: " << sequence << endl;

    // Vettore per memorizzare l'immagine sulla RAM
    vector<Color> h_image(width * height);
    double timeCudaMs = 0.0;

    // Esegue il calcolo su GPU
    runLyapunovCUDA(h_image, width, height, iterations, lyap_steps, sequence, 
                    min_a, max_a, min_b, max_b, timeCudaMs);

    cout << "Tempo di calcolo GPU: " << timeCudaMs << " ms" << endl;

    // Salva il risultato
    saveToPPM("lyapunov_cuda.ppm", h_image, width, height);

    return 0;
}