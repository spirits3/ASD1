/*
 -----------------------------------------------------------------------------------
 Laboratoire : ASD1 Cube magique
 Fichier     : puzzle.h
 Auteur(s)   : Jorge-André Fulgencio Esteves <jorgeand.fulgencioesteves@heig-vd.ch>,
               Florian Schaufelberger <florian.schaufelberger@heig-vd.ch>,
               Jonathan Zaehringer <jonathan.zaehringer@heig-vd.ch>

 Date        : 27.03.2018

 Compilateur : Apple LLVM version 9.0.0 (clang-900.0.39.2)
               gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.9)
               gcc version 7.2.0 (Debian 7.2.0-19)
 -----------------------------------------------------------------------------------
*/
#ifndef PUZZLE_H
#define PUZZLE_H

#include <vector>
#include <fstream>

#include "piece.h"

class Puzzle;

typedef std::vector<Puzzle> Puzzles;

class Puzzle {
    friend std::ostream& operator << (std::ostream&, const Puzzle&);
    
	private :
        uint_fast32_t fastcube;
        Pieces pieces;

    public :
        Puzzle();
        Puzzle(Piece piece);
        Pieces& getPieces();
        bool tryToInsert(const Piece& piece);
        void popLastPiece();
    void displayForVTK(std::ofstream& file);
};

#endif
