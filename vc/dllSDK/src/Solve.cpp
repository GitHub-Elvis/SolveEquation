//Solve.cpp
#include "StdAfx.h"
#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <complex>

/******************************************************************************\
��һ������ x �� n �η�
ע�⣺
1����Ҫʹ�� std::pow ���㸴�����������������鲿Ϊ�㣬ʵ��Ϊ�����������ʧ��
2��std::sqrt ���㸴����ƽ�����ƺ���û�������
\******************************************************************************/
std::complex<double> sqrtn(const std::complex<double>&x,double n)
{
    double  r   =   _hypot(x.real(),x.imag());  //ģ
    if(r > 0.0)
    {
        double  a   =   atan2(x.imag(),x.real());   //����

        n   =   1.0 / n;
        r   =   pow(r,n);
        a  *=   n;
        return std::complex<double>(r * cos(a),r * sin(a));
    }
    return std::complex<double>();
}

/******************************************************************************\
�ȽϷ��̸��Ĵ�С
\******************************************************************************/
static int __cdecl CompareX(const void*elem1,const void*elem2) 
{
    double d1   =   ((const double*)elem1)[2];
    double d2   =   ((const double*)elem2)[2];
    if(d1 < d2)
    {
        return -1;
    }
    if(d1 > d2)
    {
        return 1;
    }
    return 0;
}

/******************************************************************************\
���һԪ�Ĵη���
z   [in]    ����ϵ��
            z[0],z[1] ��ʾ 0 ����ϵ����ʵ�����鲿
            z[2],z[3] ��ʾ 1 ����ϵ����ʵ�����鲿
            z[4],z[5] ��ʾ 2 ����ϵ����ʵ�����鲿
            z[6],z[7] ��ʾ 3 ����ϵ����ʵ�����鲿
            z[8],z[9] ��ʾ 4 ����ϵ����ʵ�����鲿
x   [out]   �������ĸ�
            x[0],x[ 1],x[ 2] �� 1 ������ʵ�����鲿�����ֵ
            x[3],x[ 4],x[ 5] �� 2 ������ʵ�����鲿�����ֵ
            x[6],x[ 7],x[ 8] �� 3 ������ʵ�����鲿�����ֵ
            x[9],x[10],x[11] �� 4 ������ʵ�����鲿�����ֵ
���أ����ĸ�������Χ [0,4]
\******************************************************************************/
int __stdcall SolveEquation(const double z[10],double x[12])
{
    if(NULL == z || NULL == x)
    {//������Ч
        return 0;
    }
    std::complex<double>    xc[4];          //����ĸ���������� 4 ��
    int                     nCount  =   0;  //���ĸ���
    int                     nPower  =   0;  //��ߴ���
    if(fabs(z[8]) > DBL_MIN || fabs(z[9]) > DBL_MIN)
    {//һԪ�Ĵη��̣����㹫ʽ���á�һԪ�Ĵη���-16.04.05.pdf����ʽ(28)��(35)
        nPower  =   4;  //��ߴ���
        const std::complex<double>  a(z[8],z[9]);
        const std::complex<double>  b(z[6],z[7]);
        const std::complex<double>  c(z[4],z[5]);
        const std::complex<double>  d(z[2],z[3]);
        const std::complex<double>  e(z[0],z[1]);
        std::complex<double>        P   =   (c * c + 12.0 * a * e - 3.0 * b * d) * (1.0 / 9.0);
        std::complex<double>        Q   =   (27.0 * a * d * d + 2.0 * c * c * c + 27.0 * b * b * e - 72.0 * a * c *e - 9.0 * b * c * d) * (1.0 / 54.0);
        std::complex<double>        D   =   sqrtn(Q * Q - P * P * P,2.0);
        std::complex<double>        u   =   sqrtn(Q + D,3.0);
        std::complex<double>        v   =   sqrtn(Q - D,3.0);
        if(v.real() * v.real() + v.imag() * v.imag() > u.real() * u.real() + u.imag() * u.imag())
        {//v ��ģ�ϴ�
            u   =   v;
        }
        if(fabs(u.real()) > DBL_MIN || fabs(u.imag()) > DBL_MIN)
        {//u ��Ϊ��
            v   =   P / u;
        }
        else
        {//u Ϊ���� v ҲȡֵΪ��
            u   =
            v   =   0.0;
        }
        std::complex<double>    m;
        std::complex<double>    S   =   b * b - (8.0 / 3.0) * a * c;
        std::complex<double>    T   =   4.0 * a;
        {//���� m,S,T
            std::complex<double>    o1(-0.5,+0.86602540378443864676372317075294);//��
            std::complex<double>    o2(-0.5,-0.86602540378443864676372317075294);//��*��            
            u  *=   T;
            v  *=   T;
            std::complex<double>    t[3]    =
            {
                     u +      v,
                o1 * u + o2 * v,
                o2 * u + o1 * v,
            };
            double  dMod2   =   0.0;    //ģ��ƽ��
            double  dMax2   =   0.0;    //ģƽ�������ֵ
            int     iMax    =   -1;            
            for(int i = 0;i < 3;++i)
            {
                T       =   S + t[i];
                dMod2   =   T.real() * T.real() + T.imag() * T.imag();
                if(iMax < 0 || dMax2 < dMod2)
                {
                    dMax2   =   dMod2;
                    iMax    =   i;
                }
            }
            if(dMax2 > DBL_MIN)
            {
                m   =   sqrtn(S + t[iMax],2.0);
                S   =   2.0 * b * b - (16.0 / 3.0) * a * c - t[iMax];
                T   =   (8.0 * a * b * c - 16.0 * a * a * d - 2.0 * b * b * b) / m;
            }
            else
            {
                m   =
                T   =   0.0;
            }
        }
        v       =   (1.0 / 4.0) / a;
        u       =   sqrtn(S - T,2.0);
        xc[0]   =   (-b - m + u) * v;
        xc[1]   =   (-b - m - u) * v;
        u       =   sqrtn(S + T,2.0);
        xc[2]   =   (-b + m + u) * v;
        xc[3]   =   (-b + m - u) * v;
        nCount  =   4;        
    }
    else if(fabs(z[6]) > DBL_MIN || fabs(z[7]) > DBL_MIN)
    {//һԪ���η��̣����㹫ʽ���á�һԪ���η���-16.04.06.pdf����ʽ(29)��(34)
        nPower  =   3;  //��ߴ���
        const std::complex<double>  a(z[6],z[7]);
        const std::complex<double>  b(z[4],z[5]);
        const std::complex<double>  c(z[2],z[3]);
        const std::complex<double>  d(z[0],z[1]);
        std::complex<double>        P   =   4.0 * (b * b - 3.0 * a * c);
        std::complex<double>        Q   =   4.0 * (9.0 * a * b * c - 27.0 * a * a * d - 2.0 * b * b * b);
        std::complex<double>        D   =   sqrtn(Q * Q - P * P * P,2.0);
        std::complex<double>        u   =   sqrtn(Q + D,3.0);
        std::complex<double>        v   =   sqrtn(Q - D,3.0);
        std::complex<double>        o1(-0.5,+0.86602540378443864676372317075294);//��
        std::complex<double>        o2(-0.5,-0.86602540378443864676372317075294);//��*��
        if(v.real() * v.real() + v.imag() * v.imag() > u.real() * u.real() + u.imag() * u.imag())
        {//v ��ģ�ϴ�
            u   =   v;
        }
        if(fabs(u.real()) > DBL_MIN || fabs(u.imag()) > DBL_MIN)
        {//u ��Ϊ��
            v   =   P / u;
        }
        else
        {//u Ϊ���� v ҲȡֵΪ��
            u   =
            v   =   0.0;
        }
        D       =   (1.0 / 6.0) / a;
        xc[0]   =   (     u +      v - 2.0 * b) * D;
        xc[1]   =   (o1 * u + o2 * v - 2.0 * b) * D;
        xc[2]   =   (o2 * u + o1 * v - 2.0 * b) * D;
        nCount  =   3;        
    }
    else if(fabs(z[4]) > DBL_MIN || fabs(z[5]) > DBL_MIN)
    {//һԪ���η���
        nPower  =   2;  //��ߴ���
        const std::complex<double>  a(z[4],z[5]);
        const std::complex<double>  b(z[2],z[3]);
        const std::complex<double>  c(z[0],z[1]);
        std::complex<double>        D   =   sqrtn(b * b - 4.0 * a * c,2.0);
        std::complex<double>        t   =   (-1.0 / 2.0) / a;

        xc[0]   =   (b + D) * t;
        xc[1]   =   (b - D) * t;
        nCount  =   2;        
    }
    else if(fabs(z[2]) > DBL_MIN || fabs(z[3]) > DBL_MIN)
    {//һԪһ�η���
        nPower  =   1;  //��ߴ���
        const std::complex<double>  a(z[2],z[3]);
        const std::complex<double>  b(z[0],z[1]);
        xc[0]   =  -b / a;
        nCount  =   1;        
    }
    if(nCount > 0)
    {//ɾ����Ч�ĸ�
        int nDel = 0;   //ɾ���ĸ���
        for(int i = 0;i < nCount;++i)
        {
            if(_finite(xc[i].real()) && _finite(xc[i].imag()))
            {//�˸���Ч
                if(nDel)
                {
                    xc[i - nDel]    =   xc[i];
                }
            }
            else
            {//�˸���Ч
                ++nDel;
            }
        }
        nCount -=   nDel;
        if(nCount > 0)
        {
            const double    PI  =   3.1415926535897932384626433832795;
            int p   =   0;            
            for(int i = 0;i < nCount;++i)
            {//�� xc ���� x
                x[p + 2]    =   fabs(atan2(x[p + 1] = xc[i].imag(),x[p] = xc[i].real()));
                if(x[p + 2] > 0.5 * PI)
                {
                    x[p + 2]    =   PI - x[p + 2];
                }
                p  +=   3;
            }
            if(nCount > 1)
            {//����
                qsort(x,nCount,3 * sizeof(double),CompareX);
            }
            {//�������            
                std::complex<double> t;
                int k   =   0;
                int p   =   0;
                for(int i = 0;i < nCount;++i)
                {
                    t   =   0.0;
                    for(k = 0;k <= nPower;++k)
                    {
                        t   =   t * std::complex<double>(x[p],x[p + 1])
                            +   std::complex<double>(z[2 * (nPower - k)],z[2 * (nPower - k) + 1]);
                    }
                    x[p + 2]=   _hypot(t.real(),t.imag());
                    p      +=   3;
                }
            }
        }
    }
    return nCount;
}
