#include"travel.h"
#include"egg.h"
void drawmap()
{
	EggStart(21.19,16.51); 
	gg=LayEgg();
	MovePen(0,16.51);
	DrawBitmap("��ͼ.bmp");
}
        
void printmap(int sx,int sy,int ex,int ey)         //��ӡ���ߴ�ӡ��ͨ���� 
{   
	int v;
	double x,y;
	
	temp_g_egg[pcount] = LayEgg();
	MovePen(sx,sy); 
	SetPen(RED,0.1);
	DrawLine(ex-sx,ey-sy);
	
    x=(sx+ex)/2; y=(sy+ey)/2;
    
    v=passengers[pcount]->city_or_vehicle-1;
	if(Tnumber[v].number[0]=='k')
	{
		g_egg1[pcount] = LayEgg(); 
		MovePen(x,y);
		DrawBitmap("��.bmp");
		flag[pcount]=1;
	} 
	if(Tnumber[v].number[0]=='f')
	{
		g_egg2[pcount] = LayEgg(); 
		MovePen(x,y);
		DrawBitmap("�ɻ�.bmp");
		flag[pcount]=2;
	}
	if(Tnumber[v].number[0]=='b')
	{
		g_egg3[pcount] = LayEgg(); 
		MovePen(x,y);
		DrawBitmap("����.bmp");
		flag[pcount]=3;
	}   
} 

