#pragma once
#include <vector>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <iostream>
#include <glm/glm.hpp>
using namespace glm;
using namespace std;
class Texture
{
public:
    enum class Mode
    {
        REPEAT,
        CLAMP,
    };
    static uint8_t *
    genDefaultCheckerboardImage(int *width, int *height)
    {
        const int w = 128;
        const int h = 128;
        uint8_t *imgData = (uint8_t *)malloc(w * h * 4); // stbi_load() uses malloc(), so this is safe

        if (!imgData || w <= 0 || h <= 0)
            return nullptr;
        if (w != h)
            return nullptr;

        for (int i = 0; i < w * h; i++)
        {
            const int row = i / w;
            const int col = i % w;
            imgData[i * 4 + 0] = imgData[i * 4 + 1] = imgData[i * 4 + 2] = 0xFF * ((row + col) % 2);
            imgData[i * 4 + 3] = 0xFF;
        }

        if (width)
            *width = w;
        if (height)
            *height = h;

        return imgData;
    }
    Texture(const string &file)
    {
        int w, h;
        unsigned char *img = stbi_load(file.c_str(), &w, &h, nullptr, STBI_rgb_alpha);
        // print channels
        /*    for (int i = 0; i < w * h; i++)
            {
                const int row = i / w;
                const int col = i % w;
                std::cout << (int)img[i * 3 + 0] << " " << (int)img[i * 3 + 1] << " " << (int)img[i * 3 + 2] << " " << (int)img[i * 3 + 3] << std::endl;
            }*/
        if (!img)
        {
            std::cout << "WARNING: could not load image " << file << " using a fallback.\n"
                      << std::endl;
            img = genDefaultCheckerboardImage(&w, &h);
            if (!img)
            {
                fprintf(stderr, "FATAL ERROR: out of memory allocating image for fallback texture\n");
                exit(EXIT_FAILURE);
            }
        }

        pixels.resize(w * h * 4);
        for (int i = 0; i < w * h; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                pixels[i * 4 + j] = powf(static_cast<float>(img[i * 4 + j]) / 255.0f, 2.2);
            }
        }
        width = w;
        height = h;
        stbi_image_free(img);
    }

    vec4 sample_repeat(vec2 texcoord)
    {
        float u = texcoord.x - floor(texcoord.x);
        float v = texcoord.y - floor(texcoord.y);
        return sample_point(u, v);
    }

    vec4 sample_clamp(vec2 texcoord)
    {
        float u = std::min(1.0f, std::max(texcoord.x, 0.0f));
        float v = std::min(1.0f, std::max(texcoord.y, 0.0f));
        return sample_point(u, v);
    }

    vec4 sample_point(float u, float v)
    {
        int c = static_cast<int>((width - 1) * u);
        int r = static_cast<int>((height - 1) * v);
        int index = (r * width + c) * 4;
        return vec4(pixels[index], pixels[index + 1], pixels[index + 2], pixels[index + 3]);
    }

    vec4 sample(vec2 texcoord, Mode mode = Mode::REPEAT)
    {
        if (mode == Mode::REPEAT)
        {
            return sample_repeat(texcoord);
        }
        else
        {
            return sample_clamp(texcoord);
        }
    }

    std::vector<float> pixels;
    int width;
    int height;
};
