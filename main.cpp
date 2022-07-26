#include "core/framebuffer.h"
#include <SDL2/SDL.h>
#include "core/model.h"
#include "core/rasterizer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
int main()
{
    int width = 800;
    int height = 600;
    // Model model("data/models/Box/glTF-Embedded/Box.gltf");
    Model model("data/models/DamagedHelmet/glTF-Embedded/DamagedHelmet.gltf");
    Texture texture("DamagedHelmet/glTF/Default_albedo.jpg");

    auto projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
    auto view = glm::lookAt(vec3(0, 0, 5), vec3(0, 0, 0), vec3(0, 1, 0));

    auto mvp = projection * view;

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
            for (int i = 0; i < indices.size() - 2; i += 3)
            {
                const auto &p1 = vertices[indices[i]].position;
                const auto &p2 = vertices[indices[i + 1]].position;
                const auto &p3 = vertices[indices[i + 2]].position;

                auto clip_p1 = mvp * vec4(p1, 1.0);
                auto clip_p2 = mvp * vec4(p2, 1.0);
                auto clip_p3 = mvp * vec4(p3, 1.0);
                clip_p1 /= clip_p1.w;
                clip_p2 /= clip_p2.w;
                clip_p3 /= clip_p3.w;

                const auto &t1 = vertices[indices[i]].tex_coords;
                const auto &t2 = vertices[indices[i + 1]].tex_coords;
                const auto &t3 = vertices[indices[i + 2]].tex_coords;

                auto c1 = texture.sample(t1);
                auto c2 = texture.sample(t2);
                auto c3 = texture.sample(t3);

                TriangleInfo info{clip_p1, clip_p2, clip_p3, c1, c2, c3};

                Rasterizer::rasterize(info, &frame_buffer, Rasterizer::Mode::TRIANGLE);
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
