
#include <iostream>

/*
  Explanation:

*/

int main()
{
  //The only characters that can change independently are 'a' and 'r'. Also because no chars in chars are missing in all of (north, east, south, west) all the chars  msut
  for(int aOption = 0; aOption < 10; aOption++)
  {
    for(int rOption = 0; rOption < 10; rOption++)
    {
      //cout << "[E: " << 0 << ", A: " << aOption << ", R: " << rOption << ", T: 0" <<; ]
      printf("E: %d, A: %d, R: %d, T: %d, H: %d, N: %d, O: %d, W: %d, U: %d, S: %d \n", 0, aOption, rOption, 0, 0, 0, 0, 0, 0, 0);
      std::cout << "Common Sum: " <<  aOption + rOption << std::endl;     
    }
  }
}