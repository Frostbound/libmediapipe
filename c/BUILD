package(default_visibility = [
    "//visibility:public",
])

cc_binary(
    name = "mediapipe",
    srcs = ["mediapipe.cpp", "mediapipe.h"],
    defines = ["MEDIAPIPE_EXPORT"],
    data = [
	    "//mediapipe/modules/pose_detection:pose_detection.tflite",
	    "//mediapipe/modules/pose_landmark:pose_landmark_heavy.tflite",
    ],
    deps = [
        "//mediapipe/framework:calculator_framework",
        "//mediapipe/framework/formats:image_frame",
        "//mediapipe/framework/formats:image_frame_opencv",
        "//mediapipe/framework/port:file_helpers",
        "//mediapipe/framework/port:opencv_highgui",
        "//mediapipe/framework/port:opencv_imgproc",
        "//mediapipe/framework/port:opencv_video",
        "//mediapipe/framework/port:parse_text_proto",
        "//mediapipe/framework/port:status",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
        
        "//mediapipe/modules/pose_landmark:pose_landmark_cpu",
    ],
    linkshared = 1,
)
