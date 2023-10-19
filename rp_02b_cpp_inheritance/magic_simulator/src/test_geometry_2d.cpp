#include <iostream>
#include "geometry_2d.h"

using namespace std;

int main(int argc, char** argv) {
  Vec3 v3;
  v3[0]=1;
  v3[1]=2;
  v3[2]=0.2;
  cout << "v3" << v3 << endl;

  Isometry2 iso(v3);
  cout << "iso" << iso << endl;
  cout << "iso.inverse() " << iso.inverse() << endl;
  cout << "iso * iso.inverse() " << iso  * iso.inverse() << endl;
  
}
