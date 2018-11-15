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


//����� Ÿ�� cout�ϱ� cin �ϱ�
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

//endl�� �Լ���
#if 0
#include<stdio.h>
namespace std {
	class ostream {
	public:
		ostream() { printf(" c t o r \n "); }
		ostream& operator<<(ostream& (*_f)(ostream&)) {//endl�� ����Լ��� �Ű������� ����
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



//cout�� ����

/*
cout�� ostream�� class�� ������ü�̴�.
cout.operator<<()�Լ��� ����Ǵ� �����̴�.
�ڱ� �ڽ��� ������ �����ϱ� ������ ��¹��� ��� ����
&�� �����ؼ� �ӽ� ��ü�� ��������� �ʰ� �Ѵ�.
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
��κ��� �Լ��� ������ 3���� ���·� ������ �Ѵ�.
1. ������ �����ϴ� ���
2. �����͸� �����ϴ� ���
3. ���� �����ϴ� ���
���� 3���� ��� �� 3�� ���� �����ϴ� ���� �ӽ� ��ü�� �����Ǳ�
������ ȿ������ ����� ��������
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
	//��ü ����Լ� �Ű�����
	// a      +        b
	Int32 c = a + b;
	cout << "-------------------------" << endl;
}
#endif

//���� ������ �����ε�

//����(prefix)�����ڿ� ����(postfix)�� �����ؾ� �Ѵ�.
//���� �����ڴ� ���� �����ڿ� �����ϱ� ���� ��¥ �μ� int�� ����Ѵ�.
//���� �����ڴ� &�����Ѵ�.
//���� �����ڴ� const�� �����Ѵ�.
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
//�Ʒ� �����ڴ� ������ ������ �� �� ����.
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



//�����ڸ� �̿��� �Լ� ȣ��

/*�����ڵ� �Լ��̴�.
User Type���� �����ڸ� ����� �� �ִ�.
User Type�� Built-in Type�� ����� ���α׷� ������ �����ϱ� ����
������ ����
+ : operator+()
- : operator-()
/ : operator/()
* : operator*()
*/

#if 0
/*
   �����ڸ� �̿��� �Լ� ȣ��
   �����ڵ� �Լ��̴�.
   User Type���� �����ڸ� ����� �� �ִ�.
   User Type�� Buillt-in Type�� ����� ���α׷� ������ �����ϱ� ����
   ������ ����
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
			cout << "�Ҵ� ���� �ʾ���" << endl;
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

//������ ����(Move Constructor)

//��� ����� ���� ���翡 ���� ��ü�� ����� 0���� �����Ѵ�.
//�ڿ��� �������� �ʰ� ����(move)�ϴ°���
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
			cout << "�Ҵ� ���� ����" << endl;
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