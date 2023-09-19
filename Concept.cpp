#include <iostream>
#include <concepts>

template <typename T>
concept ComplexConcept =  requires(T v)
{
	{v.toString()}
	->std::same_as<std::string>;
	{v.hash()}
	->std::convertible_to<long>;
	std::has_virtual_destructor <T>::value ;
};

class SomeClass {
public:
		int val = 2;
		SomeClass() {}
		~SomeClass() {};
		std::string toString() {
			std::string text = "Concept toString";
			return text;
		}
		int hash() {
			int number = 1;
			return number;
		}
};

template <ComplexConcept T> void PrintType( T val) {
	val.toString();
	val.hash();
}

int main()
{
	return 0;
}
