#include "Adapter.hpp"
#include "Canvas.hpp"
#include <raylib.h>

namespace Graphic {

// -------------------------------------------------------------------------------
// --- Helper Functions ---

static void normalize3D (float& x, float& y, float& z) {
    float length = std::sqrt(x * x + y * y + z * z);
    if (length > 0.0f) {
        x /= length;
        y /= length;
        z /= length;
    }
}

// -------------------------------------------------------------------------------
// --- Window-related Functions ---

void Adapter::initWindow (int width, int height, const std::string& title) {

    #ifndef NDEBUG
        ::SetTraceLogLevel(LOG_WARNING); 
    #else
        ::SetTraceLogLevel(LOG_NONE); 
    #endif

    ::InitWindow(width, height, title.c_str());
    ::SetTargetFPS(60);
}

void Adapter::closeWindow () {
    ::CloseWindow();
}

// -------------------------------------------------------------------------------
// --- Window-related Functions ---

bool Adapter::shouldClose () {
    return ::WindowShouldClose();
}

// -------------------------------------------------------------------------------
// --- Drawing-related Functions ---

void Adapter::beginDrawing () {
    ::BeginDrawing();
}

void Adapter::endDrawing () {
    ::EndDrawing();
}

void Adapter::clearBackground (Color color) {
    ::ClearBackground(color);
}

void Adapter::beginScissorMode (int x, int y, int width, int height) {
    ::BeginScissorMode(x, y, width, height);
}

void Adapter::endScissorMode () {
    ::EndScissorMode();
}

// -------------------------------------------------------------------------------
// --- Input-related Functions: Keyboard ---

bool Adapter::isKeyPressed (int key) {
    return ::IsKeyPressed(key);
}

bool Adapter::isKeyPressedRepeat (int key) {
    return ::IsKeyPressedRepeat(key);
}

bool Adapter::isKeyDown (int key) {
    return ::IsKeyDown(key);
}

bool Adapter::isKeyReleased (int key) {
    return ::IsKeyReleased(key);
}

bool Adapter::isKeyUp (int key) {
    return ::IsKeyUp(key);
}

// -------------------------------------------------------------------------------
// --- Input-related Functions: Mouse ---

bool Adapter::isMouseButtonPressed(int button) {
    return ::IsMouseButtonPressed(button);
}

bool Adapter::isMouseButtonDown(int button) {
    return ::IsMouseButtonDown(button);
}

bool Adapter::isMouseButtonReleased(int button) {
    return ::IsMouseButtonReleased(button);
}

bool Adapter::isMouseButtonUp(int button) {
    return ::IsMouseButtonUp(button);
}

int Adapter::getMouseX() {
    return ::GetMouseX();
}

int Adapter::getMouseY() {
    return ::GetMouseY();
}

Math::Vector2D Adapter::getMousePosition(void) {
    ::Vector2 mouse_pos = ::GetMousePosition();
    return Math::Vector2D { mouse_pos.x, mouse_pos.y } ;
}

// -------------------------------------------------------------------------------
// --- Basic Shapes Drawing Functions ---

void Adapter::drawPixel (const Canvas& canvas, const Math::Vector2D& pos, Color color) {
    
    ::Vector2 pos_rl { canvas.x() + pos.x() * canvas.scale(), canvas.y() - pos.y() * canvas.scale() };

    ::DrawPixelV(pos_rl, color);
}

void Adapter::drawLine (const Canvas& canvas, const Math::Vector2D& start_pos, const Math::Vector2D& end_pos, Color color, float thick) {

    ::Vector2 start_pos_rl { canvas.x() + start_pos.x() * canvas.scale(), canvas.y() - start_pos.y() * canvas.scale() };
    ::Vector2 end_pos_rl   { canvas.x() + end_pos.x() * canvas.scale(), canvas.y() - end_pos.y() * canvas.scale() };

    ::DrawLineEx(start_pos_rl, end_pos_rl, thick, color);
}

void Adapter::drawCircle (const Canvas& canvas, const Math::Vector2D& center, float radius, Color color) {
    
    ::Vector2 center_rl { canvas.x() + center.x() * canvas.scale(), canvas.y() - center.y() * canvas.scale() };

    ::DrawCircleV(center_rl, radius, color);
}

void Adapter::drawRectangle (const Canvas& canvas, const Math::Vector2D& pos, const Math::Vector2D& size, Color color) {
    
    ::Vector2 pos_rl  { canvas.x() + pos.x() * canvas.scale(), canvas.y() + pos.y() * canvas.scale() };
    ::Vector2 size_rl { size.x() * canvas.scale(), size.y() * canvas.scale() };

    ::DrawRectangleV(pos_rl, size_rl, color);
} 

void Adapter::drawTriangle (const Canvas& canvas, const Math::Vector2D& v1, const Math::Vector2D& v2, const Math::Vector2D& v3, Color color) {
    
    ::Vector2 v1_rl { canvas.x() + v1.x() * canvas.scale(), canvas.y() - v1.y() * canvas.scale() };
    ::Vector2 v2_rl { canvas.x() + v2.x() * canvas.scale(), canvas.y() - v2.y() * canvas.scale() };
    ::Vector2 v3_rl { canvas.x() + v3.x() * canvas.scale(), canvas.y() - v3.y() * canvas.scale() };

    ::DrawTriangle(v1_rl, v2_rl, v3_rl, color);
}

void Adapter::drawVector(const Canvas& canvas, const Math::Vector2D& pos, const Math::Vector2D& vec, Color color, float thick) {
        
    float screen_x = canvas.x() + static_cast<float>(pos.x()) * canvas.scale();
    float screen_y = canvas.y() + static_cast<float>(pos.y()) * canvas.scale();

    ::Vector2 start_pos { screen_x, -screen_y };
    ::Vector2 end_pos   { screen_x + vec.x(), -(screen_y + vec.y()) };

    ::DrawLineEx(start_pos, end_pos, thick, color);
    
    if (std::abs(vec.x()) < 0.001f && std::abs(vec.y()) < 0.001f) {
        return;
    }

    float arrowScale = 0.15f; 

    Math::Vector2D vecBack { -vec.x() * arrowScale, -(-vec.y() * arrowScale) };
    Math::Vector2D vecLeft { -vec.y() * arrowScale * 0.5f, -(vec.x() * arrowScale * 0.5f) };

    Math::Vector2D arrowhead1 = vecBack + vecLeft;
    Math::Vector2D arrowhead2 = vecBack - vecLeft;

    ::DrawLineEx(end_pos, ::Vector2 { end_pos.x + arrowhead1.x(), end_pos.y + arrowhead1.y() }, thick, color);
    ::DrawLineEx(end_pos, ::Vector2 { end_pos.x + arrowhead2.x(), end_pos.y + arrowhead2.y() }, thick, color);
}

void Adapter::drawSphere (const Scene& scene, const Math::Sphere& sphere, Color color) {            // FIXME: Remove lights
    float center_x = sphere.x();
    float center_y = sphere.y();
    float radius   = sphere.radius();

    int x_min = static_cast<int>(std::floor(center_x - radius));
    int x_max = static_cast<int>(std::ceil(center_x + radius));
    int y_min = static_cast<int>(std::floor(center_y - radius));
    int y_max = static_cast<int>(std::ceil(center_y + radius));

    float radius_sq = radius * radius;

    const auto& lights = scene.lights(); 
    size_t num_lights = lights.size();

    for (int screen_y = y_min; screen_y <= y_max; ++screen_y) {
        for (int screen_x = x_min; screen_x <= x_max; ++screen_x) {
            float dx = static_cast<float>(screen_x) - center_x;
            float dy = static_cast<float>(screen_y) - center_y;
            float distSq = dx * dx + dy * dy;

            if (distSq > radius_sq) {
                continue;
            }

            float dz = std::sqrt(radius_sq - distSq);

            float nx = dx / radius;
            float ny = dy / radius;
            float nz = dz / radius;

            float world_x = static_cast<float>(screen_x);
            float world_y = static_cast<float>(screen_y);
            float world_z = dz;
        
            float total_diffuse = 0.1f; 
            float total_specular = 0.0f;

            for (size_t i = 0; i < num_lights; ++i) {
                if (lights[i].enabled) {
                    float lx = (lights[i].pos).x() - world_x;
                    float ly = (lights[i].pos).y() - world_y;
                    float lz = (lights[i].pos).z() - world_z;
                    normalize3D(lx, ly, lz);

                    // Lambert
                    float dotNL = std::max(0.0f, nx * lx + ny * ly + nz * lz);
                    total_diffuse += 0.5f * dotNL; 

                    // Phong
                    float hx = lx;
                    float hy = ly;
                    float hz = lz + 1.0f; // L + V
                    normalize3D(hx, hy, hz);

                    float dotNH = std::max(0.0f, nx * hx + ny * hy + nz * hz);
                    total_specular += std::pow(dotNH, 32.0f); 
                }
            }

            float final_r = (static_cast<float>(color.r) * total_diffuse) + (255.0f * total_specular);
            float final_g = (static_cast<float>(color.g) * total_diffuse) + (255.0f * total_specular);
            float final_b = (static_cast<float>(color.b) * total_diffuse) + (255.0f * total_specular);

            unsigned char r = static_cast<unsigned char>(std::min(255.0f, final_r));
            unsigned char g = static_cast<unsigned char>(std::min(255.0f, final_g));
            unsigned char b = static_cast<unsigned char>(std::min(255.0f, final_b));
            Color pixel_color = { r, g, b, color.a };

            Adapter::drawPixel(scene.background(), Math::Vector2D{static_cast<float>(screen_x), static_cast<float>(screen_y) }, pixel_color);   // FIXME: scene.background() is not the same as scene.canvas()
        }
    }
}

// -------------------------------------------------------------------------------
// --- Texture Drawing Functions ---

void Adapter::drawTexture (const Texture& texture, Math::Vector2D pos, Color color, float scale, float rotation) {
    ::DrawTextureEx(texture.get_raw(), ::Vector2 { pos.x(), pos.y() }, rotation, scale, color);
}

// -------------------------------------------------------------------------------
// --- Text Drawing Functions ---

void Adapter::drawFPS (const Canvas& canvas, int pos_x, int pos_y) {
    
    float screen_x = canvas.x() + static_cast<float>(pos_x) * canvas.scale();
    float screen_y = canvas.y() + static_cast<float>(pos_y) * canvas.scale();

    ::DrawFPS(static_cast<int>(screen_x), static_cast<int>(screen_y));
}


void Adapter::drawText (const Canvas& canvas, const std::string& text, int pos_x, int pos_y, int font_size, Color color) {
    
    float screen_x = canvas.x() + static_cast<float>(pos_x) * canvas.scale();
    float screen_y = canvas.y() + static_cast<float>(pos_y) * canvas.scale();

    ::DrawText(text.c_str(), static_cast<int>(screen_x), static_cast<int>(screen_y), font_size, color);
}

};