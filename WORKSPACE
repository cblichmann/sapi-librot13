workspace(name = "cblichmann_sapi_librot13")

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:utils.bzl", "maybe")

# Include the Sandboxed API dependency.
maybe(
    git_repository,
    name = "com_google_sandboxed_api",
    branch = "main",
    remote = "https://github.com/google/sandboxed-api.git",
)

# Setup transitive dependencies (e.g. Abseil).
load(
    "@com_google_sandboxed_api//sandboxed_api/bazel:sapi_deps.bzl",
    "sapi_deps",
)

sapi_deps()

load(
    "@com_google_sandboxed_api//sandboxed_api/bazel:llvm_config.bzl",
    "llvm_disable_optional_support_deps",
)

llvm_disable_optional_support_deps()

# Setup dependencies for build rules to work.
load("@rules_python//python:repositories.bzl", "py_repositories")

py_repositories()

load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")

protobuf_deps()
