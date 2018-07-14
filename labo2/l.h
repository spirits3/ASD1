/*
 -----------------------------------------------------------------------------------
 Laboratoire : ASD1 Cube magique
 Fichier     : l.h
 Auteur(s)   : Jorge-André Fulgencio Esteves <jorgeand.fulgencioesteves@heig-vd.ch>,
               Florian Schaufelberger <florian.schaufelberger@heig-vd.ch>,
               Jonathan Zaehringer <jonathan.zaehringer@heig-vd.ch>

 Date        : 27.03.2018

 Compilateur : Apple LLVM version 9.0.0 (clang-900.0.39.2)
               gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.9)
               gcc version 7.2.0 (Debian 7.2.0-19)
 -----------------------------------------------------------------------------------
*/
#ifndef L_H
#define L_H

#include <vector>

#include "piece.h"

class L : Piece {
    friend void Piece::generateAllPositions<L>(int, int, int);
    friend Pieces& Piece::initAllPositions<L>(Pieces&, unsigned id, bool display);

    static Shapes POSITION_BASE;
    static Shapes positions;
    static std::vector<uint_fast32_t> fast_positions;
    public :
        L(Shape shape, uint_fast32_t mask, unsigned id) : Piece(shape,  mask, id, 'L') {};
        static void generateAllPositions();
        static Pieces& initAllPositions(Pieces&, unsigned id, bool display = false);
};

#endif
