#pragma once
#include "BaseState.h"
#include "../blocks/Tetromino.h"
#include <allegro5/allegro.h>

class GameState : public BaseState {
public:
    GameState( ALLEGRO_DISPLAY* displayIn, ALLEGRO_EVENT_QUEUE* event_queueIn, std::stack<BaseState*>* statesIn );
    ~GameState();
    bool update( double delta );
    bool render();

private:
    bool checkCollision( Tetromino* tet );
    Tetromino* getRandomPiece();
    double totalTime;
    Tetromino* currentPiece;
    Tetromino* nextPiece;
    int updateCounter;
    Block grid[10][20];
};