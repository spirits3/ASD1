#ifndef PIECE_IMPL_H
#define PIECE_IMPL_H

#include "piece.h"

template <typename T>
void Piece::generateAllPositions(int xMax, int yMax, int zMax) {
    for(int x = 0; x <= xMax; x++) {
        for(int y = 0; y <= yMax; y++) {
            for(int z = 0; z <= zMax; z++) {
                Point adder = {x,y,z};
                for(Shape& s: T::POSITION_BASE){
                    for(Point& p: s) {
                        p += adder;
                    }
                    if(none_of(s.begin(), s.end(), [](const Point& p){ return p.max() > 2; })){
                        T::positions.push_back(s);
                        T::fast_positions.push_back(toFastPiece(s));
                    }
                    for(Point& p: s) {
                        p -= adder;
                    }
                }
            }
        }
    }
}

template <typename T>
Pieces& Piece::initAllPositions(Pieces& pieces, unsigned id, bool display) {
    for(size_t i = 0; i < T::positions.size(); i++) {
        pieces.push_back(T(T::positions[i], T::fast_positions[i], id));
    }
    if(display) {
        std::cout << "Done" << std::endl;
    }
    return pieces;
}

#endif //PIECE_IMPL_H