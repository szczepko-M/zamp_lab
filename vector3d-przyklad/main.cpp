#include <iostream>
#include "g3dVector.hh"

using namespace std;

int main()
{
  g3d::Vector  V1(2, 4.0, 5);   // Inicjalizacja z zestawem parametrów
  g3d::Vector  V2{1, 5.3 ,6.1}; // Inicjalizacja z wykorzystaniem listy
  g3d::Vector  Sum;

  cout << endl;
  cout << "  V1 = " << V1 << endl;
  cout << "  V2 = " << V2 << endl;
  Sum = V1 + V2;
  cout << " Sum = " << Sum << endl;
  cout << endl; 
}
