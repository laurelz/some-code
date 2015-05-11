#include<iostream>
#include<cmath>

using namespace std;

// 把n个骰子扔到地上，向上一面的点数总和为s
// 输入n，输出s所有可能的值，及其对应的概率
// numbers为骰子个数，DiceNum为骰子点数
void calcuNDice(int numbers, int DiceNum) {
    if (numbers <1)
		return;
	// 定义一个指针数组，每个指针指向一个出现次数序列
	// numbers个骰子，每个骰子有DiceNum个点，
	// 所以s的值域为[numbers,numbers*DiceNum]
	// 令两个数组的长度均为numbers×DiceNum+1
	// 保证可以直接通过p[i][j]访问到和为j的次数
	int * p[2];
	p[0] = new int[numbers * DiceNum + 1];
	p[1] = new int[numbers * DiceNum + 1];
	for (int i = 0; i < numbers*DiceNum+1; ++i) {
	    p[0][i] = 0;
		p[1][i] = 0;
	}

	// flag用于控制指针数组中两个指针的相互转换
	// flag = （1-flag）
	int flag= 0 ;

	// 把第一个数组p[0]初始化为n为1时的结果
	// p[0][i] = 1
	for (int i = 1; i <= DiceNum; ++i)
		p[flag][i] = 1;

	// 开始计算骰子个数大于1时的点数值及概率
	// num表示骰子的个数
	for (int num = 2; num <= numbers; ++num) {
		// 首先////\\;'';把赋值数组p[flag]的[0,num-1]值reset为0
	    for (int i = 0; i < num; ++i) 
			p[1-flag][i] = 0;

		// i 控制有num个骰子时，s的值域
		for (int i = num; i <= num*DiceNum; ++i) {
			// 首先把待赋值数组的当前s值reset为0
			p[1-flag][i] = 0;

			// 利用p[x][i] = p[y][i-1] + ... + p[y][i-DiceNum]
			for (int j = 1; j <= DiceNum && j <= i; ++j)
			    p[1-flag][i] += p[flag][i-j];
		}
		// 下一次循环之前，要把flag对应的0,1值对换
		// 保证p[1-flag]是待赋值数组，p[flag]是上一次的数组
		flag = 1- flag;
	}
	
	// 共有DiceNum^numbers种可能
	double total = pow((double)DiceNum, numbers);
	for (int i = numbers; i <= numbers*DiceNum; ++i)
		cout<<"Probability of sum "<<i<<" is "<<(double)(p[flag][i]) / total<<endl;
	delete[] p[0];
	delete[] p[1];
}

int main() {
    int num = 3;
	int dice = 6;
	calcuNDice(num,dice);
}
