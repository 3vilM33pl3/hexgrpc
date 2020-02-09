#include <hexlib/HexagonService.hpp>
#include <fmt/format.h>
#include <hexlib/HexagonLibrary.hpp>

Status HexagonService::GetHexagonRing(::grpc::ServerContext *context, const ::hexagon::HexagonRingRequest *request,
                                      ::hexagon::HexCubeResponse *response) {
    auto hexpb = request->ha();
    auto result = HexagonLibrary::Ring(Hexagon(hexpb.x(), hexpb.y(), hexpb.z()), request->radius());

    google::protobuf::RepeatedPtrField<Hex> hexpbv;
    for(auto hex : result) {
        auto hexpb = response->mutable_hc()->Add();
        hexpb->set_x(hex.q);
        hexpb->set_y(hex.r);
        hexpb->set_z(hex.s);
    }

    return Status::OK;
}
