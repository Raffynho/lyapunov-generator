#include "lyapunov.h"
#include <omp.h>

using namespace std;

int main(int argc, char* argv[]){
    // Controllo configurazione di test 
    string testLabel = (argc > 1) ? argv[1] : "Test_Manuale";
    int width        = (argc > 2) ? stoi(argv[2]) : 800;
    int height       = (argc > 3) ? stoi(argv[3]) : 800;
    string sequence  = (argc > 4) ? argv[4] : "AB";
    int iterations   = (argc > 5) ? stoi(argv[5]) : 400;
    int lyap_steps   = (argc > 6) ? stoi(argv[6]) : 400;
    int save_image   = (argc > 7) ? stoi(argv[7]) : 1; 
    
    double min_a = 2.0; double max_a = 4.0;
    double min_b = 2.0; double max_b = 4.0;

    // Legge il numero di thread passati dall'makefile 
    int requested_threads = omp_get_max_threads();

    // Definizione dell'oggetto fractal della classe LyapunovGenerator
    LyapunovGenerator fractal(width, height, iterations, lyap_steps, sequence, min_a, max_a, min_b, max_b);

    // Esecuzione del metodo 
    double start = omp_get_wtime();
    fractal.generate(); 
    double end = omp_get_wtime();
    double timeMs = (end - start) * 1000.0;

    // Salvataggio dati in file csv
    ofstream csvFile("benchmark_results.csv", ios::app);
    if (csvFile.is_open()) {
        csvFile.seekp(0, ios::end);
        if (csvFile.tellp() == 0) {
            // Intestazione 
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
    
    // Controllo flag per il salvataggio dell'immagine
    if (save_image == 1) {
        fractal.saveToPPM("lyapunov.ppm");
    }
    
    return 0;
}