#include<iostream>

using namespace std;

// 快排，数组实现
// while循环负责partition，一次partition之后的分割点为start
// 递归实现start之前和之后部分的partition
void quickSort(int *array, int s, int e) {
    if (array == NULL || s >= e) return;
    int * pa = array;
	int start = s;
	int end = e;
	int key = pa[start];
	while (start < end) {
	    while( start < end && key <= pa[end]) end--;
		pa[start] = pa[end];
		while( start < end && key >= pa[start]) start++;
		pa[end] = pa[start];
	}
	pa[start] = key;
	
	quickSort(array,s,start-1);
	quickSort(array,start+1,e);
}

// 堆排的移动节点操作
void shift(int *array, int index, int n) {
    int id = index;
	int child = id * 2 +1;
	while (child < n) {
		// 若待转换节点存在左右字节点，且右子节点更大
	  if (n > child +1 && array[child] < array[child+1]) 
			// 记录最大的节点
			child++;
		// 若父节点已经大于所有子节点，不继续移动
		if (array[child] < array[id]) break;
		else {
		  // 将父节点与较大的字节点进行交换
			int temp = array[child];
			array[child] = array[id];
			array[id] = temp;
			// 交换后，跟踪原来的父节点
			id = child;
			child = id * 2 +1;
		}
		for(int i = 0; i < n; i++) cout<<array[i]<<" ";
		cout<<endl;
	}
	return;
}
// 堆排
void heapSort(int array[], int length) {
  // 首先从最后一个非叶节点开始建立堆，复杂度为O(nlogn)
  for(int i = (length-2)/2; i>=0;i--) 
	    shift(array,i,length);
	// 将堆中的最大值取出，与数组末尾元素交换，待排序堆的长度减一	  
	for(int j = 0; j < length; j++) {
	    int temp = array[0];
		array[0] = array[length - j -1];
		array[length - j -1] = temp;
		// 从根节点开始交换元素；一次交换结束后，根节点的元素为堆的最大值
		shift(array, 0 , length - j -1);
	}
}

// 对数组a中的a[start,mid] 和 a[mid+1,end] 归并，存入b[]中
void merge(int a[], int b[], int start, int mid, int end) {
    int ib = start;
	int s1 = start, e1 = mid;
	int s2 = mid+1, e2 = end;
	while (ib <= end) {
	    if (s1 > e1)
			b[ib++] = a[s2++];
		else if (s2 > e2) 
			b[ib++] = a[s1++];
		else {
		    if (a[s1] <= a[s2])
                b[ib++] = a[s1++];
			else
				b[ib++] = a[s2++];
		}
	}
	return;
}

// 根据归并的粒度，对整个数组进行归并
void mergeLine(int a[], int b[],int seg, int size) {
    int index = 0;
	// 当归并粒度较小时，设置归并的起止点
	while (index <= size - seg*2) {
	    merge(a,b,index,index+seg-1,index+seg*2-1);
		index += seg*2;
	}
	// 当归并至尾端时，判断未归并的长度与粒度seg的大小
	if (index + seg < size)
		// 此时说明未归并的长度大于粒度
		merge(a,b,index,index+seg-1,size-1);
	else
		for(int i = index; i < size; i++)
			b[i] = a[i];
	return;
}

// 归并排序
void mergeSort(int a[], int length) {
  // 建立同样大小的临时数
	int *tmp = new int[length];
	// 开始时，粒度为一，每次归并的元素数为1
	int seg = 1;
	while (seg < length) {
	    // 根据粒度，对整个数组a归并，结果存在tmp中
	    mergeLine(a, tmp, seg, length);
		  seg += seg;
	    // 粒度翻倍，对tmp数组归并，结果存回a中
	  	mergeLine(tmp, a, seg,length);
		  seg += seg;
	}
	delete []tmp;
}
int main() {
    int arraya[10] = {1,5,3,7,0,9,8,4,5,9};
	for(int i = 0; i < 10; i++) {
	   cout<<arraya[i]<<" ";
	}
	cout<<endl;
	mergeSort(arraya,10);
	//heapSort(arraya,10);
	//quickSort(arraya,0,9);
	for(int i = 0; i < 10; i++) {
	   cout<<arraya[i]<<" ";
	}
	cout<<endl;
}
