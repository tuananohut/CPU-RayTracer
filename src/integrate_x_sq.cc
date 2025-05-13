#include "rtweekend.h"

#include <iostream>
#include <iomanip>

double icd(double d)
{
  return 2.0 * d;
}

double pdf(double x)
{
  return 0.5;
}

int main()
{
  int N = 1000000;
  auto sum = 0.;

  for (int = 0; i < N; i++)
    {
      auto x = icd(random_double());
      sum += x*x / pdf(x);  
    }

  std::cout << std::fixed << std::setprecision(12);
  std::cout << "I = " << (sum / N) << '\n';
}
