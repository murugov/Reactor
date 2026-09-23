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
// --- Implementation Of Static Methods ---

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

    Math::Vector2D vec_back { -vec.x() * arrowScale, -(-vec.y() * arrowScale) };
    Math::Vector2D vec_left { -vec.y() * arrowScale * 0.5f, -(vec.x() * arrowScale * 0.5f) };

    Math::Vector2D arrowhead1 = vec_back + vec_left;
    Math::Vector2D arrowhead2 = vec_back - vec_left;

    ::DrawLineEx(end_pos, ::Vector2 { end_pos.x + arrowhead1.x(), end_pos.y + arrowhead1.y() }, thick, color);
    ::DrawLineEx(end_pos, ::Vector2 { end_pos.x + arrowhead2.x(), end_pos.y + arrowhead2.y() }, thick, color);
}

// -------------------------------------------------------------------------------
// --- Texture Drawing Functions ---

void Adapter::drawTexture (const Canvas& canvas, const Texture& texture, Math::Vector2D pos, Color color, float scale, float rotation) {
    ::Vector2 pos_rl { canvas.x() + pos.x() * canvas.scale(), canvas.y() + pos.y() * canvas.scale() };
    
    float final_scale = scale * canvas.scale();

    ::DrawTextureEx(texture.get_raw(), pos_rl, rotation, final_scale, color);
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