/*	singleton.cpp	*/

#include <iostream>

class Singleton {
private:
	static/* inline*/ Singleton* sSp;
	Singleton() = default;
public:
	static Singleton* get_object();
	~Singleton();
};

Singleton* Singleton::sSp = nullptr;		// or the data member must be inline,

Singleton* Singleton::get_object() {
	if (sSp == nullptr) {
		sSp = new Singleton();
		}
	return sSp;
}

Singleton::~Singleton() {
	delete sSp;
	sSp = nullptr;
}

int main() {
	Singleton* sp1 = Singleton::get_object();
    Singleton* sp2 = Singleton::get_object();
    Singleton* sp3 = Singleton::get_object();

    std::cout << "Address of sp1: " << sp1 << std::endl;
    std::cout << "Address of sp2: " << sp2 << std::endl;
    std::cout << "Address of sp3: " << sp3 << std::endl;

return 0;
}
