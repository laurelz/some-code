#include<iostream>
using namespace std;

//------------------method1-------------------//
class Num {
public:
    Num() {
	    ++n;
		sum += n;
	}
	static void StartUp() {
		n = 0;
		sum = 0;
	}
   	static unsigned int getSum() {
		return sum;
	}
private:
    static unsigned int n;
    static unsigned int sum;	
};
// 静态成员变量须在类体外进行初始化
unsigned int Num::n = 0;
unsigned int Num::sum = 0;

// 输入一个数n，计算1+2+...+n的值。
// 不使用乘除法、while,for,if-else,switch及条件判断语句(A?B:C)
// 方法1,利用静态变量和构造函数，构造函数中对静态变量累加，
// 通过创建n个类的实例，执行构造函数n次，得到静态变量的累加和
void printSum_m1(int n) {
	Num::StartUp();
    Num * pn = new Num[n];
	cout<<Num::getSum()<<endl;
	delete []pn;
	pn = NULL;
}

//------------------method2-------------------//
class Num_Base;
// 定义一个全局变量，一个大小为2的指针数组
// 第一个是指向基类对象的指针，第二个是指向子类对象的指针
Num_Base* Num_Array[2];

class Num_Base {
public:
	virtual int getNum(int n) {
		// 基类虚函数的工作是递归的截至条件，返回0
		// 注意，这里必须返回0
		// 如果返回n，此时的n值为-1（0-1）
	    return 0;
	}
};

class Num_Derived : public Num_Base {
public:
	virtual int getNum(int n) {
		// 通过!!n来确定使用哪一个指针，从而调用不同的虚函数
		// 当n为0时，!!n仍为0(false)，array[0]为基类指针
		// 当n>0时，!!n为1(true)，array[1]为子类指针
		// 子类虚函数的工作是递归调用虚函数(n-1)
	    return Num_Array[!!n]->getNum(n-1) + n;
	}
};
// 第二种方法，通过虚函数和指针数组来实现递归
// 定义一个指针数组，两个指针分别指向基类对象和子类对象
// 不能使用if-else语句，所以将n值转化为0,1值，对应为数组下标
// 从而访问不同的数组元素，分别调用子类和基类的虚函数
void printSum_m2(int n) {
    Num_Base n1;
	Num_Derived n2;
	Num_Array[0] = &n1;
	Num_Array[1] = &n2;
	cout<<Num_Array[1]->getNum(n)<<endl;
}
//------------------method3-------------------//
int main() {
	int n;
	cin>>n;
	printSum_m1(n);
	printSum_m2(n);
}
