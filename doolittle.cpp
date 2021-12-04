#include<iostream>
using namespace std;

/* Doolitte分解将矩阵分解为单位下三角矩阵与上三角矩阵
，进行举证方程的求解。
算法伪代码：
1.定义矩阵与相应向量
系数举证A[n][n]，常数项矩阵b[n]
LU分解中L[n][n],U[n][n],以及中间变量y[n],解向量x[n]。
2. 初始化，并将A举证LU分解
3. 令Ux=y,解出Ly=b中y向量
4. 解出Ux=y中x向量*/

void Doolittle(int n, double *A, double *b)//n为阶数，A为系数矩阵 b为常数矩阵
{
    //系数矩阵与常数矩阵作为doolittle函数输入，并在堆区开辟空间给相应的L，U，y的空间
    double *L = new double[n*n];//开辟L矩阵空间
    double *U = new double[n*n];//开辟U矩阵空间
    double *y = new double[n];//开辟y矩阵空间
    double *x = new double[n];//解向量x最终将以结果输出

    //先将相应矩阵初始化
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            *(U+i*n+j) = 0;
            if (i==j)
            {
                *(L+n*i+j) = 1;
            }
            else
            {
                *(L+i*n+j) = 0;
            }
            
        }
        
    }

    //将矩阵A LU分解，计算矩阵LU的值
    for (int i = 0; i < n; i++)//求U第一行，L第一列
    {
       *(U+i) = *(A+i);//计算U矩阵第一行的值
       *(L+i*n) = (*(A+i*n))/U[0];//计算L矩阵第一列的值 
    }
    int sum = 0;//根据公式u的第i行的第j个元素的值为aij-一个和
    for (int i = 1; i < n; i++)
    {
        for (int j = i; j < n; j++)//这里指向的是第i行的第j个值，sum应该为i-1个和，且对应每行的第j个元素
        {
            for (int k = 0; k < i; k++)
            {
                sum += (*(L+i*n+k))*(*(U+k*n+j));
            }
            *(U+i*n+j) = *(A+i*n+j) - sum;//此处将U第i行元素求出，之后求L第i列元素

            sum = 0;
            for (int s = 0; s < i; s++)
            {
                sum += (*(L+j*n+s))*(*(U+s*n+i));
            }
            *(L+j*n+i) = (*(A+j*n+i)-sum)/(*(U+i*n+i));//此处将L第i行元素求出，进入下一次循环，求i+1行与i+1列

            sum = 0;
        } 

    }

    //Ux=y，求解Ly=b
    *(y) = *(b);//解第一个y

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            sum += (*(L+i*n+j)*(*(y+j)));
        }
        *(y+i) = *(b+i) - sum;//解出剩余y分量
    }
    sum = 0;

    cout<<"解y："<<endl;
    for (int i = 0; i < n; i++)
    {
        cout<<"y"<<i+1<<":"<<*(y+i)<<endl;
    }
    //求解Ux=y
    *(x+n-1) = *(y+n-1)/(*(U+n*n-1));//得出x第n个分量
    for (int i = n-2; i >= 0; i--)
    {
        for (int j = i+1; j < n; j++)
        {
            sum += (*(U+i*n+j))*(*(x+j));
        }
        *(x+i) = (*(y+i)-sum)/(*(U+i*n+i));
    }
    
    cout<<"解x："<<endl;
    for (int i = 0; i < n; i++)
    {
        cout<<"x"<<i+1<<":"<<*(x+i)<<endl;
    }
    delete[] L;
    delete[] U;
    delete[] y;
    delete[] x;
} 

int main()
{
    double *A=new double[9];
    A[0]=1;
    A[1]=0;
    A[2]=1;
    A[3]=0;
    A[4]=1;
    A[5]=0;
    A[6]=2;
    A[7]=0;
    A[8]=1;
    
    double *b = new double[3];
    b[0]=16;
    b[1]=6;
    b[2]=40;
    Doolittle(3,A,b);
    delete[] A;
    delete[] b;
    
    return 0;
}