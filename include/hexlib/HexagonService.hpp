#pragma once

#include <grpc++/grpc++.h>
#include <hexagon.grpc.pb.h>
#include <hexlib/Hexagon.hpp>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using hexagon::HexAxial;
using hexagon::HexCube;
using hexagon::Request;
using hexagon::Response;

class HexagonService final : public hexagon::HexagonService::Service {
public:
    void SayHello();

    grpc::Status GetHexagons(::grpc::ServerContext *context, const ::hexagon::Request *request,
                             ::hexagon::Response *response) override;
};
