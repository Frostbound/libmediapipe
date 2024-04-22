# Description:
#   OpenCV libraries for video/image processing on MacOS

licenses(["notice"])  # BSD license

exports_files(["LICENSE"])

load("@bazel_skylib//lib:paths.bzl", "paths")

cc_library(
    name = "opencv",
    srcs = glob(
        [
            "lib/libopencv_core4.a",
            "lib/libopencv_calib3d4.a",
            "lib/libopencv_features2d4.a",
            "lib/libopencv_highgui4.a",
            "lib/libopencv_imgcodecs4.a",
            "lib/libopencv_imgproc4.a",
            "lib/libopencv_video4.a",
            "lib/libopencv_videoio4.a",
        ],
    ),
    hdrs = glob(["include/opencv2/**/*.h*"]),
    includes = ["include/"],
    linkstatic = 1,
    visibility = ["//visibility:public"],
)
