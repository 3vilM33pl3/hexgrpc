#include <hexlib/HexagonService.hpp>
#include <fmt/format.h>
#include <hexlib/Hexagon.hpp>


void HexagonService::SayHello() {
    fmt::print("Haai");
}

Status HexagonService::GetHexagons(ServerContext *context,
        const Request *request, Response *response) {

    for(auto item: request->hc()) {
        auto ha = response->add_ha();
        Hexagon::Cube2Axial(&item, ha);
    }

    return Status::OK ;
}
