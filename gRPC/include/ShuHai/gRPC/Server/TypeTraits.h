#pragma once

#include "ShuHai/gRPC/TypeTraits.h"
#include "ShuHai/TypeTraits.h"
#include "ShuHai/FunctionTraits.h"

namespace ShuHai::gRPC::Server
{
    /**
     * \brief Deduce types from function AsyncService::Request<RpcName>.
     * \tparam F Type of function AsyncService::Request<RpcName> in generated code.
     */
    template<typename F>
    struct AsyncRequestTraits;

    template<typename Service, typename Request, typename Response>
    struct AsyncRequestTraits<void (Service::*)(grpc::ServerContext*, Request*,
        grpc::ServerAsyncResponseWriter<Response>* response, grpc::CompletionQueue*, grpc::ServerCompletionQueue*,
        void*)>
    {
        using ServiceType = Service;
        using RequestType = Request;
        using ResponseType = Response;
        using StreamingInterfaceType = grpc::ServerAsyncResponseWriter<Response>;

        static constexpr RpcType RpcType = RpcType::NORMAL_RPC;
    };

    template<typename Service, typename Request, typename Response>
    struct AsyncRequestTraits<void (Service::*)(grpc::ServerContext*, Request*, grpc::ServerAsyncWriter<Response>*,
        grpc::CompletionQueue*, grpc::ServerCompletionQueue*, void*)>
    {
        using ServiceType = Service;
        using RequestType = Request;
        using ResponseType = Response;
        using StreamingInterfaceType = grpc::ServerAsyncWriter<Response>;

        static constexpr RpcType RpcType = RpcType::SERVER_STREAMING;
    };

    template<typename Service, typename Request, typename Response>
    struct AsyncRequestTraits<void (Service::*)(grpc::ServerContext*, grpc::ServerAsyncReader<Response, Request>*,
        grpc::CompletionQueue*, grpc::ServerCompletionQueue*, void*)>
    {
        using ServiceType = Service;
        using RequestType = Request;
        using ResponseType = Response;
        using StreamingInterfaceType = grpc::ServerAsyncReader<Response, Request>;

        static constexpr RpcType RpcType = RpcType::CLIENT_STREAMING;
    };

    template<typename Service, typename Request, typename Response>
    struct AsyncRequestTraits<void (Service::*)(grpc::ServerContext*, grpc::ServerAsyncReaderWriter<Response, Request>*,
        grpc::CompletionQueue*, grpc::ServerCompletionQueue*, void*)>
    {
        using ServiceType = Service;
        using RequestType = Request;
        using ResponseType = Response;
        using StreamingInterfaceType = grpc::ServerAsyncReaderWriter<Response, Request>;

        static constexpr RpcType RpcType = RpcType::BIDI_STREAMING;
    };

    template<typename F, RpcType T, typename Result>
    using EnableIfRpcTypeMatch = std::enable_if_t<AsyncRequestTraits<F>::RpcType == T, Result>;
}
