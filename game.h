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
      WAIT_TO_START = 0,
      START_GAME = 1,
      END_GAME = 2,
      COMPLETE = 3
    };

    // list of directions that could be said
    enum DIRECTIONS {
      right = 1,
      left = 2,
      down = 3,
      up = 4
    };

    enum GAME_STATES getState(void);
    void checkResponse(enum DIRECTIONS direction);
    void nextLevel(void);
    void restartGame(void);
    void endGame(void);

  private:
    void displayDirection(enum DIRECTIONS direction);
    void setRandomDirection(void);
    void displaySequence(void);

    // start at the beginning
    enum GAME_STATES state = WAIT_TO_START;

    // store sequence
    DIRECTIONS sequence[MAX_MOVES];
    // the level you're on (or the number of moves available)
    int level = 0;
    // moves made so far
    int move = 0;
};

#endif  // GAME_H_