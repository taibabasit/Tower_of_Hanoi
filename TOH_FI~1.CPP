#include<graphics.h>
#include<iostream.h>
#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
# define Y 20
union REGS in,out;
int n,peg1[6],peg2[6],peg3[6],top1,top2=-1,top3=-1;
int val[5];

int callmouse()
{
    in.x.ax=1;
    int86(51,&in,&out);
    return 1;
}

void mouseposi(int &xpos,int &ypos,int &click)
{
    in.x.ax=3;
    int86(51,&in,&out);
    click=out.x.bx;
    xpos=out.x.cx;
    ypos=out.x.dx;
}

int mousehide()
{
    in.x.ax=2;
    int86(51,&in,&out);
    return 1;
}

void setposi(int &xpos,int &ypos)
{
    in.x.ax=4;
    in.x.cx=xpos;
    in.x.dx=ypos;
    int86(51,&in,&out);
}

struct peg
{
    int pos,top,x1[6],y1[6],x2[6],y2[6];
}source,dest,aux;

int pop(int peg[],int &top)
{
    int disk;
    disk=peg[top];
    top--;
    return disk;
}

void push(int disk,int peg[],int &top)
{
    top++;
    peg[top]=disk;
}

int check(int peg[],int top,int disk,peg a)
{
    if(peg[top]<disk)
    {
       switch(a.pos)
       {
	  case 0:
	  push(disk,peg1,top1);
	  break;
	  case 1:
	  push(disk,peg2,top2);
	  break;
	  case 2:
	  push(disk,peg3,top3);
	  break;
       }
       return 1;
    }
    else
       return 0;
}
void create(peg &p1,int &top1,peg &p2,int &top2);
void movedisk(int a,peg &from,peg &to);

void towerm()
{
    int x,y,cl,flag=0,disk,ch;
    peg *s,*d;
    callmouse();
    int a=100,b=400;
    setposi(a,b);
    do
     {
       mouseposi(x,y,cl);

       if(cl==1&&x>=550&&x<=600&&y>=324&&y<=346)
	   exit(1);
       else if(cl==1&&x>=100&&x<=110&&y>=100&&y<=300)
	 {
	   s=&source;
	   flag=1;
	   disk=pop(peg1,top1);
	 }
       else if(cl==1&&x>=315&&x<=325&&y>=100&&y<=300)
	 {
	   s=&aux;
	   flag=1;
	   disk=pop(peg2,top2);
	 }
       else if(cl==1&&x>=530&&x<=540&&y>=100&&y<=300)
	 {
	   s=&dest;
	   flag=1;
	   disk=pop(peg3,top3);
	 }
     }while(flag==0);
flag=0;
setposi(a,b);
callmouse();
    do
     {
	 mouseposi(x,y,cl);
	 if(cl==1&&x>=550&&x<=600&&y>=324&&y<=346)
	 exit(1);
      else if(cl==1&&x>=100&&x<=110&&y>=100&&y<=300)
	{
	 d=&source;
	 flag=1;
	 ch=check(peg1,top1,disk,*s);
	 if(ch==0)
	   push(disk,peg1,top1);
	}
      else if(cl==1&&x>=315&&x<=325&&y>=100&&y<=300)
	{
	  d=&aux;
	  flag=1;
	  ch=check(peg2,top2,disk,*s);
	  if(ch==0)
	   push(disk,peg2,top2);
	}
      else if(cl==1&&x>=530&&x<=540&&y>=100&&y<=300)
	{
	  d=&dest;
	  flag=1;
	  ch=check(peg3,top3,disk,*s);
	  if(ch==0)
	   push(disk,peg3,top3);}
	}while(flag==0);
   if(ch==0)
   {
     create(*s,s->top,*d,d->top);
     movedisk(disk,*s,*d);
     s->top--;
   }
   else
   {
     setfillstyle(SOLID_FILL,LIGHTGRAY);
     bar(200,335,400,357);
     outtextxy(210,330,"Invalid Move");
     delay(1000);
     setfillstyle(SOLID_FILL,BLUE);
     bar(200,335,400,357);
   }
setposi(a,b);
   if(top3!=n-1)
     towerm();
   else
   {
     setfillstyle(SOLID_FILL,LIGHTGRAY);
     bar(200,335,400,357);
     outtextxy(210,330,"GAME COMPLETED");
   }
}

void create(peg &p1,int &top1,peg &p2,int &top2)
{
  int x,y;
  top2++;
  x=p1.x1[top1];
  y=p2.y1[top2-1];
  p2.y1[top2]=y-30;
  if(p1.pos==0&&p2.pos==2)
    p2.x1[top2]=x+430;
  else if(p1.pos==0&&p2.pos==1)
    p2.x1[top2]=x+215;
  else if(p1.pos==1&&p2.pos==2)
    p2.x1[top2]=x+215;
  else if(p1.pos==2&&p2.pos==1)
    p2.x1[top2]=x-215;
  else if(p1.pos==2&&p2.pos==0)
    p2.x1[top2]=x-430;
  else if(p1.pos==1&&p2.pos==0)
    p2.x1[top2]=x-215;
}

void movedisk(int a,peg &from,peg &to)
{
  int x,y,size=val[a-1]*40,xa,ya;
  x=from.x1[from.top];
  y=from.y1[from.top];
  do
  {
    setfillstyle(SOLID_FILL,BLACK);
    bar(x,y,x+size,y+Y);
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    bar(x+size/2-5,y,x+size/2+5 ,y+Y);
    y-=30;
    setfillstyle(SOLID_FILL,10+n-a);
    bar(x,y,x+size,y+Y);
    delay(300);
   }while(y>60);
  xa=to.x1[to.top];
  do
  {
    setfillstyle(SOLID_FILL,BLACK);
    bar(x,y,x+size,y+Y);
    if(xa<x)
      x-=43;
    else
      x+=43;
    setfillstyle(SOLID_FILL,10+n-a);
    bar(x,y,x+size,y+Y);
    delay(300);
  }while(x!=xa);
  ya=to.y1[to.top];
  int j=0;
  do
  {
    setfillstyle(SOLID_FILL,BLACK);
    bar(x,y,x+size,y+Y);
    if(j>0)
     {
       setfillstyle(SOLID_FILL,LIGHTGRAY);
       bar(x+size/2-5,y,x+size/2+5 ,y+Y);
     }
    y+=30;
    setfillstyle(SOLID_FILL,10+n-a);
    bar(x,y,x+size,y+Y);
    delay(300);
    j++;
  }while(y<ya);
}

void tower(int n,peg &from,peg &to,peg &aux)
{
 if(n==1)
 {
   create(from,from.top,to,to.top);
   movedisk(1,from,to);
   from.top--;
   return;
 }
 tower(n-1,from,aux,to);
 create(from,from.top,to,to.top);
 movedisk(n,from,to);
 from.top--;
 tower(n-1,aux,to,from);
}

int main()
{
 int i;
 int gd=DETECT,gm;
 do
 {
   printf("\nEnter no. of disks :-limit(1-5):-  ");
   scanf("%d",&n);
 }while((n<1)&&(n>5));
 initgraph(&gd,&gm,"C://TURBOC3//BGI");
 settextstyle(TRIPLEX_FONT,HORIZ_DIR,1);
 setbkcolor(BLUE);
 setfillstyle(SOLID_FILL,LIGHTGRAY);
 bar(150,13,490,33);
 bar(30,324,170,346);
 bar(550,324,600,346);
 bar(30,355,170,377);
 setcolor(RED);
 outtextxy(180,10,"T O W E R  O F  H A N O I");
 setcolor(MAGENTA);
 outtextxy(60,321,"MANUAL");
 outtextxy(555,321,"EXIT");
 outtextxy(60,356,"COMPUTER");
 setfillstyle(SOLID_FILL,LIGHTGRAY);
 bar(100,100,110,300);
 bar(530,100,540,300);
 bar(315,100,325,300);
 bar(0,300,640,310);
 for(i=0;i<5;i++)
 {
   source.x1[i]=5+20*i;
   source.y1[i]=270-30*i;
   source.x2[i]=205-20*i;
   source.y2[i]=290-30*i;
 }
 source.y1[-1]=300;
 dest.y1[-1]=300;
 aux.y1[-1]=300;
 source.pos=0;
 aux.pos=1;
 dest.pos=2;
 source.top=n-1;
 dest.top=-1;
 aux.top=-1;
 int z=5;
 for(i=n-1;i>=0;i--)
  val[i]=z--;
 for(i=0;i<n;i++)
 {
   setfillstyle(SOLID_FILL,10+i);
   bar(source.x1[i],source.y1[i],source.x2[i],source.y2[i]);
 }
 top1=n-1;
 for(i=0;i<n;i++)
  peg1[i]=n-i;
 peg2[-1]=10;
 peg3[-1]=10;
 int x,y,cl,a,b;
 a=100;
 b=400;
 setposi(a,b);
 callmouse();
     do
      {
	 mouseposi(x,y,cl);
	 if(cl==1&&x>=550&&x<=600&&y>=324&&y<=346)
	   exit(1);
	 else if(cl==1&&x>=30&&x<=170&&y>=355&&y<=377)
	   tower(n,source,dest,aux);
	 else if(cl==1&&x>=30&&x<=170&&y>=324&&y<=346)
	 { setcolor(BLUE);
	   setfillstyle(SOLID_FILL,LIGHTGRAY);
	   bar(200,335,500,357);
	   outtextxy(210,330,"YOU ARE IN MANNUAL MODE");
	   delay(1000);
	   setfillstyle(SOLID_FILL,BLUE);
	   bar(200,335,510,357);
	   setfillstyle(SOLID_FILL,LIGHTGRAY);
	   bar(200,325,510,370);
	   outtextxy(210,326,"FIRST CLICK ON SOURCE PEG");
	   outtextxy(210,350,"THEN CLICK ON DESTINATION PEG");
	   delay(1000);
	   setfillstyle(SOLID_FILL,BLUE);
	   bar(200,325,510,370);
	   towerm();
	 }
      }while(!kbhit());
      int ch;
      cleardevice();
      cout<<"do you want to play more?";
      cin>>ch;
      while(ch==1)
      {
      cleardevice();
      main();
      }
 getch();
 mousehide();
 closegraph();
 return 0;
}