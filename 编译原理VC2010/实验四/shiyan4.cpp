#include <iostream>
using namespace std;
 char a[80];     // 字符串的存入
char sym;       // 单个的判断字符
int i=0;        // 字符串下标
 void E();       // 功能识别函数
void E2();      // 功能识别函数
void T();       // 功能识别函数
void T2();      // 功能识别函数
void F();       // 功能识别函数
void input();   // 输入函数
void advance(); // 字符串小标进一函数
 void main()
{
        while(1)
       {
        input();
       advance();
       E();                      // 从首个推导式E开始
       if (sym=='#')
              cout<<"success"<<endl;
       else
              cout<<"fail"<<endl;
       i=0;                      // 重新输入时，下标置0
       }
      }
 void E()
{
	 printf("E\n");
       T();
       E2();
}
 void E2()
{
	  printf("E2\n");
	  int i=0;
       if(sym=='+')
       {
		      printf("+\n");
			  i=1;
              advance();
              T();
              E2();
       }
       else if (sym != ')' && sym != '#')
       {
              cout<<"error!"<<endl;
              exit(0);
       }
	   if(!i)
		   printf("空\n");
}
 void T()
{
	 	   printf("T\n");
       F();

       T2();


}
 void T2()
{
       printf("T2\n");
	   int i=0;
       if(sym=='*')
       {
		      printf("*\n");
			  i=1;
              advance();
              F();
              T2();
       }
       else  if(sym!='+'&&sym!=')'&&sym!='#')
       {
              cout<<"error!"<<endl;
                            exit(0);
       }
	   if(!i)
	   	   printf("空\n");
	   	   
}
 
void F()
{
	printf("F\n");
       if(sym=='(')
       {
              advance();
              E();
              if(sym==')')
                     advance();
              else
              {
                     cout<<"error!"<<endl;
                            exit(0);
              }
       }
       else if(sym=='i')
       {
		      printf("i\n");
              advance();
       }
       else
       {
              cout<<"error!"<<endl;
                     exit(0);
       }
	   	   
}
 
 
void input()
{
  
       cout<<"请输入需识别的句子:";
       cin>>a;
 
}
  void advance()
{
 
       sym=a[i];
       i++;
	   	   printf("advance\n");
}