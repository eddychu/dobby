#include <SDL2/SDL.h>
#include <memory>
#include <vector>
#include <iostream>
#define EPSILON 0.000001f
#define M4D(aRow, bCol)                           \
    a.v[0 * 4 + (aRow)] * b.v[(bCol)*4 + 0] +     \
        a.v[1 * 4 + (aRow)] * b.v[(bCol)*4 + 1] + \
        a.v[2 * 4 + (aRow)] * b.v[(bCol)*4 + 2] + \
        a.v[3 * 4 + (aRow)] * b.v[(bCol)*4 + 3]

#define M4V4D(mRow, x, y, z, w) \
    x *m.v[0 * 4 + mRow] +      \
        y *m.v[1 * 4 + mRow] +  \
        z *m.v[2 * 4 + mRow] +  \
        w *m.v[3 * 4 + mRow]

struct Vec3
{
    union
    {
        struct
        {
            float x, y, z;
        };
        float v[3];
    };

    inline Vec3() : x(0), y(0), z(0) {}
    inline Vec3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    inline Vec3(float *fv) : x(fv[0]), y(fv[1]), z(fv[2]) {}

    friend Vec3 operator+(const Vec3 &l, const Vec3 &r)
    {
        return Vec3(l.x + r.x, l.y + r.y, l.z + r.z);
    }
    friend Vec3 operator-(const Vec3 &l, const Vec3 &r)
    {
        return Vec3(l.x - r.x, l.y - r.y, l.z - r.z);
    }

    friend Vec3 operator*(const Vec3 &l, const Vec3 &r)
    {
        return Vec3(l.x * r.x, l.y * r.y, l.z * r.z);
    }

    friend Vec3 operator*(const Vec3 &l, float f)
    {
        return Vec3(l.x * f, l.y * f, l.z * f);
    }

    friend float dot(const Vec3 &l, const Vec3 &r)
    {
        return l.x * r.x + l.y * r.y + l.z * r.z;
    }

    friend Vec3 cross(const Vec3 &l, const Vec3 &r)
    {
        return Vec3(l.y * r.z - l.z * r.y, l.z * r.x - l.x * r.z, l.x * r.y - l.y * r.x);
    }

    friend float lenSq(const Vec3 &v)
    {
        return dot(v, v);
    }

    friend float len(const Vec3 &v)
    {
        float lenSq = v.x * v.x + v.y * v.y + v.z * v.z;
        if (lenSq < EPSILON)
        {
            return 0.0f;
        }
        return sqrtf(lenSq);
    }

    friend Vec3 normalize(const Vec3 &v)
    {
        float l = len(v);
        if (l < EPSILON)
        {
            throw std::runtime_error("normalize: zero length vector");
        }
        return v * (1.0f / l);
    }

    friend float angle(const Vec3 &l, const Vec3 &r)
    {
        float l_len = lenSq(l);
        float r_len = lenSq(r);
        if (l_len < EPSILON || r_len < EPSILON)
        {
            throw std::runtime_error("angle: zero length vector");
        }
        float dot_ = dot(l, r);
        float len_ = sqrtf(l_len * r_len);
        return acosf(dot_ / len_);
    }
};

struct Vec4
{
    union
    {
        struct
        {
            float x, y, z, w;
        };
        float v[4];
    };
    inline Vec4() : x(0), y(0), z(0), w(0) {}
    inline Vec4(float x_, float y_, float z_, float w_) : x(x_), y(y_), z(z_), w(w_) {}
    inline Vec4(float *fv) : x(fv[0]), y(fv[1]), z(fv[2]), w(fv[3]) {}

    friend Vec4 operator+(const Vec4 &l, const Vec4 &r)
    {
        return Vec4(l.x + r.x, l.y + r.y, l.z + r.z, l.w + r.w);
    }

    friend Vec4 operator*(const Vec4 &l, float f)
    {
        return Vec4(l.x * f, l.y * f, l.z * f, l.w * f);
    }
};

struct Mat4
{
    union
    {
        float v[16];
        struct
        {
            Vec4 right;
            Vec4 up;
            Vec4 forward;
            Vec4 pos;
        };
        struct
        {
            float xx;
            float xy;
            float xz;
            float xw;
            float yx;
            float yy;
            float yz;
            float yw;
            float zx;
            float zy;
            float zz;
            float zw;
            float tx;
            float ty;
            float tz;
            float tw;
        };

        struct
        {
            float c0r0;
            float c0r1;
            float c0r2;
            float c0r3;
            float c1r0;
            float c1r1;
            float c1r2;
            float c1r3;
            float c2r0;
            float c2r1;
            float c2r2;
            float c2r3;
            float c3r0;
            float c3r1;
            float c3r2;
            float c3r3;
        };

        struct
        {
            float r0c0;
            float r1c0;
            float r2c0;
            float r3c0;
            float r0c1;
            float r1c1;
            float r2c1;
            float r3c1;
            float r0c2;
            float r1c2;
            float r2c2;
            float r3c2;
            float r0c3;
            float r1c3;
            float r2c3;
            float r3c3;
        };
    };

    inline Mat4() : xx(1), xy(0), xz(0), xw(0),
                    yx(0), yy(1), yz(0), yw(0),
                    zx(0), zy(0), zz(1), zw(0),
                    tx(0), ty(0), tz(0), tw(1) {}
    inline Mat4(float *fv) : xx(fv[0]), xy(fv[1]), xz(fv[2]), xw(fv[3]),
                             yx(fv[4]), yy(fv[5]), yz(fv[6]), yw(fv[7]),
                             zx(fv[8]), zy(fv[9]), zz(fv[10]), zw(fv[11]),
                             tx(fv[12]), ty(fv[13]), tz(fv[14]), tw(fv[15]) {}
    inline Mat4(
        float xx_, float xy_, float xz_, float xw_,
        float yx_, float yy_, float yz_, float yw_,
        float zx_, float zy_, float zz_, float zw_,
        float tx_, float ty_, float tz_, float tw_) : xx(xx_), xy(xy_), xz(xz_), xw(xw_),
                                                      yx(yx_), yy(yy_), yz(yz_), yw(yw_),
                                                      zx(zx_), zy(zy_), zz(zz_), zw(zw_),
                                                      tx(tx_), ty(ty_), tz(tz_), tw(tw_) {}

    friend Mat4 operator+(const Mat4 &l, const Mat4 &r)
    {
        return Mat4(
            l.xx + r.xx, l.xy + r.xy, l.xz + r.xz, l.xw + r.xw,
            l.yx + r.yx, l.yy + r.yy, l.yz + r.yz, l.yw + r.yw,
            l.zx + r.zx, l.zy + r.zy, l.zz + r.zz, l.zw + r.zw,
            l.tx + r.tx, l.ty + r.ty, l.tz + r.tz, l.tw + r.tw);
    }

    friend Mat4 operator*(const Mat4 &m, float f)
    {
        return Mat4(
            m.xx * f, m.xy * f, m.xz * f, m.xw * f,
            m.yx * f, m.yy * f, m.yz * f, m.yw * f,
            m.zx * f, m.zy * f, m.zz * f, m.zw * f,
            m.tx * f, m.ty * f, m.tz * f, m.tw * f);
    }

    friend Mat4 operator*(const Mat4 &a, const Mat4 &b)
    {
        return Mat4(
            M4D(0, 0), M4D(1, 0), M4D(2, 0), M4D(3, 0),
            M4D(0, 1), M4D(1, 1), M4D(2, 1), M4D(3, 1),
            M4D(0, 2), M4D(1, 2), M4D(2, 2), M4D(3, 2),
            M4D(0, 3), M4D(1, 3), M4D(2, 3), M4D(3, 3));
    }

    friend Mat4 transpose(const Mat4 &m)
    {
        return Mat4(
            m.xx, m.yx, m.zx, m.tx,
            m.xy, m.yy, m.zy, m.ty,
            m.xz, m.yz, m.zz, m.tz,
            m.xw, m.yw, m.zw, m.tw);
    }

    friend Vec4 operator*(const Mat4 &m, const Vec4 &v)
    {
        return Vec4(
            M4V4D(0, v.x, v.y, v.z, v.w),
            M4V4D(1, v.x, v.y, v.z, v.w),
            M4V4D(2, v.x, v.y, v.z, v.w),
            M4V4D(3, v.x, v.y, v.z, v.w));
    }

    static Mat4 lookAt(const Vec3 &position, const Vec3 &target, const Vec3 &up)
    {
        Vec3 f = normalize(target - position) * -1.0f;
        Vec3 r = normalize(cross(up, f));
        Vec3 u = normalize(cross(f, r));
        Vec3 t = Vec3(
            -dot(r, position),
            -dot(u, position),
            -dot(f, position));
        return Mat4(
            r.x, u.x, f.x, 0,
            r.y, u.y, f.y, 0,
            r.z, u.z, f.z, 0,
            t.x, t.y, t.z, 1);
    }

    static Mat4 frustum(float l, float r, float b, float t, float n, float f)
    {
        if (l == r || t == b || n == f)
        {
            throw std::runtime_error("Invalid frustum parameters");
        }
        return Mat4(
            (2.0f * n) / (r - l), 0, 0, 0,
            0, (2.0f * n) / (t - b), 0, 0,
            (r + l) / (r - l), (t + b) / (t - b), (-(f + n)) / (f - n), -1,
            0, 0, (-2 * f * n) / (f - n), 0);
    }

    static Mat4 perspective(float fov, float aspect, float znear, float zfar)
    {
        float ymax = znear * tanf(fov * 3.14159265359f / 360.0f);
        float xmax = ymax * aspect;

        return frustum(-xmax, xmax, -ymax, ymax, znear, zfar);
    }

    friend std::ostream &operator<<(std::ostream &os, const Mat4 &m)
    {
        os << "Mat4(" << m.xx << ", " << m.xy << ", " << m.xz << ", " << m.xw << ", "
           << m.yx << ", " << m.yy << ", " << m.yz << ", " << m.yw << ", "
           << m.zx << ", " << m.zy << ", " << m.zz << ", " << m.zw << ", "
           << m.tx << ", " << m.ty << ", " << m.tz << ", " << m.tw << ")";
        return os;
    }
};

struct Mesh
{
    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> uvs;
    std::vector<unsigned int> indices;
};

struct Scene
{
    std::vector<std::shared_ptr<Model>> models;
};

struct Camera
{
    Vec3 position;
    Vec3 target;
    Vec3 up;
    float fov;
    float aspect;
    float znear;
    float zfar;

    Camera(Vec3 position_, Vec3 target_, Vec3 up_,
           float fov_,
           float aspect_,
           float znear_,
           float zfar_) : position(position_),
                          target(target_),
                          up(up_),
                          fov(fov_),
                          aspect(aspect_),
                          znear(znear_),
                          zfar(zfar_)
    {
    }

    Mat4 getViewMatrix()
    {
        return Mat4::lookAt(position, target, up);
    }

    Mat4 getProjectionMatrix()
    {
        return Mat4::perspective(fov, aspect, znear, zfar);
    }
};

struct Framebuffer
{
    int width;
    int height;
    Framebuffer(int width_, int height_) : width(width_), height(height_)
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

struct Shader
{
    Mat4 uniform_model;
    Mat4 uniform_view;
    Mat4 uniform_projection;
    Vec4 vertex(const Vec3 &v)
    {
        return uniform_projection * uniform_view * uniform_model * Vec4(v.x, v.y, v.z, 1);
    }

    Vec4 fragment() const
    {
        return Vec4(1, 0, 0, 0);
    }
};

struct Material
{
    Material(std::shared_ptr<Shader> shader_) : diffuse(Vec4(1, 1, 1, 1)), specular(Vec4(1, 1, 1, 1)), shininess(0), shader(shader_)
    {
    }
    Vec4 diffuse;
    Vec4 specular;
    float shininess;
    std::shared_ptr<Shader> shader;
};

struct Model
{
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Material> material;
};

struct Renderer
{

    Renderer(const int width_, const int height_) : width(width_), height(height_),
                                                    frameBuffer(width_, height_)
    {
        SDL_Init(SDL_INIT_VIDEO);
        window = SDL_CreateWindow("Hello World",
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  width,
                                  height,
                                  SDL_WINDOW_OPENGL);
        surface = SDL_GetWindowSurface(window);
    }

    void render(std::unique_ptr<Scene> scene, std::unique_ptr<Camera> camera)
    {
        running = true;
        auto mesh = scene->models[0]->mesh;
        auto material = scene->models[0]->material;
        Mat4 model;
        Mat4 view = camera->getViewMatrix();
        Mat4 projection = camera->getProjectionMatrix();
        material->shader->uniform_model = model;
        material->shader->uniform_view = view;
        material->shader->uniform_projection = projection;

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
            frameBuffer.clear();

            auto vertices = mesh->vertices;
            auto normals = mesh->normals;
            auto uvs = mesh->uvs;
            auto indices = mesh->indices;

            for (int i = 0; i < indices.size(); i++)
            {
                auto index = indices[i];
                auto vertex = vertices[index * 3];
                auto normal = normals[index * 3];
                auto uv = uvs[index * 2];
                auto m = projection * view * model;
                Vec3 v;
                v.x = vertex;
                v.y = vertices[index * 3 + 1];
                v.z = vertices[index * 3 + 2];
                auto coords = material->shader->vertex(v);

                // perspetive divide
                coords = coords * (1.0f / coords.w);

                // viewport transform
                v.x = (v.x + 1.0f) * width / 2.0f + 0.5f;
                v.y = (1.0f - v.y) * height / 2.0f + 0.5f;

                // face culling

                // rasterize
                float xMax =

                    frameBuffer.setPixel(v.x, v.y, 1.0f, 0.0f, 0.0f);
            }

            SDL_LockSurface(surface);
            memcpy(surface->pixels, frameBuffer.data.data(), frameBuffer.width * frameBuffer.height * sizeof(Uint32));
            SDL_UnlockSurface(surface);
            SDL_UpdateWindowSurface(window);
        }

        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    // void clipping(const Vec4 &clipCoords)
    // {
    //     if (clipCoords.w < 0)
    //     {
    //         return;
    //     }
    //     auto x = clipCoords.x / clipCoords.w;
    //     auto y = clipCoords.y / clipCoords.w;
    //     auto z = clipCoords.z / clipCoords.w;
    //     if (x < -1 || x > 1 || y < -1 || y > 1 || z < 0 || z > 1)
    //     {
    //         return;
    //     }
    // }

    SDL_Window *window;
    SDL_Surface *surface;
    Framebuffer frameBuffer;
    bool running = false;
    int width;
    int height;
    std::vector<Vec4> clipCoords;
};

int main()
{

    int width = 800;
    int height = 600;
    Renderer renderer(width, height);

    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
    mesh->vertices = {-0.99f, 0.99f, 0.0f,
                      -0.99f, -0.99f, 0.0f,
                      0.99f, -0.99f, 0.0f};
    mesh->normals = {0.0f, 0.0f, 1.0f,
                     0.0f, 0.0f, 1.0f,
                     0.0f, 0.0f, 1.0f};
    mesh->uvs = {0.0f, 0.0f,
                 1.0f, 0.0f,
                 0.0f, 1.0f};
    mesh->indices = {0, 1, 2};

    std::shared_ptr<Material> material = std::make_shared<Material>(std::make_shared<Shader>());
    material->diffuse = Vec4(1, 0, 0, 1);
    material->specular = Vec4(1, 1, 1, 1);
    material->shininess = 0.0f;

    std::unique_ptr<Model> model = std::make_unique<Model>();
    model->mesh = mesh;
    model->material = material;

    std::unique_ptr<Scene> scene = std::make_unique<Scene>();
    scene->models.push_back(std::move(model));

    std::unique_ptr<Camera> camera = std::make_unique<Camera>(
        Vec3(0.0f, 0.0f, 1.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f), 90.0f, (float)width / (float)height, 0.1f, 100.0f);

    renderer.render(std::move(scene), std::move(camera));
}
