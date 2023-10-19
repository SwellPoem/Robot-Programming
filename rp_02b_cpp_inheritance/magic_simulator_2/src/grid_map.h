#pragma once
#include "precision.h"
#include "vec_x.h"
#include "draw_helpers.h"

// grid mapping class
struct GridMap {
  // size of the gris
  int rows;
  int cols;
  Scalar resolution;      // meters*pixel
  Scalar inv_resolution;  // pixel*meters

  Vec2i origin;  // rows/2, cols/2;
  uint8_t* values;

  //loads a map from an image
  void loadFromImage(const char *filename, Scalar resolution);
  
  // TODO 8: make a constructor that
  // - allocates rows*cols char in values;
  // - stores rows and cols in member object
  // - sets the origin to the middle (in pixels)
  // - sets the resolution and inv_resolution
  GridMap(int rows, int cols, Scalar resolution);

  // TODO 9: // polish memory on destruction
  ~GridMap();
  
  // returns the pixel at r,c, row major order
  inline const uint8_t& at(int r, int c) const {
    // TODO 9
    return values[r * cols + c];
  }

  // same as above with write access
  inline uint8_t& at(int r, int c) {
    // returns the pixel at r,c, row major order
    // TODO 10
    return values[r * cols + c];
  }

  // converts world coordinates to grid coordinates
  // beware that dest[0]=cols, dest[1]=rows
  inline Vec2i world2grid(const Vec2& src) {
    Vec2i dest;
    dest[0] = origin[0] + inv_resolution * src[0];
    dest[1] = origin[1] + inv_resolution * src[1];
    return dest;
  };

  // converts grid coordinates to world coordinates
  inline Vec2 grid2world(const Vec2i& src) {
    Vec2 dest;
    dest[0] = (src[0] - origin[0]) * resolution;
    dest[1] = (src[1] - origin[1]) * resolution;
    return dest;
  }

  // TODO 11: write the comment to this function :)
  inline bool inside(const Vec2i& src) {
    return src[0] >= 0 && src[0] < cols && src[1] >= 0 && src[1] < rows;
  }

  // TODO 12: write the comment to this function
  inline bool inside(const Vec2& src) { return inside(world2grid(src)); }

  // WARINING! i changed the order of the arguments and added a max_range
  bool scanRay(Vec2& hit, const Vec2& origin, const Vec2& direction, const Scalar max_range);

  //renders a map to a canvas
  void draw(Canvas& dest);
};
