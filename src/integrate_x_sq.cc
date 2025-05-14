#include "rtweekend.h"

#include <iostream>
#include <iomanip>

double icd(double d)
{
  return std::sqrt(4.0 * d);
}

double pdf(double x)
{
  return x / 2.0;
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
