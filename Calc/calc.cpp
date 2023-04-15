#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>


using namespace std;

class mstring
{
public:
    explicit mstring(const char* str)
    {
        cout << "string constructed " << str << endl;
        _size = strlen(str) + 1;
        _string = new char[_size];
        strcpy(_string, str);
    }

    mstring(const mstring& other)
    {
        cout << "string copy constructed " << other._string << endl;
        _string = new char[other._size];
        strcpy(_string, other._string);
        _size = other._size;
    }

    mstring& operator=(const mstring& other)
    {
        cout << "string copy constructed " << other._string << endl;
        _string = new char[other._size];
        strcpy(_string, other._string);
        _size = other._size;

        return *this;
    }

    mstring(mstring&& other) noexcept // конструктор копирования перемещения
    {
        cout << "move constructor " << other._string << endl;
        _string = other._string;
        _size = other._size;
        other._string = nullptr;
        other._size = 0;
    }

    mstring& operator=(mstring&& other) noexcept // конструктор присваивания перемещения
    {
        cout << "move assignment constructor " << other._string << endl;
        _string = other._string;
        _size = other._size;
        other._string = nullptr;
        other._size = 0;

        return *this;
    }



    ~mstring() noexcept
    {
        delete[] _string;
    }

    friend ostream& operator<<(ostream& os, const mstring& str);

private:
    char* _string;
    size_t _size;
};

ostream& operator<<(ostream& os, const mstring& str)
{
    os << str._string;
    return os;
}