#include"travel.h"
/*实现第二个策略，计算最短时间*/
void least_time(int s_city,int days,int s_time)
{
	int time_min=100000;
	int update_time;
	int index;             //最小值对应的序号
	int i,j,v,counter;
	int * p;              //p数组存的是前一个点
	int * final;                      //记录数组
	int count1,count2,count3; 
	int Time[11],dddays[11];    //记录到达每个城市的时间 
	final=(int *)malloc(sizeof(int)*city_num);
	p=(int *)malloc(sizeof(int *)*city_num);
	
	for(counter=0;counter<city_num;counter++)
	{
		dddays[counter]=days;
		Time[counter]=s_time;	
	}
	
	for(counter=0;counter<city_num;counter++)
	{
		time_matrix[counter]=(time_arc *)malloc(sizeof(time_arc )*city_num);
		for(i=0;i<city_num;i++)
		    time_matrix[counter][i].mini_time=-1;
	}
		
    time_path=(int***)malloc(city_num*sizeof(int**));   	
	for(count1=0;count1<city_num;count1++)
	{
		time_path[count1]=(int**)malloc(city_num*sizeof(int*));
		for(count2=0;count2<city_num;count2++)
		{
			time_path[count1][count2]=(int*)malloc(city_num*sizeof(int));
			for(count3=0;count3<city_num;count3++)
				time_path[count1][count2][count3]=-1;
		}
	}  


	for (v = 0; v<=city_num-1; v++) //循环 初始化
    {
        final[v] = 0;   //若final[i] = 1则说明 顶点vi+1已在集合S中
		p[v] = -1;//设空路径
    }
	final[s_city-1]=1; //初始化顶点属于集合S

	cal_mini_minute(s_city,days,s_time);
	//计算源城市对应的time_matrix那一行
 //在源城市到其他城市最短时间中选择一个最小值
	for(i=0;i<city_num;i++)
	    if(i!=s_city-1&&time_matrix[s_city-1][i].mini_time>0&&time_matrix[s_city-1][i].mini_time<time_min)
	    {
		    time_min=time_matrix[s_city-1][i].mini_time;
		    index=i;
        }
    final[index]=1;
    p[index]=index+1;

	Time[index]=s_time+time_min;
	//到达一个新的城市的分钟数，判断这个分钟时间是否超过24*60
	if(Time[index]>=24*60)   //Time（分钟数）超过一天
	{
		dddays[index]=Time[index]/(24*60)+days;
		Time[index]=Time[index]%(24*60);
    }
	//已经得到到达一个新的城市的时间 
	for(j=0;j<city_num-2;j++)
	{
		time_min=100000;
		cal_mini_minute(index+1,dddays[index],Time[index]);
		//以下一个城市为开始城市，计算它到其他城市的最短时间和对应的车

		 //更新index对应城市之后城市到源城市的最短时间
		for(i=0;i<city_num;i++)
		{
		    if(i!=index&&final[i]==0&&num[index][i]>0)
		    {
		    	update_time=time_matrix[index][i].mini_time +
			            	time_matrix[s_city-1][index].mini_time;
				if((time_matrix[s_city-1][i].mini_time>0&&
				   update_time<time_matrix[s_city-1][i].mini_time)||
				   (time_matrix[s_city-1][i].mini_time<0&&update_time>0))
				{
					time_matrix[s_city-1][i].mini_time=update_time;
					p[i]=index+1;
		    	}
		    }
		}
		//在源城市到其他城市最短时间中选择一个最小值
	    for(i=0;i<city_num;i++)
	        if(time_matrix[s_city-1][i].mini_time<time_min&&final[i]==0&&time_matrix[s_city-1][i].mini_time!=-1)
	        {
		        time_min=time_matrix[s_city-1][i].mini_time;
		        index=i;
            }
		final[index]=1;
		
		if(p[index]==-1)
		    p[index]=index+1;
		
		if(p[index]==index+1)  //该点与源城市直连 
		{
			Time[index]=s_time+time_min;
			if(Time[index]>=24*60)                //新的一天
	    	{
		    	dddays[index]=Time[index]/(24*60)+days;
		    	Time[index]=Time[index]%(24*60);
        	}
		}	
		else //该点与源点之间有途径城市 
		{
			Time[index]=Time[p[index]-1]+time_min;
			if(Time[index]>=24*60)                //新的一天
	    	{
		    	dddays[index]=Time[index]/(24*60)+dddays[p[index]-1];
		    	Time[index]=Time[index]%(24*60);
        	}
		}
		//到达一个新的城市的分钟数，判断这个分钟时间是否超过24*60
	    if(Time[index]>=24*60)                //新的一天
	    {
		    dddays[index]=Time[index]/(24*60)+dddays[index];
		    Time[index]=Time[index]%(24*60);
        }
	}

	for(i=0;i<city_num;i++)
    {
    	if(i!=s_city-1)
    	{
		    search_t_Path(p,s_city-1,i);
    	}
    }
}

//根据p数组查找最短路径
void search_t_Path(int *p,int source,int terminal)
{
    int queue[city_num+1];//存放从source开始的最短路径
    int i=0,j,k;
    int temp;

	if(p[terminal]==terminal+1)  //无途径
		 time_path[source][terminal][0]=terminal+1;
    else            // 有途径
    {
    	temp=p[terminal]-1;
    	for(;p[temp]!=temp+1;i++)
        {
        	queue[i] = temp+1;
        	temp = p[temp]-1;
    	}
    	for(j=i-1,k=1;j>=0;j--,k++)
			time_path[source][terminal][k]=queue[j];
		time_path[source][terminal][0]=temp+1;
	}
}
