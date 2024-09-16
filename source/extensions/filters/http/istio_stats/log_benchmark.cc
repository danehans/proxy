#include "benchmark/benchmark.h"
#include "source/extensions/filters/http/istio_stats/istio_stats.h"
#include "source/common/stream_info/stream_info_impl.h"
#include "source/common/http/header_map_impl.h"
#include "source/common/http/header_utility.h"
#include "source/common/common/utility.h"
#include "source/extensions/filters/http/istio_stats/config.pb.h"  // Include the generated proto header for config

using namespace Envoy::Extensions::HttpFilters::IstioStats;

static void BM_IstioStatsFilterLog(benchmark::State& state) {
    // Initialize the header maps using factory methods
    auto request_headers = Envoy::Http::RequestHeaderMapImpl::create();
    request_headers->setCopy(Envoy::Http::LowerCaseString(":method"), "GET");
    request_headers->setCopy(Envoy::Http::LowerCaseString(":path"), "/");

    auto response_headers = Envoy::Http::ResponseHeaderMapImpl::create();
    response_headers->setCopy(Envoy::Http::LowerCaseString(":status"), "200");

    auto response_trailers = Envoy::Http::ResponseTrailerMapImpl::create();

    // Use RealTimeSource for benchmarking
    Envoy::RealTimeSource time_source;

    // Properly construct StreamInfoImpl using RealTimeSource
    Envoy::StreamInfo::StreamInfoImpl stream_info(time_source, nullptr, Envoy::StreamInfo::FilterState::LifeSpan::Connection);

    // Initialize the PluginConfig proto config for Istio Stats
    auto proto_config = std::make_shared<stats::PluginConfig>();

    // Use the IstioStatsFilterConfigFactory to create the filter factory
    IstioStatsFilterConfigFactory factory;
    auto config = factory.createEmptyConfigProto();
    config->MergeFrom(*proto_config);

    // Benchmark the log method over multiple iterations
    for (auto _ : state) {
        // Use this section to simulate actual logging for benchmarking.
        // For example:
        // istio_stats_filter.log(*request_headers, stream_info);
    }
}

// Register the benchmark
BENCHMARK(BM_IstioStatsFilterLog)->Unit(benchmark::kMicrosecond);

BENCHMARK_MAIN();
