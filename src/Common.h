#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <memory>

using Byte = unsigned char;
using Word = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long;

#define NO_IMPL                               \
  {                                           \
    fprintf(stderr, "NOT YET IMPLEMENTED\n"); \
    exit(-5);                                 \
  }
