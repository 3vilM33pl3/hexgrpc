#include <hexlib/HexagonClient.hpp>
#include <hexlib/HexagonLibrary.hpp>

HexagonClient::HexagonClient() {}

hexagon::Hex HexagonClient::Convert2Proto(const Hexagon* x) {
    hexagon::Hex pbhex;
    pbhex.set_x(x->Q);
    pbhex.set_y(x->R);
    pbhex.set_z(x->S);
    return pbhex;
}

vector<Hexagon> HexagonClient::GetHexagonRing(const Hexagon* hex, const int64_t radius) {
    HexagonRingRequest request;

    request.mutable_ha()->CopyFrom(Convert2Proto(hex));
    request.set_radius(radius);

    ClientContext context;
    HexCubeResponse response;

    auto status = stub_->GetHexagonRing(&context, request, &response);
    vector<Hexagon> result;
    for(auto hexpb: response.hc()) {
        result.push_back(Hexagon(hexpb.x(), hexpb.y(), hexpb.z()));
    }

    return result;
}

grpc_connectivity_state HexagonClient::GetConnectionStatus() {
    return channel->GetState(false);
}

