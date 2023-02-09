#include <iostream>

class A {
public:
	A(): pointer_member{ new int{1} } 
	{
		std::cout << "This is a default constructor!\n";
	}

	A(const A& obj) : pointer_member{ new int{obj.GetA()} }
	{
		std::cout << "This is a copy constructor!\n";
	}

	A(A&& obj) noexcept: pointer_member{ obj.pointer_member }
	{
		std::cout << "Move constructor\n";
	}

	A& operator=(const A& obj)
	{
		std::cout << "Assign operator\n";
		*pointer_member = obj.GetA();
		return *this;
	}

	int GetA() const { return *pointer_member; }

	~A()
	{
		std::cout << "Destructor\n";
		delete pointer_member;
	}

private:
	int* pointer_member;
};

void ShowA(A&& a)
{
	std::cout << "void ShowA(A&& a) ";
	std::cout << a.GetA()<<"\n";
}

void ShowA(const A& a)
{
	std::cout << "void ShowA(const A& a) ";
	std::cout << a.GetA() << "\n";
}

int main() {
	A a;
	ShowA(a);
	ShowA(std::move( a ));
	ShowA(A());
	std::cout << "Program end\n";
	return 0;
}