#ifndef HEXBOARD_H
#define HEXBOARD_H

#include "hex.h"

class HexBoard
{
public:
    //constructor
    HexBoard();

    QList<Hex*> getHexes();

    //public function
    void placeHexes(int x, int y, int nCols, int nRows);

private:
    void createHexColumn(int x, int y, int nRows);
    QList<Hex*> hexes;
};

#endif // HEXBOARD_H
