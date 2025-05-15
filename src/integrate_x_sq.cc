#include "rtweekend.h"

#include <iostream>
#include <iomanip>

double icd(double d)
{
  return 8. * std::pow(d, 1. / 3.);
}

double pdf(double x)
{
  return (3./8.) * x*x;
}

int main()
{
  int N = 1;
  auto sum = 0.;

  for (int = 0; i < N; i++)
    {
      auto z = random_double();
      if (z == 0.0) // Ignore zero to avoid NaNs
	continue;
      
      sum += x*x / pdf(x);  
    }

  std::cout << std::fixed << std::setprecision(12);
  std::cout << "I = " << (sum / N) << '\n';
}
