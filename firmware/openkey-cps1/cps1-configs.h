// This file was generated by gen-cps1-configs.

#define CONFIG_MAX  27
#define CONFIG_SIZE 18
uint8_t chip_configs[CONFIG_MAX][CONFIG_SIZE] = {
  // cps1 using programmed B-21                                                                                      12345  prom
  { 0x00, 0x73, 0xe2, 0xc0, 0x69, 0x01, 0x53, 0xd8, 0x29, 0x1c, 0x1a, 0xe4, 0x0b, 0x85, 0x1f, 0x87, 0xff, 0x40 }, // 00000 [CCx ] CPS_B_21_BT3 Captain Commando
  { 0x01, 0xef, 0xee, 0xc3, 0x69, 0x19, 0x5f, 0xd8, 0x75, 0xac, 0x1a, 0xe4, 0x38, 0x45, 0x1f, 0x87, 0xff, 0x00 }, // 00001 [KDx ] CPS_B_21_BT2 The King of Dragons
  { 0x00, 0x73, 0xe2, 0xc0, 0x60, 0x41, 0x17, 0xc8, 0x77, 0x40, 0x3a, 0x64, 0xcf, 0xcd, 0x1f, 0xa7, 0xff, 0x40 }, // 00010 [KRx ] CPS_B_21_BT4 Knights of the Round
  { 0x03, 0xeb, 0xff, 0xc7, 0xe8, 0xbf, 0x5f, 0xd8, 0x00, 0x00, 0x7e, 0xe0, 0x00, 0x1f, 0x1f, 0x87, 0xff, 0x40 }, // 00011 [Q5  ] CPS_B_21_BT6 Capcom World 2
  { 0x03, 0xe7, 0xff, 0x4f, 0xff, 0x3f, 0xff, 0xfc, 0x00, 0x00, 0x7f, 0xe0, 0x00, 0x1f, 0x1f, 0xb7, 0xff, 0x00 }, // 00100 [QDx ] CPS_B_21_BT7 Quiz & Dragons
  { 0x00, 0xeb, 0x26, 0xc1, 0x60, 0xc9, 0x11, 0xc8, 0x6c, 0xf4, 0x0a, 0x61, 0xcd, 0x61, 0x1f, 0xa7, 0xff, 0x42 }, // 00101 [RTx ] CPS_B_21_BT1 Three Wonders
  { 0x00, 0xeb, 0x26, 0xc1, 0x68, 0x49, 0x57, 0xd9, 0x39, 0xc4, 0x3a, 0xe9, 0xce, 0x2d, 0x1f, 0x87, 0xff, 0x40 }, // 00110 [VAx ] CPS_B_21_BT5 Varth

  // cps1.5 using programmed B-21
  { 0x03, 0xf3, 0xff, 0x17, 0xc3, 0x3e, 0x0f, 0x9d, 0x27, 0x7c, 0x5c, 0xd7, 0x8a, 0x50, 0x1f, 0x2f, 0xff, 0x00 }, // 00111 [CDx ] CPS_B_21_QS2 Cadillacs & Dinosaurs
  { 0x07, 0xee, 0xff, 0xb7, 0xeb, 0x3f, 0x47, 0x05, 0xa7, 0xd0, 0x3c, 0x19, 0x00, 0x64, 0x1f, 0x5f, 0xfe, 0x83 }, // 01000 [MBx ] CPS_B_21_QS4 Slam Masters / Muscle Bomber
  { 0x0b, 0xed, 0xff, 0x77, 0xf3, 0x3f, 0x83, 0x5c, 0x00, 0x00, 0x7e, 0xc0, 0x00, 0x1f, 0x1f, 0xaf, 0xfe, 0x83 }, // 01001 [MBDx] CPS_B_21_QS5 Muscle Bomber Duo
  { 0x03, 0xe4, 0xff, 0x37, 0xcb, 0x7e, 0x4b, 0x2c, 0x00, 0x00, 0x7d, 0x40, 0x00, 0x1f, 0x1f, 0x4f, 0xfe, 0x83 }, // 01010 [PSx ] CPS_B_21_QS3 Punisher
  { 0x03, 0xef, 0xff, 0xb7, 0xea, 0xbf, 0x4f, 0xcc, 0x00, 0x00, 0x7e, 0x40, 0x00, 0x1f, 0x1f, 0x8f, 0xff, 0x00 }, // 01011 [TK2 ] CPS_B_21_QS1 Warriors of Fate

  // raw B-xxx chips
  { 0x03, 0xeb, 0xff, 0xc7, 0xee, 0xff, 0x6f, 0xd4, 0x00, 0x02, 0xfe, 0x80, 0x00, 0x1f, 0xbf, 0x9f, 0xfe, 0x40 }, // 01100 [B-01] CPS_B_01     Forgotten Worlds / Ghouls'n Ghosts / Strider
  { 0x0b, 0xea, 0x1f, 0x8f, 0xe4, 0xff, 0x3f, 0xd0, 0x00, 0x00, 0x7e, 0xa0, 0x00, 0x1f, 0x1f, 0xb7, 0xfe, 0x40 }, // 01101 [B-02] CPS_B_02     Dynasty Wars
  { 0x0f, 0xf2, 0x5f, 0x9f, 0xe8, 0xff, 0x5f, 0xd8, 0x00, 0x00, 0x7e, 0xe0, 0x00, 0x1f, 0x1f, 0xc7, 0xff, 0x40 }, // 01110 [B-03] CPS_B_03     Willow
  { 0x13, 0xea, 0x1f, 0xaf, 0xf2, 0xff, 0x4f, 0xe0, 0x00, 0x00, 0x7e, 0x60, 0x00, 0x1f, 0x1f, 0xbf, 0xfe, 0x40 }, // 01111 [B-04] CPS_B_04     Final Fight
  { 0x17, 0xee, 0x1f, 0xcf, 0xf1, 0x7f, 0x7f, 0xd8, 0x00, 0x02, 0x7e, 0xa0, 0x00, 0x1f, 0x9f, 0xa7, 0xfe, 0x40 }, // 10000 [B-05] CPS_B_05     1941
  { 0x07, 0xf3, 0x3f, 0xc7, 0xef, 0x7f, 0x6f, 0xd4, 0x00, 0x00, 0x7e, 0x80, 0x00, 0x1f, 0x1f, 0x9f, 0xfe, 0xc1 }, // 10001 [B-11] CPS_B_11     Area 88 / U.N. Squadron
  { 0x0b, 0xea, 0x1f, 0x8f, 0xe4, 0xff, 0x3f, 0xd0, 0x00, 0x00, 0x7e, 0xa0, 0x00, 0x1f, 0x1f, 0xb7, 0xfe, 0x41 }, // 10010 [B-12] CPS_B_12     Mercs
  { 0x0f, 0xe6, 0xff, 0xb7, 0xea, 0xbf, 0x4f, 0xcc, 0x00, 0x00, 0x7e, 0x40, 0x00, 0x1f, 0x1f, 0x8f, 0xff, 0x41 }, // 10011 [B-13] CPS_B_13     Magic Sword
  { 0x13, 0xf5, 0xff, 0x77, 0xdb, 0x3e, 0xcf, 0xac, 0x00, 0x00, 0x7d, 0x40, 0x00, 0x1f, 0x1f, 0x4f, 0xfe, 0xc1 }, // 10100 [B-14] CPS_B_14     Mega Twins / Chiki Chiki Boys / sf2ui
  { 0x17, 0xe4, 0xff, 0x37, 0xcb, 0x7e, 0x4f, 0x8c, 0x00, 0x00, 0x7c, 0x40, 0x00, 0x1f, 0x1f, 0x0f, 0xfe, 0x81 }, // 10101 [B-15] CPS_B_15     Nemo
  { 0x1b, 0xec, 0x1f, 0x0f, 0xc4, 0xfe, 0x3f, 0x90, 0x00, 0x00, 0x7c, 0xa0, 0x00, 0x1f, 0x1f, 0x37, 0xff, 0x01 }, // 10110 [B-16] CPS_B_16     Carrier Air Wing / U.S. Navy
  { 0x1f, 0xf0, 0x9f, 0x2f, 0xcc, 0x7e, 0x7f, 0xa0, 0x00, 0x00, 0x7d, 0x20, 0x00, 0x1f, 0x1f, 0x57, 0xfe, 0xc1 }, // 10111 [B-17] CPS_B_17     Some older Street Figher 2s
  { 0x23, 0xed, 0x1f, 0x4f, 0xd4, 0x7e, 0xbf, 0xb0, 0x00, 0x00, 0x7d, 0xa0, 0x00, 0x1f, 0x1f, 0x77, 0xff, 0x01 }, // 11000 [B-18] CPS_B_18     sf2ee / sf2ue
  { 0x00, 0x0b, 0x21, 0xc0, 0xae, 0xc7, 0x62, 0x54, 0x00, 0x02, 0x96, 0x80, 0x00, 0x06, 0x87, 0x9a, 0x12, 0x40 }, // 11001 [B-21] CPS_B_21_DEF Bunch SF2s + Others / Boots

  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // 11010 bad dsw value
};
