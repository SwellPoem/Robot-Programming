#include <iostream>
#include "grid_map.h"
#include "isometry_2.h"

using namespace std;

int main(int argc, char** argv) {
  if (argc<2) {
    cout << "usage: " << argv[0] << " <image_file> <resolution>" << endl;
    return -1;
  }
  const char* filename=argv[1];
  Scalar resolution=atof(argv[2]);

  cout << "Running " << argv[0]
       << " with arguments" << endl
       << "-filename:" << argv[1] << endl
       << "-resolution: " << argv[2] << endl;

  GridMap grid_map(0,0, 0.1);
  grid_map.loadFromImage(filename, resolution);
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
