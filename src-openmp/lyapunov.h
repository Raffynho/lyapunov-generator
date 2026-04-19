#ifndef LYAPUNOV_HPP
#define LYAPUNOV_HPP

#include <vector>
#include <cstdint> 
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include <omp.h>

using namespace std;

struct Color {
    uint8_t r, g, b;
};

class LyapunovGenerator {
private:
    int width, height, iterations, lyap_steps;
    string sequence;
    double min_a, max_a, min_b, max_b;
    vector<Color> image;

    Color getColor(double lambda) const;

public:
    // Costuttore della classe
    LyapunovGenerator(int w, int h, int iter, int steps, const std::string& seq,
                      double minA, double maxA, double minB, double maxB);

    // Metodo per la generazione del frattale
    void generate();
    
    // Metodo per il savataggio dell'immagine in formato PPM
    void saveToPPM(const string& filename) const;
};

#endif 