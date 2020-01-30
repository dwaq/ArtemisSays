/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "command_responder.h"

#include <Arduino.h>

#include "game.h"

// class for the game state machine
ArtemisSays game;

// Pins on the top right header (in order)
#define UNKNOWN_LED 14
#define YES_LED 8
#define NO_LED 10
#define UP_LED 9
#define DOWN_LED 26 
#define LEFT_LED 15
#define RIGHT_LED 19
#define GO_LED 18

void startOrEndGame(void) {
  // if we're waiting to start the game
  if (game.getState() == ArtemisSays::WAIT_TO_START) {
    // it has been said, so move to the first level
    game.nextLevel();
  }
  // going to end the game
  else if (game.getState() == ArtemisSays::END_GAME) {
    game.endGame();
  }
}

// This implementation will light up the LEDs on the board in response to
// different commands.
void RespondToCommand(tflite::ErrorReporter* error_reporter,
                      int32_t current_time, const char* found_command,
                      uint8_t score, bool is_new_command) {
  static bool is_initialized = false;
  if (!is_initialized) {
    // Setup LED's as outputs
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(UNKNOWN_LED, OUTPUT);
    pinMode(YES_LED, OUTPUT);
    pinMode(NO_LED, OUTPUT);
    pinMode(UP_LED, OUTPUT);
    pinMode(DOWN_LED, OUTPUT);
    pinMode(LEFT_LED, OUTPUT);
    pinMode(RIGHT_LED, OUTPUT);
    pinMode(GO_LED, OUTPUT);
    is_initialized = true;
  }
  static int count = 0;

  // Toggle the blue LED every time an inference is performed.
  ++count;
  if (count & 1) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }

  // Clear all LEDs, then turn the specific one on
  digitalWrite(UNKNOWN_LED, LOW);
  digitalWrite(YES_LED, LOW);
  digitalWrite(NO_LED, LOW);
  digitalWrite(UP_LED, LOW);
  digitalWrite(DOWN_LED, LOW);
  digitalWrite(LEFT_LED, LOW);
  digitalWrite(RIGHT_LED, LOW);
  digitalWrite(GO_LED, LOW);

  if (is_new_command) {
    error_reporter->Report("Heard %s (%d) @%dms", found_command, score,
                           current_time);
    if (found_command[1] == 'n') {
      error_reporter->Report("\nUNKNOWN");
      digitalWrite(UNKNOWN_LED, HIGH);
    }
    else if (found_command[0] == 'y') {
      error_reporter->Report("\nYES");
      digitalWrite(YES_LED, HIGH);

      // if game has ended
      if (game.getState() == ArtemisSays::END_GAME) {
        // restart the game
        game.restartGame();
      }
    }
    else if (found_command[0] == 'n') {
      error_reporter->Report("\nNO");
      digitalWrite(NO_LED, HIGH);

      // Sometimes "go" is interpreted as "no"
      // so just let it work the same way
      startOrEndGame();
    }
    else if (found_command[0] == 'u') {
      error_reporter->Report("\nUP");
      digitalWrite(UP_LED, HIGH);

      // if game is started
      if (game.getState() == ArtemisSays::START_GAME) {
        // check that the correct direction has been said
        game.checkResponse(ArtemisSays::up);
      }
    }
    else if (found_command[0] == 'd') {
      error_reporter->Report("\nDOWN");
      digitalWrite(DOWN_LED, HIGH);

      // if game is started
      if (game.getState() == ArtemisSays::START_GAME) {
        // check that the correct direction has been said
        game.checkResponse(ArtemisSays::down);
      }
    }
    else if (found_command[0] == 'l') {
      error_reporter->Report("\nLEFT");
      digitalWrite(LEFT_LED, HIGH);

      // if game is started
      if (game.getState() == ArtemisSays::START_GAME) {
        // check that the correct direction has been said
        game.checkResponse(ArtemisSays::left);
      }
    }
    else if (found_command[0] == 'r') {
      error_reporter->Report("\nRIGHT");
      digitalWrite(RIGHT_LED, HIGH);

      // if game is started
      if (game.getState() == ArtemisSays::START_GAME) {
        // check that the correct direction has been said
        game.checkResponse(ArtemisSays::right);
      }
    }
    else if (found_command[0] == 'g') {
      error_reporter->Report("\nGO");
      digitalWrite(GO_LED, HIGH);

      // Sometimes "go" is interpreted as "no"
      // so just let it work the same way
      startOrEndGame();
    }
  }
}
