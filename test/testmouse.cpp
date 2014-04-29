#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

int main(int argc,char * argv[]) {

  string command = "";
 
  for(int i = 1; i < argc; i++){
    command += argv[i];
    command += " ";
  }
  
  //using Xautomation script
  string call = "xte ";
  call += command;
  
  system(call.c_str());

  return 0;
}
