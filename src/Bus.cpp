#include "Bus.h"

Bus::Bus(/* args */) {
  if (!cart->loadCartridge("../roms/tetris.gb")) {
    // printf("Failed to load ROM file: %s\n", argv[1]);
    // return -2;
  }

  printf("Cart loaded..\n");
}

Bus::~Bus() {}

Byte Bus::readBus(Word address) {
  if (address < 0x8000) {
    // ROM Data
    Byte value = cart->readCard(address);
    return value;
  }

  NO_IMPL
}
void Bus::writeBus(Word address, Byte value) {
  if (address < 0x8000) {
    // ROM Data
    cart->writeCard(address, value);
    return;
  }

  NO_IMPL
}