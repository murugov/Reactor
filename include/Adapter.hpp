#ifndef ADAPTER_HPP
#define ADAPTER_HPP

#include <string>
#include <raylib.h>
#include "Canvas.hpp"
#include "Colors.hpp"
#include "Vector.hpp"
#include "Scene.hpp"
#include "Sphere.hpp"

namespace Graphic {

// NOTE: It is not currently in use, but it is expected to find an application.
struct Rectangle {
    Math::Vector2D pos;
    Math::Vector2D size;
};

class Adapter {
public:
    // -------------------------------------------------------------------------------
    // --- Deleted Constructor ---

    Adapter() = delete;

    // -------------------------------------------------------------------------------
    // --- Window-related Functions ---

    static void initWindow (int width, int height, const std::string& title);
    static void closeWindow ();

    // -------------------------------------------------------------------------------
    // --- Window-related Functions ---

    static bool shouldClose ();

    // -------------------------------------------------------------------------------
    // --- Drawing-related Functions ---

    static void beginDrawing ();
    static void endDrawing ();
    static void clearBackground (Color color);
    static void beginScissorMode (int x, int y, int width, int height);
    static void endScissorMode (); 

    // -------------------------------------------------------------------------------
    // --- Input-related Functions: Keyboard ---

    static bool isKeyPressed (int key);
    static bool isKeyPressedRepeat (int key);
    static bool isKeyDown (int key);
    static bool isKeyReleased (int key);
    static bool isKeyUp (int key);

    // -------------------------------------------------------------------------------
    // --- Input-related Functions: Mouse ---

    static bool isMouseButtonPressed(int button);
    static bool isMouseButtonDown(int button);
    static bool isMouseButtonReleased(int button);
    static bool isMouseButtonUp(int button);

    static int getMouseX();
    static int getMouseY();
    static Math::Vector2D getMousePosition(void);

    // -------------------------------------------------------------------------------
    // --- Basic Shapes Drawing Functions ---

    static void drawPixel (const Canvas& canvas, const Math::Vector2D& pos, Color color);
    static void drawLine (const Canvas& canvas, const Math::Vector2D& start_pos, const Math::Vector2D& end_pos, Color color, float thick = 1.0f);
    static void drawCircle (const Canvas& canvas, const Math::Vector2D& center, float radius, Color color);
    static void drawRectangle (const Canvas& canvas, const Math::Vector2D& pos, const Math::Vector2D& size, Color color);
    static void drawTriangle (const Canvas& canvas, const Math::Vector2D& v1, const Math::Vector2D& v2, const Math::Vector2D& v3, Color color);
    static void drawVector (const Canvas& canvas, const Math::Vector2D& pos, const Math::Vector2D& vec, Color color, float thick);
    static void drawSphere (const Scene& scene, const Math::Sphere& sphere, Graphic::Color color); // FIXME: Remove LightManager

    // -------------------------------------------------------------------------------
    // --- Texture Drawing Functions ---

    static void drawTexture (const Texture& texture, Math::Vector2D pos, Color color, float scale = 1.0f, float rotation = 0.0f);

    // -------------------------------------------------------------------------------
    // --- Text Drawing Functions ---

    static void drawFPS (const Canvas& canvas, int pos_x, int pos_y);
    static void drawText (const Canvas& canvas, const std::string& text, int pos_x, int pos_y, int font_size, Color color);
};

}

#endif