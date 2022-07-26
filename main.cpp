#include "core/framebuffer.h"
#include <SDL2/SDL.h>
#include "core/model.h"
int main()
{
    // Model model("data/models/Box/glTF-Embedded/Box.gltf");
    Model model("data/models/DamagedHelmet/glTF-Embedded/DamagedHelmet.gltf");
    int width = 800;
    int height = 600;
    SDL_Init(SDL_INIT_VIDEO);
    auto window = SDL_CreateWindow("Hello World",
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   width,
                                   height,
                                   SDL_WINDOW_OPENGL);
    auto surface = SDL_GetWindowSurface(window);

    FrameBuffer frame_buffer(width, height);

    bool running = true;
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
        frame_buffer.clear();
        for (const auto &mesh : model.meshes)
        {
            const auto &indices = mesh.indices;
            const auto &vertices = mesh.vertices;
            for (int i = 0; i < indices.size(); i++)
            {
                const auto &position = vertices[indices[i]].position;
                auto x = (int)((position.x + 1.0f) * 0.5f * width);
                auto y = (int)((position.y + 1.0f) * 0.5f * height);
                if (x >= 0 && x < width && y >= 0 && y < height)
                {
                    frame_buffer.set_pixel(x, y, 1.0, 0.0, 0.0);
                }
            }
        }
        SDL_LockSurface(surface);
        memcpy(surface->pixels, frame_buffer.data.data(), frame_buffer.width * frame_buffer.height * sizeof(Uint32));
        SDL_UnlockSurface(surface);
        SDL_UpdateWindowSurface(window);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
}
