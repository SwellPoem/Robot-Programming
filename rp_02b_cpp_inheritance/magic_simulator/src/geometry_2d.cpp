#include "geometry_2d.h"
using namespace std;

ostream& operator << (ostream& os, const Vec2& src) {
  os << "Vec2 " << (&src) << " [ ";
  for (int i=0; i<src.Dim; ++i) {
    os << src.values[i] << " ";
  }
  os << "]";
  return os;
}

ostream& operator << (ostream& os, const Vec3& src) {
  os << "Vec3 (" << &src << ") [ ";
  for (int i=0; i<src.Dim; ++i) {
    os << src.values[i] << " ";
  }
  os << "]";
  return os;
}

ostream& operator << (ostream& os, const Isometry2& src) {
  os << "Iso2 (" << &src << ") " << endl;
  for (int r=0; r<src.Dim; ++r) {
    for (int c=0; c<src.Dim; ++c) 
      os << src.rotation[r][c] << " ";
    os << "| " << src.translation[r] << endl;
  }
  return os;
}


// TODO 13:
// traverses the grid along a ray having direction "direction", represented as a unit vector
// the ray starts at "origin"
// the function proceeds by walking on a line origin + direction*res*k (with k parameter)
// until it either
// -- finds a cell whose value is > than a threshold (127) [return true]
// -- exits from the grid [return false]
// the value "hit" should contain the last traversed coordinates
bool GridMap::scanRay(Vec2& hit,
                     const Vec2& direction,
                     const Vec2& origin) {
  //TODO
  return false;
}
