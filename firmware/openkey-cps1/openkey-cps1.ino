#include <avr/sleep.h>
#include "cps1-configs.h"

// PIN 8 (PIN_B1) <=> CNB PIN 62
#define SET_DATA      PORTB.OUTSET = PIN1_bm
#define CLR_DATA      PORTB.OUTCLR = PIN1_bm

// PIN 9 (PIN_B0) <=> CNB PIN 61
#define SET_CLK2      PORTB.OUTSET = PIN0_bm
#define CLR_CLK2      PORTB.OUTCLR = PIN0_bm

// PIN 10 (PIN_A0) used for UPDI (ATtiny programming)

// PIN 11 (PIN_A1) <=> CNA PIN 19
#define SET_CLK1      PORTA.OUTSET = PIN1_bm
#define CLR_CLK1      PORTA.OUTCLR = PIN1_bm

// PIN 12 (PIN_A2) <=> CNA PIN 20
#define SET_SETUP     PORTA.OUTSET = PIN2_bm
#define CLR_SETUP     PORTA.OUTCLR = PIN2_bm

// doing bit shifting takes a variable amount
// of time depending on the how far the shift
// is.  Using the below lookup table to try
// and keep a consistent clock period when
// sending data.
uint8_t masks[8] = {
  0x01, 0x02, 0x04, 0x08,
  0x10, 0x20, 0x40, 0x80,
};

void setup() {
    // set the programming pins as outputs
  PORTA.DIR = PIN1_bm | PIN2_bm;
  PORTB.DIR = PIN0_bm | PIN1_bm;

  // setup initial output states
  // https://www.youtube.com/watch?v=IBZc__9sM28&t=1196s
  SET_SETUP;
  CLR_CLK1;
  CLR_CLK2;
  CLR_DATA;

  // Testing Notes:
  // - using a delay down near 500us will cause some games to report an
  //   addresss or ram error on boot
  // - going below that, programming stops working
  delayMicroseconds(1000);

  // enable pull-ups on dsw pins
  PORTA.PIN4CTRL |= PORT_PULLUPEN_bm;  // PIN 2 (PIN_PA4) <=> DSW5
  PORTA.PIN5CTRL |= PORT_PULLUPEN_bm;  // PIN 3 (PIN_PA5) <=> DSW4
  PORTA.PIN6CTRL |= PORT_PULLUPEN_bm;  // PIN 4 (PIN_PA6) <=> DSW3
  PORTA.PIN7CTRL |= PORT_PULLUPEN_bm;  // PIN 5 (PIN_PA7) <=> DSW2
  PORTB.PIN3CTRL |= PORT_PULLUPEN_bm;  // PIN 6 (PIN_PB3) <=> DSW1

  // stage #1: clocks on clock #1
  // https://www.youtube.com/watch?v=IBZc__9sM28&t=1232s
  for(int i = 0;i < 4;i++) {
    SET_CLK1;
    CLR_CLK1;
  }

  // using updated info for stage #2/3
  // https://gitlab.com/loic.petit/cps2-reverse/-/blob/master/DLs/DL-0921/doc/security-scheme.md
  // stage #2: unlock key
  send_bits(0x5, 3);

  // stage #3: clocks on clock #2
  for(int i = 0;i < 15;i++) {
    SET_CLK2;
    CLR_CLK2;
  }

  uint8_t config_num = read_dsw();
  if(config_num >= CONFIG_MAX) {
    config_num = CONFIG_MAX - 1;
  }

  for(int i = 0; i < CONFIG_SIZE; i++) {
    send_bits(chip_configs[config_num][i], 8);
  }

  CLR_CLK1;
  CLR_CLK2;
  CLR_DATA;
  CLR_SETUP;
  
  // NOTE: We dont connect pins 19/20 between the C and B boards.  These
  // pins are needed for programming but are normally tied to ground on
  // the B board.  In testing it appears the cps-b-21 chip has an internal
  // pull down for both, so it should be safe to disable pin output and
  // power down the ATtiny.

  // set all pins to be inputs
  PORTA.DIR = 0;
  PORTB.DIR = 0;

  // power down
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  sleep_cpu();
}

void loop() {
  while(1) {}
}

void send_bits(uint16_t data, int8_t num_bits) {
  num_bits--;
  while(num_bits >= 0) {
    uint32_t bit = data & masks[num_bits];
    if(bit) {
      SET_DATA;
    } else {
      CLR_DATA;
    }
    SET_CLK2;
    CLR_CLK2;
    num_bits--;
  }
}

// DSW1 = PB3 = bit4
// DSW2 = PA7 = bit3
// DSW3 = PA6 = bit2
// DSW4 = PA5 = bit1
// DSW5 = PA4 = bit0
uint8_t read_dsw() {
  uint8_t dsw = 0;
 
  // negate the bits since we are using
  // pull-ups so "on"s will be low
  uint8_t porta = PORTA.IN ^ 0xff;
  uint8_t portb = PORTB.IN ^ 0xff;

  dsw = porta >> 4;
  dsw = dsw | ((portb & 0b0001000) << 1);
  return dsw;
}
