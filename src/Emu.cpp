#include "Emu.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

Emu::Emu(/* args */) {}

Emu::~Emu() {}

EmuContext *Emu::getContext() { return &ctx; }

void Emu::delay(u32 ms) { SDL_Delay(ms); }

int Emu::emuRun(int argc, char **argv) {
  /*if (argc < 2) {
     printf("Usage: emu <rom_file>\n");
     return -1;
 }*/
  Cartridges card{};

  if (!card.loadCartridges("../roms/superml.gb")) {
    printf("Failed to load ROM file: %s\n", argv[1]);
    return -2;
  }

  printf("Cart loaded..\n");

  SDL_Init(SDL_INIT_VIDEO);
  printf("SDL INIT\n");
  TTF_Init();
  printf("TTF INIT\n");

  Cpu cpu{};

  ctx.running = true;
  ctx.paused = false;
  ctx.ticks = 0;

  while (ctx.running) {
    if (ctx.paused) {
      delay(10);
      continue;
    }

    if (!cpu.cpuStep()) {
      printf("CPU Stopped\n");
      return -3;
    }

    ctx.ticks++;
  }

  return 0;
}