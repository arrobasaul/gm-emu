#include "Emu.h"

int main(int argc, char **argv) {
  Emu emu{};
  return emu.emuRun(argc, argv);
}