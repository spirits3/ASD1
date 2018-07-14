/*
 -----------------------------------------------------------------------------------
 Laboratoire : ASD1 Cube magique
 Fichier     : shape.cpp
 Auteur(s)   : Jorge-André Fulgencio Esteves <jorgeand.fulgencioesteves@heig-vd.ch>,
               Florian Schaufelberger <florian.schaufelberger@heig-vd.ch>,
               Jonathan Zaehringer <jonathan.zaehringer@heig-vd.ch>

 Date        : 27.03.2018

 Compilateur : Apple LLVM version 9.0.0 (clang-900.0.39.2)
               gcc version 5.4.0 20160609 (Ubuntu 5.4.0-6ubuntu1~16.04.9)
               gcc version 7.2.0 (Debian 7.2.0-19)
 -----------------------------------------------------------------------------------
*/
#include <iostream>

#include "shape.h"

std::ostream& displayShape (const Shape& s, std::ostream& os){
    os << "[";
    for(const Point& p : s) {
        os << "(" << p[0] << "," << p[1] << "," << p[2] << ")";
    }

    os << "]";
    
    return os;
}

std::ostream& operator<< (std::ostream& os, const Shape& rhs){
    return displayShape(rhs, os);
}
