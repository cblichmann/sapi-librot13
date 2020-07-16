#include <libgen.h>

#include <iostream>

#include "rot13_sapi.sapi.h"
#include "sandboxed_api/util/flag.h"

// These exist and can be set programmatically
ABSL_DECLARE_FLAG(string, sandbox2_danger_danger_permit_all);
ABSL_DECLARE_FLAG(string, sandbox2_danger_danger_permit_all_and_log);

// Implement a custom sandbox that disables namespaces.
// Note that we need to use absolute paths for both input and output, as the
// sandboxee will have a different working directory.
class Rot13SapiSandbox : public Rot13Sandbox {
 public:
  Rot13SapiSandbox(const std::string& in_file, const std::string& out_file)
      : in_file_(in_file), out_file_(out_file) {}

  std::unique_ptr<sandbox2::Policy> ModifyPolicy(
      sandbox2::PolicyBuilder*) override {
    // Return a new policy.
    return sandbox2::PolicyBuilder()
        .AddFile(in_file_)
        // Why are we adding a directory here?
        .AddDirectoryAt(dirname(&out_file_[0]), "/output", /*is_ro=*/false)
        .BuildOrDie();
  }

 private:
  std::string in_file_;
  std::string out_file_;
};

int main(int argc, char* argv[]) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  if (argc != 3) {
    std::cerr << "usage: " << basename(argv[0]) << " INPUT OUTPUT\n";
    return 1;
  }

  std::string in_file(argv[1]);
  std::string out_file(argv[2]);

  std::cout << "initializing sandbox...\n";
  Rot13SapiSandbox sandbox(in_file, out_file);
  sandbox.Init().IgnoreError();

  std::cout << "obfuscating " << in_file << ", saving to " << out_file
            << "...\n";

  Rot13Api api(&sandbox);
  sapi::v::ConstCStr in_file_var(in_file.c_str());
  std::string out_file_in_sandboxee(std::string("/output/") +
                                    basename(&out_file[0]));
  sapi::v::ConstCStr out_file_var(out_file_in_sandboxee.c_str());

  std::cout << "result: "
            << api.Rot13File(in_file_var.PtrBefore(), out_file_var.PtrBefore())
                   .value()
            << "usec\n";
  return 0;
}
