#include <iostream>
using namespace std;


int main()
{
    setlocale(LC_ALL, "Russian");  

    cout << "��� ���������� - 1, ������������ - 2, ��������� ��� ������" << endl;
    int sel = 0;
    cin >> sel;

    while (sel == 1 || sel == 2)
    {
        int size = 0;
        cout << "������� ������ �������" << endl;
        cin >> size;
        int shift;
        cout << "������� ������ ������" << endl;
        cin >> shift;
        char *array = new char[100];
        cout << "������� ������� " << endl;
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
        cout << endl << "��� ���������� - 1, ������������ - 2, ��������� ��� ������" << endl;
        cin >> sel;
    }
    return 0;
}