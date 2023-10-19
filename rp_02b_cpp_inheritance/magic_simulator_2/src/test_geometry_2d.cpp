#include <iostream>

#include "geometry_2d.h"

using namespace std;

int main(int argc, char** argv) {
  Vec2i v0;
  v0[0] = 1;
  v0[1] = 2;
  cout << "v0" << v0 << endl;
  Vec2i v1 = v0 * 2;
  cout << "v1" << v1 << endl;
  v1 += v1;
  cout << "v1" << v1 << endl;
  Vec2i v2 = v0 + v1;
  cout << "v2" << v2 << endl;
  Vec2i vk = v0;
  vk *= v1;
  cout << "vk" << vk << endl;

  Vec3 v3;
  v3[0] = 1;
  v3[1] = 2;
  v3[2] = 0.2;
  cout << "v3" << v3 << endl;

  Vec3 iso_vec;
  iso_vec[0] = 1;
  iso_vec[1] = 1;
  iso_vec[2] = M_PI_2;

  Isometry2 iso(iso_vec);
  cout << "iso" << iso << endl;
  cout << "iso.inverse() " << iso.inverse() << endl;
  cout << "iso * iso.inverse() " << iso * iso.inverse() << endl;
  Vec2 test_vect;
  test_vect[0] = 1;
  test_vect[1] = 0;
  Vec2 res = iso * test_vect;
  cout << "iso * test_vect " << res << endl;

  GridMap grid_map(0,0, 0.1);
  grid_map.loadFromImage(argv[1], 0.1);
  Canvas canvas;
  Vec2 center=grid_map.grid2world(grid_map.origin);
  cerr << "center: " << center[0] << "  "<< center[1] << endl;
  cerr << "origin: " << grid_map.origin[0] << "  "<< grid_map.origin[1] << endl;
  
  float alpha=0;
  while(1) {
    grid_map.draw(canvas);
    Vec2 direction;
    direction[0]=cos(alpha);
    direction[1]=sin(alpha);
    Vec2 dest;
    bool hit = grid_map.scanRay(dest, center, direction, 100);
    drawLine(canvas, grid_map.world2grid(center), grid_map.world2grid(dest), 127);
    
    showCanvas(canvas, 0);
    
    alpha+=0.01;
  }
}
