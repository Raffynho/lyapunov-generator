#include "lyapunov.h"
#include <omp.h>

using namespace std;

int main(int argc, char* argv[]) {
    string testLabel = (argc > 1) ? argv[1] : "Test_Manuale";
    int width        = (argc > 2) ? stoi(argv[2]) : 800;
    int height       = (argc > 3) ? stoi(argv[3]) : 800;
    string sequence  = (argc > 4) ? argv[4] : "AB";
    int iterations   = (argc > 5) ? stoi(argv[5]) : 400;
    int lyap_steps   = (argc > 6) ? stoi(argv[6]) : 400;
    int save_image   = (argc > 7) ? stoi(argv[7]) : 1; 
    
    double min_a = 2.0; double max_a = 4.0;
    double min_b = 2.0; double max_b = 4.0;

    // Legge il numero di thread passati dall'esterno (es. dal Makefile)
    int requested_threads = omp_get_max_threads();

    LyapunovGenerator fractal(width, height, iterations, lyap_steps, sequence, min_a, max_a, min_b, max_b);

    // --- UNICA ESECUZIONE ---
    auto start = chrono::high_resolution_clock::now();
    fractal.generate(); 
    auto end = chrono::high_resolution_clock::now();
    double timeMs = chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.0;

    // --- SALVATAGGIO IN CSV (Solo dati grezzi puri) ---
    ofstream csvFile("benchmark_results.csv", ios::app);
    if (csvFile.is_open()) {
        csvFile.seekp(0, ios::end);
        if (csvFile.tellp() == 0) {
            // Intestazione semplificata: niente più speedup o efficienza calcolati qui
            csvFile << "Test_Name,Threads,Width,Height,Sequence,Iterations,Time_ms\n";
        }
        csvFile << testLabel << "," 
                << requested_threads << "," 
                << width << "," 
                << height << "," 
                << sequence << "," 
                << iterations << ","
                << timeMs << "\n";
        csvFile.close();
    }
    
    // --- SALVATAGGIO IMMAGINE CONDIZIONALE ---
    if (save_image == 1) {
        fractal.saveToPPM("lyapunov.ppm");
    }
    
    return 0;
}