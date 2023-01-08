#include <iostream>
using namespace std;


int main()
{
    setlocale(LC_ALL, "Russian");  

    cout << "для шифрования - 1, дешифрования - 2, остальное для выхода" << endl;
    int sel = 0;
    cin >> sel;

    while (sel == 1 || sel == 2)
    {
        int size = 0;
        cout << "введите размер массива" << endl;
        cin >> size;
        int shift;
        cout << "введите размер сдвига" << endl;
        cin >> shift;
        char *array = new char[100];
        cout << "введите символы " << endl;
        cin >> array;

        //for (int i = 0; i < size; ++i)
        //{
        //    cin >> array[i]; 
        //}

        
        if (sel == 1)
        {
            for (int i = 0; i < size; ++i)
            {
                if (array[i] == 'z') 
                {
                    array[i] = 'a' + shift - 1; 
                }
                else if (array[i] == 'Z')
                {
                    array[i] = 'A' + shift - 1;
                }
                else
                {
                    array[i] += shift;
                }
            }
        }
        else
        {
            for (int i = 0; i < size; ++i)
            {
                if (array[i] == 'z')
                {
                    array[i] = 'a' - shift - 1;
                }
                else if (array[i] == 'Z')
                {
                    array[i] = 'A' - shift - 1;
                }
                else
                {
                    array[i] -= shift;
                }
            }
        }

        for (int i = 0; i < size; ++i)
        {
            cout << array[i]; 
        }

        delete[] array;
        cout << endl << "для шифрования - 1, дешифрования - 2, остальное для выхода" << endl;
        cin >> sel;
    }
    return 0;
}