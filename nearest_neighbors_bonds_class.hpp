#ifndef NEAREST_NEIGHBORS_BONDS
#define NEAREST_NEIGHBORS_BONDS

#include <vector>
#include <string>

class nearest_neighbors_bonds {
    public:
        int Lx                    ;
        int Ly                    ; 
        int N                     ;
        int coordination_number   ;
        std::string geometry      ;

        std::vector<int> vertex1  ;
        std::vector<int> vertex2  ;
        std::vector<int> nn_bonds ;
    private:



};

#endif 