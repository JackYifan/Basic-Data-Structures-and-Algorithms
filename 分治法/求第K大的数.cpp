#include<iostream>
using namespace std;
void swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}
//在[left,right]中查找第K大的元素
void findKmax(int a[], int left, int right, int k) {
	int i = left, j = right, partition = a[i];
	//当i==j时没必要再进行交换
	while (i < j) {
		while (i < j&&a[j] >= partition) j--;
		swap(a[i], a[j]);
		while (i < j&&a[i] < partition) i++;
		swap(a[i], a[j]);
	}
	if (right - i + 1 == k) return;
	if (right - i + 1 > k) {
		findKmax(a, i + 1, right, k);
	}
	else {
		findKmax(a, left, i - 1, k - (right - i + 1));
	}

}


int main() {
	int a[] = { 8,3,4,1,9,7,10,6 };
	int k = 4;
	int n = sizeof(a) / sizeof(int);
	findKmax(a, 0, n - 1, k);
	cout << a[n - k];
}