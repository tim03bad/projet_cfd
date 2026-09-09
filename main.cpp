#include <SFML/Graphics.hpp>
#include <vector>
#include "noeud.hpp"
#include "element.hpp"
#include "maille.hpp"

int main()
{
    Maille* maille = new Maille();
    maille->construction_maille(20,30,30);

    std::vector<Element*> ptr_elements;
    int nb_element;
    ptr_elements = maille->get_ptr_elements();
    nb_element = maille->get_nb_element();

    std::vector<sf::ConvexShape*> liste_triangle;

    sf::RenderWindow window(sf::VideoMode({1000, 700}), "SFML Triangle");

    for (int i=0; i<nb_element; i++) {
        // Créer un triangle
        sf::ConvexShape* triangle = new sf::ConvexShape;
        Element* ptr_element;
        ptr_element = ptr_elements[i];
        std::vector<Noeud*> ptr_noeuds;
        ptr_noeuds = ptr_element->get_ptr_noeuds();


        triangle->setPointCount(3);
        for (int j=0; j<3; j++) {
            Noeud* ptr_noeud;
            ptr_noeud = ptr_noeuds[j];
            triangle->setPoint(j, sf::Vector2f(ptr_noeud->get_y(), ptr_noeud->get_x()));
        }

        // Définir la couleur de remplissage et la couleur des bords
        triangle->setFillColor(sf::Color::Green);
        triangle->setOutlineColor(sf::Color::Black);
        triangle->setOutlineThickness(1); // Épaisseur des bords
        liste_triangle.push_back(triangle);
    }

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        window.clear(sf::Color::White);
        for (int i=0; i<nb_element; i++) {
            window.draw(*liste_triangle[i]);
        }
        window.display();
    }

    for (sf::ConvexShape* triangle : liste_triangle) {
        delete triangle;
    }
    delete maille;

    return 0;
}