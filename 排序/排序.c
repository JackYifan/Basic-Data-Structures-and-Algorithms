#include<stdio.h>
#include<stdlib.h>
void swap(int*p1, int*p2) {
	int t;
	t = *p1;
	*p1 = *p2;
	*p2 = t;
}
void printArray(const int* array, int size) {
	for (int i = 0; i < size; i++)
		printf("%d ", array[i]);
	printf("\n");
}
void selectionSort(int*array, int size) {
	int minv, min;
	//[i,size-1]
	for (int i = 0; i < size - 1; i++) {
		minv = array[i];
		min = i;
		for (int j = i + 1; j < size; j++) {
			if (array[j] < minv) {
				minv = array[j];
				min = j;
			}
		}
		if (min - i) swap(&array[i], &array[min]);
		printf("%d: ", i);
		printArray(array, size);
	}
}
//插入排序是稳定排序，当相等时不插入 最好情况是O(n)
void insertionSort(int*array, int size) {
	//0号默认排序
	int x, j;
	for (int i = 1; i < size; i++) {
		x = array[i];
		for (j = i; j > 0 && array[j - 1] > x; j--) {
			array[j] = array[j - 1];
		}
		array[j] = x;
		printf("%d: ", i);
		printArray(array, size);
	}
}

//冒泡排序两个元素相等时不交换，所以是稳定的
void bubbleSort(int* array, int size) {
	int flag = 1;
	for (int i = 0; flag&&i < size - 1; i++) {
		flag = 0;
		for (int j = 0; j < size - i - 1; j++) {
			if (array[j] > array[j + 1]) swap(&array[j], &array[j + 1]);
			flag = 1;
		}
		printf("%d: ", i);
		printArray(array, size);
	}
}
//标号从0开始
void percolateDown(int k, int *array, int size) {
	int x;
	x = array[k];
	int i, child;
	for (i = k; i * 2 + 1 <= size - 1; i = child) {
		child = i * 2 + 1;
		if (child != size - 1 && array[child + 1] > array[child]) child++;
		if (x < array[child]) array[i] = array[child];
		else break;
	}
	array[i] = x;
}
void heapSort(int*array, int size) {
	//把数组改造成堆，找到最后一个有儿子的结点并全部做下滤操作
	for (int i = size / 2 - 1; i >= 0; i--) {
		percolateDown(i, array, size);
	}
	for (int i = size - 1; i > 0; i--) {
		swap(&array[0], &array[i]);
		percolateDown(0, array, i);
	}
}
void merge(int*a,int*t,int li,int ri,int re){
	int begin=li;
	int le=ri-1;
	int ti=li;
	while(li<=le&&ri<=re){
		if(a[li]<=a[ri]) t[ti++]=a[li++];
		else t[ti++]=a[ri++];
	}
	while(li<=le) t[ti++]=a[li++];
	while(ri<=re) t[ti++]=a[ri++];
	for(int i=begin;i<=re;i++){
		a[i]=t[i];
	}
}
// [left,right]
void msort(int*array,int*tmp,int left ,int right){
	if(left >= right ) return ;
	int mid;
	mid=(left+right)/2;
	msort(array,tmp,left,mid);
	msort(array,tmp,mid+1,right);
	merge(array,tmp,left,mid+1,right);
}
void mergeSort(int*array,int size){
	int*tmp=(int*)malloc(sizeof(int)*size);
	if(!tmp) return ;
	msort(array,tmp,0,size-1);
	free(tmp);
}
int mediumPivot(int*a,int left,int right){
	int mid=(left+right)/2;
	if(a[left]>a[mid]) swap(&a[left],&a[mid]);
	if(a[left]>a[right]) swap(&a[left],&a[right]);
	if(a[mid]>a[right]) swap(&a[mid],&a[right]);
	swap(&a[mid],&a[right-1]);
	return a[right-1];
}
const int CUTOFF=3;
void quick_sort(int*a,int left ,int right){
	int pivot ;
	if(right-left<CUTOFF) insertionSort(a+left,right-left+1);
	else{
		pivot = mediumPivot(a,left,right);
		int i=left+1;
		int j=right-2;
		while(1){
			while(a[i]<pivot) i++;
			while(a[j]>pivot) j--;
			if(i<j) swap(&a[i],&a[j]);
			else break;
		}
		swap(&a[i],&a[right-1]);
		quick_sort(a,left,i-1);
		quick_sort(a,i+1,right);
	}
	

}
void quickSort(int*array,int size){
	quick_sort(array,0,size-1);
}
int main() {
	int array[6] = { 19,54,4,30,70,2 };
	// selectionSort(array,6);
	// insertionSort(array,6);
	// bubbleSort(array,6);
	// heapSort(array, 6);
	// mergeSort(array,6);
	quickSort(array,6);
	printArray(array, 6);
	return 0;
}