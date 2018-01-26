#pragma once

#include "polyscope/gl/gl_utils.h"

#include <vector>


namespace polyscope {

// A histogram that shows up in ImGUI
class Histogram {
public:
  Histogram();
  Histogram(std::vector<double>& values);
  Histogram(std::vector<double>& values, const std::vector<double>& weights);

  ~Histogram();

  void buildHistogram(std::vector<double>& values, const std::vector<double>& weights = {});
  void updateColormap(const gl::Colormap* newColormap);

  void buildUI();

  float colormapRangeMin, colormapRangeMax; // in DATA values, not [0,1]

private:
  // = Helpers

  // Manage the actual histogram
  void fillBuffers();
  void smoothCurve(std::vector<double>& yVals);
  size_t histBinCount = 200;
  std::vector<double> weightedHistCurveY;        // size of buckets
  std::vector<double> unweightedHistCurveY;      // size of buckets
  std::vector<std::array<double, 2>> histCurveX; // left and right sides of each bucket, in "data" coordinates
  double minVal;
  double maxVal;
  bool hasWeighted = false;
  bool useWeighted = false;


  // Render to texture
  void renderToTexture();
  void prepare();
  GLuint texDim = 600;
  GLuint framebufferInd, textureInd;
  gl::GLProgram* program = nullptr;
  const gl::Colormap* colormap = &gl::CM_CONST_RED;
};


}; // namespace polyscope
