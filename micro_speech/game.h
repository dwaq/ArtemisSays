/* 
This library handles the state machine for the game
==============================================================================*/

#ifndef GAME_H_
#define GAME_H_

class ArtemisSays {
  public:
    // list of the states for the game
    enum GAME_STATES {
      WAIT_FOR_GO = 0,
      START_GAME = 1
    };

    enum GAME_STATES getState(void);
    void changeState(enum GAME_STATES newState);

  private:
    // start at the beginning
    // TODO: do I need a state for the splash screen prior to this? 
    enum GAME_STATES state = WAIT_FOR_GO;
};

#endif  // GAME_H_