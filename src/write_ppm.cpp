#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code from computer-graphics-raster-images
  assert(
    (num_channels == 3 || num_channels ==1 ) &&
    ".ppm only supports RGB or grayscale images");
  ////////////////////////////////////////////////////////////////////////////
  assert(
    (width>0 && height>0) &&
    ".ppm only support RGB that has height and width greater than 0");
  std::ofstream img;
  img.open(filename, std::ios::binary);
  if (!img.is_open()) {
    return false;
  } else {
    if (num_channels == 3){
      img << "P6\n";}
    else if (num_channels == 1){
      img << "P5\n";}
      img << width << " " << height << "\n255\n";
    for (int i=0; i<height*width*num_channels; i++) {
      img << data[i];}
    img.close();
    return true;
  }
  ////////////////////////////////////////////////////////////////////////////
}
