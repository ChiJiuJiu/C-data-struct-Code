#include<bits/stdc++.h>
using namespace std;
class Person {

	public:
		int a;
		int b;
		int c;
		static int A;

		Person() {

		}

		//初始化列表
		Person(int a, int b, int c):  a(a), b(b), c(c) {

		}

		static void fun(){
			cout << "fun running, get A = " << A << endl;
		}
	
	private:
		static int B;
};

int Person::A = 100;


int main() {
	Person p1;
	Person p2(10,20,30);
	cout << "a = " << p2.a << endl;
	cout << "b = " << p2.b << endl;
	cout << "c = " << p2.c << endl;
	cout << "A = " << Person :: A<< endl;
	Person::fun();
}
