#pragma once
#include "Bus.h"
#include "Common.h"
#include "Instructions.h"

class Cpu {
 private:
  Word fetched = 0x0000;  // Represents the working input value to the ALU
  Word mem_dest = 0x0000;
  Byte opcode = 0x0000;

  Word addr_abs = 0x0000;

  bool halted, stepping, int_master_enabled;

  std::vector<INSTRUCTION> lookup3;
  std::map<Byte, INSTRUCTION> lookup;
  std::unique_ptr<INSTRUCTION> curInst = nullptr;
  std::shared_ptr<Bus> bus = nullptr;

  enum FLAGCPU {
    C = (1 << 4),  // Carry flag
    H = (1 << 5),  // Half Carry flag (BCD)
    N = (1 << 6),  // Subtraction flag (BCD)
    Z = (1 << 7),  // Zero flag
  };

 private:
  Word reverse(Word n);
  Word readReg(reg_type rt);
  void init();
  void emuCycles(int cpu_cycles);
  void fetch_instruction();
  void fetch_data();
  void execute();
  bool checkCond();
  // std::string getNameInst(in_type t);
  void ConnectBus(std::shared_ptr<Bus> bus) { bus = bus; }
  void setFlag(FLAGCPU f, bool v);
  Byte getFlag(FLAGCPU f);

 public:
  Byte a = 0x00;     // A Register
  Byte b = 0x00;     // B Register
  Byte c = 0x00;     // C Register
  Byte d = 0x00;     // D Register
  Byte e = 0x00;     // E Register
  Byte h = 0x00;     // H Register
  Byte l = 0x00;     // L Register
  Byte f = 0x00;     // F Register
  Word sp = 0x0000;  // Stack Pointer (points to location on bus)
  Word pc = 0x0000;  // Program Counter

  Byte status = 0x00;  // Status Register
 public:
  Cpu();
  Cpu(std::shared_ptr<Bus> bus);
  ~Cpu();

  bool cpuStep();
  Byte read(Word address);
  void write(Word address, Byte value);
  // Address Mode
  Byte NIM();
  Byte IMP();
  Byte R();
  Byte RD8();
  Byte D16();

  // instructions
  Byte NON();
  Byte NOP();
  Byte DI();
  Byte LD();
  Byte XOR();
  Byte JP();
};
