#include "Graphic/Adapter.hpp"
#include "Math/Transform.hpp"

namespace Graphic {

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

void Adapter::beginScissorMode (const Math::Transform2D& transform) {
    ::BeginScissorMode(static_cast<int>(transform.pos.x()),  -static_cast<int>(transform.pos.y()),
                       static_cast<int>(transform.size.x()), -static_cast<int>(transform.size.y()));
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

void Adapter::drawPixel (const Math::Vector2D& pos, Color color) {
    ::DrawPixelV({ pos.x(), -pos.y() }, color);
}

void Adapter::drawLine (const Math::Vector2D& start_pos, const Math::Vector2D& end_pos, Color color, float thick) {
    ::DrawLineEx({ start_pos.x(), -start_pos.y() }, { end_pos.x(), -end_pos.y() }, thick, color);
}

void Adapter::drawCircle (const Math::Circle& circle, Color color) {
    ::DrawCircleV({ circle.pos.x(), -circle.pos.y() }, circle.radius, color);
}

void Adapter::drawRectangle (const Math::Rectangle& rect, Color color) {
    ::DrawRectangleV({ rect.pos.x(), -rect.pos.y() }, { rect.size.x(), -rect.size.y() }, color);
} 

void Adapter::drawTriangle (const Math::Triangle& triangle, Color color) {
    ::DrawTriangle({ triangle.v1.x(), -triangle.v1.y() },
                   { triangle.v2.x(), -triangle.v2.y() },
                   { triangle.v3.x(), -triangle.v3.y() }, color);
}

void Adapter::drawVector(const Math::Transform2D& transform, Color color, float thick) {
    Math::Vector2D pos = transform.pos;
    Math::Vector2D vec = transform.size;
    
    ::Vector2 start_pos { pos.x(), -pos.y() };
    ::Vector2 end_pos   { pos.x() + vec.x(), -(pos.y() + vec.y()) };

    ::DrawLineEx(start_pos, end_pos, thick, color);
    
    if (std::abs(vec.x()) < 0.001f && std::abs(vec.y()) < 0.001f) {
        return;
    }

    float arrow_scale = 0.15f; 

    Math::Vector2D vec_back { -vec.x() * arrow_scale, -(-vec.y() * arrow_scale) };
    Math::Vector2D vec_left { -vec.y() * arrow_scale * 0.5f, -(vec.x() * arrow_scale * 0.5f) };

    Math::Vector2D arrowhead_1 = vec_back + vec_left;
    Math::Vector2D arrowhead_2 = vec_back - vec_left;

    ::DrawLineEx(end_pos, ::Vector2 { end_pos.x + arrowhead_1.x(), end_pos.y + arrowhead_1.y() }, thick, color);
    ::DrawLineEx(end_pos, ::Vector2 { end_pos.x + arrowhead_2.x(), end_pos.y + arrowhead_2.y() }, thick, color);
}

// -------------------------------------------------------------------------------
// --- Texture Drawing Functions ---

void Adapter::drawTexture (const Texture& texture, const Math::Transform2D& transform, Color color) {
    if (texture.is_loaded()) {
        ::DrawTextureEx(texture.get_raw(), { transform.pos.x(), -transform.pos.y() },
                    transform.rotation, transform.scale, Colors::White);
    }
    else {
        Adapter::drawRectangle({ transform.pos, transform.size }, color);
    }
}

// -------------------------------------------------------------------------------
// --- Text Drawing Functions ---

void Adapter::drawFPS (int pos_x, int pos_y) {
    ::DrawFPS(pos_x, pos_y);
}

void Adapter::drawText (const std::string& text, int pos_x, int pos_y, int font_size, Color color) {
    ::DrawText(text.c_str(), pos_x, pos_y, font_size, color);
}

} // namespace Graphic