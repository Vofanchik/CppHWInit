#include <iostream>
using namespace std;


int main()
{
    setlocale(LC_ALL, "Russian");
    char a;
    string tex = "¬ведите операцию: дл€ сложени€ +, вычитани€ -, умножени€ *, делени€ /, факториала !, степени ^, выхода q";
    cout << tex << endl;
    cin >> a;
    while (a != 'q')
    {
        int x,y;
        cout << "¬ведите левый операнд" << endl;
        cin >> x;

        if (a != '!') {
            cout << "¬ведите правый операнд" << endl;
            cin >> y;
        }

        switch (a)
        {
        case '-':
            cout << x << " - " << y << " = " << x - y << endl;
            break;
        case '+':
            cout << x << " + " << y << " = " << x + y << endl;
            break;
        case '*':
            cout << x << " * " << y << " = " << x * y << endl;
            break;
        case '\\':
            if (y == 0) {
                cout << "на ноль не делитс€" << endl;
                break;
            }
            cout << x << " / " << y << " = " << x / float(y) << endl;
            break;
        
        case '!': {
            int fac = 1;
            int i = 1;
            while (i < x) {
                fac *= ++i;
            }
            cout << "‘акториал числа " << x << " = " << fac << endl;
            break;
        }
        case '^': {
            int i = 1;
            int power = 1;
            while (i <= y)
            {
                power *= x;
                i++;
            }

            cout << x << " в " << y << " степени = " << power << endl;
            break;
        }
        default:
            cout << "ошибка";
            break;
        }
        cout << tex << endl;
        cin >> a;
    }
    
    return 0;
}