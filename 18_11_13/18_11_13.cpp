//cin example
#if 0
#include<iostream>
using namespace std;

int main() {
	char c;
	int a;
	double d;
	//cout << a;
	cin >> c >> a >> d;
	cout << "c : " << c << "  a : " << a << "  d : " << d << endl;

	return 0;
}
#endif


//사용자 타입 cout하기 cin 하기
#if 0
#include<iostream>
using namespace std;
class Complex {
	double real;
	double image;
public:
	Complex(double r, double i) :real(r), image(i) {}
	friend ostream& operator<<(ostream&, const Complex&);
	friend istream& operator>>(istream&, Complex&);
};

ostream& operator<<(ostream& os, const Complex& p) {
	os << p.real << " + " << p.image << "i ";
	return os;
}

istream& operator>>(istream& os, Complex& p) {
	/*int real;
	double image;
	
	os >> real >> image;
	p.real = real;
	p.image = image;*/

	os >> p.real >> p.image;

	return os;
}

int main() {
	Complex c(1.2, 3.2);
	cout << c << endl; //1.2 + 3.2i
	cin >> c;
	cout << c << endl;
}
#endif



#if 0
#include<iostream>
using namespace std;
class A {
public:
	void a(int a) {}
	/*void a(double a) {}*/
};

void main() {
	A x;
	x.a(3.14);
}
#endif

//endl을 함수로
#if 0
#include<stdio.h>
namespace std {
	class ostream {
	public:
		ostream() { printf(" c t o r \n "); }
		ostream& operator<<(ostream& (*_f)(ostream&)) {//endl의 멤버함수를 매개변수로 가짐
			return _f(*this);
		}
		ostream& operator<<(const char* s) {
			printf("%s", s);
			return *this;
		}
		~ostream() {
			printf(" d t o r \n ");
		}
	};
	ostream& endl(ostream& _outs) {
		return _outs << "\n";
	}
	ostream cout;
}

int main() {
	using namespace std;
	cout << "hello" << endl << "world" << endl << "skypwk";
	endl(cout);

	return 0;
}

#endif



//cout의 원리

/*
cout은 ostream의 class의 전역객체이다.
cout.operator<<()함수가 실행되는 원리이다.
자기 자신의 참조를 리턴하기 때문에 출력물을 계속 나열
&를 리턴해서 임시 객체가 만들어지지 않게 한다.
*/
#if 0
#include <stdio.h>
namespace std {
	const char * endl = "\n";
	class ostream {
	public:
		ostream() { printf("c t o r"); }
		ostream& operator<<(const char* s) {
			printf("%s", s);
			return *this;
		}
		ostream& operator<<(int n) {
			printf("%d", n);
			return *this;
		}
		ostream& operator<<(double d) {
			printf("%f", d);
			return *this;
		}
		ostream& operator<<(char* c) {
			printf("%c", c);
			return *this;
		}
		~ostream() { printf("d t o r"); }
	};
	ostream cout;
}

int main() {
	int n = 10;
	using namespace std;
	//std::cout << "n = " << n << std::endl;
	//cout << "hello" << endl << "world" << endl << "skypwk";
	cout << 3.14 << endl;
	////std::cout = "n = " = n = std::endl;
	//((std::cout = "n = ") = n) = std::endl;;
}

#endif

//return value optimization

/*
대부분의 함수는 다음의 3가지 형태로 리턴을 한다.
1. 참조를 리턴하는 경우
2. 포인터를 리턴하는 경우
3. 값을 리턴하는 경우
위의 3가지 경우 중 3번 값을 리턴하는 경우는 임시 객체가 생성되기
때문에 효율성이 상당히 떨어진다
*/
#if 0
#include<iostream>
using namespace std;
class Int32 {
	int _value;
public:
	Int32(int n = 0) :_value(n) {
		cout << "ctor" << endl;
	}
	~Int32() {
		cout << "dtor" << endl;
	}
	Int32(const Int32&) {
		cout << "Copy ctor" << endl;
	}
	Int32& operator=(const Int32&) {
		cout << "assign" << endl;
		return *this;
	}
	friend const Int32 operator+(const Int32& a, const Int32& b);
};
const Int32 operator+(const Int32& a, const Int32& b) {
	/*Int32 temp(a._value + b._value);
	return temp;*/
	return Int32(a._value + b._value);
}

int main() {
	Int32 a = 10, b = 20;
	cout << "-------------------------" << endl;
	//객체 멤버함수 매개변수
	// a      +        b
	Int32 c = a + b;
	cout << "-------------------------" << endl;
}
#endif

//증감 연산자 오버로딩

//전위(prefix)연산자와 후위(postfix)를 구별해야 한다.
//후위 연산자는 전위 연산자와 구별하기 위해 가짜 인수 int을 사용한다.
//전위 연산자는 &리턴한다.
//후위 연산자는 const를 리턴한다.
//++a : int& operator++()
//a++ : const int operator++(int)
#if 0
#include<iostream>
using namespace std;
class Int32 {
public:
	int a;
	int data;
	Int32 (int n = 0, int n2 = 0) : a(n),data(n2) {}
	void show() {
		cout << "a : " << a << "  data: " << data << endl;
	}
	Int32& operator++() {
		++data;
		++a;
		return *this;
	}
	const Int32& operator++(int) {
		const Int32 temp = *this;
		++(this->data);
		return temp;
		//return ++(*this);
		//return (this->data)++;
	}
};

int main() {
	Int32 a(10,20);
	Int32 b = ++++a;
	a.show();
	b.show();
	Int32 c = a++;
	a.show();
	c.show();
}
#endif


//Rules
//아래 연산자는 연산자 재정의 할 수 없다.
//:: , .* sizeof ?: # ##

#if 0
#include<stdio.h>

int main() {
	int a = 10;
	int b;

	b = ++++a;
	printf("b: %d\n", b);
	/*b = a++++;*/
}
#endif



//연산자를 이용한 함수 호출

/*연산자도 함수이다.
User Type에도 연산자를 사용할 수 있다.
User Type을 Built-in Type과 비슷한 프로그램 구문을 지원하기 위해
다형성 지원
+ : operator+()
- : operator-()
/ : operator/()
* : operator*()
*/

#if 0
/*
   연산자를 이용한 함수 호출
   연산자도 함수이다.
   User Type에도 연산자를 사용할 수 있다.
   User Type을 Buillt-in Type과 비슷한 프로그램 구문을 지원하기 위해
   다형성 지원
   + : operator+()
   - : operator-()
   / : operator/()
   * : operator*()
*/
#include<iostream>
using namespace std;
class Int32
{
	int data;
	double d;
public:
	Int32(int n = 0) :data(n) {
		d = (double)n;
	}
	int GetData()const { return data; }
	void show()
	{
		cout << "data:  " << data << " d: " << d << endl;
	}
	const Int32 operator+(double _d)
	{
		Int32 k;
		//k = data + r.GetData();
		k.d = d + _d;
		return k;
	}
	const Int32 operator+(const Int32& r);
	const Int32 operator-(const Int32& r)
	{
		Int32 k;
		k = data - r.GetData();
		return k;
	}
	const Int32 operator*(const Int32& r)
	{
		Int32 k;
		k = data * r.GetData();
		return k;
	}
	const Int32 operator/(const Int32& r)
	{
		Int32 k;
		k = data / r.GetData();
		return k;
	}
	const Int32 operator%(const Int32& r)
	{
		Int32 k;
		k = data % r.GetData();
		return k;
	}
	const Int32 operator+(int i)
	{
		Int32 k;
		k = data + i;
		return k;
	}
	//const Int32 operator+(int i)
	//{
	//   Int32 k;
	//   k = data + i;
	//   return k;
	//}

};
const Int32 Int32::operator+(const Int32& r) {
	Int32 k;
	k = this->data + r.data;
	return k;
}
const Int32 operator+(int i, Int32& r) {//(const Int32)=(int) + (Int32)
	return Int32(i + r.GetData());
}
int main()
{
	Int32 a(10), b(20);
	Int32 c;
	//c = a + b;
	c.show();
	c = a + b;
	c.show();
	c = a - b;
	c.show();
	c = a * b;
	c.show();
	c = a / b;
	c.show();
	c = a % b;
	c.show();
	c = a + 10;
	c.show();
	//c = 10 + a;
	c.show();
	c = a + 3.4;
	c.show();
	c = 10 + a;
	c.show();
	return 0;

}
#endif

//Move constructor

#if 0
#include<iostream>
#pragma warning(disable:4996)
using namespace std;
class Cat {
	char * name;
	int age;
public:
	Cat(const char *s, int a) :age(a) {
		name = new char[strlen(s) + 1];
		strcpy(name, s);
	}
	//copy constructor
	Cat(const Cat& c) :age(c.age) {
		name = new char[strlen(c.name) + 1];
		strcpy(name, c.name);
	}
	//move constrcutor
	Cat(Cat&& c) :name(c.name), age(c.age) {
		c.name = 0;
		c.age = 0;
	}
	void show() {
		if (!name) {
			cout << "할당 되지 않았음" << endl;
			return;
		}
		cout << "name: " << name << "  age:" << age << endl;
	}
	~Cat() { delete[] name; }
};

int main() {
	Cat c1{ "nabi",2 };
	c1.show();
	Cat c2 = c1;
	c2.show();
	Cat c3 = static_cast<Cat&&>(c1); //move constructor
	c3.show();
	c1.show();

	return 0;
}
#endif

//소유권 이전(Move Constructor)

//모든 멤버를 얕은 복사에 원복 객체의 멤버를 0으로 변경한다.
//자원을 복사하지 않고 전달(move)하는개념
#if 0
#include<iostream>
using namespace std;
#pragma warning(disable:4996)

class Cat {
	char * name;
	int age;
public:
	Cat(Cat& c) :name(c.name), age(c.age) {
		c.name = 0;
		c.age = 0;
	}
	Cat(const char* s, int a) :age(a) {
		name = new char[strlen(s) + 1];
		strcpy(name, s);
	}
	void show(){
		if (!name) {
			cout << "할당 되지 않음" << endl;
			return;
		}
		cout << "name:" << name << "  age :" << endl;
	}
	~Cat() { delete[] name; }
};

int main() {
	Cat c1("nabi", 2);
	Cat c2 = c1;

	c1.show();
	c2.show();
}
#endif