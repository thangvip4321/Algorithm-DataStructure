# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_binary
cc_binary(
    name = "main",
    srcs = glob(["*.cpp"]),
    copts = ["-Isrc"],
    deps = [
        "//src:algo-lib",
        # "//test:algo-test",
    ],
)
