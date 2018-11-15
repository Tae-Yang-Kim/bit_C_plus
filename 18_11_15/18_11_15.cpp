#if 1
#include<iostream>
using namespace std;
class Shape {
public:
	int type;
	int test;
	~Shape() {
		cout << "Shape" << endl;
	}
	void show() {
		cout << "type: " << type << endl;
	}
};
class Rect : public Shape {
public:
	int left, top, right, bottom;
	~Rect() {
		cout << "Rect()" << endl;
	}
	void show() {
		cout << endl;
		cout << "left : " << left << endl;
		cout << "top : " << top<< endl;
		cout << "right : " << right<< endl;
		cout << "bottom: " << bottom<< endl;
		cout << endl;
	}
};

int main() {
	Rect r;
	//Rect temp();
	Shape *p = &r;
	p->type = 1;
	//((Rect*)p)->left = 100;
	r.show();
	p++;
	/*p->type = 10;
	r.show();
	p++;
	p->type = 20;
	r.show();
	p++;
	p->type = 30;
	r.show();
	p++;
	p->type = 40;*/
	p->test = 200;
	p->type = 300;
	r.show();
}
#endif


//정적 바인딩의 한계와 동적 바인딩 -> virutal
#if 0
#include<iostream>
using namespace std;
class Animal
{
public:
	virtual void Cry() { cout << "Animal::Cry()" << endl; }
	void Cry(int) {
		cout << "Animal::Cry(int)" << endl;
	}
};
class Dog : public Animal {
public:
	void Cry() {
		cout << "Dog::Cry" << endl;
	}
};

int main() {
	Animal animal;
	Dog dog;
	Animal *an = &dog;
	animal.Cry();
	animal.Cry(3);
	//dog.cry(3);
	dog.Animal::Cry(3);
	dog.Animal::Cry();
	((Dog*)an)->Cry(); //업캐스팅
	an->Cry();
	dog.Cry();
}
#endif

//protectd
#if 0
#include<iostream>
using namespace std;
class A {
protected:
	int a;
};
class Base :public A{
private:
	int one;
protected:
	int two;
public:
	int three;
};

class D : public Base {
public:
	int d;
	void foo() {
		d = two;
	}
};

class E : protected D {
private:
	int m;
public:
	int e;
};
int main() {

	D d;
}
#endif

//test 신경 ㄴ
#if 0
#include<iostream>
using namespace std;

class AAA {
	int aaa;
public:
	void set(int _a) {
		aaa = _a;
	}
	void show() { cout << "aaa : "<<aaa << endl; }
};
class BBB : protected AAA{
	int bbb;
public:
	void set(int _a, int _b) {
		AAA::set(_a);
		bbb = _b;
	}
	void show() { 
		AAA::show();
		cout << "bbb : " << bbb << endl; 
	}
};
class CCC : protected BBB{
	int ccc;
public:
	void set(int _a, int _b, int _c) {
		BBB::set(_a, _b);
		ccc = _c;
	}
	void show() { 
		BBB::show();
		cout << "ccc : " << ccc << endl; 
	}
};

int main() {

	CCC c;
	c.set(10, 20, 30);
	c.show();
	return 0;
}
#endif


//자식 객체 생성시 생성자 소멸자 flow chart

//자식 객체를 생성하면, 다음과 같은 순서로 생성자, 소멸자가 호출된다.
//1. 메모리 할당
//2. 부모의 생성자 호출
//3. 자식의 생성자 호출
//4. 자식의 소멸자 호출
//5. 부모의 소멸자 호출
#if 0
#include<iostream>
using namespace std;
class Base {
	int x;
public:
	Base() { cout << "Base::Base()" << endl; }
	Base(int n) { x = n; cout << "Base::Base(int)" << endl; }
	~Base() { cout << "Base::~Base()" << endl; }
	void show() {
		cout << "x:  " << x << endl;`
	}
};
class D : public Base {
public:
	int y;
	D() { cout << "D:D()" << endl; }
	D(int n):Base(n) { cout << "D:D(int)" << endl; }
	~D() { cout << "D::~D()" << endl; }
};

int main() {
	D d(3);
	d.show();
}

#endif


//상속 예제2
#if 0
#include<iostream>
#pragma warning(disable:4996)
using namespace std;
class people{
	char name[20];
	int age;
public:
	void set(char *_name, int _age) {
		strcpy(name, _name);
		age = _age;
	}
	void show() {
		cout << " name : " << name << endl;
		cout << " age  : " << age  << endl;
	}
};

class Student : public people
{
public:
	int id;
	void set(char *_name, int _age, int _id) {
		people::set(_name, _age);
		id = _id;
	}
	void show() {
		people::show();
		cout << "id   : " << id   << endl;
	}
};

class Professor : public people
{
public:
	int lab;
	void set(char *_name, int _age, int _lab) {
		people::set(_name, _age);
		lab = _lab;
	}
	void show() {
		people::show();
		cout << "lab  : " << lab << endl;
	}
};

class Teacher : public people
{
public:
	int major;
	void set(char *_name, int _age, int _major) {
		people::set(_name, _age);
		major = _major;
	}
	void show() {
		people::show();
		cout << "major : " << major << endl;
	}
};

int main() {
	Professor p;
	Teacher t;
	Student s;

	p.set((char*)"Professor", 35, 507);
	p.show();
	t.set((char*)"Teacher", 24, 505);
	t.show();
	s.set((char*)"Student", 17, 509);
	s.show();
}
#endif

//상속
#if 0
#include<iostream>
using namespace std;
class Base
{
	int a;
public:
	Base(int a=5) {
		xxx = a;
	}
	int xxx;
	void foo() { cout << "Base::foo()" << endl; }
	void show() { cout << "xxx: " << xxx << endl; }
};
class D : private Base // 파생 , 서브 , 자식
{

public:
	D(int x, int y) :yyy(y), Base(x) {}
	/*D(int x, int y) :yyy(y) {
		Base::Base(x);
	}*/
	int yyy;

	void show() {
		Base::show();
		cout << "yyy " << yyy << endl;
	}
	void foo() { cout << "D::foo()" << endl; }
	void goo() { cout << "D::goo()" << endl; }
};

int main()
{
	D d(30, 40);
	Base b(20);
	//   d.xxx = 10;
	d.yyy = 20;
	d.foo();
	d.show();
	b.foo();
}

#endif

//C++에서 지원해주는 STL 이건 list
#if 0
#include<iostream>
#include<list>
#include<algorithm>
#include<vector>
using namespace std;

int main() {
	/*list<int> s;
	s.push_front(10);
	s.push_front(20);
	s.push_front(30);
	s.push_front(40);
	s.push_front(50);
	s.push_front(60);

	s.pop_front();

	list<int>::iterator p = s.begin();
	while (p != s.end()) {
		cout << *p << endl;
		p++;
	}
	reverse(s.begin(), s.end());
	cout << "__________________" << endl;
	p = s.begin();
	while(p != s.end()) {
		cout << *p << endl;
		p++;
	}*/
	vector<int> s;
	s.push_back(10);
	s.push_back(20);
	s.push_back(30);
	s.push_back(40);
	s.push_back(50);
	s.push_back(60);
	
	vector<int>::iterator p = s.begin();
	while (p != s.end()) {
		cout << *p << endl;
		p++;
	}
	reverse(s.begin(), s.end());
	cout << "__________________" << endl;
	p = s.begin();
	while (p != s.end()) {
		cout << *p << endl;
		p++;
	}
}
#endif
//이터레이터 = 반복자

//
#if 0
#include<iostream>
using namespace std;
template<typename T>
struct Node {
	T data;
	Node* next;
	Node(const T& a, Node *n) : data(a), next(n) { }
};

template<typename T>
class slist_iterator {
	Node<T>* current;
public:
	slist_iterator(Node<T>* p = 0):current(p){}

	//++, *, ==, !=가 필요하다.
	inline slist_iterator& operator++() {
		current = current->next;
		return *this;
	}
	inline T& operator*() { 
		return current->data; 
	}
	inline bool operator==(const slist_iterator& s) {
		return current == s.current;
	}
	inline bool operator!=(const slist_iterator& s) {
		return current != s.current;
	}
};

template<typename T>
class slist {
	Node<T> *head;
public:
	slist() :head(0) { }
	void push_front(const T& a) { head = new Node<T>(a, head); }
	T pop_front() {
		Node<T> *temp = new Node<T>(head->data, head);
		T data;
		data = temp->data;
		head = head->next;
		delete temp;

		return data;
	}

	void show() {
		Node<T>* temp;
		for (temp = head; temp != 0; temp = temp->next) {
			cout << "data:  " << temp->data << endl;
		}
	}
	typedef slist_iterator<T> iterator;
	iterator begin() {
		return iterator(head);
	}
	iterator end() {
		return iterator(0);
	}
};

template<typename T1, typename T2>
T1 xfind(T1 first, T1 last, T2 v)
{
	while (first != last && *first != v)
	{
		++first;
	}
	return first == last ? 0 : first;
}

int main() {
	slist<int> s;
	s.push_front(10);
	s.push_front(20);
	s.push_front(30);
	s.push_front(40);
	s.push_front(50);
	s.push_front(60);

	s.show();

	cout << s.pop_front() << endl;

	s.show();
	cout << "-----------------" << endl;
	slist_iterator<int> p1 = xfind(s.begin(), s.end(), 30);
	cout << *p1 << endl;
	cout << "__________________" << endl;
	slist<int>::iterator p = s.begin();
	while (p != s.end())
	{
		cout << *p << endl;
		++p;
	}
}
#endif

//Template를 이용한 stack pop함수 구현

//데이터 컨테이너
#if 0
#include<iostream>
using namespace std;

template<typename T>
struct Node {
	T data;
	Node* next;
	Node(const T& a, Node *n) : data(a), next(n) { }
};

template<typename T>
class slist {
	Node<T> *head;
public:
	slist() :head(0) { }
	void push_front(const T& a) { head = new Node<T>(a, head); }
	T pop_front() {
		Node<T> *temp = new Node<T>(head->data, head);
		T data;
		data = temp->data;
		head = head->next;
		delete temp;

		return data;
	}
	void show() {
		Node<T>* temp;
		for (temp = head; temp != 0; temp = temp->next) {
			cout << "data:  " << temp->data << endl;
		}
	}
};
int main() {
	slist<int> s;
	s.push_front(10);
	s.push_front(20);
	s.push_front(30);
	s.push_front(40);
	s.push_front(50);
	s.push_front(60);

	s.show();

	cout << s.pop_front() << endl;

	s.show();

	//xfind(20, 50, 30);
}
#endif