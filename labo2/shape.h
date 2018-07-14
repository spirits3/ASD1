/*
 -----------------------------------------------------------------------------------
 Laboratoire : ASD1 Cube magique
 Fichier     : shape.h
 Auteur(s)   : Jorge-André Fulgencio Esteves <jorgeand.fulgencioesteves@heig-vd.ch>,
               Florian Schaufelberger <florian.schaufelberger@heig-vd.ch>,
               Jonathan Zaehringer <jonathan.zaehringer@heig-vd.ch>

 Date        : 27.03.2018

 Compilateur : Apple LLVM version 9.0.0 (clang-900.0.39.2)
               gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.9)
               gcc version 7.2.0 (Debian 7.2.0-19)
 -----------------------------------------------------------------------------------
*/
#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <valarray>
#include <iostream>

typedef std::valarray<int> Point;
typedef std::vector<Point> Shape;

typedef std::vector<Shape> Shapes;

std::ostream& displayShape (const Shape& s, std::ostream& os = std::cout);
std::ostream& operator<< (std::ostream&, const Shape&);

#endif
