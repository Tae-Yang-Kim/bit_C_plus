#include <iostream>
using namespace std;

#if 0
/*
   변환 연산자, 변환 생성자

   변환 연산자 = 객체가 다른 type으로 변환 될때 호출된다.
			 return type을 명시하지 않는다.
			 반드시 해당 type을 return해야한다.

   변환 생성자 = 파라미터가 1개인 생성자
			다른 type을 해당 객체로 변환할때 사용된다.

						변환 연산자
				  ------------------------->
		user define type                  Other type(char,int,double,float)
				  <-------------------------
						변환 생성자
*/
class Complex {
	int real;
	int image;
public:
	Complex(int a, int b) :real(a), image(b) {} //생성자

	Complex(int r) : real(r), image(0) {} //변환 생성자 , 매개변수가 1개 컴파일러가 아는 타입으로 만들어주려면 매개변수가 1개이어야함.

	operator int() { //변환 연산자, return type을 명시하지않아도 return이 된다. 현재는 int
		return real;
	}
	operator char() {
		return (char)real;
	}
};
int main() {
	int n;
	char ch;
	Complex c(1, 2);

	n = c; //변환 연산자 호출
	ch = c;//변환 연산자 호출
	n = 100;
	c = n; //변환 생성자 호출
}
#endif

#if 0
/*
		 스마트 포인터

   개념 : 임의의 객체가 다른 타입의 포인터 역할을 하는것
   구현원리: ->와 *연산자를 재정의 해서 포인터 처럼 보이게 한다.
   장점: 진짜 포인터가 아니라 객체이다.
	  생성/복사/대입/소멸의 모든과정을 제어 할 수 있다.
	  대표적 활용이 소멸자에서의 자원 해지 기능!
	  아래 클래스가 핵심이다.
*/
class Car {
public:
	void Go() { cout << " Car Go" << endl; }
	~Car() { cout << "Car distroy " << endl; }
};
class Ptr { //스마트 포인터
	Car* obj;
public:
	Ptr(Car* p = 0) :obj(p) {}
	~Ptr() { delete obj; } //자동 삭제 기능을 가지는 스마트 포인터

	Car* operator->() {
		return obj;
	}
	Car& operator*() {
		return *obj;
	}
};
struct AAA {
	int a;
	void foo() {
		cout << "foo()" << endl;
	}
};
int main() {
	AAA *ip;
	Car test;
	//Ptr p = new Car;
	Ptr p = &test;

	(*p).Go();
	p->Go();
	//p->->Go();
	//p.operator->() => 주소값
	//주소값->Go()라서 원래는 ->->이지만 컴파일러가 알아서 처리해줌.

	test.Go();

	ip = new AAA;
	ip->a = 10;
	//*ip.a = 20;
	//ip->foo();
	//(*ip)->foo();

}
//C에서의 연산과 똑같이 해주고 싶은데 C++로 넘어오면서 Class, struct에 func가 들어오게 되고 똑같이 연산하는 방법을
//찾다보니까 연산자를 오버로딩할수 밖에 없었다.
// Lvalue = Rvalue
// Location = Reference
#endif

#if 0
//스마트 포인터 템플릿을 이용한 일반화
//1.template으로 만들기.
struct A {
	int a;
};
class C1 {
public:
	int c1;
};
class C2 {
	int c2;
public:
	void SetData(int r) {
		c2 = r;
	}
	int GetData() {
		return c2;
	}
};
template<typename T>
class Ptr {
	T* obj;
public:
	Ptr(T* p = 0) :obj(p) {}
	~Ptr() { delete obj; }

	T* operator->() { return obj; }
	T& operator*() { return *obj; }
};
int main() {
	Ptr<int>p1 = new int;
	*p1 = 10;
	cout << *p1 << endl;

	Ptr<A>p3 = new A;
	p3->a = 50;
	cout << (*p3).a << endl;
	cout << p3->a << endl;

	Ptr<C1>p4 = new C1;
	p4->c1 = 100;
	cout << (*p4).c1 << endl;
	cout << p4->c1 << endl;

	Ptr<C2>p5 = new C2;
	p5->SetData(60);
	cout << (*p5).GetData() << endl;
	cout << p5->GetData() << endl;
}
#endif

#if 0
//shallow copy보완 + start pointer
template<typename T>
class Ptr {
	T* obj;
	int *ref; //참조계수
public:
	Ptr(T* p = 0) :obj(p) { ref = new int(1); } //생성자
	Ptr(const Ptr& p = 0) :obj(p.obj), ref(p.ref) { ++(*ref); } //복사생성자
	//들어오는값을 고정하기위해 const사용

	~Ptr() {
		if (--(*ref) == 0) { delete obj; delete ref; }
	}

	T* operator->() { return obj; }
	T& operator*() { return *obj; }
};

int main() {
	Ptr<int>p1 = new int;
	*p1 = 10;
	cout << *p1 << endl;

	Ptr<int>p2 = p1; //복사생성자 호출
	cout << *p2 << endl;
}
#endif

#if 0
//내부에서 shallow copy + smart pointer 지원
int main() {
	shared_ptr<int> p1(new int);
	*p1 = 10;

	shared_ptr<int>p2 = p1;;
	cout << *p2 << endl;
}
#endif

#if 0
//ref가 class안에 들어있으면 객체가 생성되야만 ref멤버 변수를 사용할수 있다.
//ref를 내가 필요할때마다 가져다가 쓰기위해서 독립적인 클래스로 바꿔준다.
//ref가 무슨 기능을 하는지 알아야 뽑아서 쓸수있다.
//reference가 무슨기능을 하는지 확인한다.-> 연결된 객체의 갯수 확인
//ref를 따로 클래스를 생성하고 다른 클래스에서 상속받아서 사용하게끔 하고싶은것.
class Cat {
	int mCount;
public:
	Cat() :mCount(0) { } //생성자
	~Cat() { cout << "~Cat" << endl; }
	void incStrong() { ++mCount; }
	void decStrong() { if (!(--mCount)) delete this; }
};
int main() {
	Cat *p1 = new Cat;
	p1->incStrong();

	Cat *p2 = p1;
	p2->incStrong();

	p2->decStrong();
	p1->decStrong();

}
#endif

#if 0
class Cat { //ref의 class화
	int mCount;
public:
	Cat() :mCount(0) { } //생성자
	~Cat() { cout << "~Cat" << endl; }
	void incStrong() { ++mCount; }
	void decStrong() { if (!(--mCount)) delete this; }
};

//객체 안에 있는 참조계수를 자동으로 관리해주는 스마트 포인터를 도입하자.
template<typename T>
class sp {
	T* mPtr;
public:
	sp(T* other = 0) :mPtr(other) { //생성자
		if (mPtr) mPtr->incStrong();
	}
	sp(const sp& p) : mPtr(p.mPtr) { //복사생성자
		if (mPtr) mPtr->incStrong();
	}
	~sp() { //소멸자
		if (mPtr) mPtr->decStrong();
	}
	T* operator->() { return mPtr; }
	T& operator*() { return *mPtr; }

};

int main() {
	sp<Cat>p1 = new Cat;
	sp<Cat>p2 = p1;
}
#endif

#if 0
//reference가 smart pointer안에 있도록 위의 코드에서 수정했는데 내가가리킬 구조체에 ref클래스를 상속해 이어지도록 변경
//overriding:덮어쓰기
class RefBase {
	int mCount;
public:
	RefBase() :mCount(0) { }
	virtual ~RefBase() {}// body가 없는 함수, 가상함수
	void incStrong() { ++mCount; }
	void decStrong() { if (!(--mCount)) delete this; }
};
template<typename T> class sp {
	T* mPtr;
public:
	sp(T* other = 0) : mPtr(other) { //생성자
		if (mPtr) mPtr->incStrong();
	}
	sp(const sp& p) :mPtr(p.mPtr) { //복사생성자
		if (mPtr) mPtr->incStrong();
	}
	~sp() { if (mPtr) mPtr->decStrong(); } //소멸자
	T* operator->() { return mPtr; }
	T& operator*() { return *mPtr; }
};
class Dog : public RefBase { //RefBase를 Dog가 상속받는다.
public:
	~Dog() { cout << "~Dog" << endl; }
};
int main() {
	sp<Dog>p1 = new Dog;
	sp<Dog>p2 = p1;
}
#endif

#if 0
//일반화 프로그래밍
//일반화(Generic) 프로그래밍: 하나의 함수나 클래스를 다양하게 활용할 수 있도록 만드는것
int main() {
	char *s = (char *)"abcdefgh";
	char *p = strchr(s, 'c');
	//strchr : 문자열의 처음부터NULL까지 내가 원하는 문자를 찾아줌.
	printf("%s", p);
}
#endif

#if 0
//위의 코드는 string밖에 찾아주지못한다. -> 일반화를 해보자.
//1.[first, last)사이의 부문 문자열 검색. last는 검색에 포함 안됨.
template<typename T>
T *xfind(T* first, T* last, T v) {
	//first = 문자열 첫주소, last = 문자열 첫주소 + strlen(문자열), v = 찾을 문자
	while (first != last && *first != v) { ++first; }
	return first == last ? 0 : first;
}
int main() {
	char *s = (char *)"abcdefg";
	char *p = xfind(s, s + strlen(s), 'b');
	printf("p : %s\n", p);
	printf("*p : %c\n", *p);
	int x[10] = { 1,2,3,4,5,6,7,8,9 };
	int *ip = xfind(x, x + 10, 6);
	printf("ip : %d\n", ip);
	printf("*ip : %d\n", *ip);
	char str[12] = "hello world";
	char *cp = xfind(str, str + 12, 'w');
	printf("cp : %s\n", cp);
	//printf("*cp : %s\n", *cp);
}
#endif

#if 1
//데이터 컨테이너
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
};
int main() {
	slist<int> s;
	s.push_front(10);
	s.push_front(20);
	s.push_front(30);

}
#endif