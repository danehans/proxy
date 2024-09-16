load(
    "@envoy//bazel:envoy_build_system.bzl",
    "envoy_cc_library",
)

package(default_visibility = ["//visibility:public"])

licenses(["notice"])

# Proto and C++ generation from proto file
proto_library(
    name = "config",
    srcs = ["config.proto"],
    deps = [
        "@com_google_protobuf//:duration_proto",
    ],
)

cc_proto_library(
    name = "config_cc_proto",
    deps = [":config"],
)

# Istio Stats filter implementation
envoy_cc_library(
    name = "istio_stats",
    srcs = ["istio_stats.cc"],
    hdrs = ["istio_stats.h"],
    repository = "@envoy",
    deps = [
        ":config_cc_proto",  # Include the generated proto
        "//extensions/common:metadata_object_lib",
        "@com_google_cel_cpp//eval/public:builtin_func_registrar",
        "@com_google_cel_cpp//eval/public:cel_expr_builder_factory",
        "@com_google_cel_cpp//parser",
        "@envoy//envoy/registry",
        "@envoy//envoy/router:string_accessor_interface",
        "@envoy//envoy/server:factory_context_interface",
        "@envoy//envoy/server:filter_config_interface",
        "@envoy//envoy/singleton:manager_interface",
        "@envoy//envoy/stream_info:filter_state_interface",
        "@envoy//source/common/grpc:common_lib",
        "@envoy//source/common/http:codes_lib",
        "@envoy//source/common/http:header_map_lib",
        "@envoy//source/common/http:header_utility_lib",
        "@envoy//source/common/network:utility_lib",
        "@envoy//source/common/stream_info:utility_lib",
        "@envoy//source/extensions/filters/common/expr:cel_state_lib",
        "@envoy//source/extensions/filters/common/expr:context_lib",
        "@envoy//source/extensions/filters/common/expr:evaluator_lib",
        "@envoy//source/extensions/filters/http/common:pass_through_filter_lib",
        "@envoy//source/extensions/filters/http/grpc_stats:config",
    ],
)

# Benchmark setup
cc_binary(
    name = "log_benchmark",
    srcs = ["log_benchmark.cc"],
    deps = [
        "@com_github_google_benchmark//:benchmark",  # Google Benchmark
        "@envoy//source/common/common:utility_lib",  # Envoy's common utility library
        "@envoy//source/common/http:header_map_lib",  # Target for HTTP header maps
        "@envoy//source/common/http:header_utility_lib",  # Target for HTTP header utilities
        "@envoy//source/common/stream_info:stream_info_lib",  # Correct Envoy stream_info target
        "@envoy//source/common/http:codes_lib",  # Target for HTTP status codes
        "//source/extensions/filters/http/istio_stats:config_cc_proto",  # Include the generated proto
        "//source/extensions/filters/http/istio_stats",  # Istio Stats Filter code
    ],
)
