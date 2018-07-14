/*
 -----------------------------------------------------------------------------------
 Laboratoire : ASD1 Cube magique
 Fichier     : piece.h
 Auteur(s)   : Jorge-André Fulgencio Esteves <jorgeand.fulgencioesteves@heig-vd.ch>,
               Florian Schaufelberger <florian.schaufelberger@heig-vd.ch>,
               Jonathan Zaehringer <jonathan.zaehringer@heig-vd.ch>

 Date        : 27.03.2018

 Compilateur : Apple LLVM version 9.0.0 (clang-900.0.39.2)
               gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.9)
               gcc version 7.2.0 (Debian 7.2.0-19)
 -----------------------------------------------------------------------------------
*/
#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <algorithm>
#include <valarray>
#include <iostream>
#include <string>

#include "shape.h"

uint_fast32_t toFastPiece(const Shape& s);

class Piece;

typedef std::vector<Piece> Pieces;

class Piece {
friend std::ostream& operator << (std::ostream& os, const Piece& p);
friend bool operator < (const Piece&, const Piece&);
friend bool operator > (const Piece&, const Piece&);
friend bool operator == (const Piece&, const Piece&);

private :
    Shape shape;
    uint_fast32_t mask;
    unsigned ownId;
    char name;

public :
    Piece();
    Piece(Shape shape, uint_fast32_t mask, unsigned ownId, char name);
    Shape getShape() const;
    uint_fast32_t getMask() const;
    unsigned getId() const;
    char getName() const;

    template<typename T>
    static void generateAllPositions(int xMax = 3, int yMax = 3, int zMax = 3);

    template<typename T>
    static Pieces& initAllPositions(Pieces& pieces, unsigned id, bool display);
};

#include "piece_impl.h"

#endif
