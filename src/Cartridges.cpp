#include "Cartridges.h"

typedef struct {
  char filename[1024];
  u32 rom_size;
  Byte *rom_data;
  RomHeader *header;
} CartContext;

static CartContext ctx;

static const char *ROM_TYPES[] = {
    "ROM ONLY",
    "MBC1",
    "MBC1+RAM",
    "MBC1+RAM+BATTERY",
    "0x04 ???",
    "MBC2",
    "MBC2+BATTERY",
    "0x07 ???",
    "ROM+RAM 1",
    "ROM+RAM+BATTERY 1",
    "0x0A ???",
    "MMM01",
    "MMM01+RAM",
    "MMM01+RAM+BATTERY",
    "0x0E ???",
    "MBC3+TIMER+BATTERY",
    "MBC3+TIMER+RAM+BATTERY 2",
    "MBC3",
    "MBC3+RAM 2",
    "MBC3+RAM+BATTERY 2",
    "0x14 ???",
    "0x15 ???",
    "0x16 ???",
    "0x17 ???",
    "0x18 ???",
    "MBC5",
    "MBC5+RAM",
    "MBC5+RAM+BATTERY",
    "MBC5+RUMBLE",
    "MBC5+RUMBLE+RAM",
    "MBC5+RUMBLE+RAM+BATTERY",
    "0x1F ???",
    "MBC6",
    "0x21 ???",
    "MBC7+SENSOR+RUMBLE+RAM+BATTERY",
};
/*
static const char *LIC_CODE[0xA5] = {
    [0x00] = "None",
    [0x01] = "Nintendo R&D1",
    [0x08] = "Capcom",
    [0x13] = "Electronic Arts",
    [0x18] = "Hudson Soft",
    [0x19] = "b-ai",
    [0x20] = "kss",
    [0x22] = "pow",
    [0x24] = "PCM Complete",
    [0x25] = "san-x",
    [0x28] = "Kemco Japan",
    [0x29] = "seta",
    [0x30] = "Viacom",
    [0x31] = "Nintendo",
    [0x32] = "Bandai",
    [0x33] = "Ocean/Acclaim",
    [0x34] = "Konami",
    [0x35] = "Hector",
    [0x37] = "Taito",
    [0x38] = "Hudson",
    [0x39] = "Banpresto",
    [0x41] = "Ubi Soft",
    [0x42] = "Atlus",
    [0x44] = "Malibu",
    [0x46] = "angel",
    [0x47] = "Bullet-Proof",
    [0x49] = "irem",
    [0x50] = "Absolute",
    [0x51] = "Acclaim",
    [0x52] = "Activision",
    [0x53] = "American sammy",
    [0x54] = "Konami",
    [0x55] = "Hi tech entertainment",
    [0x56] = "LJN",
    [0x57] = "Matchbox",
    [0x58] = "Mattel",
    [0x59] = "Milton Bradley",
    [0x60] = "Titus",
    [0x61] = "Virgin",
    [0x64] = "LucasArts",
    [0x67] = "Ocean",
    [0x69] = "Electronic Arts",
    [0x70] = "Infogrames",
    [0x71] = "Interplay",
    [0x72] = "Broderbund",
    [0x73] = "sculptured",
    [0x75] = "sci",
    [0x78] = "THQ",
    [0x79] = "Accolade",
    [0x80] = "misawa",
    [0x83] = "lozc",
    [0x86] = "Tokuma Shoten Intermedia",
    [0x87] = "Tsukuda Original",
    [0x91] = "Chunsoft",
    [0x92] = "Video system",
    [0x93] = "Ocean/Acclaim",
    [0x95] = "Varie",
    [0x96] = "Yonezawa/spal",
    [0x97] = "Kaneko",
    [0x99] = "Pack in soft",
    [0xA4] = "Konami (Yu-Gi-Oh!)",
};*/

Cartridges::Cartridges(/* args */) {
  LIC_CODE[0x00] = "None";
  LIC_CODE[0x01] = "Nintendo R&D1";
  LIC_CODE[0x08] = "Capcom";
  LIC_CODE[0x13] = "Electronic Arts";
  LIC_CODE[0x18] = "Hudson Soft";
  LIC_CODE[0x19] = "b-ai";
  LIC_CODE[0x20] = "kss";
  LIC_CODE[0x22] = "pow";
  LIC_CODE[0x24] = "PCM Complete";
  LIC_CODE[0x25] = "san-x";
  LIC_CODE[0x28] = "Kemco Japan";
  LIC_CODE[0x29] = "seta";
  LIC_CODE[0x30] = "Viacom";
  LIC_CODE[0x31] = "Nintendo";
  LIC_CODE[0x32] = "Bandai";
  LIC_CODE[0x33] = "Ocean/Acclaim";
  LIC_CODE[0x34] = "Konami";
  LIC_CODE[0x35] = "Hector";
  LIC_CODE[0x37] = "Taito";
  LIC_CODE[0x38] = "Hudson";
  LIC_CODE[0x39] = "Banpresto";
  LIC_CODE[0x41] = "Ubi Soft";
  LIC_CODE[0x42] = "Atlus";
  LIC_CODE[0x44] = "Malibu";
  LIC_CODE[0x46] = "angel";
  LIC_CODE[0x47] = "Bullet-Proof";
  LIC_CODE[0x49] = "irem";
  LIC_CODE[0x50] = "Absolute";
  LIC_CODE[0x51] = "Acclaim";
  LIC_CODE[0x52] = "Activision";
  LIC_CODE[0x53] = "American sammy";
  LIC_CODE[0x54] = "Konami";
  LIC_CODE[0x55] = "Hi tech entertainment";
  LIC_CODE[0x56] = "LJN";
  LIC_CODE[0x57] = "Matchbox";
  LIC_CODE[0x58] = "Mattel";
  LIC_CODE[0x59] = "Milton Bradley";
  LIC_CODE[0x60] = "Titus";
  LIC_CODE[0x61] = "Virgin";
  LIC_CODE[0x64] = "LucasArts";
  LIC_CODE[0x67] = "Ocean";
  LIC_CODE[0x69] = "Electronic Arts";
  LIC_CODE[0x70] = "Infogrames";
  LIC_CODE[0x71] = "Interplay";
  LIC_CODE[0x72] = "Broderbund";
  LIC_CODE[0x73] = "sculptured";
  LIC_CODE[0x75] = "sci";
  LIC_CODE[0x78] = "THQ";
  LIC_CODE[0x79] = "Accolade";
  LIC_CODE[0x80] = "misawa";
  LIC_CODE[0x83] = "lozc";
  LIC_CODE[0x86] = "Tokuma Shoten Intermedia";
  LIC_CODE[0x87] = "Tsukuda Original";
  LIC_CODE[0x91] = "Chunsoft";
  LIC_CODE[0x92] = "Video system";
  LIC_CODE[0x93] = "Ocean/Acclaim";
  LIC_CODE[0x95] = "Varie";
  LIC_CODE[0x96] = "Yonezawa/s’pal";
  LIC_CODE[0x97] = "Kaneko";
  LIC_CODE[0x99] = "Pack in soft";
  LIC_CODE[0xA4] = "Konami (Yu-Gi-Oh!)";
}

Cartridges::~Cartridges() {}

bool Cartridges::loadCartridges(char *cart) {
  snprintf(ctx.filename, sizeof(ctx.filename), "%s", cart);

  FILE *fp = fopen(cart, "r");

  if (!fp) {
    printf("Failed to open: %s\n", cart);
    return false;
  }

  printf("Opened: %s\n", ctx.filename);

  fseek(fp, 0, SEEK_END);
  ctx.rom_size = ftell(fp);

  rewind(fp);

  ctx.rom_data = (Byte *)malloc(ctx.rom_size);
  fread(ctx.rom_data, ctx.rom_size, 1, fp);
  fclose(fp);

  ctx.header = (RomHeader *)(ctx.rom_data + 0x100);
  ctx.header->title[15] = 0;

  printf("Cartridge Loaded:\n");
  printf("\t Title    : %s\n", ctx.header->title);
  printf("\t Type     : %2.2X (%s)\n", ctx.header->type, getTypeName());
  printf("\t ROM Size : %d KB\n", 32 << ctx.header->rom_size);
  printf("\t RAM Size : %2.2X\n", ctx.header->ram_size);
  printf("\t LIC Code : %2.2X (%s)\n", ctx.header->lic_code, getlicenseName().c_str());
  printf("\t ROM Vers : %2.2X\n", ctx.header->version);

  Word x = 0;
  for (Word i = 0x0134; i <= 0x014C; i++) {
    x = x - ctx.rom_data[i] - 1;
  }

  printf("\t Checksum : %2.2X (%s)\n", ctx.header->checksum, (x & 0xFF) ? "PASSED" : "FAILED");

  return true;
}

std::string Cartridges::getlicenseName() {
  if (ctx.header->new_lic_code <= 0xA4) {
    std::map<Byte, std::string>::iterator it;

    for (it = LIC_CODE.begin(); it != LIC_CODE.end(); ++it) {
      if (it->first == ctx.header->lic_code) return it->second;
    }
    // return LIC_CODE[ctx.header->lic_code];
  }

  return "UNKNOWN";
}

const char *Cartridges::getTypeName() {
  if (ctx.header->type <= 0x22) {
    return ROM_TYPES[ctx.header->type];
  }

  return "UNKNOWN";
}
