#ifndef INTERPOLATE_H
#define INTERPOLATE_H

class Interpolate
{
 public:
  Interpolate();
  int CurrentStep;
  
  void InterpolateLinear(int dim, float start[], float finish[], int steps, float current[], bool & done);

};


#endif
