#include "hexboard.h"
#include "game.h"

extern Game* game;

HexBoard::HexBoard()    {

}

void HexBoard::placeHexes() {
    createHexColumn(100, 100, 5);
}

void HexBoard::createHexColumn(int x, int y, int nRows) {

    for(int i = 0; i < nRows; i++)  {
        Hex* hex = new Hex();
        hex->setPos(x, y + 82 * i);
        hexes.append(hex);
        game->m_gScene->addItem(hex);

    }
}
