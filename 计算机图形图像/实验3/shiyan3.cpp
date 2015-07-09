#include<stdio.h>  
#include<string.h>  
#include<conio.h>  
#include<windows.h>  
#include<graphics.h>   
#include<math.h>  
#define N 1000  
int n;//控制点的个数  
struct Point  //控制点的坐标  
{  
    double x;  
    double y;  
}point[N];  
void init()  //输入控制点的坐标  
{  
    int i;  
    printf("请输入控制点的个数: ");  
    scanf("%d",&n);  
    printf("请输入控制点的坐标位置\n");  
    for(i=0;i<n;i++)  
    scanf("%lf %lf",&point[i].x,&point[i].y);  
}  
void sol1()  //绘制控制多边形的轮廓  
{  
    int i;  
    setcolor(RED);  
    for(i=0;i<n-1;i++)  
    line((int)point[i].x,(int)point[i].y,(int)point[i+1].x,(int)point[i+1].y);  
}  
double sol2(int nn,int k)  //计算多项式的系数C(nn,k)  
{  
    int i;  
    double sum=1;  
    for(i=1;i<=nn;i++)  
		sum*=i;  
    for(i=1;i<=k;i++)  
		sum/=i;  
    for(i=1;i<=nn-k;i++)  
		sum/=i;  
    return sum;  
}  
void sol3(double t)  //计算Bezier曲线上点的坐标  
{  
    double x=0,y=0,Ber;  
    int k;  
    for(k=0;k<n;k++)  
    {  
        Ber=sol2(n-1,k)*pow(t,k)*pow(1-t,n-1-k);  
        x+=point[k].x*Ber;  
        y+=point[k].y*Ber;  
    }  
    putpixel((int)x,(int)y,GREEN);  
}  
void sol4()  //根据控制点，求曲线上的m个点  
{  
    int m=500,i;  
    for(i=0;i<=m;i++)  
    sol3((double)i/(double)m);  
}  
int main()  
{  
    init();  
    initgraph(640, 480);   
    sol1();  
    sol4();  
    getch();  
    closegraph();  
    return 0;  
}  