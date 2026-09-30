#include "Gameplay/SquareMolecule.hpp"
#include "Graphic/Adapter.hpp"

namespace Gameplay {

// -------------------------------------------------------------------------------
// --- Implementation Of Static Methods ---

void SquareMolecule::update(float dt) {
    pos_ = pos_ + velocity_ * dt;
}

void SquareMolecule::draw() const {
    Graphic::Adapter::drawRectangle({ pos_, size_ }, color_);
}

} // namespace Gameplay