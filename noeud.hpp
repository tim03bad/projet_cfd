#ifndef NOEUD_HPP
#define NOEUD_HPP

#include <iostream>
#include <vector>
#include "element.hpp"

class Noeud {
private:
    double x;
    double y;
    int nb_knot;
    std::vector<Element*> ptr_voisins;
    int nb_voisins;

public:
    Noeud(double x_value, double y_value, int no) {
        x = x_value;
        y = y_value;
        nb_knot = no;
        ptr_voisins = {};
        nb_voisins = 0;
    }

    double get_x() {
        return x;
    }

    double get_y() {
        return y;
    }

    int get_nb_knot() {
        return nb_knot;
    }

    std::vector<Element*> get_ptr_voisins() {
        return ptr_voisins;
    }

    int get_nb_voisins() {
        return nb_voisins;
    }

    void lien_element(Element* ptr_voisin) {
        ptr_voisins.push_back(ptr_voisin);
    } 

    void display() {
        std::cout << "Nb: " << nb_knot << "   x: " << x << "   y: " << y << std::endl;
    }
};

#endif