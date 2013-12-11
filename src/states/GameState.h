#pragma once
#include "BaseState.h"
#include "../entities/Tetromino.h"
#include "../entities/Grid.h"
#include <allegro5/allegro.h>

class GameState : public BaseState {
public:
    GameState( ALLEGRO_DISPLAY* displayIn, ALLEGRO_EVENT_QUEUE* event_queueIn, std::stack<BaseState*>* statesIn );
    ~GameState();
    bool update( double delta );
    bool render();

private:
    bool checkCollision( Tetromino* tet );
    Tetromino* getRandomPiece( ALLEGRO_BITMAP* blockIn );
    double totalTime;
    Tetromino* currentPiece;
    Tetromino* nextPiece;
    int updateCounter;
    //std::vector<std::vector<Block*>> grid;
    Grid* grid;
    ALLEGRO_BITMAP* blockImg;

};