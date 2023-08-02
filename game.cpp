#include "game.h"
#include "button.h"
#include<QDebug>


Game::Game(QWidget *parent)
    :m_eCurrentPlayer(Player1)
    ,m_gCardToPlace(nullptr)
{
    //set up screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024, 650);

    //set up scene
    m_gScene = new QGraphicsScene();
    m_gScene->setSceneRect(0, 0, 1024, 650);
    setScene(m_gScene);

    //seed random number to generate random attack value
    std::random_device rd; // Seed for random engine.
    m_rRandomEngine.seed(rd());

}

void Game::start()  {
    //clear screen
    m_gScene->clear();

    m_gHexBoard  = new HexBoard();
    m_gHexBoard->placeHexes(210, 30, 7, 7);
    drawGUI();
    createInitialCards();
}

void Game::drawPanel(int x, int y, int width, int height, QColor color, double opacity) {

    QGraphicsRectItem* panel = new QGraphicsRectItem(x, y, width, height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity);

    m_gScene->addItem(panel);

}

void Game::drawGUI() {
    //draw left panel
    drawPanel(0, 0, 150, height(), Qt::darkCyan);

    //draw the right panel
    drawPanel(width() - 150, 0, 150, height(), Qt::darkCyan);

    //Place Player1 text;
    QGraphicsTextItem* player1Text = new QGraphicsTextItem(QString("Player 1's cards:"));
    player1Text->setPos(25, 0);
    m_gScene->addItem(player1Text);

    //Place Player2 text;
    QGraphicsTextItem* player2Text = new QGraphicsTextItem(QString("Player 2's cards:"));
    player2Text->setPos(width() - 125, 0);
    m_gScene->addItem(player2Text);

    //Place the current player text
    m_gCurrentPlayerText = new QGraphicsTextItem();
    setCurrentPlayer(m_eCurrentPlayer);
    m_gCurrentPlayerText->setPos(450, 0);
    m_gScene->addItem(m_gCurrentPlayerText);

}

void Game::createNewCard(Player player) {
    //create new card
    Hex* card = new Hex();
    card->setOwner(player);
    card->setIsPlaced(false);

    //randomise side attack of card
    std::uniform_int_distribution<int> distribution(1, 6);
    for(auto i = 0; i < 6; i++) {
        int randomNum = distribution(m_rRandomEngine);
        card->setAttackof(i, randomNum);
    }
    card->displaySideAttack();
    //add to proper list
    if(player == Player1) {
        m_gPlayer1Cards.append(card);
    }
    else {
        m_gPlayer2Cards.append(card);
    }

    //draw the card
    drawCards();

}

void Game::createInitialCards() {
    //create player1's cards
    for(auto i = 0; i < 5; i++) {
        createNewCard(Player1);
    }

    //create player2's cards
    for(auto i = 0; i < 5; i++) {
        createNewCard(Player2);
    }

    drawCards();
}

void Game::drawCards()
{
    //remove cards from scene from player1
    foreach(auto card, m_gPlayer1Cards) {
        m_gScene->removeItem(card);
    }

    //remove cards from scene from player2
    foreach(auto card, m_gPlayer2Cards) {
        m_gScene->removeItem(card);
    }

    //draw cards from scene from player1
    for(auto i = 0; i < m_gPlayer2Cards.size(); i++) {
        auto card = m_gPlayer2Cards[i];
        card->setPos(width() - 150 + 13, 25 + 85 * i);
        m_gScene->addItem(card);
    }

    //draw cards from scene from player2
    for(auto i = 0; i < m_gPlayer1Cards.size(); i++) {
        auto card = m_gPlayer1Cards[i];
        card->setPos(13, 25 + 85 * i);
        m_gScene->addItem(card);
    }
}

void Game::removeFromDeck(Hex *card, Player player) {

    if(player == Player1) {
        //remove from player1
        m_gPlayer1Cards.removeAll(card);
    }
    else {
        m_gPlayer2Cards.removeAll(card);
    }

    drawCards();
}

void Game::nextPlayersTurn()
{
    if(getCurrentPlayer() == Player1) {
        setCurrentPlayer(Player2);
    }
    else {
        setCurrentPlayer(Player1);
    }
}

void Game::DisplayMainMenu() {
    //Create the title Text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("HEXTY"));
    QFont titleFont("comic sans", 50);
    titleText->setFont(titleFont);

    int xpos = this->width() / 2 - titleText->boundingRect().width() / 2;
    int ypos = this->height() / 2 - titleText->boundingRect().height();

    titleText->setPos(xpos, ypos);
    m_gScene->addItem(titleText);

    //Create the play button
    Button* playButton = new Button(QString("Play"));
    xpos = this->width() / 2 - titleText->boundingRect().width() / 2;
    ypos = this->height() / 2;

    playButton->setPos(xpos, ypos);
    connect(playButton, SIGNAL(clicked()), this, SLOT(start()));
    m_gScene->addItem(playButton);

    //create quit button
    Button* quitButton = new Button(QString("Quit"));
    ypos = ypos + 3 * quitButton->boundingRect().height() / 2;

    quitButton->setPos(xpos, ypos);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    m_gScene->addItem(quitButton);


}

Player Game::getCurrentPlayer() {

    return m_eCurrentPlayer;
}

void Game::setCurrentPlayer(Player nextPlayer)
{
    //set player text
    QString player;
    if(nextPlayer == Player1) {
        player = "Player 1";
    }
    else {
        player = "Player 2";
    }
    m_eCurrentPlayer = nextPlayer;
    //set player turn text
    m_gCurrentPlayerText->setPlainText(QString("Whose Turn: ") + player);
}

void Game::pickUpCard(Hex *card)
{
    if(card->getOwner() == getCurrentPlayer() && !m_gCardToPlace) {
        qDebug() << "Card is being picked up";
        qDebug() << getCurrentPlayer();
        m_gCardToPlace = card;
        m_pOriginalPos = card->pos();
        return;
    }
}

void Game::placeCard(Hex *hexToReplace)
{
    //Replaces the specified Hex to card to place
    if(m_gCardToPlace) {
        qDebug() <<"Card is Place";
        m_gCardToPlace->setPos(hexToReplace->pos());
        m_gHexBoard->getHexes().removeAll(hexToReplace);
        m_gHexBoard->getHexes().append(m_gCardToPlace);
        m_gScene->removeItem(hexToReplace);
        delete hexToReplace;

        m_gCardToPlace->setIsPlaced(true);
        removeFromDeck(m_gCardToPlace, getCurrentPlayer());

        m_gCardToPlace = nullptr;

        //replace the space with new card
        createNewCard(getCurrentPlayer());
        //make it next players turn
        nextPlayersTurn();
    }
}

void Game::mouseMoveEvent(QMouseEvent *event) {

    //if there is a card to place make it follow the mouse
    if(m_gCardToPlace) {
        m_gCardToPlace->setPos(event->pos());
    }

    QGraphicsView::mouseMoveEvent(event);
}

void Game::mousePressEvent(QMouseEvent* event) {

    if(event->button() == Qt::RightButton) {
        if(m_gCardToPlace) {
            m_gCardToPlace->setPos(m_pOriginalPos);
            m_gCardToPlace = nullptr;
            return;
        }
    }

    QGraphicsView::mousePressEvent(event);
}
