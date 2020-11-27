/* Test for Vector and Matrix */
#include <stdio.h>      /* printf */
#include <assert.h>     /* assert */

#include "../include/libmatrix.hpp"
using namespace libmatrix;
using namespace std;

const int nb_test = 20;

int affectation()
{
 Vec3i a;
 Vec3i u = Vec3i({1,3,4});
 Vec3i u2 = Vec3i({1,3,4});
 Vec3i v(a);
 v[0] = 2; v[1] = 7; v[2] = -5;
 assert(a==vect3izero);
 assert(u==u2);
 assert(v==Vec3i({2,7,-5}));

 cout << "Affection réussi"

 

return 1;
}

void print_number(int* myInt) {
  assert (myInt!=NULL);
  printf ("%d\n",*myInt);
}

int main ()
{
  int a=10;
  int * b = NULL;
  int * c = NULL;

  b=&a;

  print_number (b);
  print_number (c);

  return 0;
}