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

void ArtemisSays::checkResponse(enum DIRECTIONS direction) {
  // draw the shape to match the direction said
  switch (direction) {
    case right:
      drawRight();
      break;
    case left:
      drawLeft();
      break;
    case down:
      drawDown();
      break;
    case up:
      drawUp();
      break;
  }

  // check that direction said matches the current move
  if (direction == sequence[move]) {
    // go to next move
    move++;

    // when all moves are complete, go to the next level
    if (move == level) {
      // prepare for next level
      ArtemisSays::setRandomDirection();
    }
  }
  // incorrect thing said
  else {
    // show losing text
    displayReplayScreen();

    // wait to decide what's next
    state = END_GAME;
  }
}

void ArtemisSays::restartGame(void) {
  // reset variables
  level = 0;
  move = 0;

  // TODO: call startGame() somehow
}

void ArtemisSays::endGame(void) {
  // go into another state so voice commands stop working
  state = COMPLETE;

  displayEndGame();
  // TODO: Go into low power mode or something
}