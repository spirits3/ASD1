/*
 -----------------------------------------------------------------------------------
 Laboratoire : ASD1 Cube magique
 Fichier     : c.h
 Auteur(s)   : Jorge-André Fulgencio Esteves <jorgeand.fulgencioesteves@heig-vd.ch>,
               Florian Schaufelberger <florian.schaufelberger@heig-vd.ch>,
               Jonathan Zaehringer <jonathan.zaehringer@heig-vd.ch>

 Date        : 27.03.2018

 Compilateur : Apple LLVM version 9.0.0 (clang-900.0.39.2)
               gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.9)
               gcc version 7.2.0 (Debian 7.2.0-19)
 -----------------------------------------------------------------------------------
*/
#ifndef C_H
#define C_H

#include <vector>

#include "piece.h"

class C : Piece {
    friend void Piece::generateAllPositions<C>(int, int, int);
    friend Pieces& Piece::initAllPositions<C>(Pieces&, unsigned id, bool display);

    static Shapes POSITION_BASE;
    static Shapes positions;
    static std::vector<uint_fast32_t> fast_positions;
    public :
        C(Shape shape, uint_fast32_t mask, unsigned id) : Piece(shape,  mask, id, 'C') {};
        static void generateAllPositions();
        static Pieces& initAllPositions(Pieces&, unsigned id, bool display = false);
};

#endif
