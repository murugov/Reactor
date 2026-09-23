#include "Button.hpp"
#include "Adapter.hpp"
#include "Canvas.hpp"

namespace Graphic {

void Button::updateAndDraw(const Canvas& canvas) {
    float scale = canvas.scale();

    float screen_x = canvas.x() + pos_.x() * scale;
    float screen_y = canvas.y() + pos_.y() * scale;
    float screen_w = size_.x() * scale;
    float screen_h = size_.y() * scale;

    Math::Vector2D mouse_pos = Adapter::getMousePosition();

    // AABB Collision
    bool is_hovered = (mouse_pos.x() >= screen_x && mouse_pos.x() <= screen_x + screen_w &&
                       mouse_pos.y() >= screen_y && mouse_pos.y() <= screen_y + screen_h);

    Color current_color = is_hovered ? hover_color_ : base_color_;
    Adapter::drawRectangle(canvas, pos_, size_, current_color);

    int text_x = static_cast<int>(pos_.x() + 10.0f);
    int text_y = static_cast<int>(pos_.y() + size_.y() / 2.0f - 10.0f);
    Adapter::drawText(canvas, text_, text_x, text_y, 20, Colors::Black);

    if (is_hovered && Adapter::isMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (onClick_) {
            onClick_();
        }
    }
}

}
