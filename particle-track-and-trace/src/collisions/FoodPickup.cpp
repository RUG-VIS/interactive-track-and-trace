#include "FoodPickup.h"

void FoodPickup::handleCollision(int index) const {
  ParticleRemover::handleCollision(index);
  health->changeHealth(0.2);
//  health->grace();
  camera->zoomScreen();
  character->dash();
  badges->logFoodConsumption();
}

FoodPickup::FoodPickup(
        const vtkSmartPointer<vtkPoints> &particles,
        const std::shared_ptr<Health> &health,
        const std::shared_ptr<Camera> &camera,
        const std::shared_ptr<Character> &character,
        const std::shared_ptr<Badges> &badges
) : ParticleRemover(particles), health(health), camera(camera), character(character), badges(badges) {}