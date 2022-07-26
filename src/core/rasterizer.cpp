#include "core/rasterizer.h"
#include "framebuffer.h"
#include <iostream>
struct EdgeEquation
{
    float a;
    float b;
    float c;
    bool tie;

    EdgeEquation(const vec3 &v0, const vec3 &v1)
    {
        a = v0.y - v1.y;
        b = v1.x - v0.x;
        c = -(a * (v0.x + v1.x) + b * (v0.y + v1.y)) / 2;
        tie = a != 0 ? a > 0 : b > 0;
    }

    /// Evaluate the edge equation for the given point.
    float evaluate(float x, float y)
    {
        return a * x + b * y + c;
    }

    /// Test if the given point is inside the edge.
    bool test(float x, float y)
    {
        return test(evaluate(x, y));
    }

    /// Test for a given evaluated value.
    bool test(float v)
    {
        return (v > 0 || v == 0 && tie);
    }
};

struct ParameterEquation
{
    float a;
    float b;
    float c;

    ParameterEquation(
        float p0,
        float p1,
        float p2,
        const EdgeEquation &e0,
        const EdgeEquation &e1,
        const EdgeEquation &e2,
        float area)
    {
        float factor = 1.0f / (2.0f * area);

        a = factor * (p0 * e0.a + p1 * e1.a + p2 * e2.a);
        b = factor * (p0 * e0.b + p1 * e1.b + p2 * e2.b);
        c = factor * (p0 * e0.c + p1 * e1.c + p2 * e2.c);
    }

    /// Evaluate the parameter equation for the given point.
    float evaluate(float x, float y)
    {
        return a * x + b * y + c;
    }
};

void Rasterizer::rasterize(const TriangleInfo &info, FrameBuffer *frame_buffer, Mode mode)
{
    if (mode == Mode::POINT)
    {
        auto red = vec3(1.0, 0.0, 0.0);
        Rasterizer::draw_point(info.v1, red, frame_buffer);
        Rasterizer::draw_point(info.v2, red, frame_buffer);
        Rasterizer::draw_point(info.v3, red, frame_buffer);
    }
    else if (mode == Mode::TRIANGLE)
    {
        Rasterizer::draw_triangle(info, frame_buffer);
    }
}

void Rasterizer::draw_point(const vec3 &v, const vec3 &color, FrameBuffer *frame_buffer)
{
    int width = frame_buffer->width;
    int height = frame_buffer->height;
    auto screen_v = Rasterizer::viewport_transform(v, width, height);
    auto x = (int)screen_v.x;
    auto y = (int)screen_v.y;

    if (x >= 0 && x < width && y >= 0 && y < height)
    {
        frame_buffer->set_pixel(x, y, color.x, color.y, color.z);
    }
}

void Rasterizer::draw_line(const vec3 &v1, const vec3 &v2, const vec3 &color, FrameBuffer *frame_buffer)
{
}

vec3 Rasterizer::viewport_transform(const vec3 &v, int width, int height)
{
    auto x = (v.x + 1.0f) * 0.5f * width + 0.5f;
    auto y = (1.0f - v.y) * 0.5f * height + 0.5f;
    return vec3(x, y, v.z);
}

void Rasterizer::draw_triangle(const TriangleInfo &info, FrameBuffer *frame_buffer)
{

    int width = frame_buffer->width;
    int height = frame_buffer->height;

    auto v1s = Rasterizer::viewport_transform(info.v1, width, height);
    auto v2s = Rasterizer::viewport_transform(info.v2, width, height);
    auto v3s = Rasterizer::viewport_transform(info.v3, width, height);
    float xMax = std::max(std::max(v1s.x, v2s.x), v3s.x);
    float xMin = std::min(std::min(v1s.x, v2s.x), v3s.x);
    float yMax = std::max(std::max(v1s.y, v2s.y), v3s.y);
    float yMin = std::min(std::min(v1s.y, v2s.y), v3s.y);
    xMax = std::min(xMax, (float)width - 1.0f);
    yMax = std::min(yMax, (float)height - 1.0f);
    xMin = std::max(xMin, 0.0f);
    yMin = std::max(yMin, 0.0f);

    EdgeEquation e1(v2s, v3s);
    EdgeEquation e2(v3s, v1s);
    EdgeEquation e3(v1s, v2s);

    float area = 0.5 * (e1.c + e2.c + e3.c);
    if (area < 0)
        return;
    auto c1 = info.c1;
    auto c2 = info.c2;
    auto c3 = info.c3;
    ParameterEquation r(c1.x, c2.x, c3.x, e1, e2, e3, area);
    ParameterEquation g(c1.y, c2.y, c3.y, e1, e2, e3, area);
    ParameterEquation b(c1.z, c2.z, c3.z, e1, e2, e3, area);

    for (int i = (int)xMin; i <= (int)xMax; i++)
    {
        for (int j = (int)yMin; j <= (int)yMax; j++)
        {
            if (e1.test(i, j) && e2.test(i, j) && e3.test(i, j))
            {

                frame_buffer->set_pixel((int)i, (int)j, r.evaluate(i, j), g.evaluate(i, j), b.evaluate(i, j));
            }
        }
    }
}
