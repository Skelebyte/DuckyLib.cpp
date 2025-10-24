#include "../../include/graphics/color.hpp"

using namespace ducky;
using namespace ducky::graphics;

Color::Color() : r(1.0f), g(1.0f), b(1.0f), a(1.0f) {}

Color::Color(float r_, float g_, float b_, float a_)
    : r(r_), g(g_), b(b_), a(a_) {}

Color Color::white() { return Color(1.0f, 1.0f, 1.0f, 1.0f); }

Color Color::black() { return Color(0.0f, 0.0f, 0.0f, 1.0f); }

Color Color::grey() { return Color(0.5f, 0.5f, 0.5f, 1.0f); }

Color Color::pink() { return Color(1.0f, 0.0f, 1.0f, 1.0f); }

Color Color::red() { return Color(1.0f, 0.0f, 0.0f, 1.0f); }

Color Color::green() { return Color(0.0f, 1.0f, 0.0f, 1.0f); }

Color Color::blue() { return Color(0.0f, 0.0f, 1.0f, 1.0f); }
