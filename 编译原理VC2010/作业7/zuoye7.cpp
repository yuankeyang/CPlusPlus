#include<iostream>
#include<stdlib.h>
using namespace std;
int f(int &,int &);
int f1(int x,int* py,int** ppz){
	**ppz+=1;
	*py+=2;
	x+=3;
	return x+*py+**ppz;
}
int main(){
	//int a=3;
	int c=4;
	int* b=&c;
	int** a=&b;
	//cout<<f(a,a);
	cout<<f1(c,b,a);
	system("pause");
	return 0;
}
int f(int &x,int &y){
	x=x+1;
	y=y+2;
	return x+y;
}