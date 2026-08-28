#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <iostream>
#include "noeud.hpp"

class Element {
    private:
        Noeud* noeud_1;
        Noeud* noeud_2;
        Noeud* noeud_3;
        int nb_element;
        
    public:
    Element(Noeud* ptr_1, Noeud* ptr_2, Noeud* ptr_3, int no) {
        noeud_1 = ptr_1;
        noeud_2 = ptr_2;
        noeud_3 = ptr_3;
        nb_element = no;
    }

    std::vector<Noeud*> get_ptr_noeuds() {
        std::vector<Noeud*> ptr_noeuds;
        ptr_noeuds = {noeud_1,noeud_2,noeud_3};
        return ptr_noeuds;
    }
};

#endif