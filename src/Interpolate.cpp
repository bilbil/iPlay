#include "Interpolate.h"

Interpolate::Interpolate()
{
  this->CurrentStep = 0;
}

void Interpolate::InterpolateLinear(int dim, int start[], int finish[], int steps, int current[], bool & done)
{

  int * diff = new int[dim];
  int * step = new int[dim];

  // for each dimension, calculate the difference and step size
  for(int i = 0; i < dim; i++){
    diff[i] = finish[i] - start[i];
    step[i] = diff[i]/steps;
  }

  //check if finished  
  if(CurrentStep >= steps){
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
    current[i] += step[i];
  }

  CurrentStep++;
}
