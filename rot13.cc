#include "rot13.h"

#include <sys/resource.h>
#include <sys/time.h>

#include <algorithm>
#include <fstream>

// ROT13-transforms a character. Assumes char is ASCII encoded.
constexpr char Rot13(char c) {
  if (c >= 'A' && c <= 'Z') {
    return 'A' + ((c - 'A') + 13) % 26;
  }
  if (c >= 'a' && c <= 'z') {
    return 'a' + ((c - 'a') + 13) % 26;
  }
  return c;
}

int Rot13File(const char* input_file, const char* output_file) {
  std::ifstream in(input_file, std::ios::binary);
  std::ofstream out(output_file, std::ios::binary);
  std::transform(std::istreambuf_iterator<char>(in),
                 std::istreambuf_iterator<char>(),
                 std::ostreambuf_iterator<char>(out), Rot13);

  struct rusage rusage;
  if (getrusage(RUSAGE_SELF, &rusage) != 0) {
    return -1;
  }
  return rusage.ru_utime.tv_sec * 1000000 + rusage.ru_utime.tv_usec;
}
