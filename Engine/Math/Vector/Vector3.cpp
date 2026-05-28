#include "PreCompileHedder.h"
#include "Vector3.h"


Vector3::Vector3 () : data(0.0f, 0.0f, 0.0f) {}

Vector3::Vector3(float x_, float y_, float z_) : data(x_, y_, z_) {}

Vector3::Vector3(float entries_[3]) :data(entries_[0], entries_[1], entries_[2]) {}
