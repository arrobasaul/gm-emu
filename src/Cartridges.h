#pragma once
#include <map>
#include <string>

#include "Common.h"
typedef struct {
  Byte entry[4];
  Byte logo[0x30];

  char title[16];
  Word new_lic_code;
  Byte sgb_flag;
  Byte type;
  Byte rom_size;
  Byte ram_size;
  Byte dest_code;
  Byte lic_code;
  Byte version;
  Byte checksum;
  Word global_checksum;
} RomHeader;

class Cartridges {
 private:
  std::map<Byte, std::string> LIC_CODE;

 private:
  std::string getlicenseName();
  const char *getTypeName();

 public:
  Cartridges();
  ~Cartridges();
  bool loadCartridges(char *cart);
};
