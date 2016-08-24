#include <iostream>
using namespace std;

int main (){


int x;

cin >> x;
if (x % 2 != 0)
   {
   cout << "inputted x was odd";
   x = x - 1;
   }
if (x % 2 == 0)
   {
   cout << "inputted x was even";
   x = x - 2;
   }
cout << "largest even less than input is " << x;

return 0;
}