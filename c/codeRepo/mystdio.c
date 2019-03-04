
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>



void reverse(char *s, int start, int end)
{ 
    char t; 
    while(end>start){
        t=s[start]; 
        s[start]=s[end]; 
        s[end]=t;
        start++; 
        end--; 
    }  
}

int getStr(char *buffer,int maxLen){
    char c;  // 读取到的一个字符
    int len = 0;  // 当前输入的字符串的长度
    // 一次读取一个字符，保存到buffer
    // 直到遇到换行符(\n)，或者长度超过maxLen时，停止读取
    while( (c=getchar()) != '\n' ){
        buffer[len++]=c;  // 将读取到的字符保存到buffer
        if(len>=maxLen){
            break;
        }
    }
    buffer[len]='\0';  // 读取结束，在末尾手动添加字符串结束标志
    fflush(stdin);  // 刷新输入缓冲区
    return len;
}