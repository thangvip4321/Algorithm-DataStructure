# load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# http_archive(
#     name = "gtest",
#     build_file = "@//:gtest.BUILD",
#     sha256 = "353571c2440176ded91c2de6d6cd88ddd41401d14692ec1f99e35d013feda55a",
#     strip_prefix = "googletest-release-1.11.0",
#     url = "https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip",
# )
# workspace(name = "algorithm")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "gtest",
    # build_file = "@//:gtest.BUILD",
    sha256 = "94c634d499558a76fa649edb13721dce6e98fb1e7018dfaeba3cd7a083945e91",
    strip_prefix = "googletest-release-1.10.0",
    url = "https://github.com/google/googletest/archive/release-1.10.0.zip",
)

http_archive(
    name = "rules_cc",
    strip_prefix = "rules_cc-40548a2974f1aea06215272d9c2b47a14a24e556",
    urls = ["https://github.com/bazelbuild/rules_cc/archive/40548a2974f1aea06215272d9c2b47a14a24e556.zip"],
)
