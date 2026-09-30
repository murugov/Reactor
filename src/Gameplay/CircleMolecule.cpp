#include "Gameplay/CircleMolecule.hpp"
#include "Graphic/Adapter.hpp"

namespace Gameplay {

// -------------------------------------------------------------------------------
// --- Implementation Of Static Methods ---

void CircleMolecule::update (float dt) {
    pos_ = pos_ + velocity_ * dt;
}

void CircleMolecule::draw () const {
    Graphic::Adapter::drawCircle({ pos_, radius_ }, color_);
}

} // namespace Gameplay
