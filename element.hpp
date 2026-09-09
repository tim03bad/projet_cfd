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
        ptr_1->lien_element(this);
        ptr_2->lien_element(this);
        ptr_3->lien_element(this);
    }

    std::vector<Noeud*> get_ptr_noeuds() {
        std::vector<Noeud*> ptr_noeuds;
        ptr_noeuds = {noeud_1,noeud_2,noeud_3};
        return ptr_noeuds;
    }

    double aire() {
        double x1 = noeud_1->get_x();
        double y1 = noeud_1->get_y();
        double x2 = noeud_2->get_x();
        double y2 = noeud_2->get_y();
        double x3 = noeud_3->get_x();
        double y3 = noeud_3->get_y();
        double l = sqrt((x2-x1) * (x2-x1) + (y2-y1) * (y2-y1));
        double h = sqrt((x3-(x2+x1)/2) * (x3-(x2+x1)/2) + (y3-(y2+y1)/2) * (y3-(y2+y1)/2));
        return l*h/2;
    }
};

#endif