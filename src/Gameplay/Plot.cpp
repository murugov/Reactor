#include "Gameplay/Plot.hpp"
#include "Graphic/Adapter.hpp"

namespace Gameplay {

void Plot::pushValue(float value) {
    data_history_.push_back(value);
    
    if (data_history_.size() >= max_samples_) {
        data_history_.erase(data_history_.begin());
    }

    if (value > max_value_) {
        max_value_ = value;
    }
}

void Plot::draw() {
    if (data_history_.size() < 2) return;

    canvas_.draw(); 
    
    float offset_x = canvas_.x();
    float offset_y = canvas_.y();

    float canvas_w = static_cast<float>(canvas_.width());
    float canvas_h = static_cast<float>(canvas_.height());

    // X-axis step
    float step_x = canvas_w / static_cast<float>(max_samples_ - 1);

    for (size_t i = 0; i < data_history_.size() - 1; ++i) {
        float local_x1 = static_cast<float>(i) * step_x;
        float local_y1 = canvas_h - (data_history_[i] / max_value_) * canvas_h;

        float local_x2 = static_cast<float>(i + 1) * step_x;
        float local_y2 = canvas_h - (data_history_[i + 1] / max_value_) * canvas_h;

        Math::Vector2D p1{ offset_x + local_x1, offset_y + local_y1 };
        Math::Vector2D p2{ offset_x + local_x2, offset_y + local_y2 };

        Graphic::Adapter::drawLine(p1, p2, color_, 1.5f);
    }
}


} // namespace Gameplay