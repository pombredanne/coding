#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>



/*
交换两个数据 不产生临时变量 仅仅适合int类型
a=a^b;  
b=a^b;  
a=a^b; 

或者
a=a+b;  
b=a-b;  
a=a-b; 

*/

//从小到大 进行冒泡排序
void BubbleSort(int num[],int len){
    uint8_t i,j;
    for(i=len-1;i>0;--i)          //从n-1循环的到0，也是n次
		for(j=0;j<i;j++)
			if(num[j]>num[j+1]) //num[j]<num[j+1] 修改次从大到小排序
			{
				int temp=num[j];
				num[j]=num[j+1];
				num[j+1]=temp;
			}
}

void BubbleSort_xor(int arr[], int n)
{
     int i = 0, j =0;     
     for(i = 0; i < n; i++)
       for(j = 0; j < n - 1 - i; j++)
       {
             if(arr[j] > arr[j + 1])
             {
                       arr[j] = arr[j] ^ arr[j+1];
                       arr[j+1] = arr[j] ^ arr[j+1];
                       arr[j] = arr[j] ^ arr[j+1];
             }             
       }     
}

void BubbleSort_add(int arr[], int n)
{
     int i = 0, j =0;     
     for(i = 0; i < n; i++)
       for(j = 0; j < n - 1 - i; j++)
       {
             if(arr[j] > arr[j + 1])
             {
                       arr[j] = arr[j] + arr[j+1];
                       arr[j+1] = arr[j] - arr[j+1];
                       arr[j] = arr[j] - arr[j+1];
             }             
       }     
}

//冒泡排序 从大到小
void BubbleSort_rev(int num[],int len){
    uint8_t i,j;
    for(i=len-1;i>0;--i)          //从n-1循环的到0，也是n次
		for(j=0;j<i;j++)
			if(num[j]<num[j+1]) //num[j]<num[j+1] 修改次从大到小排序
			{
				int temp=num[j];
				num[j]=num[j+1];
				num[j+1]=temp;
			}
}

void BubbleSort_xor_rev(int arr[], int n)
{
     int i = 0, j =0;     
     for(i = 0; i < n; i++)
       for(j = 0; j < n - 1 - i; j++)
       {
             if(arr[j] < arr[j + 1])
             {
                       arr[j] = arr[j] ^ arr[j+1];
                       arr[j+1] = arr[j] ^ arr[j+1];
                       arr[j] = arr[j] ^ arr[j+1];
             }             
       }     
}

void BubbleSort_add_rev(int arr[], int n)
{
     int i = 0, j =0;     
     for(i = 0; i < n; i++)
       for(j = 0; j < n - 1 - i; j++)
       {
             if(arr[j] < arr[j + 1])
             {
                       arr[j] = arr[j] + arr[j+1];
                       arr[j+1] = arr[j] - arr[j+1];
                       arr[j] = arr[j] - arr[j+1];
             }             
       }     
}

//从小到大 选择排序
void SelectSort(int a[],int n)  
{  
    int i,j;  
    for(i=0;i<n-1;i++)              //n个数要进行n-1趟比较，每次确定一个最小数放在a[i]中  
    {  
        int k=i;                    //假设a[0]是最小的数，把下标0放在变量K里面，  
        for(j=i+1;j<n;j++)            
            if(a[k]>a[j])  k=j;     //如果a[k]>a[j] 前面的数比后面的数大，交换下标，此时k指向小的数  
        if(k!=i)  
        {  
            int temp=a[i];  
            a[i]=a[k];  
            a[k]=temp;  
        }  
    }  
  
} 

void SelectSort_xor(int a[],int n)  
{  
    int i,j;  
    for(i=0;i<n-1;i++)              //n个数要进行n-1趟比较，每次确定一个最小数放在a[i]中  
    {  
        int k=i;                    //假设a[0]是最小的数，把下标0放在变量K里面，  
        for(j=i+1;j<n;j++)            
            if(a[k]>a[j])  k=j;     //如果a[k]>a[j] 前面的数比后面的数大，交换下标，此时k指向小的数  
        if(k!=i)  
        {  
            a[i]=a[i]^a[k];  
            a[k]=a[k]^a[i];  
            a[i]=a[i]^a[k];
        }  
    }  
  
} 

void SelectSort_add(int a[],int n)  
{  
    int i,j;  
    for(i=0;i<n-1;i++)              //n个数要进行n-1趟比较，每次确定一个最小数放在a[i]中  
    {  
        int k=i;                    //假设a[0]是最小的数，把下标0放在变量K里面，  
        for(j=i+1;j<n;j++)            
            if(a[k]>a[j])  k=j;     //如果a[k]>a[j] 前面的数比后面的数大，交换下标，此时k指向小的数  
        if(k!=i)  
        {  
            a[i]=a[i]+a[k];  
            a[k]=a[i]-a[k];  
            a[i]=a[i]-a[k];
        }  
    }  
  
} 

void SelectSort_rev(int a[],int n)  
{  
    int i,j;  
    for(i=0;i<n-1;i++)              //n个数要进行n-1趟比较，每次确定一个最小数放在a[i]中  
    {  
        int k=i;                    //假设a[0]是最小的数，把下标0放在变量K里面，  
        for(j=i+1;j<n;j++)            
            if(a[k]<a[j])  k=j;     //如果a[k]>a[j] 前面的数比后面的数大，交换下标，此时k指向小的数  
        if(k!=i)  
        {  
            int temp=a[i];  
            a[i]=a[k];  
            a[k]=temp;  
        }  
    }  
  
} 

void SelectSort_xor_rev(int a[],int n)  
{  
    int i,j;  
    for(i=0;i<n-1;i++)              //n个数要进行n-1趟比较，每次确定一个最小数放在a[i]中  
    {  
        int k=i;                    //假设a[0]是最小的数，把下标0放在变量K里面，  
        for(j=i+1;j<n;j++)            
            if(a[k]<a[j])  k=j;     //如果a[k]>a[j] 前面的数比后面的数大，交换下标，此时k指向小的数  
        if(k!=i)  
        {  
            a[i]=a[i]^a[k];  
            a[k]=a[k]^a[i];  
            a[i]=a[i]^a[k];
        }  
    }  
  
} 

void SelectSort_add_rev(int a[],int n)  
{  
    int i,j;  
    for(i=0;i<n-1;i++)              //n个数要进行n-1趟比较，每次确定一个最小数放在a[i]中  
    {  
        int k=i;                    //假设a[0]是最小的数，把下标0放在变量K里面，  
        for(j=i+1;j<n;j++)            
            if(a[k]<a[j])  k=j;     //如果a[k]>a[j] 前面的数比后面的数大，交换下标，此时k指向小的数  
        if(k!=i)  
        {  
            a[i]=a[i]+a[k];  
            a[k]=a[i]-a[k];  
            a[i]=a[i]-a[k];
        }  
    }  
  
} 

// int main(int argc,char ** argv){

//     uint8_t i;
//     uint8_t num[5];
//     printf("%d",sizeof(int));
//     printf("%d",sizeof(uint8_t));

//     for(i=0;i<5;i++){
//         scanf("%d",&num[i]);
//     }

//     SelectSort_add_rev(num,sizeof(num)/sizeof(int));

//     // printf("%lu",sizeof(num)/sizeof(int));

//     for(i=0;i<5;i++){
//         printf("%d",num[i]);
//     }
//     return 0;
// }