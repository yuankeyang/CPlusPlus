#include <iostream>
using namespace std;
 char a[80];     // �ַ����Ĵ���
char sym;       // �������ж��ַ�
int i=0;        // �ַ����±�
 void E();       // ����ʶ����
void E2();      // ����ʶ����
void T();       // ����ʶ����
void T2();      // ����ʶ����
void F();       // ����ʶ����
void input();   // ���뺯��
void advance(); // �ַ���С���һ����
 void main()
{
        while(1)
       {
        input();
       advance();
       E();                      // ���׸��Ƶ�ʽE��ʼ
       if (sym=='#')
              cout<<"success"<<endl;
       else
              cout<<"fail"<<endl;
       i=0;                      // ��������ʱ���±���0
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
		   printf("��\n");
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
	   	   printf("��\n");
	   	   
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
  
       cout<<"��������ʶ��ľ���:";
       cin>>a;
 
}
  void advance()
{
 
       sym=a[i];
       i++;
	   	   printf("advance\n");
}