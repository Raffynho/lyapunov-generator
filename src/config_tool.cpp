#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    // Valori di default
    string width = "800";
    string height = "800";
    string sequence = "AB";
    string iter = "400";
    string steps = "400";

    // Leggiamo gli argomenti da riga di comando (se presenti)
    // L'ordine che useremo sarà: ./config_tool <width> <height> <sequence> <iter> <steps>
    if (argc >= 3) {
        width = argv[1];
        height = argv[2];
    }
    if (argc >= 4) {
        sequence = argv[3];
    }
    if (argc >= 6) {
        iter = argv[4];
        steps = argv[5];
    }

    // Apriamo e sovrascriviamo il file config.txt
    ofstream file("config.txt");
    if (!file.is_open()) {
        cerr << "Errore: Impossibile creare config.txt" << endl;
        return 1;
    }

    // Scriviamo i parametri formattati correttamente
    file << "# Configurazione generata dinamicamente da config_tool\n";
    file << "width=" << width << "\n";
    file << "height=" << height << "\n";
    file << "iterations=" << iter << "\n";
    file << "lyap_steps=" << steps << "\n";
    file << "sequence=" << sequence << "\n";
    file << "min_a=0.\n";
    file << "max_a=4.0\n";
    file << "min_b=0.0\n";
    file << "max_b=4.0\n";

    cout << "[Config Tool] Generato config.txt -> " << width << "x" << height 
         << " | Seq: " << sequence << " | Iter: " << iter << "+" << steps << endl;

    return 0;
}