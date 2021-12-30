#include <iostream>
#include "HugeInteger.h"

using namespace std;
int main()
{
    HugeInteger h1{ "125" };
    HugeInteger h2{ 56 };
    HugeInteger h3;
    h3 = h1 * h2;
    cout << h1 << "\n" << h2 << endl;
    cout << h3 << endl;
    cout << h1 + h2 << endl;
    cout << (h1 > h2) << " " << (h2 < h1)<<endl;
    cout << (h1 >= h2) << " " << (h2 <= h1)<<endl;
    cout << (h1 == h2) << " " << (h2 == h1)<<endl;
}
