#include "msp.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "../inc/Clock.h"
#include "../inc/UART0.h"
#include "../inc/Reflectance.h"
#include "../inc/Motor.h"
#include "../inc/PWM.h"
#include "../inc/Bump.h"
#include "../inc/LaunchPad.h"
//鍙傛暟瀹氫箟
uint16_t L = 6000;
uint16_t R = 6000;
uint16_t l = 4500;
uint16_t r = 4500;
uint8_t Data;//绾㈠璇诲彇鐨勬暟鍊�
uint8_t MOD1_Finished = 0;//绗竴闃舵鏄惁瀹屾垚
uint8_t MOD2_Finished = 0;
uint8_t ii = 0;
uint8_t flag = 0;//鍓嶅悗宸﹀彸杞悜鏍囧織
char path_maze[49];//璁板綍灏忚溅涓�闃舵鐨勮矾绾�


void Port2_Init(void){
    P2->SEL0 = 0x00;
    P2->SEL1 = 0x00;
    P2->DS = 0x77;
    P2->DIR = 0x07;
    P2->OUT = 0x00;
}

void Port2_Output(uint8_t data){
    P2->OUT = data;
}
//瀛楃涓叉浛鎹�
char* ReplaceSubStr(const char* str, const char* srcSubStr, const char* dstSubStr, char* out)
 {                                                         //this is a string replace function
    const char *p;
    char *_out = out;
    const char *_str = str;
    const char *_src = srcSubStr;
    const char *_dst = dstSubStr;
    int src_size = strlen(_src);
    int dst_size = strlen(_dst);
    int len = 0;

    do
    {
        p = strstr(_str, _src);
        if(p == 0)
    {
        strcpy(_out, _str);
        return out;
    }

    len = p - _str;
    memcpy(_out, _str, len);
    memcpy(_out + len, _dst, dst_size);
    _str = p + src_size;
    _out = _out + len + dst_size;
    } while(p);
    return out;
}

void main1(void)
{
    uint8_t Data;
    UART0_Initprintf();
    Clock_Init48MHz();
    Reflectance_Init();
//    Motor_Init();
//    Port2_Init();

    while(1){
        Data = Reflectance_Read(1000);
        printf("%02x\n",Data);
        Clock_Delay1ms(10);
    }
}

void MOD1(){
        Port2_Output(0x07);
        Data = Reflectance_Read(1000);
        printf("%02x\n",Data);
 //       Clock_Delay1ms(10);
        switch(Data){
            case 0x18:
                Motor_Forward(l,r);
                break;
            case 0xFF://T锟斤拷路锟斤拷 十锟斤拷路锟斤拷//宸﹁浆
            case 0x7F:
            case 0xFE:
            case 0x7E:
                  //  Motor_Forward(l,r);
                   // Clock_Delay1ms(15);
                    Data = Reflectance_Read(1000);
                    if(Data== 0xE0||Data==0xC0||Data==0x00||Data==0x80 || Data == 0x60 || Data == 0x40)
                    {
                        Motor_Left(L,R+1000);
                        Clock_Delay1ms(280);
                        flag = 3;
                    }
                    else
                    {
                        Motor_Left(L,R+1000);
                        Clock_Delay1ms(280);
                        flag = 3;
                    }
                break;
            case 0xF0://锟斤拷转 锟斤拷 直锟斤拷 + 锟斤拷转
            case 0xF8://宸﹁浆
            case 0x78:
                    Motor_Forward(l,r);
                    Clock_Delay1ms(15);
                    Data=Reflectance_Read(1000);
                    if(Data==0x18||Data==0x38||Data==0xB8||Data==0x30||Data==0xB0||Data==0x06||Data==0xC0||Data==0xE0||Data==0x70||Data==0x30||Data==0xC0||Data==0x60||Data==40)
                    {
                         Motor_Left(L,R+1000);
                         Clock_Delay1ms(280);
                         flag = 3;
                    }
                    else
                    {
                          Motor_Left(L,R+1000);
                          Clock_Delay1ms(280);
                          flag = 3;
                    }

                 break;

            case 0x0F://锟斤拷转 锟斤拷 直锟斤拷+锟斤拷转
            case 0x1F://鍙宠浆+鍙宠浆|鐩磋
            case 0x1E:
                Motor_Forward(L,R);
                Clock_Delay1ms(50);
                Data = Reflectance_Read(1000);

                if(Data == 0x0F || Data == 0x1F || Data == 0x1E || Data == 0x60 || Data == 0xC0 || Data == 0x40){
                    Motor_Forward(L,R);
                    Clock_Delay1ms(60);
                    Data = Reflectance_Read(1000);
                    if(Data == 0x00){
                        Motor_Right(L+1000,R);
                        Clock_Delay1ms(370);
                        Motor_Forward(L,R);
                        Clock_Delay1ms(130);
                        Motor_Left(L,R+1000);
                        Clock_Delay1ms(30);
                        flag = 4;
                    }
                    else{
                        Motor_Forward(L,R);
                        flag = 1;
                    }

                }
                 break;


            case 0x08:
            case 0x0C:
                Port2_Output(0x07);
                Motor_Right(l,r);
                break;
            case 0x10:
            case 0x30:
                Port2_Output(0x07);
                Motor_Left(l,r);
                break;
            case 0x00:
                Motor_Left(L,R);
                Clock_Delay1ms(350);
                flag = 2;
                break;
            case 0xDB:
            case 0x5B:
            case 0x49:
            case 0x92:
            case 0x6D:
            case 0xC9:
            case 0x9B:
                Motor_Left(L,R);
                Clock_Delay1ms(630);
                Motor_Forward(L,R);
                Clock_Delay1ms(100);
                MOD1_Finished = 1;
                break;
            default:
                Motor_Stop();
                break;

        }
        switch(flag){               //select the flag then S B L R means qian hou zuo you in chinese
            case 1:path_maze[ii]='S';ii++;break;
            case 2:
                    if(path_maze[ii-1]=='B') {}else {path_maze[ii]='B';ii++;}break;//if already has a B then
            case 3:path_maze[ii]='L';ii++;break;                                  //we won't write a B
            case 4:path_maze[ii]='R';ii++;break;
            default:break;
        }
            flag=0;
}

void MOD2(){
//    Data = Reflectance_Read(1000);
//    if((Data == 0x1F)||(Data == 0x0F)||(Data == 0x07)||(Data == 0xF8)||(Data == 0xF0)||(Data == 0xE0)||(Data==0xFF))
//       {
//           switch(path_maze[ii]){
//               case 'L':
//                        Motor_Forward(l,r);
//                        Clock_Delay1ms(25);
//                        Motor_Left(L,R+1000);
//                        Clock_Delay1ms(300);
//                        break;
//               case 'S':
//                        Motor_Forward(L,R);
//                        Clock_Delay1ms(200);
//                        break;
//               case 'R':
//                        Motor_Forward(l,r);
//                        Clock_Delay1ms(25);
//                        Motor_Right(L+1000,R);
//                        Clock_Delay1ms(300);
//                        break;
//           }
//           ii--;
//       }
    Port2_Output(0x06);
    Data = Reflectance_Read(1000);
    switch(Data){
        case 0x18:
            Motor_Forward(l,r);
            break;

        case 0x1F:
        case 0x0F:
        case 0x07:
        case 0xF8:
        case 0xF0:
        case 0xE0:
        case 0xFF:
        {
            switch(path_maze[ii]){
                   case 'L':
                            Motor_Forward(l,r);
                            Clock_Delay1ms(25);
                            Motor_Left(L,R+1000);
                            Clock_Delay1ms(300);
                            break;
                   case 'S':
                            Motor_Forward(L,R);
                            Clock_Delay1ms(200);
                            break;
                   case 'R':
                            Motor_Forward(l,r);
                            Clock_Delay1ms(25);
                            Motor_Right(L+1000,R);
                            Clock_Delay1ms(300);
                            break;
               }
               ii--;
               break;
        }

        case 0x08:
        case 0x0C:
           Port2_Output(0x07);
           Motor_Right(l,r);
           break;
        case 0x10:
        case 0x30:
           Port2_Output(0x07);
           Motor_Left(l,r);
           break;
        case 0x00:
            Motor_Stop();
            break;
          //模式二返回时判断三条线暂停
//        case 0xDB:
//        case 0x5B:
//        case 0x49:
//        case 0x92:
//        case 0x6D:
//        case 0xC9:
//        case 0x9B:
//            Motor_Stop();
//            break;


    }
}

void main(void)
   {

    char i=0,leng;
    const char *substr[6]={"LBR","LBS","RBL","SBL","SBS","LBL"}; //these strings can be replaced by
    const char *keys[6]={"B","R","B","R","B","S"};
    UART0_Initprintf();
    Clock_Init48MHz();
    Reflectance_Init();
    Motor_Init();
    Port2_Init();
    //判断起点开始运行
//    uint8_t p=1;
//    while(p){
//        Port2_Output(0x03);
//        Data = Reflectance_Read(1000);
//        switch(Data)
//            case 0xDB:{
//                Motor_Forward(L,R);
//                Clock_Delay1ms(300);
//                 p = 0;
//                 break;}
//    }

    while(!MOD1_Finished){
        MOD1();
//        while(LaunchPad_Input()==0);  // wait for touch
//        while(LaunchPad_Input()){break;};
    }
    path_maze[ii]='\0';

    //杩涜瀛楃涓叉浛鎹�
    do
    {
         leng=strlen(path_maze);
         for (i=0;i<6;i++)
            ReplaceSubStr(path_maze,substr[i],keys[i],path_maze);
    }while(strlen(path_maze)<leng);

    //瀵规渶浼樿矾寰勫彇鍙�
    for (i=0;i<strlen(path_maze);i++) {
        if (path_maze[i]=='L') path_maze[i]='R';
        else if (path_maze[i]=='R') path_maze[i]='L';
    }
    ii=strlen(path_maze)-1;
    while(1){
        MOD2();
   }
}

