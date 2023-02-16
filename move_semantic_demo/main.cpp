#include <iostream>
#include <memory>
#include <string>

class A {
public:
	explicit A(std::string n) :pointer_member{ new int{1} }, name{ n }{}

	A() : pointer_member{ new int{1} }, name{""}
	{
		std::cout << "This is a default constructor!\n";
	}

	A(const A& obj) : pointer_member{ new int{obj.GetA()} }, name{obj.name}
	{
		std::cout << "This is a copy constructor!\n";
	}

	A(A&& obj) noexcept : pointer_member{ obj.pointer_member }, name{obj.name}
	{
		obj.pointer_member = nullptr;
		std::cout << "Move constructor\n";
	}

	A& operator=(const A& obj)
	{
		std::cout << "Assign operator\n";
		*pointer_member = obj.GetA();
		name = obj.name;
		return *this;
	}

	int GetA() const { return *pointer_member; }

	~A()
	{
		std::cout << "Destructor :"<<name<<"!\n";
		if (pointer_member != nullptr)
		{
			delete pointer_member;
		}
	}
private:
	int* pointer_member;
	std::string name;
};

void ShowA(A&& a)
{
	std::cout << "void ShowA(A&& a) ";
	std::cout << a.GetA()<<"\n";
}

A RetA()
{
	A result{"result"};
	return result;
}

void ShowA(const A& a)
{
	std::cout << "void ShowA(const A& a) ";
	std::cout << a.GetA() << "\n";
}

class IB
{
public:
	virtual std::string getB() = 0;
};

class B : public IB
{
public:
	std::string getB() override { return "B\n"; }
};

class C
{
public:
	C(std::unique_ptr<IB>&& impl) : b{ std::move(impl) } {}
	std::string Say() { return b->getB(); }
private:
	std::unique_ptr<IB> b;
};

int main() {
	//A a("a");
	A* a = new A("a");
	//ShowA(a);
	ShowA(*a);
	//ShowA(std::move( a ));
	ShowA(A());
	//A move_a2{ std::move(a) };
	A move_a2{ std::move(*a) };
	A move_a{ RetA() };
	std::cout << "Program end\n";
	delete a;

	std::unique_ptr<int> p1 = std::make_unique<int>();
	*p1 = 1;
	std::cout << *p1 << "\n";
	std::unique_ptr<int> p2 = std::move(p1);
	std::cout << *p2 << "\n";

	C c{std::make_unique<B>()};
	std::cout << c.Say();

	return 0;
}