/*
 -----------------------------------------------------------------------------------
 Laboratoire : ASD1 Cube magique
 Fichier     : l.cpp
 Auteur(s)   : Jorge-André Fulgencio Esteves <jorgeand.fulgencioesteves@heig-vd.ch>,
               Florian Schaufelberger <florian.schaufelberger@heig-vd.ch>,
               Jonathan Zaehringer <jonathan.zaehringer@heig-vd.ch>

 Date        : 27.03.2018

 Compilateur : Apple LLVM version 9.0.0 (clang-900.0.39.2)
               gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.9)
               gcc version 7.2.0 (Debian 7.2.0-19)
 -----------------------------------------------------------------------------------
*/
#include <vector>

#include "l.h"

using namespace std;

Shapes L::POSITION_BASE = {
    Shape{Point{0,0,0}, Point{1,0,0}, Point{2,0,0}, Point{0,1,0}},
    Shape{Point{0,0,0}, Point{1,0,0}, Point{2,0,0}, Point{0,0,1}},
    Shape{Point{0,0,0}, Point{0,1,0}, Point{1,1,0}, Point{2,1,0}},
    Shape{Point{0,0,0}, Point{1,0,1}, Point{2,0,1}, Point{0,0,1}},

    Shape{Point{0,0,0}, Point{1,0,0}, Point{0,1,0}, Point{0,2,0}},
    Shape{Point{0,0,0}, Point{0,1,0}, Point{0,2,0}, Point{0,0,1}},
    Shape{Point{0,0,0}, Point{1,0,0}, Point{1,1,0}, Point{1,2,0}},
    Shape{Point{0,0,0}, Point{0,0,1}, Point{0,1,1}, Point{0,2,1}},

    Shape{Point{0,0,0}, Point{0,1,0}, Point{0,2,0}, Point{1,2,0}},
    Shape{Point{0,0,0}, Point{0,1,0}, Point{0,2,0}, Point{0,2,1}},
    Shape{Point{0,2,0}, Point{1,2,0}, Point{1,1,0}, Point{1,0,0}},
    Shape{Point{0,2,0}, Point{0,2,1}, Point{0,1,1}, Point{0,0,1}},

    Shape{Point{0,0,0}, Point{0,1,0}, Point{0,1,1}, Point{0,1,2}},
    Shape{Point{0,1,0}, Point{1,1,0}, Point{2,1,0}, Point{2,0,0}},
    Shape{Point{0,0,0}, Point{1,0,0}, Point{2,0,0}, Point{2,1,0}},
    Shape{Point{0,0,0}, Point{1,0,0}, Point{2,0,0}, Point{2,0,1}},

    Shape{Point{0,0,0}, Point{0,0,1}, Point{0,0,2}, Point{1,0,2}},
    Shape{Point{0,0,0}, Point{0,0,1}, Point{0,0,2}, Point{0,1,2}},
    Shape{Point{1,0,0}, Point{1,0,1}, Point{1,0,2}, Point{0,0,2}},
    Shape{Point{0,1,0}, Point{0,1,1}, Point{0,1,2}, Point{0,0,2}},

    Shape{Point{0,0,1}, Point{1,0,1}, Point{2,0,1}, Point{2,0,0}},
    Shape{Point{0,0,2}, Point{0,0,1}, Point{0,0,0}, Point{1,0,0}},
    Shape{Point{0,1,0}, Point{0,0,0}, Point{0,0,1}, Point{0,0,2}},
    Shape{Point{0,0,0}, Point{1,0,0}, Point{1,0,1}, Point{1,0,2}},
};

Shapes L::positions;
vector<uint_fast32_t> L::fast_positions;

void L::generateAllPositions() {
    std::cout << "Demarrage de la generation des solutions pour L... ";
    Piece::generateAllPositions<L>();
    std::cout << "Done, trouver : " << L::positions.size() << std::endl;
}

Pieces& L::initAllPositions(Pieces& p, unsigned id, bool display) {
    if(display) {
        std::cout << "Demarrage de l'initialiation des objets C... ";
    }
    return Piece::initAllPositions<L>(p, id, display);
}
