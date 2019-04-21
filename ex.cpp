#include <iostream>
using namespace std;

class Person {
	public:
	int age;
	Person(const Person &p){
		age = p.age;
	}
	Person(){
	}
	Person(int ages){
		age = ages;
	}
};

int main(){
	Person p1 = Person();
	Person p3 = 20;
	p1.age = 10;
	Person p2(p1);
	cout << p2.age << endl;
	cout << p3.age << endl;
	
	Person *p4 = new Person();
	p4->age = 20;
	cout << "p4µÄÄêÁä" << p4->age << endl; 
}
