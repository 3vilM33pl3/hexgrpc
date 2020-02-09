#pragma once

#include <grpc++/grpc++.h>
#include <hexagon.grpc.pb.h>
#include <hexlib/HexagonLibrary.hpp>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using hexagon::HexAxial;
using hexagon::Hex;
using hexagon::ConversionRequest;


class HexagonService final : public hexagon::HexagonService::Service {
public:
    Status GetHexagonRing(::grpc::ServerContext *context, const ::hexagon::HexagonRingRequest *request,
                          ::hexagon::HexCubeResponse *response) override;

public:

};
