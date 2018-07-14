/*
 -----------------------------------------------------------------------------------
 Laboratoire : ASD1 Cube magique
 Fichier     : main.cpp
 Auteur(s)   : Jorge-André Fulgencio Esteves <jorgeand.fulgencioesteves@heig-vd.ch>,
               Florian Schaufelberger <florian.schaufelberger@heig-vd.ch>,
               Jonathan Zaehringer <jonathan.zaehringer@heig-vd.ch>

 Date        : 27.03.2018

 Compilateur : Apple LLVM version 9.0.0 (clang-900.0.39.2)
               gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.9)
               gcc version 7.2.0 (Debian 7.2.0-19)
 -----------------------------------------------------------------------------------
*/
#include <cstdlib>
#include <vector>

#include "c.h"
#include "t.h"
#include "l.h"
#include "s.h"
#include "puzzle.h"
#include "magic_cube.h"

using namespace std;


int main () {

    cout << "Generation des translations de toutes les pièces" << endl << endl;

    //generation des translations
    C::generateAllPositions();
    T::generateAllPositions();
    L::generateAllPositions();
    S::generateAllPositions();

    cout << endl << endl;

    ArrPieces allPieces;
    Pieces temp;

    //Stockage de l'ensemble des solutions sous forme d'objet
    allPieces.push_back(L::initAllPositions(temp, 0));
    temp.clear();
    allPieces.push_back(L::initAllPositions(temp, 1));
    temp.clear();
    allPieces.push_back(L::initAllPositions(temp, 2));
    temp.clear();
    allPieces.push_back(L::initAllPositions(temp, 3));
    temp.clear();
    allPieces.push_back(T::initAllPositions(temp, 4));
    temp.clear();
    allPieces.push_back(S::initAllPositions(temp, 5));
    temp.clear();
    allPieces.push_back(C::initAllPositions(temp, 6));
    temp.clear();

    //Brute force de l'ensemble des solutions
    Puzzles allSolutions;
    bruteForceMagicCube(allPieces, allSolutions);

    //Suppression des permutations des pièces semblables
    Puzzles solutions(allSolutions);
    removeSolutionByPermutation(solutions);

    cout << endl;

    // Ecriture dans un fichier de l'ensemble des solutions
    ofstream file;
    file.open("allSolutions.txt");
    for(Puzzle p : solutions) {
        p.displayForVTK(file);
    }
    file.close();

    cout << "Recherche des positions de la piece C ne donnant aucune solution : " << endl << endl;

    // Detection des pièces C ne donnant aucune solution
    file.open("cWithOutSolution.txt");
    for(Piece& p : allPieces.back()){
        int count = countSolutionMatching(p, solutions);
        Puzzle puzzle(p);

        if(count == 0) {
            cout << "Position du C ne donnant aucune solution : " << endl;
            puzzle.displayForVTK(file);
            cout << puzzle << endl;
        }
    }
    file.close();

    cout << "Recherche des possibilités de combinaisons avec les pièces C,L,T,S : " << endl << endl;

    //Brute force solutions avec des combinaisons différentes de pièce
	allPieces.clear();
    solutions.clear();
    megaBruteForce(allPieces, solutions);

    // Ecriture dans un fichier de l'ensemble des solutions des combinaisons
	file.open("allCombinaisons.txt");
    for(Puzzle p : solutions) {
        p.displayForVTK(file);
    }
    file.close();

    return EXIT_SUCCESS;
}

