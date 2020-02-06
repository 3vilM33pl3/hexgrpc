// Implementations of methods described here: https://www.redblobgames.com/grids/hexagons/

#pragma once

#include <hexagon.grpc.pb.h>

using hexagon::HexAxial;
using hexagon::HexCube;

class Hexagon {
public:
    static void Cube2Axial(const HexCube* hc, HexAxial* ha) {
        ha->set_u(hc->x()), ha->set_v(hc->z());
    }
};