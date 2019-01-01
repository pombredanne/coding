#ifndef __H__MYSORT
#define __H__MYSORT

#include<stdint.h>
#include<stdbool.h>
#include<stdio.h>

//冒泡排序的三种实现 从小到大
void BubbleSort(int num[],int len);
void BubbleSort_xor(int arr[], int n);
void BubbleSort_add(int arr[], int n);

void BubbleSort_rev(int num[],int len);
void BubbleSort_xor_rev(int arr[], int n);
void BubbleSort_add_rev(int arr[], int n);


//选择排序  从小到大 
void SelectSort(int a[],int n);
void SelectSort_xor(int a[],int n);
void SelectSort_add(int a[],int n);

void SelectSort_rev(int a[],int n);
void SelectSort_xor_rev(int a[],int n);
void SelectSort_add_rev(int a[],int n);




#endif