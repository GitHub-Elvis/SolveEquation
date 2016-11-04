using System;

public class Complex
{
    public double x = 0.0;
    public double y = 0.0;
    //���캯��
    public Complex()
    {
        x = y = 0.0;
    }
    //���캯��
    public Complex(double x,double y)
    {
        this.x = x;
        this.y = y;
    }
    //ģ
    public double Abs()
    {
        return Math.Sqrt(x * x + y * y);
    }
    //����
    public double Arg()
    {
        return Math.Atan2(y,x);
    }
    //�� n �η�
    public Complex sqrtn(double n)
    {
        Complex t   =   new Complex();
        double  r   =   x * x + y * y;

        if(r > 0.0)
        {
            n   =   1.0 / n;
            r   =   Math.Pow(r, 0.5 * n);
            double a = Arg() * n;   //����
            t.x =   r * Math.Cos(a);
            t.y =   r * Math.Sin(a);
        }
        return t;
    }
    //�����������������
    public static Complex operator +(Complex c)
    {
        return c;
    }
    //�����������������
    public static Complex operator -(Complex c)
    {
        return new Complex(-c.x, -c.y);
    }
    //��������������ӷ�
    public static Complex operator +(Complex a, Complex b)
    {
        return new Complex(a.x + b.x, a.y + b.y);
    }
    //��������������ӷ�
    public static Complex operator +(double d, Complex c)
    {
        return new Complex(d + c.x, c.y);
    }
    //��������������ӷ�
    public static Complex operator +(Complex c, double d)
    {
        return new Complex(c.x + d, c.y);
    }
    //�����������������
    public static Complex operator -(Complex a, Complex b)
    {
        return new Complex(a.x - b.x, a.y - b.y);
    }
    //�����������������
    public static Complex operator -(double d, Complex c)
    {
        return new Complex(d - c.x, -c.y);
    }
    //�����������������
    public static Complex operator -(Complex c, double d)
    {
        return new Complex(c.x - d, c.y);
    }
    //��������������˷�
    public static Complex operator *(Complex a, Complex b)
    {
        return new Complex(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
    }
    //��������������˷�
    public static Complex operator *(double d, Complex c)
    {
        return new Complex(d * c.x, d * c.y);
    }
    //��������������˷�
    public static Complex operator *(Complex c, double d)
    {
        return new Complex(d * c.x, d * c.y);
    }
    //�����������������
    public static Complex operator /(Complex a, Complex b)
    {
        double m2 = b.x * b.x + b.y * b.y;
        return new Complex((a.x * b.x + a.y * b.y) / m2, (a.y * b.x - a.x * b.y) / m2);
    }
    //�����������������
    public static Complex operator /(Complex c,double d)
    {
        return new Complex(c.x / d, c.y / d);
    }
    //�����������������
    public static Complex operator /(double d,Complex c)
    {
        d /= c.x * c.x + c.y * c.y;
        return new Complex(d * c.x, -d * c.y);
    }
}