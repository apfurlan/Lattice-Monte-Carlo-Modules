#include "nearest_neighbors_bonds_class.hpp"
#include <iostream>
#include <iomanip>

// void print_neighbors(const nearest_neighbor_bonds& lattice, int site) {
//     const auto& nn = lattice.get_nn_list();
//     int ncoord = lattice.get_coordination();
    
//     std::cout << "Neighbors of site " << site << ": ";
//     for (int i = 0; i < ncoord; ++i) {
//         std::cout << nn[site * ncoord + i] << " ";
//     }
//     std::cout << "\n";
// }

int main() {

        // Create and build a triangular lattice
        
        const int Lx = 4                          ; // Lattice size in x-direction
        const int Ly = 4                          ; // Lattice size in y-direction
        const int coordination_number = 6         ; // Coordination number
        const std::string geometry = "triangular" ; // Geometry type


        nearest_neighbors_bonds nnb(Lx, Ly, geometry); ; 
        // nnb.build(Lx, Ly, geometry);                ;


        return 0; 
}