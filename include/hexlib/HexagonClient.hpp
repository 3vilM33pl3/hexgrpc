#pragma once

#include <grpc++/grpc++.h>
#include "hexagon.grpc.pb.h"

using namespace std;

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using hexagon::Request;
using hexagon::Response;
using hexagon::HexCube;
using hexagon::HexAxial;
using hexagon::HexagonService;


class HexagonClient {
public:
    HexagonClient();

    explicit HexagonClient(const shared_ptr<Channel>& channel) : stub_(HexagonService::NewStub(channel)) {}

    Status Send(vector<HexAxial>& hexAxials);
    void Add(const HexCube& hc);
private:
    unique_ptr<HexagonService::Stub> stub_;
    vector<HexCube> HexCubes;

};
