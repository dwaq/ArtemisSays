/* 
This library handles the state machine for the game
==============================================================================*/

#ifndef GAME_H_
#define GAME_H_

// assume nobody will make it past this many moves
#define MAX_MOVES 15

class ArtemisSays {
  public:
    // list of the states for the game
    enum GAME_STATES {
      WAIT_FOR_GO = 0,
      START_GAME = 1,
      END_GAME = 2
    };

    // list of directions that could be said
    enum DIRECTIONS {
      right = 1,
      left = 2,
      down = 3,
      up = 4
    };

    enum GAME_STATES getState(void);
    void changeState(enum GAME_STATES newState);
    void setRandomDirection(void);
    void displaySequence(void);
    void checkResponse(enum DIRECTIONS direction);
    void restartGame(void);

  private:
    // start at the beginning
    // TODO: do I need a state for the splash screen prior to this? 
    enum GAME_STATES state = WAIT_FOR_GO;

    // store sequence
    DIRECTIONS sequence[MAX_MOVES];
    // the level you're on (or the number of moves available)
    int level = 0;
    // moves made so far
    int moves = 0;
};

#endif  // GAME_H_