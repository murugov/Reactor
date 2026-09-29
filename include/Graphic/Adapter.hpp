#ifndef ADAPTER_HPP
#define ADAPTER_HPP

#include <string>
#include <raylib.h>
#include "Graphic/Colors.hpp"
#include "Graphic/Texture.hpp"
#include "Math/Geometry.hpp"
#include "Math/Transform.hpp"
#include "Math/Vector.hpp"

namespace Graphic {

class Adapter {
public:
    // -------------------------------------------------------------------------------
    // --- Deleted Constructor ---

    Adapter() = delete;

    // -------------------------------------------------------------------------------
    // --- Static Methods Prototypes ---

    // -------------------------------------------------------------------------------
    // --- Window-related Functions ---

    static void initWindow  (int width, int height, const std::string& title);
    static void closeWindow ();

    // -------------------------------------------------------------------------------
    // --- Window-related Functions ---

    static bool shouldClose ();

    // -------------------------------------------------------------------------------
    // --- Drawing-related Functions ---

    static void beginDrawing     ();
    static void endDrawing       ();
    static void clearBackground  (Color color);
    static void beginScissorMode (const Math::Transform2D& transform);
    static void endScissorMode   (); 

    // -------------------------------------------------------------------------------
    // --- Input-related Functions: Keyboard ---

    static bool isKeyPressed       (int key);
    static bool isKeyPressedRepeat (int key);
    static bool isKeyDown          (int key);
    static bool isKeyReleased      (int key);
    static bool isKeyUp            (int key);

    // -------------------------------------------------------------------------------
    // --- Input-related Functions: Mouse ---

    static bool isMouseButtonPressed  (int button);
    static bool isMouseButtonDown     (int button);
    static bool isMouseButtonReleased (int button);
    static bool isMouseButtonUp       (int button);

    static int getMouseX ();
    static int getMouseY ();
    static Math::Vector2D getMousePosition (void);

    // -------------------------------------------------------------------------------
    // --- Basic Shapes Drawing Functions ---

    static void drawPixel     (const Math::Vector2D& pos, Color color);
    static void drawLine      (const Math::Vector2D& start_pos, const Math::Vector2D& end_pos, Color color, float thick = 1.0f);
    static void drawCircle    (const Math::Circle& circle, Color color);
    static void drawRectangle (const Math::Rectangle& rect, Color color);
    static void drawTriangle  (const Math::Triangle& triangle, Color color);
    static void drawVector    (const Math::Transform2D& transform, Color color, float thick = 1.0f);

    // -------------------------------------------------------------------------------
    // --- Texture Drawing Functions ---

    static void drawTexture (const Texture& texture, const Math::Transform2D& transform, Color color);

    // -------------------------------------------------------------------------------
    // --- Text Drawing Functions ---

    static void drawFPS  (int pos_x, int pos_y);
    static void drawText (const std::string& text, int pos_x, int pos_y, int font_size, Color color);
};

} // namespace Graphic

#endif