#ifndef ARRETE_HPP
#define ARRETE_HPP

#include <iostream>
#include <vector>
#include "noeud.hpp"

class Arrete {
    private:
        Noeud* ptr_depart;
        Noeud* ptr_fin;
        int nb_edge;
        Noeud* ptr_n_gauche;
        Noeud* ptr_n_droite;

    public:
    Arrete(Noeud* ptr_1, Noeud* ptr_2, int no) {
        ptr_depart = ptr_1;
        ptr_fin = ptr_2;
        nb_edge = no;
        ptr_n_gauche = nullptr;
        ptr_n_droite = nullptr;
    }

    std::vector<Noeud*> get_ptr_noeuds() {
        std::vector<Noeud*> noeuds = {ptr_depart,ptr_fin};
        return noeuds;
    }

    
};

#endif