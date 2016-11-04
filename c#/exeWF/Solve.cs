using System;

public class Solve
{
    private static double DBL_MIN = 2.2250738585072014e-308;
    /******************************************************************************\
    ���һԪ�Ĵη���
    z   [in]    ����ϵ��
                z[0],z[1] ��ʾ 0 ����ϵ����ʵ�����鲿
                z[2],z[3] ��ʾ 1 ����ϵ����ʵ�����鲿
                z[4],z[5] ��ʾ 2 ����ϵ����ʵ�����鲿
                z[6],z[7] ��ʾ 3 ����ϵ����ʵ�����鲿
                z[8],z[9] ��ʾ 4 ����ϵ����ʵ�����鲿
    ���أ��������ĸ� x[]
    x[0],x[ 1],x[ 2] �� 1 ������ʵ�����鲿�����ֵ
    x[3],x[ 4],x[ 5] �� 2 ������ʵ�����鲿�����ֵ
    x[6],x[ 7],x[ 8] �� 3 ������ʵ�����鲿�����ֵ
    x[9],x[10],x[11] �� 4 ������ʵ�����鲿�����ֵ
    \******************************************************************************/
    public static double[] SolveEquation(double[] z)
    {
        if(z == null || z.Length < 10)
        {//������Ч
            return null;
        }
        Complex[]   xc      =   new Complex[4]; //����ĸ���������� 4 ��
        int         nCount  =   0;              //���ĸ���
        int         nPower  =   0;              //��ߴ���
        if(Math.Abs(z[8]) > DBL_MIN || Math.Abs(z[9]) > DBL_MIN)
        {//һԪ�Ĵη��̣����㹫ʽ���á�һԪ�Ĵη���-16.04.05.pdf����ʽ(28)��(35)
            nPower  =   4;  //��ߴ���
            Complex a   =   new Complex(z[8],z[9]);
            Complex b   =   new Complex(z[6],z[7]);
            Complex c   =   new Complex(z[4],z[5]);
            Complex d   =   new Complex(z[2],z[3]);
            Complex e   =   new Complex(z[0],z[1]);
            Complex P   =   (c * c + 12.0 * a * e - 3.0 * b * d) * (1.0 / 9.0);
            Complex Q   =   (27.0 * a * d * d + 2.0 * c * c * c + 27.0 * b * b * e - 72.0 * a * c *e - 9.0 * b * c * d) * (1.0 / 54.0);
            Complex D   =   (Q * Q - P * P * P).sqrtn(2.0);
            Complex u   =   (Q + D).sqrtn(3.0);
            Complex v   =   (Q - D).sqrtn(3.0);
            if(v.x * v.x + v.y * v.y > u.x * u.x + u.y * u.y)
            {//v ��ģ�ϴ�
                u   =   v;
            }
            if(Math.Abs(u.x) > DBL_MIN || Math.Abs(u.y) > DBL_MIN)
            {//u ��Ϊ��
                v   =   P / u;
            }
            else
            {//u Ϊ���� v ҲȡֵΪ��
                u = new Complex();
                v = new Complex();
            }
            Complex    m;
            Complex    S   =   b * b - (8.0 / 3.0) * a * c;
            Complex    T   =   4.0 * a;
            {//���� m,S,T
                Complex o1  =   new Complex(-0.5,+0.86602540378443864676372317075294);//��
                Complex o2  =   new Complex(-0.5,-0.86602540378443864676372317075294);//��*��            
                u  *=   T;
                v  *=   T;
                Complex[]   t   =   new Complex[]
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
                    dMod2   =   T.x * T.x + T.y * T.y;
                    if(iMax < 0 || dMax2 < dMod2)
                    {
                        dMax2   =   dMod2;
                        iMax    =   i;
                    }
                }
                if(dMax2 > DBL_MIN)
                {
                    m   =   (S + t[iMax]).sqrtn(2.0);
                    S   =   2.0 * b * b - (16.0 / 3.0) * a * c - t[iMax];
                    T   =   (8.0 * a * b * c - 16.0 * a * a * d - 2.0 * b * b * b) / m;
                }
                else
                {
                    m = new Complex();
                    T = new Complex();
                }
            }
            v       =   (1.0 / 4.0) / a;
            u       =   (S - T).sqrtn(2.0);
            xc[0]   =   (-b - m + u) * v;
            xc[1]   =   (-b - m - u) * v;
            u       =   (S + T).sqrtn(2.0);
            xc[2]   =   (-b + m + u) * v;
            xc[3]   =   (-b + m - u) * v;
            nCount  =   4;        
        }
        else if(Math.Abs(z[6]) > DBL_MIN || Math.Abs(z[7]) > DBL_MIN)
        {//һԪ���η��̣����㹫ʽ���á�һԪ���η���-16.04.06.pdf����ʽ(29)��(34)
            nPower  =   3;  //��ߴ���
            Complex a   =   new Complex(z[6],z[7]);
            Complex b   =   new Complex(z[4],z[5]);
            Complex c   =   new Complex(z[2],z[3]);
            Complex d   =   new Complex(z[0],z[1]);
            Complex P   =   4.0 * (b * b - 3.0 * a * c);
            Complex Q   =   4.0 * (9.0 * a * b * c - 27.0 * a * a * d - 2.0 * b * b * b);
            Complex D   =   (Q * Q - P * P * P).sqrtn(2.0);
            Complex u   =   (Q + D).sqrtn(3.0);
            Complex v   =   (Q - D).sqrtn(3.0);
            Complex o1  =   new Complex(-0.5,+0.86602540378443864676372317075294);//��
            Complex o2  =   new Complex(-0.5,-0.86602540378443864676372317075294);//��*��
            if(v.x * v.x + v.y * v.y > u.x * u.x + u.y * u.y)
            {//v ��ģ�ϴ�
                u   =   v;
            }
            if(Math.Abs(u.x) > DBL_MIN || Math.Abs(u.y) > DBL_MIN)
            {//u ��Ϊ��
                v   =   P / u;
            }
            else
            {//u Ϊ���� v ҲȡֵΪ��
                u = new Complex();
                v = new Complex();
            }
            D       =   (1.0 / 6.0) / a;
            xc[0]   =   (     u +      v - 2.0 * b) * D;
            xc[1]   =   (o1 * u + o2 * v - 2.0 * b) * D;
            xc[2]   =   (o2 * u + o1 * v - 2.0 * b) * D;
            nCount  =   3;        
        }
        else if(Math.Abs(z[4]) > DBL_MIN || Math.Abs(z[5]) > DBL_MIN)
        {//һԪ���η���
            nPower  =   2;  //��ߴ���
            Complex a   =   new Complex(z[4],z[5]);
            Complex b   =   new Complex(z[2],z[3]);
            Complex c   =   new Complex(z[0],z[1]);
            Complex D   =   (b * b - 4.0 * a * c).sqrtn(2.0);
            Complex t   =   (-1.0 / 2.0) / a;

            xc[0]   =   (b + D) * t;
            xc[1]   =   (b - D) * t;
            nCount  =   2;        
        }
        else if(Math.Abs(z[2]) > DBL_MIN || Math.Abs(z[3]) > DBL_MIN)
        {//һԪһ�η���
            nPower  =   1;  //��ߴ���
            Complex a   =   new Complex(z[2], z[3]);
            Complex b   =   new Complex(z[0],z[1]);
            xc[0]   =  -b / a;
            nCount  =   1;        
        }
        if(nCount > 0)
        {//ɾ����Ч�ĸ�
//             int nDel = 0;   //ɾ���ĸ���
//             for(int i = 0;i < nCount;++i)
//             {
//                 if(_finite(xc[i].x) && _finite(xc[i].y))
//                 {//�˸���Ч
//                     if(nDel)
//                     {
//                         xc[i - nDel]    =   xc[i];
//                     }
//                 }
//                 else
//                 {//�˸���Ч
//                     ++nDel;
//                 }
//             }
//             nCount -=   nDel;
            if(nCount > 0)
            {
                double[] x = new double[3 * nCount];
                int p   =   0;            
                for(int i = 0;i < nCount;++i)
                {//�� xc ���� x
                    x[p + 2]    =   Math.Abs(Math.Atan2(x[p + 1] = xc[i].y,x[p] = xc[i].x));
                    if(x[p + 2] > 0.5 * Math.PI)
                    {
                        x[p + 2] = Math.PI - x[p + 2];
                    }
                    p  +=   3;
                }
                if(nCount > 1)
                {//����
                    double dMax = 0.0;
                    int iMax = 0;
                    int i0 = 0;
                    int k = 0;
                    for (int i = nCount - 1; i > 0; --i)
                    {
                        dMax = x[iMax = i0 = i * 3 + 2];
                        for (k = i0 - 3; k > 0; k -= 3)
                        {
                            if(dMax < x[k])
                            {
                                dMax = x[iMax = k];
                            }
                        }
                        if (iMax != i0)
                        {
                            for (k = 0; k < 3; ++k)
                            {
                                dMax = x[iMax - k];
                                x[iMax - k] = x[i0 - k];
                                x[i0 - k] = dMax;
                            }
                        }
                    }
                }
                {//�������            
                    Complex t = new Complex();
                    int k   =   0;
                    p = 0;
                    for(int i = 0;i < nCount;++i)
                    {
                        t.x = t.y = 0.0;
                        for(k = 0;k <= nPower;++k)
                        {
                            t   =   t * new Complex(x[p],x[p + 1])
                                +   new Complex(z[2 * (nPower - k)],z[2 * (nPower - k) + 1]);
                        }
                        x[p + 2]=   t.Abs();
                        p      +=   3;
                    }
                }
                return x;
            }
        }
        return null;
    }
}