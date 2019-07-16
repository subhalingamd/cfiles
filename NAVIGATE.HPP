#include<bios.h>
#include<conio.h>

int UPDOWN(int miny,int opts)
{
int init=1,inp, y=miny, maxy=miny+opts-1;
gotoxy(1,miny);
do {
inp=bioskey(0);
if (inp==18432)
{
 if (y!=miny)
 {
  gotoxy(1,--y); init--;
 }
}
if (inp==20480)
{
 if (y!=maxy)
 {
  gotoxy(1,++y); init++;
 }
}
} while(inp!=7181);
return init;}

int UPDOWN_SUS(int miny,int opts)
{
int init=1,inp, y=miny, maxy=miny+opts-1;
gotoxy(1,miny);
do {
inp=bioskey(0);
if (inp==18432)
{
 if (y!=miny)
 {
  gotoxy(1,--y); init--;
 }
}
if (inp==20480)
{
 if (y!=maxy)
 {
  gotoxy(1,++y); init++;
 }
}
if (inp==19200||inp==19712)
return -1;
} while(inp!=7181);
return init;}
