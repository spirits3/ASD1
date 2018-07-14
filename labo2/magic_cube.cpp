/*
 -----------------------------------------------------------------------------------
 Laboratoire : ASD1 Cube magique
 Fichier     : magic_cube.cpp
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
#include <ctime>
#include <string>

#include "magic_cube.h"
#include "puzzle.h"
#include "c.h"
#include "t.h"
#include "l.h"
#include "s.h"

void recursion(std::vector<ArrPieces>& allCombinations, ArrPieces& allPieces, unsigned index, int elemType, unsigned id) {
    Pieces temp;
	
	if(index >= 27) {
        return;
    }
	
    switch(elemType) {
        case 0:
            allPieces.push_back(C::initAllPositions(temp, id));
            index += 3;
            break;
        case 1:
            allPieces.push_back(T::initAllPositions(temp, id));
            index += 4;
            break;
        case 2:
            allPieces.push_back(S::initAllPositions(temp, id));
            index += 4;
            break;
        case 3:
            allPieces.push_back(L::initAllPositions(temp, id));
            index += 4;
            break;
        default:
            break;
	}
	
	if(index == 27 && id == 6) {
		allCombinations.push_back(allPieces);
	}
	
    for (int j = elemType; j < 4; ++j) {
        recursion(allCombinations, allPieces, index, j, id + 1);
    }
	
    allPieces.pop_back();
	
}


void megaBruteForce(ArrPieces& allPieces, Puzzles& solutions) {
    std::vector<ArrPieces> allCombinations;
	Pieces temp;
    ArrPieces minimalCombination;
    Puzzles   minimalSolution;

    std::cout << "Calcul des combinaisons des pieces T, L, S et C." << std::endl;
	recursion(allCombinations, allPieces, 0, 0, 0);
	
    std::cout << allCombinations.size() << " combinasions valables ont ete trouve." << std::endl << std::endl;
	
    for(ArrPieces tab : allCombinations) {
        Puzzles tempSolutions;

        std::cout << "Cette combinaison : ";
        for(Pieces p : tab) {
            std::cout << p.at(0).getName() << " ";
        }
        std::cout << std::endl;

        bruteForceMagicCube(tab, tempSolutions);
		removeSolutionByPermutation(tempSolutions);

        std::cout << std::endl;

        if(tempSolutions.size() != 0) {
            if(tempSolutions.size() < minimalSolution.size()) {
                minimalCombination = tab;
                minimalSolution = tempSolutions;
            }

            solutions.insert(solutions.end(), tempSolutions.begin(), tempSolutions.end());
        }

        solutions.push_back(Puzzle());
        tempSolutions.clear();
    }

    std::cout << "Combinaison ayant le moin de solution est ";
    for(Pieces p : minimalCombination) {
        std::cout << p.at(0).getName() << " ";
    }
    std::cout << std::endl;

    std::cout << "Avec les solutions suivantes : " << std::endl;
    for(Puzzle& p : minimalSolution) {
        std::cout << p;
    }
    std::cout << std::endl;
}

void bruteForceMagicCube(const ArrPieces& allPieces, Puzzles& solutions) {
    Puzzle puzzle;
    std::cout << "\rEn cours de Brute force (trouver : 0)... ";

    auto now = time(nullptr);

    bruteForceMagicCube(allPieces, solutions, puzzle, allPieces.size());

    std::cout << "Fini en " << time(nullptr) - now << "[s]" << std::endl;
}

void bruteForceMagicCube(const ArrPieces& allPieces, Puzzles& solutions, Puzzle& puzzle, size_t index) {
    if (index == 0) {
        solutions.push_back(puzzle);
        std::cout << std::flush << "\rEn cours de Brute force (trouver : " << solutions.size() << ")... ";
        return;
    }
    
    for (const Piece& p : allPieces.at(index - 1)) {
        if(puzzle.tryToInsert(p)) {
            bruteForceMagicCube(allPieces, solutions, puzzle, index - 1);
            puzzle.popLastPiece();
        }
    }
}

void removeSolutionByPermutation(Puzzles& solutions) {
	if(solutions.size() < 2) {
		return;
	}
	
    Puzzles baseSolutions(solutions);
    solutions.clear();

    std::cout << "\rEn cours de suppression des solutions a double (trouver : 0)... ";
    for(Puzzle& p: baseSolutions) {
        sort(p.getPieces().begin(), p.getPieces().end());
    }

    for(auto iter = baseSolutions.begin() + 1; iter != baseSolutions.end(); iter++) {

        if(none_of(solutions.begin(), solutions.end(), [iter](Puzzle& comp){ return comp.getPieces() == iter->getPieces(); })) {
            solutions.push_back(*iter);
            std::cout << std::flush << "\rEn cours de suppression des solutions a double (trouver : " << solutions.size() << ")... ";
        }

    }

    std::cout << "Done" << std::endl;
}

int countSolutionMatching(Piece& piece, Puzzles& puzzles) {

    int count = 0;
    for(Puzzle& puzzle : puzzles) {
        for(Piece& p : puzzle.getPieces()) {
            if(p == piece) {
                ++count;
            }
        }
    }
    return count;
}
