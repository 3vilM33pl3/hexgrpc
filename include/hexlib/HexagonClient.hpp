#pragma once

#include <grpc++/grpc++.h>
#include "hexagon.grpc.pb.h"
#include "HexagonLibrary.hpp"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using hexagon::ConversionRequest;
using hexagon::HexAxialResponse;
using hexagon::HexagonRingRequest;
using hexagon::HexCubeResponse;
using hexagon::Hex;
using hexagon::HexAxial;
using hexagon::HexagonService;

using namespace std;

class HexagonClient {
public:
    HexagonClient();
    explicit HexagonClient(const shared_ptr<Channel>& channel) :
            stub_(HexagonService::NewStub(channel)), channel(channel) {}


    grpc_connectivity_state GetConnectionStatus();

    vector<Hexagon> GetHexagonRing(const Hexagon* hex, const int64_t radius);

private:
    unique_ptr<HexagonService::Stub> stub_;
    vector<Hex> HexCubes;
    shared_ptr<Channel> channel;
    static hexagon::Hex Convert2Proto(const Hexagon* x);
};
