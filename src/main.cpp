#include "lyapunov.h"

using namespace std;

unordered_map<string, string> readConfig(const string& filename) {
    unordered_map<string, string> config;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "Attenzione: Impossibile aprire " << filename << ". Verranno usati i valori di default." << endl;
        return config;
    }

    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        size_t delimiterPos = line.find('=');
        if (delimiterPos != string::npos) {
            string key = line.substr(0, delimiterPos);
            string value = line.substr(delimiterPos + 1);
            config[key] = value;
        }
    }
    return config;
}

int main() {
    auto config = readConfig("config.txt");

    int width = config.count("width") ? stoi(config["width"]) : 800;
    int height = config.count("height") ? stoi(config["height"]) : 800;
    int iterations = config.count("iterations") ? stoi(config["iterations"]) : 400;
    int lyap_steps = config.count("lyap_steps") ? stoi(config["lyap_steps"]) : 400;
    string sequence = config.count("sequence") ? config["sequence"] : "AB";
    
    double min_a = config.count("min_a") ? stod(config["min_a"]) : 2.0;
    double max_a = config.count("max_a") ? stod(config["max_a"]) : 4.0;
    double min_b = config.count("min_b") ? stod(config["min_b"]) : 2.0;
    double max_b = config.count("max_b") ? stod(config["max_b"]) : 4.0;

    cout << "=== Generatore Frattali di Lyapunov ===" << endl;
    cout << "Sequenza: " << sequence << " | Risoluzione: " << width << "x" << height << endl;

    // Istanziamo un SINGOLO oggetto
    LyapunovGenerator fractal(width, height, iterations, lyap_steps, sequence, min_a, max_a, min_b, max_b);

    // --- TEST SEQUENZIALE ---
    cout << "\n[1] Avvio generazione SEQUENZIALE..." << endl;
    auto startSeq = chrono::high_resolution_clock::now();
    fractal.generateSequential();
    auto endSeq = chrono::high_resolution_clock::now();
    double timeSeqMs = chrono::duration_cast<chrono::microseconds>(endSeq - startSeq).count() / 1000.0;
    cout << "Tempo Sequenziale: " << timeSeqMs << " ms" << endl;

    // --- TEST PARALLELO ---
    // Nota: L'array 'image' all'interno di fractal viene semplicemente sovrascritto
    cout << "\n[2] Avvio generazione PARALLELA (OpenMP)..." << endl;
    auto startPar = chrono::high_resolution_clock::now();
    fractal.generateParallel();
    auto endPar = chrono::high_resolution_clock::now();
    double timeParMs = chrono::duration_cast<chrono::microseconds>(endPar - startPar).count() / 1000.0;
    cout << "Tempo Parallelo:   " << timeParMs << " ms" << endl;

    // --- RISULTATI ---
    double speedup = timeSeqMs / timeParMs;
    cout << "\n=== RISULTATI PERFORMANCE ===" << endl;
    cout << "Speedup calcolato: " << speedup << "x" << endl;
    
    // Salviamo l'immagine (che conterrà il risultato dell'ultima run, quella parallela)
    fractal.saveToPPM("lyapunov.ppm");

    return 0;
}