#ifndef INTERPOLATE_H
#define INTERPOLATE_H

class Interpolate
{
 public:
  Interpolate();
  int CurrentStep;
  
  void InterpolateLinear(int dim, int start[], int finish[], int steps, int current[], bool & done);

};


#endif
