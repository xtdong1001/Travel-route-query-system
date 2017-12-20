#include"travel.h"
/*ʵ�ֵڶ������ԣ��������ʱ��*/
void least_time(int s_city,int days,int s_time)
{
	int time_min=100000;
	int update_time;
	int index;             //��Сֵ��Ӧ�����
	int i,j,v,counter;
	int * p;              //p��������ǰһ����
	int * final;                      //��¼����
	int count1,count2,count3; 
	int Time[11],dddays[11];    //��¼����ÿ�����е�ʱ�� 
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


	for (v = 0; v<=city_num-1; v++) //ѭ�� ��ʼ��
    {
        final[v] = 0;   //��final[i] = 1��˵�� ����vi+1���ڼ���S��
		p[v] = -1;//���·��
    }
	final[s_city-1]=1; //��ʼ���������ڼ���S

	cal_mini_minute(s_city,days,s_time);
	//����Դ���ж�Ӧ��time_matrix��һ��
 //��Դ���е������������ʱ����ѡ��һ����Сֵ
	for(i=0;i<city_num;i++)
	    if(i!=s_city-1&&time_matrix[s_city-1][i].mini_time>0&&time_matrix[s_city-1][i].mini_time<time_min)
	    {
		    time_min=time_matrix[s_city-1][i].mini_time;
		    index=i;
        }
    final[index]=1;
    p[index]=index+1;

	Time[index]=s_time+time_min;
	//����һ���µĳ��еķ��������ж��������ʱ���Ƿ񳬹�24*60
	if(Time[index]>=24*60)   //Time��������������һ��
	{
		dddays[index]=Time[index]/(24*60)+days;
		Time[index]=Time[index]%(24*60);
    }
	//�Ѿ��õ�����һ���µĳ��е�ʱ�� 
	for(j=0;j<city_num-2;j++)
	{
		time_min=100000;
		cal_mini_minute(index+1,dddays[index],Time[index]);
		//����һ������Ϊ��ʼ���У����������������е����ʱ��Ͷ�Ӧ�ĳ�

		 //����index��Ӧ����֮����е�Դ���е����ʱ��
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
		//��Դ���е������������ʱ����ѡ��һ����Сֵ
	    for(i=0;i<city_num;i++)
	        if(time_matrix[s_city-1][i].mini_time<time_min&&final[i]==0&&time_matrix[s_city-1][i].mini_time!=-1)
	        {
		        time_min=time_matrix[s_city-1][i].mini_time;
		        index=i;
            }
		final[index]=1;
		
		if(p[index]==-1)
		    p[index]=index+1;
		
		if(p[index]==index+1)  //�õ���Դ����ֱ�� 
		{
			Time[index]=s_time+time_min;
			if(Time[index]>=24*60)                //�µ�һ��
	    	{
		    	dddays[index]=Time[index]/(24*60)+days;
		    	Time[index]=Time[index]%(24*60);
        	}
		}	
		else //�õ���Դ��֮����;������ 
		{
			Time[index]=Time[p[index]-1]+time_min;
			if(Time[index]>=24*60)                //�µ�һ��
	    	{
		    	dddays[index]=Time[index]/(24*60)+dddays[p[index]-1];
		    	Time[index]=Time[index]%(24*60);
        	}
		}
		//����һ���µĳ��еķ��������ж��������ʱ���Ƿ񳬹�24*60
	    if(Time[index]>=24*60)                //�µ�һ��
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

//����p����������·��
void search_t_Path(int *p,int source,int terminal)
{
    int queue[city_num+1];//��Ŵ�source��ʼ�����·��
    int i=0,j,k;
    int temp;

	if(p[terminal]==terminal+1)  //��;��
		 time_path[source][terminal][0]=terminal+1;
    else            // ��;��
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
