#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>
#include<unistd.h>
#include<time.h>
#include<termios.h>
#include"myheader.h"
#include"mysort.h"
#include"myalgorithm.h"


/*
源文件中实现变量    函数的定义  并指定链接范围


*/
//仅能一次初始化

uint32_t score = 0;
uint32_t scheme = 0;


//Matrix Module  矩阵运算

int getTransposeMatrix(uint8_t * matrix,uint8_t row,uint8_t column,uint8_t ** transposeMatrix){
   uint8_t i,j;

   for(i=0;i<row;++i){
        for(j=0;j<column;++j){
            transposeMatrix[j][i]=matrix[row*i+j];
        }
   }

   return 0;
}

int getTransposeMatrix_oneArray(uint8_t * matrix,uint8_t row,uint8_t column,uint8_t * transposeMatrix){
   uint8_t i,j;

   for(i=0;i<row;++i){
        for(j=0;j<column;++j){
            transposeMatrix[column*j+i]=matrix[row*i+j];
        }
   }

   return 0;
}

//C = A*B   要求：A的列数 = B的行数  ==> C的行数 = A的行数；C的列数 = B的列数
void matrixMul(uint8_t **A, uint8_t **B, uint32_t **C, uint8_t rowA, uint8_t columnB, uint8_t columnA){

    for (uint8_t i=0;i<rowA;i++){
        for (uint8_t j=0; j<columnB;j++){
            C[i][j] = 0;
            for (uint8_t k=0;k<columnA;k++){
                C[i][j]+=A[i][k]*B[k][j];
            }
         }
     }
}

void matrixMul_oneArray(uint8_t *A, uint8_t *B, uint32_t *C, uint8_t rowA, uint8_t columnB, uint8_t columnA){
    
    for (uint8_t i=0;i<rowA;i++){
        for (uint8_t j=0; j<columnB;j++){
            C[rowA*i+j] = 0;
            for (uint8_t k=0;k<columnA;k++){
                C[rowA*i+j]+=A[rowA*i+k]*B[columnA*k+j];
            }
         }
     }
}


//————————————————————

void printfBoard(uint8_t board[SIZE][SIZE]){
    uint8_t x,y;
    for(x=0;x<SIZE;x++){
        for(y=0;y<SIZE;y++){
            printf("%d\t",board[x][y]);
        }
    }
}

// Check functions

bool gameWin(void){

    bool success = false;
    uint8_t dataa,datab,datac,datad;
    dataa = (score&0xff);
    datab = (score>>8)&0xff;
    datac = (score>>16)&0xff;
    datad = (score&0xff000000)>>24;

    // return true;
    if(dataa != 0xfe){
        return ((dataa>>8)<<dataa)&0xff;//must false = 0
    }

    if(datab != 0xff){
        return ((datab>>8)<<datab)&0xff;//must false = 0
    }

    if(datac+datad != 0x01){
        return ((datac>>8)<<datac)&0xff;//must false = 0
    }
    success = true;

    return success;
}

bool checkBoard(uint8_t board[SIZE][SIZE]){
    uint8_t i,j;
    int array[SIZE*SIZE];
    bool success = false;
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            array[4*i+j] = board[i][j];
        }
    }

    BubbleSort_xor(array,sizeof(array)/sizeof(int));

    for(i=0;i<SIZE*SIZE;i++){
        if(array[i]!=i+1) success = false;        
    }

    // return true;
    return success;
}

//进制转换

void str2hex(char *source,char *dest,int keyLen){
    uint8_t i;  
    uint8_t highByte, lowByte;  
  
    for (i = 0; i < keyLen; i++)  
    {  
        highByte = source[i] >> 4;  
        lowByte = source[i] & 0x0f ;  
  
        highByte += 0x30;  
  
        if (highByte > 0x39)  
                dest[i * 2] = highByte + 0x07;  
        else  
                dest[i * 2] = highByte;  
  
        lowByte += 0x30;  
        if (lowByte > 0x39)  
            dest[i * 2 + 1] = lowByte + 0x07;  
        else  
            dest[i * 2 + 1] = lowByte;  
    }  
    return ;  
}

//字节流转换为十六进制字符串的另一种实现方式  
void Hex2Str( const char *sSrc,  char *sDest, int nSrcLen )  
{  
    int  i;  
    char szTmp[3];  
  
    for( i = 0; i < nSrcLen; i++ )  
    {  
        sprintf( szTmp, "%02X", (unsigned char) sSrc[i] );  
        memcpy( &sDest[i * 2], szTmp, 2 );  
    }  
    return ;  
}  
  
// //十六进制字符串转换为字节流  
// void HexStrToByte(const char* source, unsigned char* dest, int sourceLen)  
// {  
//     short i;  
//     unsigned char highByte, lowByte;  
      
//     for (i = 0; i < sourceLen; i += 2)  
//     {  
//         highByte = toupper(source[i]);  
//         lowByte  = toupper(source[i + 1]);  
  
//         if (highByte > 0x39)  
//             highByte -= 0x37;  
//         else  
//             highByte -= 0x30;  
  
//         if (lowByte > 0x39)  
//             lowByte -= 0x37;  
//         else  
//             lowByte -= 0x30;  
  
//         dest[i / 2] = (highByte << 4) | lowByte;  
//     }  
//     return ;  
// }  

int main_check(char *key,uint8_t board[SIZE][SIZE],uint8_t keyLen){
    uint8_t i,j;
    char *hexKey;
    hexKey = (char *)malloc(keyLen*2);
    uint8_t * transposeMatrix = NULL;
    uint32_t * resultMatrix = NULL;
    int success = 0;

    // for test
    // score = 131070;
    // for(i=0;i<SIZE;i++){
    //     for(j=0;j<SIZE;j++){
    //         board[i][j]=4*(i)+j+1;
    //     }
    // }
    // only for test

    str2hex(key,hexKey,keyLen);
    transposeMatrix = (uint8_t *)malloc(sizeof(uint8_t *)*SIZE*SIZE);
    //矩阵 乘法
    /*
    board = {
        1 ,2 ,3 ,4 ,
        5 ,6 ,7 ,8 ,
        9 ,10,11,12,
        13,14,15,16
    }

    key = {
        *,*,*,*,
        *,*,*,*,
        *,*,*,*,
        *,*,*,*
    }
    */
    // printf("Done!\n");
    getTransposeMatrix_oneArray((uint8_t *)hexKey,4,4,transposeMatrix);

    // for(i=0;i<4;i++){
    //     for(j=0;j<4;j++){
    //         printf("%d\t",transposeMatrix[4*i+j]);
    //     }
    // }

    // printf("Done!\n");
    uint8_t rev_matrix[16] = {
        1,0,0,0,
        2,1,0,0,
        3,2,1,0,
        9,3,2,1
    };

    // 可逆运算
    //不可逆运算的话需要采用爆破，不过照着key的长度来看 爆破的难度很高啊
    /*
    可逆矩阵
    rev_matrix = {
        1,0,0,0,
        2,1,0,0,
        3,2,1,0,
        9,3,2,1
    }
    对应的逆矩阵为
    uint8_t reverse_matrix[16] = {
        1,0,0,0,
        -2,1,0,0,
        1,-2,1,0,
        -5,1,-2,1
    };
    */
   // 54      51      53      55      157     152     154     165     313     307     309     326     796     787     782     819
   // 
    uint32_t cmp_result[16] = {55, 49, 54, 51, 152, 158, 157, 173, 304, 313, 318, 330, 785, 797, 769, 803};
    resultMatrix  = (uint32_t *)malloc(sizeof(uint32_t)*4*4);
    matrixMul_oneArray((uint8_t *)rev_matrix,transposeMatrix,resultMatrix,4,4,4);

    // printf("\n");
    // for(i=0;i<4;i++){
    //     for(j=0;j<4;j++){
    //         printf("%d\t",resultMatrix[4*i+j]);
    //     }
    // }

    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            uint32_t in = cmp_result[4*i+j]^board[i][j];
            if(resultMatrix[4*i+j] != in) success = rand()%256;
        }
    }
    //直接将运算结果同已知进行比较  算了 这样子简单一点。。。 最好是不直接出现这一段数据，可以想办法 隐藏到其他地方去，或者是在程序运行时根据board进行解密得到key
    //general board xor result 将最后的结果同board xor 得到正确的比较的结果

    return success;
}

int paintFlag(char key[],uint8_t keyLen){
    
    char enc[32]  = {0x65,0x52,0xC0,0x67,0x1F,0xFE,0xF2,0x60,0x70,0x55,0xE0,0xEB,0xBD,0x8C,0x55,0x90,0x16,0x80,0x5D,0x2E,0xA4,0x7D,0xF1,0x86,0x9A,0xCE,0x65,0x5A,0xCF,0x76,0x9D};
    uint8_t s[256] = {0}; //S-box

    rc4_init(s,(uint8_t *)key, strlen(key)); //初始化密钥
    rc4_crypt(s,(uint8_t *)enc,strlen(enc));//解密

    printf("Now you can take the flag:%s\n",enc);


    return 0;
}


//------------


//这个函数没有修改！
void getColor(uint8_t value,char *color,size_t length){
    uint8_t original[] = {8,255,1,255,2,255,3,255,4,255,5,255,6,255,7,255,9,0,10,0,11,0,12,0,13,0,14,0,255,0,255,0};
	uint8_t blackwhite[] = {232,255,234,255,236,255,238,255,240,255,242,255,244,255,246,0,248,0,249,0,250,0,251,0,252,0,253,0,254,0,255,0};
	uint8_t bluered[] = {235,255,63,255,57,255,93,255,129,255,165,255,201,255,200,255,199,255,198,255,197,255,196,255,196,255,196,255,196,255,196,255};
	uint8_t *schemes[] = {original,blackwhite,bluered};

    uint8_t *background = schemes[scheme]+0;
	uint8_t *foreground = schemes[scheme]+1;
	if (value > 0) while (value--) {
		if (background+2<schemes[scheme]+sizeof(original)) {
			background+=2;
			foreground+=2;
		}
	}
	snprintf(color,length,"\033[38;5;%d;48;5;%dm",*foreground,*background);//设置terminal 颜色
} 

void drawBoard(uint8_t board[SIZE][SIZE]){

    uint8_t x,y;
    char reset[] = "\033[m";//关闭所有属性 \033[0m 0 可以省略
    char color[40];
    printf("\033[H");//光标复位

	printf("2048.c %17d pts\n\n",score);

    for(y=0;y<SIZE;y++){
        //每个小块都是 3 * 7
        for(x=0;x<SIZE;x++){
            getColor(board[x][y],color,40);
            printf("%s",color);
            printf("       ");//代表某一个块
			printf("%s",reset);//复位颜色 避免对之后的颜色造成影响
        }
        printf("\n");
        for(x=0;x<SIZE;x++){
            getColor(board[x][y],color,40);
            printf("%s",color);
            //打印文字 块
            if(board[x][y]!=0){
                char s[8];
                snprintf(s,8,"%u",(uint32_t)1<<board[x][y]);
                uint8_t t = 7 - strlen(s);
                printf("%*s%s%*s",t-t/2,"",s,t/2,"");
            }else{
                printf("   ·   ");
            }
            printf("%s",reset);
        }
        printf("\n");

        for(x=0;x<SIZE;x++){
            getColor(board[x][y],color,40);
            printf("%s",color);
            printf("       ");//代表某一个块
			printf("%s",reset);//复位颜色 避免对之后的颜色造成影响
        }
        printf("\n");
    }
    printf("\n");
	printf("        ←,↑,→,↓ or q        \n");
	printf("\033[A");//光标上移 一行
    
}

void addRandom(uint8_t board[SIZE][SIZE]){
    static bool initialized = false;
    uint8_t x,y;
    uint8_t r,len = 0;
    uint8_t n,list[SIZE*SIZE][2];

    if(!initialized){
        srand(time(NULL));
        initialized = true;
    }

    for(x=0;x<SIZE;x++){
        for(y=0;y<SIZE;y++){
            if(board[x][y]==0){
                //Get empty positon to list[0] list[1]
                list[len][0]=x;
                list[len][1]=y;
                len++;
            }
        }
    }
    if(len>0){
        r = rand()%len;
        //Random positon(x,y)
        x = list[r][0];
        y = list[r][1];
        n = (rand()%10)/9+1;//What's result ? 1 OR 2
        board[x][y]=n;
    }

}

void initBoard(uint8_t board[SIZE][SIZE]){
    int i,j;
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            board[i][j]=0;
        }
    }

    addRandom(board);
    addRandom(board);

    drawBoard(board);
    score = 0;
}

//翻转
void rotateBoard(uint8_t board[SIZE][SIZE]){
    uint8_t x,y,tmp;
    uint8_t n = SIZE;
    for(x=0;x<n/2;x++){
        for(y=x;y<n-x-1;y++){
            tmp = board[x][y];
            board[x][y] = board[y][n-x-1];
            board[y][n-x-1]=board[n-x-1][n-y-1];
            board[n-x-1][n-y-1]=board[n-y-1][x];
            board[n-y-1][x]=tmp;
        }
    }
}

uint8_t findTarget(uint8_t array[SIZE],uint8_t x,uint8_t stop){
    uint8_t t;
    //begin direct return
    if(x==0){
        return x;
    }
    for(t=x-1;t>=0;t--){
        if(array[t]!=0){
            if(array[t]!=array[x]){
                return t+1;
            }
            return t;
        }else{
            if(t==stop) return  t;
        }
    }
    return x;

}

//移动 或者 合并 move or merge
bool slideArray(uint8_t array[SIZE]){
    bool success = false;
    uint8_t x,t,stop = 0;
    for(x=0;x<SIZE;x++){
        if(array[x]!=0){
            //找到需要移动到的位置，以及是否需要进行合并
            t = findTarget(array,x,stop);
            //如果目标位置和起始位置不同进行 move or merge
            if(t!=x){
                //判断是否进行合并
                if(array[t]==0){
                    array[t]=array[x];
                }else if(array[t]==array[x]){
                    //increase power of two
                    array[t]++;//2的n次幂
                    //increast score    (uint32_t)1<<array[t] == 2**array[t]    
                    score +=(uint32_t)1<<array[t];
                    
                    stop = t+1;
                }
                array[x]=0;
                success = true;
            }
        }
    }
    return success;

}

bool moveUp(uint8_t board[SIZE][SIZE]){
    uint8_t x;
    bool success = false;
    for(x=0;x<SIZE;x++){
        success |= slideArray(board[x]);
    }

    // printfBoard(board);
    return success;
}


bool moveLeft(uint8_t board[SIZE][SIZE]){
    bool success;
	rotateBoard(board);
	success = moveUp(board);
	rotateBoard(board);
	rotateBoard(board);
	rotateBoard(board);
    // printf("moveleft\n");
	return success;
}

bool moveRight(uint8_t board[SIZE][SIZE]){
    bool success;
	rotateBoard(board);
	rotateBoard(board);
	rotateBoard(board);
	success = moveUp(board);
	rotateBoard(board);
    // printf("moveright\n");
	return success;
}

bool moveDown(uint8_t board[SIZE][SIZE]){
    // printf("movedown\n");
    bool success;
	rotateBoard(board);
	rotateBoard(board);
	success = moveUp(board);
	rotateBoard(board);
	rotateBoard(board);
	return success;
}



void setBufferedInput(bool enable){
    static bool enabled = true;
    static struct termios old;
    struct termios new;

    if(enable && !enabled){
        //restore the terminal
        tcsetattr(STDIN_FILENO,TCSANOW,&old);

        enabled = true;

    }else if(!enable && enabled){
        //get terminal attr
        if(tcgetattr(STDIN_FILENO,&new)==-1){
            printf("tcgetattr Error!\n");
            exit(-1);
        }
        //resotre now terminal attr
        old = new;
        //set c_cflag don't show cursor(光标)  attaction to order
        new.c_lflag &=(~ICANON & ~ECHO);

        tcsetattr(STDIN_FILENO,TCSANOW,&new);

        enabled = false;
    }

}

uint8_t countEmpty(uint8_t board[SIZE][SIZE]){
    uint8_t x,y,count=0;
    for(x=0;x<SIZE;x++){
        for(y=0;y<SIZE;y++){
            if(board[x][y]==0) count++;
        }
    }
    return count;
}

bool findPairDown(uint8_t board[SIZE][SIZE]){
    bool success=false;
    uint8_t x,y;
    for(x=0;x<SIZE;x++){
        for(y=0;y<SIZE-1;y++){
            if(board[x][y]==board[x][y+1]) return true;
        }
    }

    return success;
}

bool gameEnded(uint8_t board[SIZE][SIZE]){
    bool ended = true;
    if(countEmpty(board)>0) return false;

    if(findPairDown(board)) return false;
    rotateBoard(board);
    if(findPairDown(board)) ended = false;
    rotateBoard(board);
    rotateBoard(board);
    rotateBoard(board);

    return ended;
}
void signal_callback_handler(int signum){
    printf("        TERMINATED          \n");
    setBufferedInput(true);//恢复终端初始配置，显示输入字符
    printf("\033[?25h\033[m");//显示光标
    exit(signum);
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




