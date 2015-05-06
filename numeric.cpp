#include<iostream>
using namespace std;

// 求一个数是否为素数
// 素数是 因子只有1和本身的数
// 判断 1-sqrt(n) 之间的所有奇数是否为其因子
// O(n)
void isPrime(int num) {
	if (num < 2)
		return;
	if ( num == 2 || num == 3) {
        cout<<num<<" ";
		return;
	}
	if (num%2 == 0) {
		return;
	}
    for(int i = 3; i * i <= num; i += 2) {
	    if (num % i == 0) {
			return;
		}
	}
	cout<<num<<" ";
	return;
}

// 求某一范围内的素数
// 通过遍历待查范围，对每个待查数字调用单个素数判断函数
// O(n2)
void isnPrime(int start, int end) {
    for (int i = start; i <= end; i++) {
		isPrime(i);
	}
	cout<<endl;
}

// 使用筛法判断，有额外的空间消耗O(n)
// 建立从1-end的数组tmp,tmp[i] = i
// 2是素数，首先将数组内所有2的倍数置零
// 再将3的倍数置零，迭代进行，
// 直到数组中所有数都被遍历一次
// 重新遍历数组，输出值不为零的下标值，即为所有素数
// 
void isNPrime(int start, int end) {
    int *tmp = new int [end+1];
	for(int i = 2; i <= end;i++) {
	    tmp[i] = i;
	}
	// 把从2开始的所有下标是素数的倍数的值置零
	for(int j = 2; j <= end; j++) {
		// 若值已经为零，则为合数，不需要再重新置一遍零
		/*if (tmp[j] == 0)
			continue;
	    int k = 2;
		while(j*k <= end) {
		    tmp[j*k] = 0;
			++k;
		}
		*/
		// 注释代码的改进版代码，每次判断从j*j开始
		// 因为小于j×j的合数已经被小于j的素数标记过了
		// 减少一部分运算量
		if (tmp[j]) {
		    for(int k = j*j; k <= end; k+=j) 
				tmp[k] = 0;
		}
	}
	for(int i = start; i <= end; i++) {
	    if (tmp[i] != 0)
			cout<<i<<" ";
	}
	cout<<endl;
}

// 改进的筛法求素数方法，线性时间和空间复杂度
// notPrimes数组中，素数被置零，合数被置一
// 一个合数与一个素数的乘积可以表示成
// 一个更大的合数与一个更小的素数的乘积
// eg. 4*3 == 6*2
// 通过对因子的控制，保证每个合数只被置1一次
// 从而保证时间复杂度为O(n)
void isPrimeAdv(int start, int end) {
    int * notPrimes = new int[end+1];
	int * primes = new int[end+1];
	int num_primes = 0;
	for (int i = 2; i <= end; i++)
		notPrimes[i] = 0;

	for (int i = 2; i <= end; i++) {
	    if(!notPrimes[i])
			primes[num_primes++] = i;
		// 每个数字都与primes中的素数相乘，将乘积置一
		// 若该数字是某个素数的倍数，则break，防止重复赋值
		// eg. 
		// i = 4，计算 i*2
		// i = 6，计算 i*2
		// i = 9，计算 i*2，i*3
		for(int j = 0; j < num_primes; j++) {
		    notPrimes[i*primes[j]] = 1;
			if ( i % primes[j] == 0 )
				break;
		}
	}
	for(int i = 0; i < num_primes; i++) {
	    if (primes[i] >= start)
		    cout<<primes[i]<<" ";
	}
	cout<<endl;
}


// 求连续子数组的最大和，并返回最大和，以及最大的连续子数组
// 不考虑数组元素全为负数的情况（此时只需求出数组的最大值）
int getMaxSub(vector<int> &input,vector<int> &output) {
	// 排除异常情况
    if (input.size() <= 0 ) return -1;
	// 建立一个临时数组，保存当前的连续子数组tmp
	// 维护一个临时变量，保存当前的连续子数组和tmpSub
	// 建立一个结果变量，保存当前的最大连续子数组和maxSub
	vector<int>tmp;
	int tmpSub = input[0];
	int maxSub = input[0];
	output.push_back(input[0]);
	tmp.push_back(input[0]);

	for(int i = 1; i < input.size();i++) {
		// 首先把当前元素累加到tmpSub和tmp中
	    tmpSub += input[i];
		tmp.push_back(input[i]);
		if (tmpSub <= 0) {
			// 若当前连续子数组的和小于零，说明到达了拐点
			// 该子数组与之后的元素之和永远小于后面元素
			// 即当前子数组的元素均为无效元素
			// 此时需将当前连续子数组的和置为零，数组清空
			tmpSub = 0;
			tmp.clear();
		}
		if (tmpSub > maxSub) {
			// 若当前连续子数组的和大于当前最大和
			// 将最大和更新为当前连续子数组的和
			// 并将output的旧值清除，把当前的连续子数组作为新值
			// 通过调用assign()函数实现旧值的删除和新值的复制
			maxSub = tmpSub;
			output.assign(tmp.begin(),tmp.end());
		}
	}
	return maxSub;
}

int main() {
    int n = 423;
    int array[] = {1,-2,3,10,-4,7,2,-5};
    vector<int> va(array,array+7);
    vector<int> vb;
    cout<<getMaxSub(va,vb)<<endl;
    for(int i = 0; i < vb.size();i++)
	cout<<vb[i]<<" ";
    cout<<endl;
    isnPrime(101,n);
    isNPrime(101,n);
    isPrimeAdv(101,n);
}
