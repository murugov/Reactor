#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <string>
#include <functional>
#include "Adapter.hpp"
#include "Vector.hpp"
#include "Canvas.hpp"

namespace Graphic {

class Button {
private:
    Math::Vector2D pos_;
    Math::Vector2D size_;
    std::string text_;
    Color base_color_;
    Color hover_color_;
    
    std::function<void()> onClick_; 

public:
    Button(Math::Vector2D pos, Math::Vector2D size, const std::string& text, 
           Color base_color, Color hover_color, std::function<void()> onClick)
        : pos_(pos), size_(size), text_(text), 
          base_color_(base_color), hover_color_(hover_color), onClick_(onClick) {}

    ~Button() = default;

    void updateAndDraw(const Canvas& canvas);
};

}

#endif