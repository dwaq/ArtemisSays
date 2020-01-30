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

#include "am_bsp.h"  // NOLINT

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
    // it has been said, so move to the next level
    game.nextLevel();

    // go to the next state
    game.changeState(ArtemisSays::START_GAME);
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
    am_hal_gpio_pinconfig(AM_BSP_GPIO_LED_BLUE, g_AM_HAL_GPIO_OUTPUT_12);
    am_hal_gpio_pinconfig(UNKNOWN_LED, g_AM_HAL_GPIO_OUTPUT_12);
    am_hal_gpio_pinconfig(YES_LED, g_AM_HAL_GPIO_OUTPUT_12);
    am_hal_gpio_pinconfig(NO_LED, g_AM_HAL_GPIO_OUTPUT_12);
    am_hal_gpio_pinconfig(UP_LED, g_AM_HAL_GPIO_OUTPUT_12);
    am_hal_gpio_pinconfig(DOWN_LED, g_AM_HAL_GPIO_OUTPUT_12);
    am_hal_gpio_pinconfig(LEFT_LED, g_AM_HAL_GPIO_OUTPUT_12);
    am_hal_gpio_pinconfig(RIGHT_LED, g_AM_HAL_GPIO_OUTPUT_12);
    am_hal_gpio_pinconfig(GO_LED, g_AM_HAL_GPIO_OUTPUT_12);
    is_initialized = true;
  }
  static int count = 0;

  // Toggle the blue LED every time an inference is performed.
  ++count;
  if (count & 1) {
    am_hal_gpio_output_set(AM_BSP_GPIO_LED_BLUE);
  } else {
    am_hal_gpio_output_clear(AM_BSP_GPIO_LED_BLUE);
  }

  // Clear all LEDs, then turn the specific one on
  am_hal_gpio_output_clear(UNKNOWN_LED);
  am_hal_gpio_output_clear(YES_LED);
  am_hal_gpio_output_clear(NO_LED);
  am_hal_gpio_output_clear(UP_LED);
  am_hal_gpio_output_clear(DOWN_LED);
  am_hal_gpio_output_clear(LEFT_LED);
  am_hal_gpio_output_clear(RIGHT_LED);
  am_hal_gpio_output_clear(GO_LED);

  if (is_new_command) {
    error_reporter->Report("Heard %s (%d) @%dms", found_command, score,
                           current_time);
    if (found_command[1] == 'n') {
      error_reporter->Report("\nUNKNOWN");
      am_hal_gpio_output_set(UNKNOWN_LED);
    }
    else if (found_command[0] == 'y') {
      error_reporter->Report("\nYES");
      am_hal_gpio_output_set(YES_LED);

      // if game has ended
      if (game.getState() == ArtemisSays::END_GAME) {
        // restart the game
        game.restartGame();
      }
    }
    else if (found_command[0] == 'n') {
      error_reporter->Report("\nNO");
      am_hal_gpio_output_set(NO_LED);

      // Sometimes "go" is interpreted as "no"
      // so just let it work the same way
      startOrEndGame();
    }
    else if (found_command[0] == 'u') {
      error_reporter->Report("\nUP");
      am_hal_gpio_output_set(UP_LED);

      // if game is started
      if (game.getState() == ArtemisSays::START_GAME) {
        // check that the correct direction has been said
        game.checkResponse(ArtemisSays::up);
      }
    }
    else if (found_command[0] == 'd') {
      error_reporter->Report("\nDOWN");
      am_hal_gpio_output_set(DOWN_LED);

      // if game is started
      if (game.getState() == ArtemisSays::START_GAME) {
        // check that the correct direction has been said
        game.checkResponse(ArtemisSays::down);
      }
    }
    else if (found_command[0] == 'l') {
      error_reporter->Report("\nLEFT");
      am_hal_gpio_output_set(LEFT_LED);

      // if game is started
      if (game.getState() == ArtemisSays::START_GAME) {
        // check that the correct direction has been said
        game.checkResponse(ArtemisSays::left);
      }
    }
    else if (found_command[0] == 'r') {
      error_reporter->Report("\nRIGHT");
      am_hal_gpio_output_set(RIGHT_LED);

      // if game is started
      if (game.getState() == ArtemisSays::START_GAME) {
        // check that the correct direction has been said
        game.checkResponse(ArtemisSays::right);
      }
    }
    else if (found_command[0] == 'g') {
      error_reporter->Report("\nGO");
      am_hal_gpio_output_set(GO_LED);

      // Sometimes "go" is interpreted as "no"
      // so just let it work the same way
      startOrEndGame();
    }
  }
}
