#ifndef MAILLE_HPP
#define MAILLE_HPP

#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <unordered_set> // Pour optimiser la recherche d'intersection
#include "noeud.hpp"
#include "element.hpp"

class Maille {
private:
    int nb_noeud;
    int nb_element;
    std::vector<Noeud*> ptr_noeuds;
    std::vector<Element*> ptr_elements;
    std::vector<int> U;
    std::vector<int> V;

public:
    // Constructeur : initialise les attributs
    Maille() : nb_noeud(0), nb_element(0) {
        ptr_noeuds.clear();
        ptr_elements.clear();
    }

    // Destructeur : libère la mémoire allouée pour les nœuds et éléments
    ~Maille() {
        for (Noeud* ptr : ptr_noeuds) {
            delete ptr;
        }
        for (Element* ptr : ptr_elements) {
            delete ptr;
        }
    }

    // Retourne le nombre de nœuds
    int get_nb_noeud() const {
        return nb_noeud;
    }

    // Retourne le nombre d'éléments
    int get_nb_element() const {
        return nb_element;
    }

    // Retourne le vecteur de pointeurs vers les nœuds
    const std::vector<Noeud*>& get_ptr_noeuds() const {
        return ptr_noeuds;
    }

    // Retourne le vecteur de pointeurs vers les éléments
    const std::vector<Element*>& get_ptr_elements() const {
        return ptr_elements;
    }

    // Ajoute un nœud au maillage
    void ajouter_noeud(double x, double y) {
        Noeud* nouveau = new Noeud(x, y, nb_noeud);
        ptr_noeuds.push_back(nouveau);
        U.push_back(0);
        V.push_back(0);
        nb_noeud++;
    }

    // Ajoute un élément (triangle) au maillage
    void ajouter_element(Noeud* ptr_1, Noeud* ptr_2, Noeud* ptr_3) {
        Element* nouveau = new Element(ptr_1, ptr_2, ptr_3, nb_element);
        ptr_elements.push_back(nouveau);
        nb_element++;
    }

    // Construit un maillage triangulaire régulier
    void construction_maille(int h, int pas_cote_x, int pas_cote_y) {
        // Créer une grille de nœuds
        for (int i = 0; i <= pas_cote_x; i++) {
            for (int j = 0; j <= pas_cote_y; j++) {
                this->ajouter_noeud(i * h, j * h * sqrt(3) / 2);
            }
        }

        // Créer des éléments (triangles) entre les nœuds
        for (int i = 0; i < pas_cote_x; i++) {
            for (int j = 0; j < pas_cote_y; j++) {
                // Premier triangle
                Noeud* n1 = ptr_noeuds[i + j * (pas_cote_x + 1)];
                Noeud* n2 = ptr_noeuds[i + 1 + j * (pas_cote_x + 1)];
                Noeud* n3 = ptr_noeuds[i + (j + 1) * (pas_cote_x + 1)];
                this->ajouter_element(n1, n2, n3);

                // Deuxième triangle pour compléter le rectangle
                n1 = ptr_noeuds[i + 1 + j * (pas_cote_x + 1)];
                n2 = ptr_noeuds[i + (j + 1) * (pas_cote_x + 1)];
                n3 = ptr_noeuds[i + 1 + (j + 1) * (pas_cote_x + 1)];
                this->ajouter_element(n1, n2, n3);
            }
        }
    }

    // Calcule la factorielle d'un entier
    double fact(int i) {
        if (i < 0) return 0; // Cas invalide
        double result = 1;
        for (int j = 1; j <= i; j++) { // Correction : commence à j = 1
            result *= j;
        }
        return result;
    }

    // Calcule l'intégrale sur un élément avec des exposants alpha, beta, gamma
    double int_element(Element* ptr_element, int alpha, int beta) {
        double A = ptr_element->aire();
        double denom = fact(alpha + beta + 2);
        double nom = fact(alpha) * fact(beta);
        return 2 * A * nom / denom;
    }

    // Calcule l'intersection entre deux vecteurs de pointeurs d'éléments
    std::vector<Element*> inter(const std::vector<Element*>& ptr_voisins_1, const std::vector<Element*>& ptr_voisins_2) {
        std::unordered_set<Element*> set_voisins_2(ptr_voisins_2.begin(), ptr_voisins_2.end());
        std::vector<Element*> intersection;
        for (Element* ptr : ptr_voisins_1) {
            if (set_voisins_2.find(ptr) != set_voisins_2.end()) {
                intersection.push_back(ptr);
            }
        }
        return intersection;
    }

    // Calcule l'intégrale pour un nœud (cas alpha=1, beta=0, gamma=0)
    double valeur_integral(Noeud* ptr_1) {
        std::vector<Element*> ptr_voisins = ptr_1->get_ptr_voisins();
        double val_int = 0;
        for (Element* ptr : ptr_voisins) {
            val_int += int_element(ptr, 1, 0);
        }
        return val_int;
    }

    // Calcule l'intégrale pour deux nœuds
    double valeur_integral(Noeud* ptr_1, Noeud* ptr_2) {
        if (ptr_1 == ptr_2) {
            // Cas où les deux nœuds sont identiques
            std::vector<Element*> ptr_voisins = ptr_1->get_ptr_voisins();
            double val_int = 0;
            for (Element* ptr : ptr_voisins) {
                val_int += int_element(ptr, 2, 0);
            }
            return val_int;
        } else {
            // Cas où les deux nœuds sont différents
            std::vector<Element*> ptr_voisins_1 = ptr_1->get_ptr_voisins();
            std::vector<Element*> ptr_voisins_2 = ptr_2->get_ptr_voisins();
            std::vector<Element*> interval = inter(ptr_voisins_1, ptr_voisins_2);

            // Vérifie que interval a au moins 2 éléments
            if (interval.size() >= 2) {
                double val_int = int_element(interval[0], 1, 1);
                val_int += int_element(interval[1], 1, 1);
                return val_int;
            } else if (interval.size() == 1) {
                return int_element(interval[0], 1, 1);
            } else {
                return 0; // Aucun élément commun
            }
        }
    }

    double derive(Element* ptr_elem, Noeud* ptr_pointe, int dimension_deriv) {
        double x1;
        double y1;
        double x2;
        double y2;
        double x3;
        double y3;
        std::vector<Noeud*> noeuds = ptr_elem->get_ptr_noeuds();
        if (noeuds[0]==ptr_pointe) {
            x1 = ptr_pointe->get_x();
            y1 = ptr_pointe->get_y();
            x2 = noeuds[1]->get_x();
            y2 = noeuds[1]->get_y();
            x3 = noeuds[2]->get_x();
            y3 = noeuds[2]->get_y();
        }
        else if (noeuds[1]==ptr_pointe) {
            x1 = ptr_pointe->get_x();
            y1 = ptr_pointe->get_y();
            x2 = noeuds[2]->get_x();
            y2 = noeuds[2]->get_y();
            x3 = noeuds[0]->get_x();
            y3 = noeuds[0]->get_y();
        }
        else if (noeuds[2]==ptr_pointe) {
            x1 = ptr_pointe->get_x();
            y1 = ptr_pointe->get_y();
            x2 = noeuds[0]->get_x();
            y2 = noeuds[0]->get_y();
            x3 = noeuds[1]->get_x();
            y3 = noeuds[1]->get_y();
        }
        double vx = x1 - (x2+x3)/2;
        double vy = y1 - (y2+y3)/2;
        double norm_v_2 = vx * vx + vy * vy;
        if (dimension_deriv==0) {
            return vx/norm_v_2;
        }
        else if (dimension_deriv==1) {
            return vy/norm_v_2;
        }
    }

    // Calcule l'intégrale pour trois nœuds
    double valeur_integral(Noeud* ptr_1, Noeud* ptr_2, Noeud* ptr_3_deriv, int dimension_deriv) {
        if (ptr_1 == ptr_2 && ptr_2 == ptr_3_deriv) {
            // Cas où les trois nœuds sont identiques
            std::vector<Element*> ptr_voisins = ptr_1->get_ptr_voisins();
            double val_int = 0;
            for (Element* ptr : ptr_voisins) {
                val_int += int_element(ptr, 2, 0) * derive(ptr, ptr_3_deriv, dimension_deriv);
            }
            return val_int;
        } else if (ptr_1 == ptr_2) {
            // Cas où ptr_1 == ptr_2 mais ptr_3 est différent
            std::vector<Element*> ptr_voisins_1 = ptr_1->get_ptr_voisins();
            std::vector<Element*> ptr_voisins_3 = ptr_3_deriv->get_ptr_voisins();
            std::vector<Element*> interval = inter(ptr_voisins_1, ptr_voisins_3);
            if (interval.size() >= 2) {
                double val_int = int_element(interval[0], 2, 0) * derive(interval[0], ptr_3_deriv, dimension_deriv);
                val_int += int_element(interval[1], 2, 0) * derive(interval[1], ptr_3_deriv, dimension_deriv);
                return val_int;
            } else if (interval.size() == 1) {
                return int_element(interval[0], 2, 0) * derive(interval[0], ptr_3_deriv, dimension_deriv);
            } else {
                return 0;
            }
        } else if (ptr_2 == ptr_3_deriv) {
            // Cas où ptr_2 == ptr_3 mais ptr_1 est différent
            std::vector<Element*> ptr_voisins_1 = ptr_1->get_ptr_voisins();
            std::vector<Element*> ptr_voisins_2 = ptr_2->get_ptr_voisins();
            std::vector<Element*> interval = inter(ptr_voisins_1, ptr_voisins_2);
            if (interval.size() >= 2) {
                double val_int = int_element(interval[0], 1, 1) * derive(interval[0], ptr_3_deriv, dimension_deriv);
                val_int += int_element(interval[1], 1, 1) * derive(interval[1], ptr_3_deriv, dimension_deriv);
                return val_int;
            } else if (interval.size() == 1) {
                return int_element(interval[0], 1, 1) * derive(interval[0], ptr_3_deriv, dimension_deriv);
            } else {
                return 0;
            }
        } else if (ptr_1 == ptr_3_deriv) {
            // Cas où ptr_1 == ptr_3 mais ptr_2 est différent
            std::vector<Element*> ptr_voisins_1 = ptr_1->get_ptr_voisins();
            std::vector<Element*> ptr_voisins_2 = ptr_2->get_ptr_voisins();
            std::vector<Element*> interval = inter(ptr_voisins_1, ptr_voisins_2);
            if (interval.size() >= 2) {
                double val_int = int_element(interval[0], 1, 1) * derive(interval[0], ptr_3_deriv, dimension_deriv);
                val_int += int_element(interval[1], 1, 1) * derive(interval[1], ptr_3_deriv, dimension_deriv);
                return val_int;
            } else if (interval.size() == 1) {
                return int_element(interval[0], 1, 1) * derive(interval[0], ptr_3_deriv, dimension_deriv);
            } else {
                return 0;
            }
        } else {
            // Cas où les trois nœuds sont distincts
            std::vector<Element*> ptr_voisins_1 = ptr_1->get_ptr_voisins();
            std::vector<Element*> ptr_voisins_2 = ptr_2->get_ptr_voisins();
            std::vector<Element*> ptr_voisins_3 = ptr_3_deriv->get_ptr_voisins();
            std::vector<Element*> interval_partiel = inter(ptr_voisins_1, ptr_voisins_2);
            std::vector<Element*> interval = inter(interval_partiel, ptr_voisins_3);
            if (!interval.empty()) {
                return int_element(interval[0], 1, 1) * derive(interval[0], ptr_3_deriv, dimension_deriv);
            } else {
                return 0;
            }
        }
    }

    void Nu() {
        
    }
};

#endif