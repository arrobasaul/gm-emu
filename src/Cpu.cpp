#include "Cpu.h"

Cpu::Cpu(/* args */) {
  init();
  bus = std::make_shared<Bus>();
}
Cpu::Cpu(std::shared_ptr<Bus> bus) {
  init();
  ConnectBus(bus);
}

void Cpu::init() {
  pc = 0x100;
  a = 0x01;
  lookup[0x00] = {"NON", &Cpu::NOP, &Cpu::IMP, 3};
  // lookup2[0x05] = {"DEC", &Cpu::DEC, &Cpu::R, 3};
  lookup[0x0E] = {.name = "LD", .operate = &Cpu::LD, .addrmode = &Cpu::RD8, .cycles = 3, .reg_1 = RT_C};
  lookup[0xAF] = {.name = "XOR", .operate = &Cpu::XOR, .addrmode = &Cpu::R, .cycles = 3, .reg_1 = RT_A};
  lookup[0xC3] = {"JP", &Cpu::JP, &Cpu::D16, 3};
  lookup[0xF3] = {"DI", &Cpu::DI, &Cpu::NIM, 3};

  lookup3 = {
      {"NON", &Cpu::NON, &Cpu::IMP, 3}, {"NOP", &Cpu::NOP, &Cpu::R, 6}, {"DI", &Cpu::DI, &Cpu::RD8, 2}, {"DL", &Cpu::LD, &Cpu::D16, 2}, {"JP", &Cpu::JP, &Cpu::IMP, 2},
  };
}
Cpu::~Cpu() {}

Byte Cpu::read(Word address) { return bus->readBus(address); }
void Cpu::write(Word address, Byte value) {}

Word Cpu::reverse(Word n) { return ((n & 0xFF00) >> 8) | ((n & 0x00FF) << 8); }

Word Cpu::readReg(reg_type rt) {
  switch (rt) {
    case RT_A:
      return a;
    case RT_F:
      return f;
    case RT_B:
      return b;
    case RT_C:
      return c;
    case RT_D:
      return d;
    case RT_E:
      return e;
    case RT_H:
      return h;
    case RT_L:
      return l;

    case RT_AF:
      return reverse(*((Word *)&a));
    case RT_BC:
      return reverse(*((Word *)&b));
    case RT_DE:
      return reverse(*((Word *)&d));
    case RT_HL:
      return reverse(*((Word *)&h));

    case RT_PC:
      return pc;
    case RT_SP:
      return sp;
    default:
      return 0;
  }
}
void Cpu::emuCycles(int cpu_cycles) {
  // TODO...
}

void Cpu::setFlag(FLAGCPU f, bool v) {
  if (v)
    status |= f;
  else
    status &= ~f;
}

Byte Cpu::getFlag(FLAGCPU f) { return ((status & f) > 0) ? 1 : 0; }

void Cpu::fetch_instruction() {
  opcode = read(pc++);

  if (lookup.find(opcode) == lookup.end()) {
    curInst = nullptr;
  } else {
    curInst = std::make_unique<INSTRUCTION>(lookup[opcode]);
  }
}
void Cpu::fetch_data() {
  mem_dest = 0x0000;
  if (curInst == nullptr) {
    return;
  }
  // Byte data = (this->*lookup[opcode].addrmode)();
  Byte data = (this->*curInst->addrmode)();
  return;
}

void Cpu::execute() { Byte ejecute = (this->*lookup[opcode].operate)(); }

bool Cpu::cpuStep() {
  Word curPc = pc;

  fetch_instruction();
  fetch_data();
  if (curInst == nullptr) {
    return false;
  }
  printf("%04X: %-7s (%02X %02X %02X) A: %02X B: %02X C: %02X\n", curPc, curInst->name.c_str(), opcode, bus->readBus(curPc + 1), bus->readBus(curPc + 2), a, b, c);

  if (curInst == nullptr) {
    printf("Unknown Instruction! %02X\n", opcode);
    exit(-7);
  }

  execute();
  return true;
}
// Address Mode
Byte Cpu::NIM() { return 0; }
Byte Cpu::IMP() {
  printf("IMP address mode\n");

  fetched = a;
  return 0;
}
Byte Cpu::R() {
  fetched = readReg(curInst->reg_1);
  return 0;
}
Byte Cpu::RD8() {
  fetched = read(pc);
  emuCycles(1);
  pc++;
  return 0;
}
Byte Cpu::D16() {
  Word low = read(pc);
  emuCycles(1);
  Word hi = read(pc + 1);
  emuCycles(1);
  fetched = low | (hi << 8);
  pc += 2;

  return 0;
}

// instructions
Byte Cpu::NON() {
  printf("NON instructions\n");
  return 0;
}
Byte Cpu::NOP() {
  printf("NOP instructions\n");
  return 0;
}
Byte Cpu::DI() {
  int_master_enabled = false;
  return 0;
}
Byte Cpu::LD() { return 0; }
Byte Cpu::XOR() {
  status ^= fetched & 0xFF;
  setFlag(Z, 1);
  return 0;
}
Byte Cpu::JP() {
  printf("JP instructions\n");
  if (checkCond()) {
    pc = fetched;
    emuCycles(1);
  }

  return 0;
}
bool Cpu::checkCond() {
  switch (curInst->cond) {
    case CT_NONE:
      return true;
    case CT_C:
      return C;
    case CT_NC:
      return !C;
    case CT_Z:
      return Z;
    case CT_NZ:
      return !Z;
    default:
      return false;
  }
}