#ifndef ROT13_H_
#define ROT13_H_

// ROT13-obfuscates a file specified by its path, saving it to an output file.
// Returns the total number of microseconds spent in user mode.
extern "C" int Rot13File(const char* input_file, const char* output_file);

#endif  // ROT13_H_
