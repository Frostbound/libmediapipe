#ifndef MEDIAPIPE_H
#define MEDIAPIPE_H

#include <stdint.h>
#include <stddef.h>

#if _WIN32
#   ifdef MEDIAPIPE_EXPORT
#       define MEDIAPIPE_API __declspec(dllexport)
#   else
#       define MEDIAPIPE_API __declspec(dllimport)
#   endif
#else
#   define MEDIAPIPE_API __attribute__((visibility("default")))
#endif

#ifdef __ANDROID__
#   include <jni.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/// Structure specifying instance properties before creation.
typedef struct mp_instance_builder mp_instance_builder;

/// Structure containing the MediaPipe graph as well as some extra information.
/// Data in MediaPipe flows between nodes of a graph to perform computations.
/// The graph takes some packets via an input stream and outputs the resulting packets
/// via output streams that can be read from using pollers.
typedef struct mp_instance mp_instance;

/// An interface for polling packets from an output stream.
typedef struct mp_poller mp_poller;

/// The basic data flow unit in a graph.
/// Packets can be put into an input stream to process them and polled from
/// an output stream to access the results.
typedef struct mp_packet mp_packet;

/// Enum specifying the format of image data.
/// For more information, see: https://github.com/google/mediapipe/blob/master/mediapipe/framework/formats/image_format.proto
typedef enum : int {
  mp_image_format_unknown = 0,
  mp_image_format_srgb = 1,
  mp_image_format_srgba = 2,
  mp_image_format_gray8 = 3,
  mp_image_format_gray16 = 4,
  mp_image_format_ycbcr420p = 5,
  mp_image_format_ycbcr420p10 = 6,
  mp_image_format_srgb48 = 7,
  mp_image_format_srgba64 = 8,
  mp_image_format_vec32f1 = 9,
  mp_image_format_vec32f2 = 12,
  mp_image_format_lab8 = 10,
  mp_image_format_sbgra = 11
} mp_image_format;

/// A structure for wrapping pixel data.
struct mp_image{
    const uint8_t* data;
    int width;
    int height;
    mp_image_format format;
};

/// The 3D position of a landmark.
struct mp_landmark {
    float x;
    float y;
    float z;
    float visibility;
    float presence;
};

/// A list of landmarks detected for a face or hand.
struct mp_landmark_list {
    mp_landmark* elements;
    int length;
};

/// A list of hands or faces detected in an image.
struct mp_multi_face_landmark_list {
    mp_landmark_list* elements;
    int length;
};

/// A rectangle with a rotation in radians.
struct mp_rect {
    float x_center;
    float y_center;
    float width;
    float height;
    float rotation;
    long long id;
};

/// A list of rectangles.
struct mp_rect_list {
    mp_rect* elements;
    int length;
};

/// Hand landmark indices in a mp_landmark_list.
/// For more information, see: https://google.github.io/mediapipe/solutions/hands.html#hand-landmark-model
enum mp_hand_landmark{
    mp_hand_landmark_wrist = 0,
    mp_hand_landmark_thumb_cmc = 1,
    mp_hand_landmark_thumb_mcp = 2,
    mp_hand_landmark_thumb_ip = 3,
    mp_hand_landmark_thumb_tip = 4,
    mp_hand_landmark_index_finger_mcp = 5,
    mp_hand_landmark_index_finger_pip = 6,
    mp_hand_landmark_index_finger_dip = 7,
    mp_hand_landmark_index_finger_tip = 8,
    mp_hand_landmark_middle_finger_mcp = 9,
    mp_hand_landmark_middle_finger_pip = 10,
    mp_hand_landmark_middle_finger_dip = 11,
    mp_hand_landmark_middle_finger_tip = 12,
    mp_hand_landmark_ring_finger_mcp = 13,
    mp_hand_landmark_ring_finger_pip = 14,
    mp_hand_landmark_ring_finger_dip = 15,
    mp_hand_landmark_ring_finger_tip = 16,
    mp_hand_landmark_pinky_mcp = 17,
    mp_hand_landmark_pinky_pip = 18,
    mp_hand_landmark_pinky_dip = 19,
    mp_hand_landmark_pinky_tip = 20
};

enum mp_pose_landmark{
    mp_pose_landmark_nose = 0,
    mp_pose_landmark_left_eye_inner = 1,
    mp_pose_landmark_left_eye = 2,
    mp_pose_landmark_left_eye_outer = 3,
    mp_pose_landmark_right_eye_inner = 4,
    mp_pose_landmark_right_eye = 5,
    mp_pose_landmark_right_eye_outer = 6,
    mp_pose_landmark_left_ear = 7,
    mp_pose_landmark_right_ear = 8,
    mp_pose_landmark_mouth_left = 9,
    mp_pose_landmark_mouth_right = 10,
    mp_pose_landmark_left_shoulder = 11,
    mp_pose_landmark_right_shoulder = 12,
    mp_pose_landmark_left_elbow = 13,
    mp_pose_landmark_right_elbow = 14,
    mp_pose_landmark_left_wrist = 15,
    mp_pose_landmark_right_wrist = 16,
    mp_pose_landmark_left_pinky = 17,
    mp_pose_landmark_right_pinky = 18,
    mp_pose_landmark_left_index = 19,
    mp_pose_landmark_right_index = 20,
    mp_pose_landmark_left_thumb = 21,
    mp_pose_landmark_right_thumb = 22,
    mp_pose_landmark_left_hip = 23,
    mp_pose_landmark_right_hip = 24,
    mp_pose_landmark_left_knee = 25,
    mp_pose_landmark_right_knee = 26,
    mp_pose_landmark_left_ankle = 27,
    mp_pose_landmark_right_ankle = 28,
    mp_pose_landmark_left_heel = 29,
    mp_pose_landmark_right_heel = 30,
    mp_pose_landmark_left_foot_index = 31,
    mp_pose_landmark_right_foot_index = 32
};

/// Creates an instance builder, which is used by mp_create_instance to create a MediaPipe instance.
/// The instance builder requires the path to the binary graph and the name of the input stream.
MEDIAPIPE_API mp_instance_builder* mp_create_instance_builder(const char* graph_filename, const char* input_stream);

MEDIAPIPE_API void mp_destroy_instance_builder(mp_instance_builder* instance_builder);

/// Sets a float value in the node options of the graph.
MEDIAPIPE_API void mp_add_option_float(mp_instance_builder* instance_builder, const char* node, const char* option, float value);

/// Sets a double value in the node options of the graph.
MEDIAPIPE_API void mp_add_option_double(mp_instance_builder* instance_builder, const char* node, const char* option, double value);

/// Adds a side packet to the stream.
/// The function claims ownership of the packet and will deallocate it.
MEDIAPIPE_API void mp_add_side_packet(mp_instance_builder* instance_builder, const char* name, mp_packet* packet);

/// Creates a MediaPipe instance, which contains the graph with some extra information.
/// The instance should be deallocated when no longer used with mp_destroy_instance.
/// Returns NULL on failure.
MEDIAPIPE_API mp_instance* mp_create_instance(mp_instance_builder* builder);

/// Creates a poller to read packets from an output stream.
/// The poller should be deallocated before the instance with mp_destroy_poller.
/// Returns NULL on failure.
MEDIAPIPE_API mp_poller* mp_create_poller(mp_instance* instance, const char* output_stream);

/// Starts the graph associated with the instance.
/// Returns true on success.
MEDIAPIPE_API bool mp_start(mp_instance* instance);

/// Sends a packet to the input stream specified in mp_create_instance_builder.
/// The results won't be available immediately. Call mp_get_queue_size to check whether the
/// packet has been processed or mp_wait_until_idle to block until the results are available.
/// Returns true on success.
MEDIAPIPE_API bool mp_process(mp_instance* instance, mp_packet* packet);

/// Blocks until the MediaPipe graph has finished the work submitted with mp_process and
/// the results are available.
/// Returns true on success.
MEDIAPIPE_API bool mp_wait_until_idle(mp_instance* instance);

/// Returns the number of packets available in an output stream.
/// This function should be called before polling packets to avoid infinite blocking.
MEDIAPIPE_API int mp_get_queue_size(mp_poller* poller);

/// Deallocates a poller.
MEDIAPIPE_API void mp_destroy_poller(mp_poller* poller);

/// Stops the graph associated with the instance and deallocates it.
/// Returns true on success.
MEDIAPIPE_API bool mp_destroy_instance(mp_instance* instance);

/// Sets the root resource directory.
/// Model files referenced in graphs are loaded from this directory.
/// This function has no effect on Android because the resources are loaded from assets (see mp_init_asset_manager).
MEDIAPIPE_API void mp_set_resource_dir(const char* dir);

#ifdef __ANDROID__
/// Initializes the Android asset manager.
/// This function must be called before creating an instance so the resources can be loaded.
/// The asset manager is initialized with Java objects that can be passed to C code through JNI. 
/// cache_dir_path should be set to android_context.getCacheDir().getAbsolutePath().
MEDIAPIPE_API void mp_init_asset_manager(JNIEnv* env, jobject android_context, jstring cache_dir_path);
#endif

/// Creates a packet with an integer value.
MEDIAPIPE_API mp_packet* mp_create_packet_int(int value);

/// Creates a packet with a float value.
MEDIAPIPE_API mp_packet* mp_create_packet_float(float value);

/// Creates a packet with a bool value.
MEDIAPIPE_API mp_packet* mp_create_packet_bool(bool value);

/// Creates a packet with an image value.
/// The pixel data is copied and not deallocated.
MEDIAPIPE_API mp_packet* mp_create_packet_image(mp_image image);

/// Polls a packet from an output stream.
/// The packet should be deallocated with mp_destroy_packet.
MEDIAPIPE_API mp_packet* mp_poll_packet(mp_poller* poller);

/// Deallocates a packet.
MEDIAPIPE_API void mp_destroy_packet(mp_packet* packet);

/// Returns the name of the packet type.
MEDIAPIPE_API const char* mp_get_packet_type(mp_packet* packet);

/// Deallocates the type name returned by mp_get_packet_type.
MEDIAPIPE_API void mp_free_packet_type(const char* type);

/// Copies a packet image into a buffer.
MEDIAPIPE_API void mp_copy_packet_image(mp_packet* packet, uint8_t* out_data);

/// Returns the multi-face landmarks of a packet.
/// The list should be destroyed with mp_destroy_multi_face_landmarks.
MEDIAPIPE_API mp_multi_face_landmark_list* mp_get_multi_face_landmarks(mp_packet* packet);

/// Returns the normalized multi-face landmarks of a packet.
/// The list should be destroyed with mp_destroy_multi_face_landmarks.
MEDIAPIPE_API mp_multi_face_landmark_list* mp_get_norm_multi_face_landmarks(mp_packet* packet);

MEDIAPIPE_API bool mp_packet_get_bool(mp_packet* packet);

/// Deallocates a multi-face landmark list.
MEDIAPIPE_API void mp_destroy_multi_face_landmarks(mp_multi_face_landmark_list* multi_face_landmarks);

/// Returns the landmarks of a packet.
/// The list should be destroyed with mp_destroy_landmarks.
MEDIAPIPE_API mp_landmark_list* mp_get_landmarks(mp_packet* packet);

/// Returns the normalized landmarks of a packet.
/// The list should be destroyed with mp_destroy_landmarks.
MEDIAPIPE_API mp_landmark_list* mp_get_norm_landmarks(mp_packet* packet);

/// Deallocates a landmark list.
MEDIAPIPE_API void mp_destroy_landmarks(mp_landmark_list* landmarks);


/// Returns the rectangles of a packet.
/// The list should be destroyed with mp_destroy_rects.
MEDIAPIPE_API mp_rect_list* mp_get_rects(mp_packet* packet);

/// Returns the normalized rectangles of a packet.
/// The list should be destroyed with mp_destroy_rects.
MEDIAPIPE_API mp_rect_list* mp_get_norm_rects(mp_packet* packet);

/// Deallocates a rectangle list.
MEDIAPIPE_API void mp_destroy_rects(mp_rect_list* list);

/// Returns the last error message generated.
MEDIAPIPE_API const char* mp_get_last_error();

/// Deallocates the error message returned by mp_get_last_error
MEDIAPIPE_API void mp_free_error(const char* message);

#ifdef __cplusplus
}
#endif

#endif