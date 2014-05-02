#include "Interpolate.h"

Interpolate::Interpolate()
{
  this->CurrentStep = 0;
}

void Interpolate::InterpolateLinear(int dim, float start[], float finish[], int stepsTotal, float current[], bool & done)
{

  int * diff = new int[dim];
  float * step = new float[dim];

  // for each dimension, calculate the difference and step size
  for(int i = 0; i < dim; i++){
    diff[i] = finish[i] - start[i];
    step[i] = ((float)diff[i])/stepsTotal;
  }

  //check if finished  
  if(CurrentStep > stepsTotal){
    done = true;
    return;
  }

  //initialize current value when starting
  if(CurrentStep == 0){
    done = false;
    for(int i = 0; i < dim; i++){
      current[i] = start[i];
    }
  }
  
  //increment current value
  for(int i = 0; i < dim; i++){
    current[i] = start[i] + CurrentStep * step[i];
  }

  CurrentStep++;
}
