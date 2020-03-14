// Implementations of methods described here: https://www.redblobgames.com/grids/hexagons/
#pragma once

#include <cmath>

using namespace std;

struct Point
{
    double X;
    double y;
    Point(double x_, double y_): X(x_), y(y_) {}
    Point(): X(0), y(0) {}

    Point operator/ (int64_t div) {
        return Point(this->X / div, this->y / div);
    }

    Point operator/ (Point p) {
        return Point(this->X / p.X, this->y / p.y);
    }

    Point operator+ (Point p) {
        return Point(this->X + p.X, this->y + p.y);
    }

    Point operator- (Point p) {
        return Point(this->X - p.X, this->y - p.y);
    }

};

struct AxialCoordinates {
    int32_t Q;
    int32_t R;

    AxialCoordinates(int32_t Q_, int32_t R_) {
        Q = Q_;
        R = R_;
    }
};

struct Hexagon
{
    int Q;
    int R;
    int S;

    Hexagon(AxialCoordinates AC) {
        Q = AC.Q;
        R = AC.R;
        S = - AC.Q - AC.R;
    }

    Hexagon(int Q_, int R_, int S_): Q(Q_), R(R_), S(S_) {
        if (Q + R + S != 0) throw "q + r + s must be 0";
    }

    Hexagon operator/ (int64_t div) {
        return Hexagon(this->Q / div, this->R / div, this->S / div);
    }

    Hexagon operator/ (Hexagon hex) {
        return Hexagon(this->Q / hex.Q, this->R / hex.R, this->S / hex.S);
    }

    Hexagon operator+(Hexagon hex) {
        return Hexagon(this->Q + hex.Q, this->R + hex.R, this->S + hex.S);
    }

    Hexagon operator++() {
        return Hexagon(this->Q + this->Q, this->R + this->R, this->S + this->S);
    }
};


struct FractionalHexagon
{
    const double q;
    const double r;
    const double s;
    FractionalHexagon(double q_, double r_, double s_): q(q_), r(r_), s(s_) {
        if (round(q + r + s) != 0) throw "q + r + s must be 0";
    }
};


struct OffsetCoord
{
    const int col;
    const int row;
    OffsetCoord(int col_, int row_): col(col_), row(row_) {}
};


struct DoubledCoord
{
    const int col;
    const int row;
    DoubledCoord(int col_, int row_): col(col_), row(row_) {}
};


struct Orientation
{
    const double f0;
    const double f1;
    const double f2;
    const double f3;
    const double b0;
    const double b1;
    const double b2;
    const double b3;
    const double start_angle;
    Orientation(double f0_, double f1_, double f2_, double f3_, double b0_, double b1_, double b2_, double b3_, double start_angle_): f0(f0_), f1(f1_), f2(f2_), f3(f3_), b0(b0_), b1(b1_), b2(b2_), b3(b3_), start_angle(start_angle_) {}
};


struct Layout
{
    const Orientation orientation;
    const Point size;
    const Point origin;
    Layout(Orientation orientation_, Point size_, Point origin_): orientation(orientation_), size(size_), origin(origin_) {}
};

const vector<Hexagon> HexagonDirections = {
        Hexagon(1, 0, -1), Hexagon(1, -1, 0), Hexagon(0, -1, 1),
        Hexagon(-1, 0, 1), Hexagon(-1, 1, 0), Hexagon(0, 1, -1)
};

class HexagonLibrary {
public:
    static vector<Hexagon> Ring(Hexagon center, const int64_t radius) {
        vector<Hexagon> results;
        Hexagon hex = center + Scale(HexagonDirections[4], radius);

        for(int i = 0; i < 6; i++) {
            for(int j = 0; j < radius; j++ ) {
                results.push_back(hex);
                hex = Neighbor(hex, i);
            }
        }
        return results;

    }

    static Hexagon Scale(Hexagon hex, int64_t radius) {
        return Hexagon(hex.Q * radius, hex.R * radius, hex.S * radius);
    }

    static Hexagon Direction(int i) {
        assert(i >= 0 && i < 6);
        return HexagonDirections[i];
    }

    static Hexagon Neighbor(Hexagon a, int direction) {
        return a + HexagonDirections[direction];
    }

};