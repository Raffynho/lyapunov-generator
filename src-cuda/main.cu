#include "lyapunov.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream> // Aggiunto per poter scrivere il file CSV

using namespace std;

int main(int argc, char* argv[]) {
    // CORREZIONE: Ora i parametri sono sfalsati di 1 per fare spazio alla Label del test
    string testLabel = (argc > 1) ? argv[1] : "Test_Manuale";
    int width        = (argc > 2) ? stoi(argv[2]) : 800;
    int height       = (argc > 3) ? stoi(argv[3]) : 800;
    string sequence  = (argc > 4) ? argv[4] : "AB";
    int iterations   = (argc > 5) ? stoi(argv[5]) : 400;
    int lyap_steps   = (argc > 6) ? stoi(argv[6]) : 400;
    
    double min_a = 0.0, max_a = 4.0;
    double min_b = 0.0, max_b = 4.0;

    cout << "=== Generatore Lyapunov CUDA Modulare ===" << endl;
    cout << "Test: " << testLabel << " | Risoluzione: " << width << "x" << height 
         << " | Sequenza: " << sequence << endl;

    // Vettore per memorizzare l'immagine sulla RAM
    vector<Color> h_image(width * height);
    double timeCudaMs = 0.0;

    // Esegue il calcolo su GPU
    runLyapunovCUDA(h_image, width, height, iterations, lyap_steps, sequence, 
                    min_a, max_a, min_b, max_b, timeCudaMs);

    cout << "Tempo di calcolo GPU: " << timeCudaMs << " ms" << endl;

    // === SALVATAGGIO IN CSV ===
    ofstream csvFile("benchmark_results.csv", ios::app);
    if (csvFile.is_open()) {
        csvFile.seekp(0, ios::end);
        if (csvFile.tellp() == 0) {
            // Se il file è vuoto, scriviamo l'intestazione
            csvFile << "Test_Name,Width,Height,Sequence,Iterations,Time_CUDA_ms\n";
        }
        // Accodiamo i risultati della run corrente
        csvFile << testLabel << "," 
                << width << "," 
                << height << "," 
                << sequence << "," 
                << iterations << ","
                << timeCudaMs << "\n";
        csvFile.close();
    } else {
        cerr << "Errore nell'apertura del file CSV per il salvataggio dei dati!" << endl;
    }

    // Salva il risultato in PPM (il Makefile si aspetta che si chiami "lyapunov_cuda.ppm" per poterlo rinominare)
    saveToPPM("lyapunov_cuda.ppm", h_image, width, height);

    return 0;
}