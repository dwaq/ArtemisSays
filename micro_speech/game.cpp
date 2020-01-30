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

void ArtemisSays::checkResponse(enum DIRECTIONS direction) {
  // draw the shape to match the direction said
  displayDirection(direction);

  // check that direction said matches the current move
  if (direction == sequence[move]) {
    // go to next move
    move++;

    // when all moves are complete, go to the next level
    if (move == level) {
      // prepare for next level
      ArtemisSays::nextLevel();
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

// set up the next level
void ArtemisSays::nextLevel(void) {
  // set a next direction
  ArtemisSays::setRandomDirection();

  // display the upcoming sequence
  ArtemisSays::displaySequence();

  // start the game
  state = START_GAME;
}

void ArtemisSays::restartGame(void) {
  // reset variables
  level = 0;
  move = 0;
  state = WAIT_TO_START;

  // TODO: call startGame() somehow
}

void ArtemisSays::endGame(void) {
  // go into another state so voice commands stop working
  state = COMPLETE;

  // display final screen
  displayEndGame();
  
  // go into low power mode - wake it up with the reset button
  // based on code from Artemis Example: LowPower
  // TODO: PDM microphones (2) - ~50.9uA should also be powered off
#if defined(ARDUINO_SFE_EDGE2)
  pinMode(ACCEL_VDD, OUTPUT);
  digitalWrite(ACCEL_VDD, LOW);

  pinMode(MIC_VDD, OUTPUT);
  digitalWrite(MIC_VDD, LOW);

  pinMode(CAMERA_VDD, OUTPUT);
  digitalWrite(CAMERA_VDD, LOW);
#endif

  // Turn off ADC
  power_adc_disable();

  // Initialize for low power in the power control block
  am_hal_pwrctrl_low_power_init();

  // Stop the XTAL
  am_hal_clkgen_control(AM_HAL_CLKGEN_CONTROL_XTAL_STOP, 0);

  // Disable the RTC
  am_hal_rtc_osc_disable();

  // Disabling the debugger GPIOs saves about 1.2 uA total
  am_hal_gpio_pinconfig(20 /* SWDCLK */, g_AM_HAL_GPIO_DISABLE);
  am_hal_gpio_pinconfig(21 /* SWDIO */, g_AM_HAL_GPIO_DISABLE);

  // These two GPIOs are critical: the TX/RX connections between the Artemis module and the CH340S on the Blackboard
  // are prone to backfeeding each other. To stop this from happening, we must reconfigure those pins as GPIOs
  // and then disable them completely.
  am_hal_gpio_pinconfig(48 /* TXO-0 */, g_AM_HAL_GPIO_DISABLE);
  am_hal_gpio_pinconfig(49 /* RXI-0 */, g_AM_HAL_GPIO_DISABLE);

  // The default Arduino environment runs the System Timer (STIMER) off the 48 MHZ HFRC clock source.
  // The HFRC appears to take over 60 uA when it is running, so this is a big source of extra
  // current consumption in deep sleep.
  // For systems that might want to use the STIMER to generate a periodic wakeup, it needs to be left running.
  // However, it does not have to run at 48 MHz. If we reconfigure STIMER (system timer) to use the 32768 Hz
  // XTAL clock source instead the measured deepsleep power drops by about 64 uA.
  am_hal_stimer_config(AM_HAL_STIMER_CFG_CLEAR | AM_HAL_STIMER_CFG_FREEZE);

  // This option selects 32768 Hz via crystal osc. This appears to cost about 0.1 uA versus selecting "no clock".
  am_hal_stimer_config(AM_HAL_STIMER_XTAL_32KHZ);

  // This option would be available to systems that don't care about passing time, but might be set
  // to wake up on a GPIO transition interrupt.
  // am_hal_stimer_config(AM_HAL_STIMER_NO_CLK);

  // Turn OFF Flash1
  if (am_hal_pwrctrl_memory_enable(AM_HAL_PWRCTRL_MEM_FLASH_512K))
  {
    while (1);
  }

  // Power down SRAM
  PWRCTRL->MEMPWDINSLEEP_b.SRAMPWDSLP = PWRCTRL_MEMPWDINSLEEP_SRAMPWDSLP_ALLBUTLOWER32K;

  am_hal_sysctrl_sleep(AM_HAL_SYSCTRL_SLEEP_DEEP);
}

void ArtemisSays::displayDirection(enum DIRECTIONS direction) {
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

  // let the player know that the computer is going
  displayComputerTurn(level);

  // loop through each sequence
  while (position < level) {
    // get this position's direction
    enum DIRECTIONS direction = sequence[position];

    // draw that position
    displayDirection(direction);

    // delay a bit
    // TODO: what is the actual game's delay time?
    delay(500);

    // go to next position
    position++;
  }

  // let the player know it is their turn
  displayYourTurn();
}
