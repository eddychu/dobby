#pragma once
#include <vector>
#include <SDL2/SDL.h>
struct FrameBuffer
{
    int width;
    int height;
    FrameBuffer(int width_, int height_) : width(width_), height(height_)
    {
        data.resize(width * height);
    }
    void set_pixel(int x, int y, float r, float g, float b)
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