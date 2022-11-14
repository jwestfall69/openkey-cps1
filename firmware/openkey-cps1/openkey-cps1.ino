#include <avr/sleep.h>

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

typedef struct game_reg_t {
  uint8_t cps_id_addr;
  uint16_t cps_id_value;

  uint8_t multi_factor1;
  uint8_t multi_factor2;
  uint8_t multi_result1;
  uint8_t multi_result2;

  uint8_t unknown1;
  uint8_t unknown2;
  uint8_t unknown3;

  uint8_t layer_ctrl;

  uint8_t priority1;
  uint8_t priority2;
  uint8_t priority3;
  uint8_t priority4;

  uint8_t palette_ctrl;

  // layer masks are 3 bits
  // sounds like the values in mame should really only be a single bit, but
  // in some cases multiple bits are set.  not 100% clear on those, just have
  // to guess until they can be tested.
  //   mame => what should be used
  //   0x01 = 0x0
  //   0x02 = 0x1
  //   0x04 = 0x2
  //   0x08 = 0x3
  //   0x0a = ???
  //   0x10 = 0x4
  //   0x12 = 0x4 ??
  //   0x14 = 0x4 ??
  //   0x16 = 0x4 ??
  //   0x20 = 0x5
  //   0x30 = ??? 
  //   0x40 = 0x6
  //   0x80 = 0x7
  uint8_t layer1_mask;
  uint8_t layer2_mask;
  uint8_t layer3_mask;
  uint8_t layer4_mask;
  uint8_t layer5_mask;

  // 0x00 for everyone except CPS-B-16, which is 0xff
  uint8_t raster1;
  uint8_t raster2;
  uint8_t raster3;

} game_reg;

// https://github.com/ArcadeHacker/ArcadeHacker_CPS1/blob/6c506ff339f6a3df2e9696afbf5ec2615eeb207d/ArcadeHacker_CPS1.ino#L43
// https://github.com/mamedev/mame/blob/master/src/mame/capcom/cps1_v.cpp#L472
#define MAX_GAME_NUM 26  
game_reg game_regs[MAX_GAME_NUM+1] = {
   // cps id          multi factor/result         unknowns       layer ctrl         priorities           pal ctrl     layer masks (converted)        rasters                           CPS_B_XX          some games that use it
  { 0x00, 0x0000,   0x06, 0x04, 0x02, 0x00,   0x00, 0x00, 0x00,     0x20,      0x2e, 0x2c, 0x2a, 0x28,     0x30,      0x5, 0x4, 0x4, 0x0, 0x0,   0x00, 0x00, 0x00 }, // 00000 [CCx ] CPS_B_21_BT3 Captain Commando (invalid layer mask data in mame)
  { 0x00, 0x0000,   0x1e, 0x1c, 0x1a, 0x18,   0x00, 0x00, 0x00,     0x20,      0x2e, 0x2c, 0x2a, 0x28,     0x30,      0x4, 0x3, 0x4, 0x0, 0x0,   0x00, 0x00, 0x00 }, // 00001 [KDx ] CPS_B_21_BT2 The King of Dragons (invalid layer mask data in mame)
  { 0x00, 0x0000,   0x06, 0x04, 0x02, 0x00,   0x00, 0x00, 0x00,     0x28,      0x26, 0x24, 0x22, 0x20,     0x30,      0x5, 0x4, 0x1, 0x0, 0x0,   0x00, 0x00, 0x00 }, // 00010 [KRx ] CPS_B_21_BT4 Knights of the Round
  { 0x00, 0x0000,   0x00, 0x00, 0x00, 0x00,   0x00, 0x00, 0x00,     0x20,      0x2e, 0x2c, 0x00, 0x00,     0x30,      0x5, 0x2, 0x2, 0x0, 0x0,   0x00, 0x00, 0x00 }, // 00011 [Q5  ] CPS_B_21_BT6 Capcom World 2 (invalid layer mask data in mame)
  { 0x00, 0x0000,   0x00, 0x00, 0x00, 0x00,   0x00, 0x00, 0x00,     0x2c,      0x00, 0x00, 0x00, 0x00,     0x12,      0x4, 0x1, 0x4, 0x0, 0x0,   0x00, 0x00, 0x00 }, // 00100 [QDx ] CPS_B_21_BT7 Quiz & Dragons (invalid layer mask data in mame)
  { 0x32, 0x0800,   0x0e, 0x0c, 0x0a, 0x08,   0x06, 0x04, 0x00,     0x28,      0x26, 0x24, 0x22, 0x20,     0x30,      0x5, 0x2, 0x3, 0x0, 0x0,   0x00, 0x00, 0x00 }, // 00101 [RTx ] CPS_B_21_BT1 Three Wonders (invalid layer mask data in mame)
  { 0x32, 0x0000,   0x0e, 0x0c, 0x0a, 0x08,   0x00, 0x00, 0x00,     0x20,      0x2e, 0x2c, 0x2a, 0x28,     0x30,      0x5, 0x2, 0x1, 0x0, 0x0,   0x00, 0x00, 0x00 }, // 00110 [VAx ] CPS_B_21_BT5 Varth

  // cps 1.5
  { 0xff, 0x0000,   0xff, 0xff, 0xff, 0xff,   0xff, 0xff, 0xff,     0x0a,      0x0c, 0x0e, 0x00, 0x02,     0x04,      0x4, 0x4, 0x4, 0x0, 0x0,   0x00, 0x00, 0x00 }, // 00111 [CDx ] CPS_B_21_QS2 Cadillacs & Dinosaurs (invalid layer mask data in mame)
  { 0x2e, 0x0c01,   0x00, 0x00, 0x00, 0x00,   0x00, 0x00, 0x00,     0x16,      0x00, 0x02, 0x28, 0x2a,     0x2c,      0x2, 0x3, 0x4, 0x0, 0x0,   0x00, 0x00, 0x00 }, // 01000 [MBx ] CPS_B_21_QS4 Slam Masters / Muscle Bomber
  { 0x1e, 0x0c02,   0x00, 0x00, 0x00, 0x00,   0x00, 0x00, 0x00,     0x2a,      0x2c, 0x2e, 0x30, 0x32,     0x1c,      0x2, 0x3, 0x4, 0x0, 0x0,   0x00, 0x00, 0x00 }, // 01001 [MBDx] CPS_B_21_QS5 Muscle Bomber Duo
  { 0x0e, 0x0c00,   0x00, 0x00, 0x00, 0x00,   0x00, 0x00, 0x00,     0x12,      0x14, 0x16, 0x08, 0x0a,     0x0c,      0x2, 0x1, 0x5, 0x0, 0x0,   0x00, 0x00, 0x00 }, // 01010 [PSx ] CPS_B_21_QS3 Punisher
  { 0x00, 0x0000,   0x00, 0x00, 0x00, 0x00,   0x00, 0x00, 0x00,     0x22,      0x24, 0x26, 0x28, 0x2a,     0x2c,      0x4, 0x3, 0x2, 0x0, 0x0,   0x00, 0x00, 0x00 }, // 01011 [TK2 ] CPS_B_21_QS1 Warriors of Fate

  // raw
  { 0xff, 0x0000,   0xff, 0xff, 0xff, 0xff,   0xff, 0xff, 0xff,     0x26,      0x28, 0x2a, 0x2c, 0x2e,     0x30,      0x1, 0x2, 0x3, 0x5, 0x5,   0x00, 0x00, 0x00 }, // 01100 [B-01] CPS_B_01     Forgotten Worlds / Ghouls'n Ghosts / Strider (invalid layer mask data in mame)
  { 0x20, 0x0002,   0xff, 0xff, 0xff, 0xff,   0xff, 0xff, 0xff,     0x2c,      0x2a, 0x28, 0x26, 0x24,     0x22,      0x1, 0x2, 0x3, 0x0, 0x0,   0x00, 0x00, 0x00 }, // 01101 [B-02] CPS_B_02     Dynasty Wars
  { 0x24, 0x0003,   0xff, 0xff, 0xff, 0xff,   0xff, 0xff, 0xff,     0x30,      0x2e, 0x2c, 0x2a, 0x28,     0x26,      0x5, 0x4, 0x3, 0x0, 0x0,   0x00, 0x00, 0x00 }, // 01110 [B-03] CPS_B_03     Willow  
  { 0x20, 0x0004,   0xff, 0xff, 0xff, 0xff,   0xff, 0xff, 0xff,     0x2e,      0x26, 0x30, 0x28, 0x32,     0x2a,      0x1, 0x2, 0x3, 0x0, 0x0,   0x00, 0x00, 0x00 }, // 01111 [B-04] CPS_B_04     Final Fight
  { 0x20, 0x0005,   0xff, 0xff, 0xff, 0xff,   0xff, 0xff, 0xff,     0x28,      0x2a, 0x2c, 0x2e, 0x30,     0x32,      0x1, 0x3, 0x5, 0x4, 0x4,   0x00, 0x00, 0x00 }, // 10000 [B-05] CPS_B_05     1941 (invalid layer mask data in mame)
  { 0x32, 0x0401,   0xff, 0xff, 0xff, 0xff,   0xff, 0xff, 0xff,     0x26,      0x28, 0x2a, 0x2c, 0x2e,     0x30,      0x3, 0x4, 0x5, 0x0, 0x0,   0x00, 0x00, 0x00 }, // 10001 [B-11] CPS_B_11     Area 88 / U.N. Squadron  
  { 0x20, 0x0402,   0xff, 0xff, 0xff, 0xff,   0xff, 0xff, 0xff,     0x2c,      0x2a, 0x28, 0x26, 0x24,     0x22,      0x1, 0x2, 0x3, 0x0, 0x0,   0x00, 0x00, 0x00 }, // 10010 [B-12] CPS_B_12     Mercs
  { 0x2e, 0x0403,   0xff, 0xff, 0xff, 0xff,   0xff, 0xff, 0xff,     0x22,      0x24, 0x26, 0x28, 0x2a,     0x2c,      0x5, 0x1, 0x2, 0x0, 0x0,   0x00, 0x00, 0x00 }, // 10011 [B-13] CPS_B_13     Magic Sword
  { 0x1e, 0x0404,   0xff, 0xff, 0xff, 0xff,   0xff, 0xff, 0xff,     0x12,      0x14, 0x16, 0x18, 0x1a,     0x1c,      0x3, 0x5, 0x4, 0x0, 0x0,   0x00, 0x00, 0x00 }, // 10100 [B-14] CPS_B_14     Mega Twins / Chiki Chiki Boys / sf2ui  
  { 0x0e, 0x0405,   0xff, 0xff, 0xff, 0xff,   0xff, 0xff, 0xff,     0x02,      0x04, 0x06, 0x08, 0x0a,     0x0c,      0x2, 0x1, 0x5, 0x0, 0x0,   0x00, 0x00, 0x00 }, // 10101 [B-15] CPS_B_15     Nemo
  { 0x00, 0x0406,   0xff, 0xff, 0xff, 0xff,   0xff, 0xff, 0xff,     0x0c,      0x0a, 0x08, 0x06, 0x04,     0x02,      0x4, 0x3, 0x3, 0x0, 0x0,   0xff, 0xff, 0xff }, // 10110 [B-16] CPS_B_16     Carrier Air Wing / U.S. Navy (invalid layer mask data in mame)
  { 0x08, 0x0407,   0xff, 0xff, 0xff, 0xff,   0xff, 0xff, 0xff,     0x14,      0x12, 0x10, 0x0e, 0x0c,     0x0a,      0x3, 0x4, 0x1, 0x0, 0x0,   0x00, 0x00, 0x00 }, // 10111 [B-17] CPS_B_17     Some older Street Figher 2s (invalid layer mask data in mame)  
  { 0x10, 0x0408,   0xff, 0xff, 0xff, 0xff,   0xff, 0xff, 0xff,     0x1c,      0x1a, 0x18, 0x16, 0x14,     0x12,      0x4, 0x3, 0x1, 0x0, 0x0,   0x00, 0x00, 0x00 }, // 11000 [B-18] CPS_B_18     sf2ee / sf2ue
  { 0x32, 0x0000,   0x00, 0x02, 0x04, 0x06,   0x08, 0xff, 0xff,     0x26,      0x28, 0x2a, 0x2c, 0x2e,     0x30,      0x1, 0x2, 0x3, 0x5, 0x5,   0x00, 0x00, 0x00 }, // 11001 [B-21] CPS_B_21_DEF Bunch SF2s + Others / Boots (invalid layer mask data in mame)

  // bad dsw value / zero key
  { 0x00, 0x0000,   0x00, 0x00, 0x00, 0x00,   0x00, 0x00, 0x00,     0x00,      0x00, 0x00, 0x00, 0x00,     0x00,      0x0, 0x0, 0x0, 0x0, 0x0,   0x00, 0x00, 0x00 },
  
};

// doing bit shifting takes a variable amount
// of time depending on the how far the shift
// is.  Using the below lookup table to try
// and keep a consistent clock period when
// sending data.
uint16_t masks[16] = {
  0x0001, 0x0002, 0x0004, 0x0008,
  0x0010, 0x0020, 0x0040, 0x0080,
  0x0100, 0x0200, 0x0400, 0x0800,
  0x1000, 0x2000, 0x4000, 0x8000,
};

void setup() {
    // set the programming pins as outputs
  PORTA.DIR = PIN1_bm | PIN2_bm;
  PORTB.DIR = PIN0_bm | PIN1_bm;

  // setup initial output states
  // https://www.youtube.com/watch?v=IBZc__9sM28&t=1196s
  SET_SETUP;
  delay(1);
  CLR_CLK1;
  CLR_CLK2;
  CLR_DATA;

  // enable pull-ups on dsw pins
  PORTA.PIN4CTRL |= PORT_PULLUPEN_bm;  // PIN 2 (PIN_PA4) <=> DSW5
  PORTA.PIN5CTRL |= PORT_PULLUPEN_bm;  // PIN 3 (PIN_PA5) <=> DSW4
  PORTA.PIN6CTRL |= PORT_PULLUPEN_bm;  // PIN 4 (PIN_PA6) <=> DSW3
  PORTA.PIN7CTRL |= PORT_PULLUPEN_bm;  // PIN 5 (PIN_PA7) <=> DSW2
  PORTB.PIN3CTRL |= PORT_PULLUPEN_bm;  // PIN 6 (PIN_PB3) <=> DSW1

  // stage #1: clocks on clock #1
  // https://www.youtube.com/watch?v=IBZc__9sM28&t=1232s
  // derp
  for(int i = 0;i < 4;i++) {
    SET_CLK1;
    CLR_CLK1;
  }

  // using updated info for stage #2/3
  // https://gitlab.com/loic.petit/cps2-reverse/-/blob/master/DLs/DL-0921/doc/security-scheme.md
  // stage #2: unlock key
  send_data(0x5, 3);

  // stage #3: clocks on clock #2
  for(int i = 0;i < 15;i++) {
    SET_CLK2;
    CLR_CLK2;
  }

  uint8_t game_num = read_dsw();
  if(game_num > MAX_GAME_NUM) {
    game_num = MAX_GAME_NUM;
  }

  // programming the registers
  // https://www.youtube.com/watch?v=IBZc__9sM28&t=1339s
  // https://gitlab.com/loic.petit/cps2-reverse/-/blob/master/DLs/DL-0921/doc/configuration-key.md
  // data is written in serially so we need write data
  // backwards from bit 143 to bit 0
  //    bits
  // 138 - 143 = lower 6 bits of the cps_id_value
  // 133 - 137 = multiply factor #1
  // 130 - 132 = layer mask #2
  // 125 - 129 = cps_id_addr
  // 120 - 124 = multiply factor #2
  // 115 - 119 = palette ctrl
  // 110 - 114 = multiply result #1
  // 105 - 109 = priority #4
  // 102 - 104 = layer mask #3
  //  97 - 101 = multiply result #2
  //  92 -  96 = priority #3
  //  87 -  91 = multiply tc (0x00)
  //  82 -  86 = priority #2
  //  66 -  81 = check #2 data (0x00)
  //  63 -  65 = layer mask #5
  //  58 -  62 = check #1 (0x00)
  //  53 -  57 = priority #1
  //  37 -  52 = check #1 data (0x00)
  //  32 -  36 = check #2 (0x00)
  //  29 -  31 = layer mask #4
  //  24 -  28 = raster #1 (0x00)
  //  19 -  23 = layer ctrl
  //  14 -  18 = raster #2 (0x00)
  //   9 -  13 = raster #3 (0x00)
  //   6 -   8 = layer mask #1
  //   0 -   5 = upper 6 bits of cps_id_value

  send_data(game_regs[game_num].cps_id_value, 6);
  send_data(game_regs[game_num].multi_factor1 >> 1, 5);
  send_data(game_regs[game_num].layer2_mask, 3);
  send_data(game_regs[game_num].cps_id_addr >> 1, 5);
  send_data(game_regs[game_num].multi_factor2 >> 1, 5);
  send_data(game_regs[game_num].palette_ctrl >> 1, 5);
  send_data(game_regs[game_num].multi_result1 >> 1, 5);
  send_data(game_regs[game_num].priority4 >> 1, 5);
  send_data(game_regs[game_num].layer3_mask, 3);
  send_data(game_regs[game_num].multi_result2 >> 1, 5);
  send_data(game_regs[game_num].priority3 >> 1, 5);
  send_data(game_regs[game_num].unknown1 >> 1, 5);  // multi-tc
  send_data(game_regs[game_num].priority2 >> 1, 5);
  send_data(0x00, 16);  // check2_value
  send_data(game_regs[game_num].layer5_mask, 3);
  send_data(game_regs[game_num].unknown2 >> 1, 5);  // check #1
  send_data(game_regs[game_num].priority1 >> 1, 5);
  send_data(0x00, 16);  // check1_value
  send_data(game_regs[game_num].unknown3 >> 1, 5);  // check #2
  send_data(game_regs[game_num].layer4_mask, 3);
  send_data(game_regs[game_num].raster1, 5);
  send_data(game_regs[game_num].layer_ctrl >> 1, 5);
  send_data(game_regs[game_num].raster2, 5);
  send_data(game_regs[game_num].raster3, 5);
  send_data(game_regs[game_num].layer1_mask, 3);
  send_data(game_regs[game_num].cps_id_value >> 10, 6);  

  CLR_CLK1;
  CLR_CLK2;
  CLR_DATA;
  CLR_SETUP;
  
  // NOTE: We dont connect pins 19/20 between the C and B boards.  These
  // pins are needed for programming but are normally tied to ground on
  // the B board.  In testing it appears the cps-b-21 chip has an internal
  // pull down for both, so it should be safe to disable pin output and
  // power down the attiny.

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

void send_data(uint16_t data, int8_t num_bits) {
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
