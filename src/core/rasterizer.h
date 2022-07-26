#pragma once
#include <glm/glm.hpp>
using namespace glm;
class FrameBuffer;

struct TriangleInfo
{
    const vec4 v1;
    const vec4 v2;
    const vec4 v3;
    const vec4 c1;
    const vec4 c2;
    const vec4 c3;
};

class Rasterizer
{
public:
    enum class Mode
    {
        LINE,
        POINT,
        TRIANGLE,
    };

    static void rasterize(const TriangleInfo &info, FrameBuffer *frame_buffer,
                          Mode mode = Mode::POINT);

    static void draw_line(const vec3 &v1, const vec3 &v2,
                          const vec3 &color, FrameBuffer *frame_buffer);

    static void draw_triangle(const TriangleInfo &info, FrameBuffer *frame_buffer);

    static void draw_point(const vec3 &v, const vec3 &color, FrameBuffer *frame_buffer);

    static vec3 viewport_transform(const vec3 &v, int width, int height);
};
