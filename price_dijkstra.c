#include"travel.h"

/*Ҫ�ڵ��ô˺���֮ǰ��arcs��ά���鸳ֵ*/
void ShortestPath_DIJ(int present_city,price_arc **arcs1)
{
	 int w,v,i;

	 int* final;
	 int * p;
	 final=malloc(sizeof(int)*(city_num+1));  //��̬�����¼����final
	 p=malloc(sizeof(int)*(city_num+1));
     for (v = 0; v<=city_num-1; v++) //ѭ�� ��ʼ��
     {
     	  if(v!=present_city)
     	  {
     	      final[v] = 0;   //��final[i] = 1��˵�� ����vi+1���ڼ���S��
		      D[v] = arcs1[present_city][v].mini_price;
		          p[v] = -1;//���·��

              if (D[v] < MAX && D[v]>0)
		      {
			      p[v]=v+1;         //��ʾԴ�㵽v���һ������Ϊv����������
		      }
     	  }

     }
     D[present_city] = 0;
	 final[present_city]=1; //��ʼ���������ڼ���S
     //��ʼ��ѭ�� ÿ�����present_city��ĳ������v�����·�� ����v������S��
     for (i = 1; i<city_num; i++)
     {
          int min = MAX;
          for (w =0; w<=city_num-1; w++)
          {
               if (!final[w]) //���w������V-S��
               {
                    //�����������ѡ���ĵ� Ӧ����ѡ����ǰV-S����S�й�����
                    //��Ȩֵ��С�Ķ��� ��������Ϊ ��ǰ��V0����ĵ�
                    if (D[w] < min&&D[w]>0)
					{
					    v = w;
						min = D[w];
		  			}
               }
          }
          final[v] = 1; //ѡ���õ����뵽�ϼ�S��
          for (w = 0; w < city_num; w++)//���µ�ǰ���·���;���
          {
          	   if(!final[w]&&D[w]==-1&&(arcs1[v][w].mini_price>0))
          	   {
          	   	    D[w] = min + arcs1[v][w].mini_price;
                    p[w]= v+1;
			   }
               /*�ڴ�ѭ���� vΪ��ǰ��ѡ�뼯��S�еĵ�
               ���Ե�VΪ�м�� ���� d0v+dvw �Ƿ�С�� D[w] ���С�� ����� */
               if (D[w]!=-1&&!final[w] &&(arcs1[v][w].mini_price>0)&& (min+arcs1[v][w].mini_price<D[w]))     //�������·����ͬʱ�������¼;����
               {
                    D[w] = min + arcs1[v][w].mini_price;
                    p[w]= v+1;           //p[w]��ʾ��w��ǰһ����

               }
          }
     }

     for(i=0;i<city_num;i++)
          {
    	      if(i!=present_city)
    	      {
		          search_p_Path(p,present_city,i);
    	      }
          }
}
//����p����������·��
void search_p_Path(int *p,int source,int terminal)
{
    int queue[city_num+1];//��Ŵ�source��ʼ�����·��
    int i=0,j,k;
    int temp;

	if(p[terminal]==terminal+1)  //��;��
		 path[source][terminal][0]=terminal+1;
    else            // ��;��
    {
    	temp= p[terminal]-1;
    	//path[source][terminal][i]=temp;
    	for(;p[temp]!=temp+1;i++)
        {
        	queue[i] = temp+1;
        	temp = p[temp]-1;
    	}
    	for(j=i-1,k=1;j>=0;j--,k++)
			path[source][terminal][k]=queue[j];
		path[source][terminal][0]=temp+1;
	}
}


