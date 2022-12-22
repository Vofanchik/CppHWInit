#include <iostream>
using namespace std;


int main()
{
    int x,y;
    cin >> x;
    cin >> y;
    cout << x << " + " << y << " = " << x + y << endl;
    cout << x << " - " << y << " = " << x - y << endl;
    cout << x << " * " << y << " = " << x * y << endl;
    cout << x << " / " << y << " = " << x / float(y) << endl;
    cout << x << " & " << y << " = " << (x & y) << endl;
    cout << x << " | " << y << " = " << (x | y) << endl;
    cout << x << " ^ " << y << " = " << (x ^ y) << endl;

    return 0;
}