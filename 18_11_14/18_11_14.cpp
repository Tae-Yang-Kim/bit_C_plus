#include <iostream>
using namespace std;

#if 0
/*
   ��ȯ ������, ��ȯ ������

   ��ȯ ������ = ��ü�� �ٸ� type���� ��ȯ �ɶ� ȣ��ȴ�.
			 return type�� ������� �ʴ´�.
			 �ݵ�� �ش� type�� return�ؾ��Ѵ�.

   ��ȯ ������ = �Ķ���Ͱ� 1���� ������
			�ٸ� type�� �ش� ��ü�� ��ȯ�Ҷ� ���ȴ�.

						��ȯ ������
				  ------------------------->
		user define type                  Other type(char,int,double,float)
				  <-------------------------
						��ȯ ������
*/
class Complex {
	int real;
	int image;
public:
	Complex(int a, int b) :real(a), image(b) {} //������

	Complex(int r) : real(r), image(0) {} //��ȯ ������ , �Ű������� 1�� �����Ϸ��� �ƴ� Ÿ������ ������ַ��� �Ű������� 1���̾����.

	operator int() { //��ȯ ������, return type�� ��������ʾƵ� return�� �ȴ�. ����� int
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

	n = c; //��ȯ ������ ȣ��
	ch = c;//��ȯ ������ ȣ��
	n = 100;
	c = n; //��ȯ ������ ȣ��
}
#endif

#if 0
/*
		 ����Ʈ ������

   ���� : ������ ��ü�� �ٸ� Ÿ���� ������ ������ �ϴ°�
   ��������: ->�� *�����ڸ� ������ �ؼ� ������ ó�� ���̰� �Ѵ�.
   ����: ��¥ �����Ͱ� �ƴ϶� ��ü�̴�.
	  ����/����/����/�Ҹ��� �������� ���� �� �� �ִ�.
	  ��ǥ�� Ȱ���� �Ҹ��ڿ����� �ڿ� ���� ���!
	  �Ʒ� Ŭ������ �ٽ��̴�.
*/
class Car {
public:
	void Go() { cout << " Car Go" << endl; }
	~Car() { cout << "Car distroy " << endl; }
};
class Ptr { //����Ʈ ������
	Car* obj;
public:
	Ptr(Car* p = 0) :obj(p) {}
	~Ptr() { delete obj; } //�ڵ� ���� ����� ������ ����Ʈ ������

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
	//p.operator->() => �ּҰ�
	//�ּҰ�->Go()�� ������ ->->������ �����Ϸ��� �˾Ƽ� ó������.

	test.Go();

	ip = new AAA;
	ip->a = 10;
	//*ip.a = 20;
	//ip->foo();
	//(*ip)->foo();

}
//C������ ����� �Ȱ��� ���ְ� ������ C++�� �Ѿ���鼭 Class, struct�� func�� ������ �ǰ� �Ȱ��� �����ϴ� �����
//ã�ٺ��ϱ� �����ڸ� �����ε��Ҽ� �ۿ� ������.
// Lvalue = Rvalue
// Location = Reference
#endif

#if 0
//����Ʈ ������ ���ø��� �̿��� �Ϲ�ȭ
//1.template���� �����.
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
//shallow copy���� + start pointer
template<typename T>
class Ptr {
	T* obj;
	int *ref; //�������
public:
	Ptr(T* p = 0) :obj(p) { ref = new int(1); } //������
	Ptr(const Ptr& p = 0) :obj(p.obj), ref(p.ref) { ++(*ref); } //���������
	//�����°��� �����ϱ����� const���

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

	Ptr<int>p2 = p1; //��������� ȣ��
	cout << *p2 << endl;
}
#endif

#if 0
//���ο��� shallow copy + smart pointer ����
int main() {
	shared_ptr<int> p1(new int);
	*p1 = 10;

	shared_ptr<int>p2 = p1;;
	cout << *p2 << endl;
}
#endif

#if 0
//ref�� class�ȿ� ��������� ��ü�� �����Ǿ߸� ref��� ������ ����Ҽ� �ִ�.
//ref�� ���� �ʿ��Ҷ����� �����ٰ� �������ؼ� �������� Ŭ������ �ٲ��ش�.
//ref�� ���� ����� �ϴ��� �˾ƾ� �̾Ƽ� �����ִ�.
//reference�� ��������� �ϴ��� Ȯ���Ѵ�.-> ����� ��ü�� ���� Ȯ��
//ref�� ���� Ŭ������ �����ϰ� �ٸ� Ŭ�������� ��ӹ޾Ƽ� ����ϰԲ� �ϰ������.
class Cat {
	int mCount;
public:
	Cat() :mCount(0) { } //������
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
class Cat { //ref�� classȭ
	int mCount;
public:
	Cat() :mCount(0) { } //������
	~Cat() { cout << "~Cat" << endl; }
	void incStrong() { ++mCount; }
	void decStrong() { if (!(--mCount)) delete this; }
};

//��ü �ȿ� �ִ� ��������� �ڵ����� �������ִ� ����Ʈ �����͸� ��������.
template<typename T>
class sp {
	T* mPtr;
public:
	sp(T* other = 0) :mPtr(other) { //������
		if (mPtr) mPtr->incStrong();
	}
	sp(const sp& p) : mPtr(p.mPtr) { //���������
		if (mPtr) mPtr->incStrong();
	}
	~sp() { //�Ҹ���
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
//reference�� smart pointer�ȿ� �ֵ��� ���� �ڵ忡�� �����ߴµ� ��������ų ����ü�� refŬ������ ����� �̾������� ����
//overriding:�����
class RefBase {
	int mCount;
public:
	RefBase() :mCount(0) { }
	virtual ~RefBase() {}// body�� ���� �Լ�, �����Լ�
	void incStrong() { ++mCount; }
	void decStrong() { if (!(--mCount)) delete this; }
};
template<typename T> class sp {
	T* mPtr;
public:
	sp(T* other = 0) : mPtr(other) { //������
		if (mPtr) mPtr->incStrong();
	}
	sp(const sp& p) :mPtr(p.mPtr) { //���������
		if (mPtr) mPtr->incStrong();
	}
	~sp() { if (mPtr) mPtr->decStrong(); } //�Ҹ���
	T* operator->() { return mPtr; }
	T& operator*() { return *mPtr; }
};
class Dog : public RefBase { //RefBase�� Dog�� ��ӹ޴´�.
public:
	~Dog() { cout << "~Dog" << endl; }
};
int main() {
	sp<Dog>p1 = new Dog;
	sp<Dog>p2 = p1;
}
#endif

#if 0
//�Ϲ�ȭ ���α׷���
//�Ϲ�ȭ(Generic) ���α׷���: �ϳ��� �Լ��� Ŭ������ �پ��ϰ� Ȱ���� �� �ֵ��� ����°�
int main() {
	char *s = (char *)"abcdefgh";
	char *p = strchr(s, 'c');
	//strchr : ���ڿ��� ó������NULL���� ���� ���ϴ� ���ڸ� ã����.
	printf("%s", p);
}
#endif

#if 0
//���� �ڵ�� string�ۿ� ã���������Ѵ�. -> �Ϲ�ȭ�� �غ���.
//1.[first, last)������ �ι� ���ڿ� �˻�. last�� �˻��� ���� �ȵ�.
template<typename T>
T *xfind(T* first, T* last, T v) {
	//first = ���ڿ� ù�ּ�, last = ���ڿ� ù�ּ� + strlen(���ڿ�), v = ã�� ����
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
//������ �����̳�
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