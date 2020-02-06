#include <hexlib/HexagonClient.hpp>

Status HexagonClient::Send(vector<HexAxial>& hexAxials) {
    Request request;

    if(HexCubes.size() > 0) {
        for (auto item: HexCubes) {
            auto hc = request.add_hc();
            hc->set_x(item.x());
            hc->set_y(item.y());
            hc->set_z(item.z());
        }

        ClientContext context;
        Response response;
        auto status = stub_->GetHexagons(&context, request, &response);

        for (auto item: response.ha()) {
            hexAxials.push_back(item);
        }
        return status;
    }

    return Status(grpc::StatusCode::ABORTED, "Empty stack, nothing to send");
}

void HexagonClient::Add(const HexCube &hc)  {
    HexCubes.push_back(hc);
}

HexagonClient::HexagonClient() {}

