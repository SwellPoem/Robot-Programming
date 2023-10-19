#include "draw_helpers.h"

void drawLine(Canvas& dest, const Vec2i& p0, const Vec2i& p1, uint8_t color) {
  cv::line(dest, cv::Point(p0[0], p0[1]), cv::Point(p1[0], p1[1]), cv::Scalar(color, color, color), 1);
}

int showCanvas(Canvas& canvas, int timeout_ms) {
  cv::imshow("canvas", canvas);
  int key=cv::waitKey(timeout_ms);
  if (key==27) // exit on ESC
    exit(0);
  //cerr << "key" << key << endl;
  return  key;
}
