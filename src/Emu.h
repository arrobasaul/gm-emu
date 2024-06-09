#pragma once
#include "Cartridges.h"
#include "Common.h"
#include "Cpu.h"

typedef struct {
  bool paused;
  bool running;
  u64 ticks;
} EmuContext;

static EmuContext ctx;

class Emu {
 private:
  void *cpu_run(void *p);
  void delay(u32 ms);

 public:
  Emu(/* args */);
  ~Emu();

  int emuRun(int argc, char **argv);
  EmuContext *getContext();
};
