/*
 -----------------------------------------------------------------------------------
 Laboratoire : ASD1 Cube magique
 Fichier     : puzzle.cpp
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
#include <iostream>
#include <iomanip>

#include "puzzle.h"

using namespace std;

void Puzzle::displayForVTK(ofstream& file) {
    std::vector<int> tab(27, -1);

    for(Piece part : pieces) {
        Shape s = part.getShape();
        for(Point p : s) {
            tab[size_t(p[0] + 3 * p[1] + 9 * p[2])] = int(part.getId());
        }
    }

    for (int i = 2; i >= 0; i--) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                file << tab[size_t(3 * (i + 3 * j) + k)];
                if(k != 2) {
                    file << ",";
                }
            }
            file << ",";
        }
    }
    file << endl;
}

std::ostream& operator << (std::ostream& os, const Puzzle& rhs) {
    std::vector<int> tab(27, -1);

    for(Piece part : rhs.pieces) {
        Shape s = part.getShape();
        for(Point p : s) {
            tab[size_t(p[0] + 3 * p[1] + 9 * p[2])] = int(part.getId());
        }
    }

    for (int i = 2; i >= 0; i--) {
        for (int j = 0; j < 3; ++j) {
            os << "{";
            for (int k = 0; k < 3; ++k) {
                os << std::setw(2) << tab[size_t(3 * (i + 3 * j) + k)];
                if(k != 2) {
                    os << ", ";
                }
            }
            os << "}  ";
        }
        os << endl;
    } 
	os << endl;
	return os;
}

Puzzle::Puzzle()  : fastcube(0), pieces({}) {
}

Puzzle::Puzzle(Piece piece) : fastcube(0), pieces({}){
    tryToInsert(piece);
}

Pieces& Puzzle::getPieces() {
    return pieces;
}

bool Puzzle::tryToInsert(const Piece& piece) {
    if((fastcube & piece.getMask()) == 0) {
        fastcube += piece.getMask();
    
        pieces.push_back(piece);

        return true;
    }

    return false;
}

void Puzzle::popLastPiece() {
    fastcube -= pieces.back().getMask();

    pieces.pop_back();
}
