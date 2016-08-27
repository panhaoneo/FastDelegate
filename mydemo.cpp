#include <iostream>
#include "FastDelegate.h"

using namespace::std;

class Calculator
{
public:
	int Add(int a, int b)
	{
		return a+b;
	}
	int Sub(int nA, int nB)  
    {  
        return nA - nB;  
    }  
    int Multi(int nA, int nB)  
    {  
        return nA  * nB;  
    }  
};

//���庯��ָ��
typedef fastdelegate::FastDelegate2<int, int, int> AddFunc;
typedef fastdelegate::FastDelegate2<int, int, int> SubFunc;
typedef fastdelegate::FastDelegate2<int, int, int> MultiFunc;

class CalcHander
{
public:
	template <class X, class Y, class Parame1, class Parame2, class RetType>
	void bind_add(Y* x,RetType (X::*func)(Parame1 p1, Parame2 p2))
	{
		pAddFunc = fastdelegate::MakeDelegate(x, func);   //��˼�ǰ�X��ĺ���func�󶨵�Y�����x��ô
	}

	template <class X, class Y, class Parame1, class Parame2, class RetType>
	void bind_sub(Y* x,RetType (X::*func)(Parame1 p1, Parame2 p2))
	{
		pSubFunc = fastdelegate::MakeDelegate(x, func);   //��˼�ǰ�X��ĺ���func�󶨵�Y�����x��ô
	}

	template <class X, class Y, class Parame1, class Parame2, class RetType>
	void bind_multi(Y* x,RetType (X::*func)(Parame1 p1, Parame2 p2))
	{
		pMultiFunc = fastdelegate::MakeDelegate(x, func);   //��˼�ǰ�X��ĺ���func�󶨵�Y�����x��ô
	}


public:
	void Init(Calculator *pCalc)
	{
		bind_add(pCalc, &Calculator::Add);
		bind_sub(pCalc, &Calculator::Sub);
		bind_multi(pCalc, &Calculator::Multi);
	}

	void ExecAdd(int a, int b)
	{
		int sum = pAddFunc(a, b);
		cout<<"sum="<<sum<<endl;
	}
	void ExecSub(int a, int b)
	{
		int sub = pSubFunc(a, b);
		cout<<"sub="<<sub<<endl;
	}
	void ExecMulti(int a, int b)
	{
		int multi = pMultiFunc(a, b);
		cout << "multi="<<multi<<endl;
	}


private:
	AddFunc pAddFunc;
	SubFunc pSubFunc;
	MultiFunc pMultiFunc;

};


int main()
{
	Calculator calculator;				//���󶨵Ķ���
	CalcHander calchander;				//�����󶨶���
	calchander.Init(&calculator);

	calchander.ExecAdd(12,13);			//�൱�ڵ���  calculator.Add(12,13);
	calchander.ExecSub(300,100);
	calchander.ExecMulti(12,13);

	return 0;
}
