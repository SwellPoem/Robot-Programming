#include "geometry_2d.h"
using namespace std;

ostream& operator<<(ostream& os, const Vec2& src) {
  os << "Vec2 " << (&src) << " [ ";
  for (int i = 0; i < src.Dim; ++i) {
    os << src.values[i] << " ";
  }
  os << "]";
  return os;
}

std::ostream& operator<<(std::ostream& os, const Vec2i& src) {
  os << "Vec2i " << (&src) << " [ ";
  for (int i = 0; i < src.Dim; ++i) {
    os << src.values[i] << " ";
  }
  os << "]";
  return os;
}

ostream& operator<<(ostream& os, const Vec3& src) {
  os << "Vec3 (" << &src << ") [ ";
  for (int i = 0; i < src.Dim; ++i) {
    os << src.values[i] << " ";
  }
  os << "]";
  return os;
}

ostream& operator<<(ostream& os, const Isometry2& src) {
  os << "Iso2 (" << &src << ") " << endl;
  for (int r = 0; r < src.Dim; ++r) {
    for (int c = 0; c < src.Dim; ++c) os << src.rotation[r][c] << " ";
    os << "| " << src.translation[r] << endl;
  }
  return os;
}

// TODO 8: make a constructor that
// - allocates rows*cols char in values;
// - stores rows and cols in member object
// - sets the origin to the middle (in pixels)
// - sets the resolution and inv_resolution
GridMap::GridMap(int rows_, int cols_, Scalar resolution_) {
  values = new char[rows_ * cols_];
  rows = rows_;
  cols = cols_;
  resolution = resolution_;
  inv_resolution = 1.0 / resolution;
  origin = Vec2i({rows_ / 2, cols_ / 2});
}

GridMap::~GridMap() { delete[] values; }

// TODO 13:
// traverses the grid along a ray having direction "direction", represented as a
// unit vector the ray starts at "origin" the function proceeds by walking on a
// line origin + direction*res*k (with k parameter) until it either
// -- finds a cell whose value is > than a threshold (127) [return true]
// -- exits from the grid [return false]
// the value "hit" should contain the last traversed coordinates
bool GridMap::scanRay(Vec2& hit, const Vec2& direction, const Vec2& origin) {
  // TODO

  Vec2i current_position = world2grid(origin);
  Vec2 current_position_f = origin;

  while (true) {
    if (!inside(current_position)) return false;

    if (at(current_position[0], current_position[1]) > 127) {
      // Do something
      hit = grid2world(current_position);
      return true;
    }

    current_position_f += direction * 0.01;
    current_position = world2grid(current_position_f);
  }
  return false;
}
