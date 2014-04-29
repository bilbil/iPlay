#ifndef INTERPOLATE_H
#define INTERPOLATE_H

class interpolate
{
 public:
  interpolate();
  int CurrentStep;
  
  void interpolateLinear(int dim, int start[], int finish[], int steps, int current[], bool & done);

};


#endif
