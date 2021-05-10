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

# Setup Protobuf dependencies for build rules to work.
load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")

protobuf_deps()
