#include "hexboard.h"
#include "game.h"

extern Game* game;

HexBoard::HexBoard()    {

}

QList<Hex *> HexBoard::getHexes()
{
    return hexes;
}

void HexBoard::placeHexes(int x, int y, int nCols, int nRows) {

    int XSHIFT = 82;
    int YSHIFT = 41;
    for(auto i = 0; i < nCols; i++) {
        createHexColumn(x + XSHIFT * i, y + YSHIFT * (i % 2), nRows);
    }
}

void HexBoard::createHexColumn(int x, int y, int nRows) {
    int YSHIFT = 82;
    for(int i = 0; i < nRows; i++)  {
        Hex* hex = new Hex();
        hex->setPos(x, y + YSHIFT * i);
        hexes.append(hex);
        game->m_gScene->addItem(hex);
        hex->setOwner(Noone);

    }
}
