#include <iostream>
#include <vector>
#include <random>
#include <stdexcept>
#include <algorithm>


class nearest_neighbors_sites {
private:
    
    int Lx                   ; 
    int Ly                   ;
    int coordination_number  ;
    
    std::string geometry     ;
    
    std::vector<int> nn_sites;

public:

    nearest_neighbors_sites() = default;

    void build(int Lx, int Ly, std::string geometry) {
        
        this->Lx = Lx;
        this->Ly = Ly;
        this->geometry = geometry;
        
        int N = Lx * Ly;
        
        if (geometry == "square") {
            coordination_number = 4;
            nn_sites.resize(N * coordination_number);

            for (int i = 0; i < N; i++) {
                nn_sites[i * coordination_number + 0] = (i % Lx == Lx - 1) ? i - Lx + 1 : i + 1;
                nn_sites[i * coordination_number + 1] = (i + Lx) % N;
                nn_sites[i * coordination_number + 2] = (i % Lx == 0) ? i + Lx - 1 : i - 1;
                nn_sites[i * coordination_number + 3] = (i - Lx + N) % N;
            }
        }
        // Add other geometries (e.g., "triangular", "hexagonal") here
    }

    // Get neighbor index for site `i` and direction `dir`
    int get_neighbor(int i, int dir) const {
        return nn_list[i * coordination_number + dir];
    }

    // Get all neighbors of site `i`
    std::vector<int> get_neighbors(int i) const {
        return { 
            nn_list[i * coordination_number + 0],
            nn_list[i * coordination_number + 1],
            nn_list[i * coordination_number + 2],
            nn_list[i * coordination_number + 3]
        };
    }

    int get_coordination() const { return coordination_number; }
};

// ========================
// Generic Lattice Class
// ========================
template <typename T>
class lattice {
private:
    int Lx, Ly;
    int Q;  // Number of states (0 to Q-1)
    std::vector<T> sites;
    nearest_neighbors nn;

public:
    lattice(int Lx, int Ly, int Q, std::string geometry = "square") 
        : Lx(Lx), Ly(Ly), Q(Q) {
        sites.resize(Lx * Ly);
        nn.build(Lx, Ly, geometry);  // Build neighbor list
    }

    // Initialize lattice sites
    void initialize(const std::string& init_type) {
        if (init_type == "uniform") {
            T value;
            std::cout << "Enter uniform value (0 to " << Q-1 << "): ";
            std::cin >> value;
            std::fill(sites.begin(), sites.end(), value);
        }
        else if (init_type == "random") {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<T> dist(0, Q-1);
            for (auto& site : sites) site = dist(gen);
        }
        else if (init_type == "checkerboard") {
            if (Q != 2) throw std::invalid_argument("Checkerboard requires Q=2!");
            for (int i = 0; i < Ly; i++) {
                for (int j = 0; j < Lx; j++) {
                    sites[i * Lx + j] = (i + j) % 2;
                }
            }
        }
        else {
            throw std::invalid_argument("Unknown initialization type!");
        }
    }

    // Compute energy (example: Potts model)
    double compute_energy() const {
        double energy = 0.0;
        for (int i = 0; i < sites.size(); i++) {
            for (int dir = 0; dir < nn.get_coordination(); dir++) {
                int j = nn.get_neighbor(i, dir);
                energy += (sites[i] == sites[j]) ? -1.0 : 0.0;  // Simple interaction
            }
        }
        return energy;
    }

    // Print lattice configuration
    void print() const {
        std::cout << "Lattice (" << Lx << "x" << Ly << "), Q=" << Q << ":\n";
        for (int i = 0; i < Ly; i++) {
            for (int j = 0; j < Lx; j++) {
                std::cout << sites[i * Lx + j] << " ";
            }
            std::cout << "\n";
        }
    }

    // Access/modify site at (i,j)
    T& operator()(int i, int j) { return sites[i * Lx + j]; }
    const T& operator()(int i, int j) const { return sites[i * Lx + j]; }
};

// ========================
// Main Program
// ========================
int main() {
    // Ising model (Q=2)
    lattice<int> ising(4, 4, 2);
    ising.initialize("checkerboard");
    ising.print();
    std::cout << "Energy: " << ising.compute_energy() << "\n\n";

    // Potts model (Q=3)
    lattice<int> potts(3, 3, 3);
    potts.initialize("random");
    potts.print();
    std::cout << "Energy: " << potts.compute_energy() << "\n";

    return 0;
}