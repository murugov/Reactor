#ifndef PLOT_HPP
#define PLOT_HPP

#include <vector>
#include "Graphic/Canvas.hpp"
#include "Graphic/Camera.hpp"
#include "Graphic/Colors.hpp"

namespace Gameplay {

class Plot {
private:
    Graphic::Canvas& canvas_;
    std::vector<float> data_history_{};
    size_t max_samples_;
    float max_value_;
    Graphic::Color color_;

public:
    // -------------------------------------------------------------------------------
    // --- Constructor ---

    Plot(Graphic::Canvas& canvas, size_t max_samples = 150, Graphic::Color color = Graphic::Colors::White) 
        : canvas_(canvas)
        , max_samples_(max_samples)
        , max_value_(10.0f)
        , color_(color)
    {}

    // -------------------------------------------------------------------------------
    // --- Methods Prototypes ---

    void pushValue(float value);
    void draw();
};

} // namespace Gameplay

#endif
