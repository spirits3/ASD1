/*
 -----------------------------------------------------------------------------------
 Laboratoire : ASD1 Cube magique
 Fichier     : piece.cpp
 Auteur(s)   : Jorge-André Fulgencio Esteves <jorgeand.fulgencioesteves@heig-vd.ch>,
               Florian Schaufelberger <florian.schaufelberger@heig-vd.ch>,
               Jonathan Zaehringer <jonathan.zaehringer@heig-vd.ch>

 Date        : 27.03.2018

 Compilateur : Apple LLVM version 9.0.0 (clang-900.0.39.2)
               gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.9)
               gcc version 7.2.0 (Debian 7.2.0-19)
 -----------------------------------------------------------------------------------
*/
#include <bitset>

#include "piece.h"

bool operator < (const Piece& lhs, const Piece& rhs) {
    return lhs.mask < rhs.mask;
}

bool operator > (const Piece& lhs, const Piece& rhs) {
    return rhs.mask > lhs.mask;
}

bool operator == (const Piece& lhs, const Piece& rhs) {
    return lhs.mask == rhs.mask;
}

uint_fast32_t toFastPiece(const Shape& s) {
    uint_fast32_t mask = 0;

    for(const Point& p : s) {
        mask += 1<<(p[0] + p[1] * 3 + p[2] * 9);
    }

    return mask;
}

Piece::Piece() :shape(Shape()), mask(0), ownId(0), name(0) {

}

Piece::Piece(Shape shape, uint_fast32_t mask, unsigned ownId, char name) : shape(shape), mask(mask), ownId(ownId), name(name){
}

Shape Piece::getShape() const {
    return shape;
}

unsigned Piece::getId() const{
    return ownId;
}

uint_fast32_t Piece::getMask() const {
    return mask;
}

char Piece::getName() const {
    return name;
}

/*
std::ostream& operator << (std::ostream& os, const Piece& p) {
    std::bitset<27> x(p.mask);

    os << "[mask: " << x << ", shape: " << p.shape << "]";
    return os;
}
*/
