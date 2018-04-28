#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
sbit fengmin=P3^2;
sbit key1=P2^0;
sbit key2=P2^1;
sbit key3=P2^2;
sbit key4=P2^3;
sbit key5=P2^4;
sbit key6=P2^5;
sbit key7=P2^6;
uchar code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
void delayms(xms);
uchar numt0;
uint num,bai,shi,ge;
void display(uint numdis)
{
  bai=numdis/100;
  shi=(numdis/10)%10;
  ge=numdis%10;

  P0=table[bai];
  P3=0xef;
  delayms(5);

  P0=table[shi]+0x80;
  P3=0xdf;
  delayms(5);

  P0=table[ge];
  P3=0xbf;
  delayms(5);

  if(num==999)
  {fengmin=0;}

  if(num==0)
  fengmin=0;
}
void delayms(xms)
{
  uint i,j;
  for(i=xms;i>0;i--)
    for(j=110;j>0;j--);
}
void init()
{
  TMOD=0x11;
  EA=1;
  ET0=1;
  ET1=1;
}
void keyscan()
{
  if(key1==0)
  {
    delayms(10);
	if(key1==0)
	{
	  num++;
	  if(num==1000)
	    num=0;
      while(!key1);
	}
  }
  if(key2==0)
  {
    delayms(10);
	if(key2==0)
	{
	  if(num==0)
	    num=1000;
      num--;
	  while(!key2);
	}
  }
  if(key3==0)
  {
    delayms(10);
	if(key3==0)
	{
	  num=0;
	  while(!key3);
	}
  }
  if(key4==0)
  {
    delayms(10);
	if(key4==0)
	{
	  while(!key4)
	  TR0=~TR0;
	}
  }
  if(key5==0)
  {
    delayms(10);
	if(key5==0)
	{
	  while(!key5)
	  TR1=~TR1;
	}
  }
    if(key6==0)
  {
    delayms(10);
	if(key6==0)
	{
	  num=num+10;
	  if(num>=1000)
	    num=0;
      while(!key6);
	}
  }
      if(key7==0)
  {
    delayms(10);
	if(key7==0)
	{
	  num=num-10;
	  if(num<=0)
	    num=1000;
      while(!key7);
	}
  }
}
void main()
{
  init();
  while(1)
  {
    keyscan();
	display(num);  
  }
}
void T0_time() interrupt 1
{
  TH0=(65536-45872)/256;
  TL0=(65536-45872)%256;
  numt0++;
  if(numt0==2)
  {
    numt0=0;
	   	num--;
	if(num==0)
	{ 
	TR0=0; 
	num=0;
	}

  }
}
void T1_time() interrupt 3
{
  TH1=(65536-45872)/256;
  TL1=(65536-45872)%256;
  numt0++;
  if(numt0==2)
  {
    numt0=0;
	  	num++;
	if(num==1000)
	{
	TR1=0;
	 num=999;
	}

  }
}