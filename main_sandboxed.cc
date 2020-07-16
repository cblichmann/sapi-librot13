#include <libgen.h>

#include <iostream>

#include "rot13_sapi.sapi.h"
#include "sandboxed_api/util/flag.h"

// These exist and can be set programmatically
ABSL_DECLARE_FLAG(string, sandbox2_danger_danger_permit_all);
ABSL_DECLARE_FLAG(string, sandbox2_danger_danger_permit_all_and_log);

int main(int argc, char* argv[]) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  if (argc != 3) {
    std::cerr << "usage: " << basename(argv[0]) << " INPUT OUTPUT\n";
    return 1;
  }

  std::string in_file(argv[1]);
  std::string out_file(argv[2]);

  std::cout << "initializing sandbox...\n";
  Rot13Sandbox sandbox;
  sandbox.Init().IgnoreError();

  std::cout << "obfuscating " << in_file << ", saving to " << out_file
            << "...\n";

  Rot13Api api(&sandbox);
  sapi::v::ConstCStr in_file_var(in_file.c_str());
  sapi::v::ConstCStr out_file_var(out_file.c_str());

  std::cout << "result: "
            << api.Rot13File(in_file_var.PtrBefore(), out_file_var.PtrBefore())
                   .value()
            << "usec\n";
  return 0;
}
