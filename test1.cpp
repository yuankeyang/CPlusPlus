#include<iostream>
using namespace std;
class A{
public:
  void func1(){cout<<"Class A:func1()"<<endl;}
private:
  void func2(){cout<<"Class A:func2()"<<endl;}
protected:
  void func3(){cout<<"Class A:func3()"<<endl;}
};
class B:public A{
public:
  void func1(){cout<<"Class B:func1()"<<endl;}
};
int main(){
  cout<<"¼Ì³Ð£º"<<endl;
  A *a=new A();
  B *b=new B();
  A *p=new B();
  a->func1();
  b->func1();
  //b->func2();
  //b->func3();
  p->func1();
  return 0;
}
