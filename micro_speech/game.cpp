/* 
This library handles the state machine for the game
==============================================================================*/

#include "game.h"

// get the state
enum ArtemisSays::GAME_STATES ArtemisSays::getState(void) {
  return state;
}

// change the state
void ArtemisSays::changeState(enum GAME_STATES newState) {
  state = newState;
}