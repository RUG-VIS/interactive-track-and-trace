#include "Layer.h"
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

using std::string;

vtkSmartPointer<vtkRenderer> Layer::getLayer() {
  return this->renderer;
}

void Layer::updateData(int t) {
  // By default, do nothing
}

void Layer::addObservers(vtkSmartPointer<vtkRenderWindowInteractor> interactor) {
    // By default, do nothing
}


void Layer::setCamera(vtkCamera *camera) {
  this->getLayer()->SetActiveCamera(camera);
}

Layer::Layer() { }

void Layer::handleGameOver() {
  // By default, do nothing
}