#include"travel.h"

/*要在调用此函数之前给arcs二维数组赋值*/
void ShortestPath_DIJ(int present_city,price_arc **arcs1)
{
	 int w,v,i;

	 int* final;
	 int * p;
	 final=malloc(sizeof(int)*(city_num+1));  //动态申请记录数组final
	 p=malloc(sizeof(int)*(city_num+1));
     for (v = 0; v<=city_num-1; v++) //循环 初始化
     {
     	  if(v!=present_city)
     	  {
     	      final[v] = 0;   //若final[i] = 1则说明 顶点vi+1已在集合S中
		      D[v] = arcs1[present_city][v].mini_price;
		          p[v] = -1;//设空路径

              if (D[v] < MAX && D[v]>0)
		      {
			      p[v]=v+1;         //表示源点到v点第一个城市为v，即它本身
		      }
     	  }

     }
     D[present_city] = 0;
	 final[present_city]=1; //初始化顶点属于集合S
     //开始主循环 每次求得present_city到某个顶点v的最短路径 并加v到集合S中
     for (i = 1; i<city_num; i++)
     {
          int min = MAX;
          for (w =0; w<=city_num-1; w++)
          {
               if (!final[w]) //如果w顶点在V-S中
               {
                    //这个过程最终选出的点 应该是选出当前V-S中与S有关联边
                    //且权值最小的顶点 书上描述为 当前离V0最近的点
                    if (D[w] < min&&D[w]>0)
					{
					    v = w;
						min = D[w];
		  			}
               }
          }
          final[v] = 1; //选出该点后加入到合集S中
          for (w = 0; w < city_num; w++)//更新当前最短路径和距离
          {
          	   if(!final[w]&&D[w]==-1&&(arcs1[v][w].mini_price>0))
          	   {
          	   	    D[w] = min + arcs1[v][w].mini_price;
                    p[w]= v+1;
			   }
               /*在此循环中 v为当前刚选入集合S中的点
               则以点V为中间点 考察 d0v+dvw 是否小于 D[w] 如果小于 则更新 */
               if (D[w]!=-1&&!final[w] &&(arcs1[v][w].mini_price>0)&& (min+arcs1[v][w].mini_price<D[w]))     //更新最短路径的同时，按序记录途经点
               {
                    D[w] = min + arcs1[v][w].mini_price;
                    p[w]= v+1;           //p[w]表示到w的前一个点

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
//根据p数组查找最短路径
void search_p_Path(int *p,int source,int terminal)
{
    int queue[city_num+1];//存放从source开始的最短路径
    int i=0,j,k;
    int temp;

	if(p[terminal]==terminal+1)  //无途径
		 path[source][terminal][0]=terminal+1;
    else            // 有途径
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


