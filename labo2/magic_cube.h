/*
 -----------------------------------------------------------------------------------
 Laboratoire : ASD1 Cube magique
 Fichier     : magic_cube.h
 Auteur(s)   : Jorge-André Fulgencio Esteves <jorgeand.fulgencioesteves@heig-vd.ch>,
               Florian Schaufelberger <florian.schaufelberger@heig-vd.ch>,
               Jonathan Zaehringer <jonathan.zaehringer@heig-vd.ch>

 Date        : 27.03.2018

 Compilateur : Apple LLVM version 9.0.0 (clang-900.0.39.2)
               gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.9)
               gcc version 7.2.0 (Debian 7.2.0-19)
 -----------------------------------------------------------------------------------
*/
#ifndef MAGIC_CUBE_H
#define MAGIC_CUBE_H

#include <vector>
#include <iostream>

#include "puzzle.h"

typedef std::vector<Pieces> ArrPieces;

void megaBruteForce(ArrPieces& allPieces, Puzzles& solutions);
void bruteForceMagicCube(const ArrPieces& allPieces, Puzzles& solutions);
//Decorator of recursive function
void bruteForceMagicCube(const ArrPieces& allPieces, Puzzles& solutions, Puzzle& puzzle, size_t index = 0);

void removeSolutionByPermutation(Puzzles& solutions);

int countSolutionMatching(Piece& piece, Puzzles& solutions);

#endif
