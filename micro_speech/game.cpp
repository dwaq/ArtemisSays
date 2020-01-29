/* 
This library handles the state machine for the game
==============================================================================*/

#include "game.h"
#include "display.h"
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

void ArtemisSays::displaySequence(void) {
  int position = 0;

  // loop through each sequence
  while (position < level) {
    // get this position's direction
    enum DIRECTIONS direction = sequence[position];

    // draw that position
    if (direction == right) {
      drawRight();
    }
    else if (direction == left) {
      drawLeft();
    }
    else if (direction == down) {
      drawDown();
    }
    else if (direction == up) {
      drawUp();
    }

    // delay a bit
    // TODO: what is the actual game's delay time?
    delay(500);

    // go to next position
    position++;
  }
}

void ArtemisSays::restartGame(void) {
  // reset variables
  level = 0;
  moves = 0;

  // TODO: call startGame() somehow
}