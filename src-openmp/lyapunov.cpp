#include "lyapunov.h"

using namespace std;

LyapunovGenerator::LyapunovGenerator(int w, int h, int iter, int steps, const string& seq,
                                     double minA, double maxA, double minB, double maxB)
    : width(w), height(h), iterations(iter), lyap_steps(steps), sequence(seq),
      min_a(minA), max_a(maxA), min_b(minB), max_b(maxB) 
{
    image.resize(width * height);
}

Color LyapunovGenerator::getColor(double lambda) const {
    if (lambda >= 0) return {0, 0, 0}; 
    uint8_t intensity = static_cast<uint8_t>(clamp(abs(lambda) * 50.0, 0.0, 255.0));
    return {intensity, static_cast<uint8_t>(intensity / 2), static_cast<uint8_t>(255 - intensity)};
}

// === UNICO METODO DI GENERAZIONE (OpenMP) ===
void LyapunovGenerator::generate() {
    size_t seq_len = sequence.length();
    
    // Lo scheduling static è il più efficiente per questo frattale
    #pragma omp parallel for schedule(guided)
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            double a = min_a + (max_a - min_a) * x / width;
            double b = min_b + (max_b - min_b) * (height - y) / height;
            double x_val = 0.5;
            double sum_log = 0.0;

            for (int i = 0; i < iterations + lyap_steps; ++i) {
                char step_type = sequence[i % seq_len];
                double r = (step_type == 'A' || step_type == 'a') ? a : b;
                double next_x = r * x_val * (1.0 - x_val);
                if (i >= iterations) {
                    double deriv = abs(r * (1.0 - 2.0 * next_x));
                    if (deriv > 0) sum_log += log2(deriv);
                }
                x_val = next_x;
            }
            double lambda = sum_log / lyap_steps;
            image[y * width + x] = getColor(lambda);
        }
    }
}

void LyapunovGenerator::saveToPPM(const string& filename) const {
    ofstream ofs(filename);
    if (!ofs) {
        cerr << "Errore nel salvataggio del file: " << filename << endl;
        return;
    }
    ofs << "P3\n" << width << " " << height << "\n255\n";
    for (const auto& c : image) {
        ofs << (int)c.r << " " << (int)c.g << " " << (int)c.b << " ";
    }
}