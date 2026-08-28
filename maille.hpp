#ifndef MAILLE_HPP
#define MAILLE_HPP

#include <vector>
#include <iostream>
#include "noeud.hpp"
#include "arrete.hpp"
#include "element.hpp"

class Maille {
    private:
        int nb_noeud;
        int nb_arrete;
        int nb_element;
        std::vector<Noeud*> ptr_noeuds;
        std::vector<Arrete*> ptr_arretes;
        std::vector<Element*> ptr_elements;

    public:
    Maille() {
        nb_noeud = 0;
        nb_arrete = 0;
        nb_element = 0;
        ptr_noeuds = {};
        ptr_arretes = {};
        ptr_elements = {};
    }

    int get_nb_noeud() {
        return nb_noeud;
    }

    int get_nb_arrete() {
        return nb_arrete;
    }

    int get_nb_element() {
        return nb_element;
    }

    std::vector<Noeud*> get_ptr_noeuds() {
        return ptr_noeuds;
    }

    std::vector<Arrete*> get_ptr_arretes() {
        return ptr_arretes;
    }

    std::vector<Element*> get_ptr_elements() {
        return ptr_elements;
    }

    void ajouter_noeud(double x, double y) {
        Noeud* nouveau = new Noeud(x,y,nb_noeud);
        ptr_noeuds.push_back(nouveau);
        nb_noeud++;
    }

    void ajouter_arrete(Noeud* ptr_1, Noeud* ptr_2) {
        Arrete* nouveau = new Arrete(ptr_1,ptr_2,nb_arrete);
        ptr_arretes.push_back(nouveau);
        nb_arrete++;
    }

    void ajouter_element(Noeud* ptr_1, Noeud* ptr_2, Noeud* ptr_3) {
        Element* nouveau = new Element(ptr_1,ptr_2,ptr_3,nb_element);
        ptr_elements.push_back(nouveau);
        nb_element++;
    }

    void construction_maille() {
        this->ajouter_noeud(0,0);
        this->ajouter_noeud(300,0);
        this->ajouter_noeud(0,300);
        this->ajouter_arrete(ptr_noeuds[0], ptr_noeuds[1]);
        this->ajouter_arrete(ptr_noeuds[1], ptr_noeuds[2]);
        this->ajouter_arrete(ptr_noeuds[2], ptr_noeuds[0]);
        this->ajouter_element(ptr_noeuds[0], ptr_noeuds[1], ptr_noeuds[2]);
    }
};

#endif