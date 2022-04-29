#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <vector>
#include <iostream>
#include <SDL2/SDL.h>
// glm string cast
#include <glm/gtx/string_cast.hpp>

using namespace glm;

struct FrameBuffer
{
    int width;
    int height;
    FrameBuffer(int width_, int height_) : width(width_), height(height_)
    {
        data.resize(width * height);
    }
    void setPixel(int x, int y, float r, float g, float b)
    {
        int index = y * width + x;
        data[index] = SDL_MapRGB(format, r * 255, g * 255, b * 255);
    }
    void clear()
    {
        memset(data.data(), 0xD, width * sizeof(Uint32) * height);
    }
    std::vector<Uint32> data;
    SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_ARGB8888);
};

vec3 Barycentric(const vec3 &p, const vec3 &a, const vec3 &b, const vec3 &c)
{
    auto v0 = b - a, v1 = c - a, v2 = p - a;
    float d00 = dot(v0, v0);
    float d01 = dot(v0, v1);
    float d11 = dot(v1, v1);
    float d20 = dot(v2, v0);
    float d21 = dot(v2, v1);
    float denom = d00 * d11 - d01 * d01;
    float v = (d11 * d20 - d01 * d21) / denom;
    float w = (d00 * d21 - d01 * d20) / denom;
    float u = 1.0f - v - w;
    return vec3(u, v, w);
}

struct RenderState
{
    mat4 model;
    mat4 view;
    mat4 projection;
    mat4 mvp;
};

struct Renderer
{
    int width;
    int height;
    FrameBuffer frameBuffer;
    std::vector<float> zBuffer;
    RenderState renderState;

    std::vector<vec3> vertices = {
        vec3(-1, -1, 0),
        vec3(1, -1, 0),
        vec3(0, 1, 0)};

    std::vector<vec4> clipCoordsBuf;

    SDL_Window *window;
    SDL_Surface *surface;

    bool running = false;

    Renderer(int w, int h) : width(w), height(h), renderState(), frameBuffer(w, h), zBuffer(w * h, std::numeric_limits<float>::max())
    {

        renderState.projection = glm::perspective(glm::radians(45.0f), (float)w / (float)h, 0.1f, 100.0f);
        renderState.view = glm::lookAt(vec3(0, 0, 5), vec3(0, 0, 0), vec3(0, 1, 0));
        renderState.model = mat4(1.0f);
        renderState.mvp = renderState.projection * renderState.view * renderState.model;

        SDL_Init(SDL_INIT_VIDEO);
        window = SDL_CreateWindow("Hello World",
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  width,
                                  height,
                                  SDL_WINDOW_OPENGL);
        surface = SDL_GetWindowSurface(window);
    }

    void run()
    {

        running = true;
        while (running)
        {
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    running = false;
                }
            }
            render();
        }
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void render()
    {

        frameBuffer.clear();
        zBuffer.assign(width * height, std::numeric_limits<float>::max());
        // clipCoordsBuf.resize(vertices.size());
        clipCoordsBuf.clear();
        vertexProcessing(vertices);
        clipping();
        perspectiveDivision();
        viewportTransform();
        rasterization();
        fragmentProcessing();
        updateFrame();
    }

    void vertexProcessing(const std::vector<vec3> &vertices)
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            auto clipCoords = renderState.mvp * vec4(vertices[i], 1.0f);
            clipCoordsBuf.push_back(clipCoords);
        }
    }

    void clipping()
    {
        // ignore
    }

    void perspectiveDivision()
    {
        for (int i = 0; i < clipCoordsBuf.size(); i++)
        {
            clipCoordsBuf[i] /= clipCoordsBuf[i].w;
        }
    }

    void viewportTransform()
    {
        for (int i = 0; i < clipCoordsBuf.size(); i++)
        {
            clipCoordsBuf[i].x = (clipCoordsBuf[i].x + 1.0f) * 0.5f * width + 0.5f;
            clipCoordsBuf[i].y = (1.0f - clipCoordsBuf[i].y) * 0.5f * height + 0.5f;
            std::cout << to_string(clipCoordsBuf[i]) << std::endl;
        }
    }

    void rasterization()
    {
        // get bounding box
        float xMax = std::max(std::max(clipCoordsBuf[0].x, clipCoordsBuf[1].x), clipCoordsBuf[2].x);
        float xMin = std::min(std::min(clipCoordsBuf[0].x, clipCoordsBuf[1].x), clipCoordsBuf[2].x);
        float yMax = std::max(std::max(clipCoordsBuf[0].y, clipCoordsBuf[1].y), clipCoordsBuf[2].y);
        float yMin = std::min(std::min(clipCoordsBuf[0].y, clipCoordsBuf[1].y), clipCoordsBuf[2].y);
        xMax = std::max(xMax, (float)width - 1.0f);
        yMax = std::max(yMax, (float)height - 1.0f);
        xMin = std::max(xMin, 0.0f);
        yMin = std::max(yMin, 0.0f);
        // for (int v = 0; v < clipCoordsBuf.size() - 2; v += 3)
        // {

        // }
        int v = 0;
        vec3 v1 = clipCoordsBuf[v];
        vec3 v2 = clipCoordsBuf[v + 1];
        vec3 v3 = clipCoordsBuf[v + 2];
        for (int i = (int)xMin; i < (int)xMax; i++)
        {
            for (int j = (int)yMin; j < (int)yMax; j++)
            {
                vec3 barycentric = Barycentric(vec3(i + 0.5f, j + 0.5f, 0), v1, v2, v3);
                if (barycentric.x >= 0.0f && barycentric.y >= 0.0f && barycentric.z >= 0.0f)
                {
                    float z = barycentric.x * v1.z + barycentric.y * v2.z + barycentric.z * v3.z;
                    if (z < zBuffer[i + j * width])
                    {
                        zBuffer[i + j * width] = z;
                        frameBuffer.setPixel(i, j, 1.0f, 0.0f, 0.0f);
                    }
                }
            }
        }
    }

    void fragmentProcessing()
    {
        // ignore
    }

    void updateFrame()
    {
        SDL_LockSurface(surface);
        memcpy(surface->pixels, frameBuffer.data.data(), frameBuffer.width * frameBuffer.height * sizeof(Uint32));
        SDL_UnlockSurface(surface);
        SDL_UpdateWindowSurface(window);
    }
};