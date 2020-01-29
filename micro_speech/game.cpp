/* 
This library handles the state machine for the game
==============================================================================*/

#include "game.h"
#include <Arduino.h>

// get the state
enum ArtemisSays::GAME_STATES ArtemisSays::getState(void) {
  return state;
}

// change the state
void ArtemisSays::changeState(enum GAME_STATES newState) {
  state = newState;
}

void ArtemisSays::setRandomDirection(void) {
  // get a random direction
  enum DIRECTIONS direction = (DIRECTIONS) random(1, 5);

  // set the direction into the sequence
  sequence[level] = direction;

  // increase level
  level++;
}