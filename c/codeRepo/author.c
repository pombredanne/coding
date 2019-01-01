#include<stdio.h>

#include"author.h"


void printAuthorColorful(int color){

    char * line1 = "__________             ._____________\n";             
    char * line2 = "\\______   \\_____     __| _/\\______   \\ ___________\n";
    char * line3 = " |    |  _/\\__  \\   / __ |  |       _// __ \\_  __ \\\n";
    char * line4 = " |    |   \\ / __ \\_/ /_/ |  |    |   \\  ___/|  | \\/\n";
    char * line5 = " |______  /(____  /\\____ |  |____|_  /\\___  >__|\n";   
    char * line6 = "        \\/      \\/      \\/         \\/     \\/       \n";

    // printf("\033[2J\n");
    printf("\033[%dm%s",color,line1);
    printf("\033[%dm%s",color,line2);
    printf("\033[%dm%s",color,line3);
    printf("\033[%dm%s",color,line4);
    printf("\033[%dm%s",color,line5);
    printf("\033[%dm%s",color,line6);
    printf("\033[0m");//关闭所有设置的属性
    printf("\n\n");
}