#include <libgen.h>

#include <iostream>

#include "rot13.h"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "usage: " << basename(argv[0]) << " INPUT OUTPUT\n";
    return 1;
  }
  std::cout << "obfuscating " << argv[1] << ", saving to " << argv[2] << "...\n";
  std::cout << "result: " << Rot13File(argv[1], argv[2]) << "usec\n";
  return 0;
}
