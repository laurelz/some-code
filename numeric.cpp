#include<iostream>
using namespace std;
#include<vector>

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

// 在一个数组中，只有一个元素只出现一次，其他元素都出现两次
// 找出这个只出现一次的元素
int getSingleNum(int array[],int len) {
	int res = array[0];
	for (int i = 1; i < len; ++i) {
	    res ^= array[i];
	}
	return res;
}

// 在一个数组中，只有两个元素只出现一次，其他元素都出现两次
// 找出这两个只出现一次的元素
// 基于getSingleNum()，可以将这两个数分别置于两个数组中
// 保证每一个数组中，只有一个出现一次的元素，其余均出现两次
// 所以，要求出一个临界值，来将原来的元素分成两类
void getTwoSingleNum(int output[], int array[], int len) {
    int tmp = array[0];
	int res1, res2;
	int num1, num2;
	vector<int> v1, v2;
	// 首先把数组所有元素都做异或运算
	// 得到的结果即为要求的两个元素的异或结果
	// 这个异或结果tmp肯定不为零（因为二者不相同）
	// 所以tmp的二进制表示中肯定有某一位为1
	// 相应的，要求的两个元素也能保证，
	// 其中一个对应位为0,另一个对应位为1
	for (int i = 1; i < len; ++i) {
	    tmp ^= array[i];
	}
	num1 = 1;
	num2 = 0;
	// 找到tmp结果中倒数第一个为1的位，获取该二进制结果
	while(1) {
	    num2 = tmp & num1;
		// 若num2不为零，说明tmp在num1的二进制为1的那一位也为1
		if (num2 != 0)
			break;
		num1 = num1<<1;
	}
	// 把数组分为两部分，一部分对应位为1,另一部分对应位不为1
	// 其中,要求的两个数，必然是一个对应位为1,另一个对应位为0
	// 因此，每一个数组都只有一个出现一次的元素，其他出现两次
	for( int i = 0; i < len; ++i) {
	    if (num1 & array[i])
			v1.push_back(array[i]);
		else
			v2.push_back(array[i]);
	}
	// 此时分别把两个数组的所有元素进行异或运算，得到两个非零值
	res1 = v1[0];
	res2 = v2[0];
	for( int i = 1; i < v1.size(); ++i)
		res1 ^= v1[i];
	for( int i = 1; i < v2.size(); ++i)
		res2 ^= v2[i];
	output[0] = res1;
	output[1] = res2;
}

/* 计算排序数组中，某个元素的出现次数*/
int calcuFirstNum(int array[], int start, int end, int num) {
    if (start > end) return -1;
	int midIndex = (start + end) >> 1;
	int midData = array[midIndex];
	
	if (midData == num ){
		// 若下标为0,或者下标不为零且该元素的前一个元素不为num
	    if (midIndex == 0 || (midIndex > 0 && array[midIndex-1] != num))
			return midIndex;
		else
		    // 否则说明该元素前面还有相同元素，应向前搜索
			end = midIndex - 1;
	}
	else if (midData < num) 
	    start = midIndex + 1;
	else
	    end = midIndex - 1;
	return calcuFirstNum(array, start, end, num);
}

int calcuLastNum(int array[], int length, int start, int end, int num) {
    if (start > end) return -1;
	int midIndex = (start + end) >> 1;
	int midData = array[midIndex];

	if (midData == num) {
	    // 若当前元素为末尾元素，或这不为末尾元素且其后一个元素不为num
	    if (midIndex == length-1 || (midIndex < length -1 && 
				array[midIndex+1] != num))
			return midIndex;
		else 
		    // 否则说明该元素后面还有相同元素，应向后搜索
		    start = midIndex + 1;
	}
	else if (midData < num)
	    start = midIndex + 1;
	else
	    end = midIndex - 1;
	return calcuLastNum(array, length, start, end, num);
}

int getNumTimes(int array[], int length, int k) {
    if (array == NULL || length <= 0)
	    return 0;
	int start = calcuFirstNum(array, 0, length - 1, k);
	int end = calcuLastNum(array, length, 0, length - 1, k);
	if (start != -1 && end != -1)
	    return end - start + 1;
	return 0;
}

void printVal(int start, int end) {
    for(int i = start; i <= end; ++i)
		cout<<i<<" ";
	cout<<endl;
}
void printContinousSequence(int key) {
    if (key <3) return;
	int start = 1; 
	int end = 2;
	int mid = (key + 1) >> 1;
	int curSum = start + end;

	while(start < mid && start >0) {
	    if (curSum == key) {
			printVal(start,end);
			curSum -= start;
			++start;
		}
		if (curSum < key) {
		    ++end;
			curSum += end;
		}
		else {
			curSum -= start;
			++start;
		}
	}
}
// 在旋转递增数组中找到最小值
// eg. 0124567 ; 4567012
// 返回值均为0
// 使用二分法，O(logn)
int findMin(vector<int>& nums) {
    if (nums.size() <= 0)
        return -1;
    int start = 0; 
    int end = nums.size() - 1;
     
    // 把mid初始化为start，当递增数组旋转0个元素时（原递增数组）
    // 此时最小值即为start，且不满足循环条件 start元素 > end元素
    // 可以直接返回mid（start）元素
    int mid = start;
    // 当start元素大于end元素时（旋转后的递增时）循环
    while (nums[start] > nums[end]) {
           
        //若start和end是两个相连的元素，此时返回end即可
        if (end - start == 1)
            return nums[end];
              
        mid = (start + end) >> 1;
        if (nums[mid] > nums[start]) {
            // 说明mid处于递增数组中
            // 若mid的后一个元素小于mid，说明mid后一个元素在递减数组中
            // 并且是递减数组的第一个元素，该元素即为最小值
            if (nums[mid+1] < nums[mid])
                return nums[mid+1];
            // 此时mid大于start，肯定也大于end，所以start指针应指向mid
            start = mid;
        }
        else {
            // 说明mid处于递减数组中
            // 若mid的前一个元素大于mid，说明mid前一个元素在递增数组中
            // 并且是递增数组的最后一个元素，则mid即为最小值
            if (nums[mid-1] > nums[mid])
                return nums[mid];
            // 若mid的前一个元素不大于mid，说明它也处于递减数组中
            end = mid;
        }
    }
    return nums[mid];
}
int main() {
    int n = 423;
	int array[] = {1,-2,3,10,-4,7,2,-5};
	int arraya[] = {1,6,5,2,1,6,9,4,2,4};
	int arrayb[] = {1,2,3,3,3,3,3,4,6};
	int output[2];
	vector<int> va(array,array+7);
	vector<int> vb;
	cout<<getMaxSub(va,vb)<<endl;
	for(int i = 0; i < vb.size();i++)
		cout<<vb[i]<<" ";
	cout<<endl;
	isnPrime(101,n);
	isNPrime(101,n);
	isPrimeAdv(101,n);
	getTwoSingleNum(output,arraya,10);
	for(int i = 0; i < 2; i++)
		cout<<output[i]<<" ";
	cout<<endl;
	cout<<getNumTimes(arrayb,4,3)<<endl;
	printContinousSequence(5);
}
