cc_test(
    name = "algo-test",
    size = "small",
    srcs = glob(["*.cpp"]),
    copts = ["-Isrc"],
    visibility = ["//visibility:public"],
    deps = [
        "//src:algo-lib",
        "@gtest//:gtest_main",
    ],
)
