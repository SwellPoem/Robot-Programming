#pragma once
#include <cmath>
#include <iostream>
#include <cstdint>
#include <opencv2/opencv.hpp>

// this statement makes a type alias.
// after it you can use Scalar and float interchangeably.
using Scalar = float;

// simple vector2 class
struct Vec2 {
  // static in a class: declares a variable global to all instances of Vec2f
  // constexpr specifies that this variable is evaluated at compile time
  static constexpr int Dim = 2;

  // Array of values
  Scalar values[Dim];

  // inline in a function makes the function to be expanded at compilation
  // time in the positions where it is called.
  // inline functions do not admit recursion, and should be declared
  // in the header
  inline void setZero() {
    for (int i = 0; i < Dim; ++i) values[i] = Scalar(0);
  }

  // we redefine the [] operator, to support the element access
  // in an array like style. We to this in two flavors
  // const and non const

  // this returns a reference to an element of the vector,
  // hence you can change it
  inline Scalar& operator[](int p) { return values[p]; }

  // this returns a CONST reference to an element of the vector,
  // hence you cannot change it, and it is safe to use in const methods
  inline const Scalar& operator[](int p) const { return values[p]; }

  inline Vec2 operator+(const Vec2& other) const {
    Vec2 ret = *this;
    for (int i = 0; i < Dim; ++i) {
      ret[i] += other[i];
    }
    // TODO 1
    return ret;
  }

  inline Vec2& operator+=(const Vec2& other) {
    // TODO 2
    for (int i = 0; i < Dim; ++i) {
      values[i] += other[i];
    }
    return *this;
  }

  inline Vec2 operator*(const Scalar& other) const {
    // TODO 3
    Vec2 ret = *this;
    for (int i = 0; i < Dim; ++i) {
      ret[i] *= other;
    }
    return ret;
  }

  inline Vec2& operator*=(const Vec2& other) {
    // TODO 4
    for (int i = 0; i < Dim; ++i) {
      values[i] *= other[i];
    }
    return *this;
  }
};

// streaming operator allows to use cout << vec3 to print on a stream
std::ostream& operator<<(std::ostream& os, const Vec2& src);

// TODO 5: define a class Vec2i that operates on integers instead of scalars,
// and has all functions above
struct Vec2i {
  static constexpr int Dim = 2;
  int values[Dim];
  int& operator[](int p) { return values[p]; }
  const int& operator[](int p) const { return values[p]; }

  inline Vec2i operator+(const Vec2i& other) const {
    Vec2i ret = *this;
    for (int i = 0; i < Dim; ++i) {
      ret[i] += other[i];
    }
    // TODO 1
    return ret;
  }

  inline Vec2i& operator+=(const Vec2i& other) {
    // TODO 2
    for (int i = 0; i < Dim; ++i) {
      values[i] += other[i];
    }
    return *this;
  }

  inline Vec2i operator*(const int& other) const {
    // TODO 3
    Vec2i ret = *this;
    for (int i = 0; i < Dim; ++i) {
      ret[i] *= other;
    }
    return ret;
  }

  inline Vec2i& operator*=(const Vec2i& other) {
    // TODO 4
    for (int i = 0; i < Dim; ++i) {
      values[i] *= other[i];
    }
    return *this;
  }
};

// TODO 6: write the stream operator for Vec2i
std::ostream& operator<<(std::ostream& os, const Vec2i& src);

// same as before but with 3 dimensions
struct Vec3 {
  static constexpr int Dim = 3;
  Scalar values[Dim];

  Scalar& operator[](int p) { return values[p]; }
  const Scalar& operator[](int p) const { return values[p]; }

  inline Vec3 operator+(const Vec3& other) const {
    Vec3 ret = *this;
    for (int i = 0; i < Dim; ++i) {
      ret[i] += other[i];
    }
    // TODO 1
    return ret;
  }

  inline Vec3& operator+=(const Vec3& other) {
    // TODO 2
    for (int i = 0; i < Dim; ++i) {
      values[i] += other[i];
    }
    return *this;
  }

  inline Vec3 operator*(const Scalar& other) const {
    // TODO 3
    Vec3 ret = *this;
    for (int i = 0; i < Dim; ++i) {
      ret[i] *= other;
    }
    return ret;
  }

  inline Vec3& operator*=(const Vec3& other) {
    // TODO 4
    for (int i = 0; i < Dim; ++i) {
      values[i] *= other[i];
    }
    return *this;
  }
};

std::ostream& operator<<(std::ostream& os, const Vec3& src);

struct Isometry2 {
  static constexpr int Dim = 2;
  Scalar rotation[Dim][Dim];

  Vec2 translation;

  Isometry2() {}

  Isometry2(const Vec3& src) {
    const Scalar& x = src[0];
    const Scalar& y = src[1];
    const Scalar& theta = src[2];
    const Scalar s = sin(theta);
    const Scalar c = cos(theta);
    rotation[0][0] = c;
    rotation[0][1] = -s;
    rotation[1][0] = s;
    rotation[1][1] = c;
    translation[0] = x;
    translation[1] = y;
  }

  Vec3 toVector() const {
    Vec3 dest;
    dest[0] = translation[0];
    dest[1] = translation[1];
    dest[2] = atan2(rotation[1][0], rotation[0][0]);
    return dest;
  }

  inline void setIdentity() {
    for (int r = 0; r < Dim; ++r) {
      for (int c = 0; c < Dim; ++c) {
        if (r == c)
          rotation[r][c] = Scalar(1);
        else
          rotation[r][c] = Scalar(0);
      }
    }
    translation.setZero();
  }
  /* inv(R, t) = (R^T, -R^T* T) */
  inline Isometry2 inverse() const {
    Isometry2 dest;
    dest.setIdentity();

    for (int r = 0; r < Dim; ++r) {
      for (int c = 0; c < Dim; ++c) {
        dest.rotation[r][c] = rotation[c][r];
      }
    }
    for (int r = 0; r < Dim; ++r)
      for (int c = 0; c < Dim; ++c)
        dest.translation[r] -= dest.rotation[r][c] * translation[c];
    return dest;
  }

  /* (R1, t1)*(R1, t2) = (R1*R2, t1 + R1*t2) */
  inline Isometry2 operator*(const Isometry2& other) const {
    Isometry2 dest;

    for (int r = 0; r < Dim; ++r) {
      dest.translation[r] = translation[r];
      for (int c = 0; c < Dim; ++c) {
        Scalar accumulator = 0;
        for (int k = 0; k < Dim; ++k) {
          accumulator += rotation[r][k] * other.rotation[k][c];
        }
        dest.rotation[r][c] = accumulator;
        dest.translation[r] += rotation[r][c] * other.translation[c];
      }
    }
    return dest;
  }

  // (R|t)*v = R*v+t;
  inline Vec2 operator*(const Vec2& other) {
    // TODO 7
    Vec2 ret;
    for (int r = 0; r < Dim; ++r) {
      Scalar acc = 0.0;
      for (int c = 0; c < Dim; ++c) {
        acc += rotation[r][c] * other[c];
      }
      acc += translation[r];
      ret[r] = acc;
    }
    return ret;
  }
};

std::ostream& operator<<(std::ostream& os,
                         const Isometry2& iso);  // Todo in cpp

using Canvas = cv::Mat;

// draws a line from p0 to p1
void drawLine(Canvas& dest, const Vec2i& p0, const Vec2i& p1, uint8_t color);

int showCanvas(Canvas& canvas, int timeout_ms);

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
