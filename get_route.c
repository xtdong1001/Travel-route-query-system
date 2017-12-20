#include"travel.h"
//获得乘客输入 得到路线
void getInput()
{
    int start_city;
    int end_city;
    int via_city_num; //途径城市个数
    int st_year,st_month,st_day,st_hour,st_min;  //乘客出发时间
    int * middle_city;   //途经城市编号
    int a,b;                  //a,b代表模式选择
    int i=0,j;             //伴随middle_city的计数器
    int lim_d,lim_h,lim_m;//策略三限制时间
    int limit;
    int *limd,*limh,*limm;//策略三限制时间 

	//打印可选城市和对应序号 旅客进行选择
	for(i=0;i<city_num;i++)
		printf("%d %s\n",i+1,city[i]);

	printf("请输入您的出发时间(x年-x月-x日-x时-x分)！\n");
	
	while(1)
	{
		scanf("%d-%d-%d-%d-%d",&st_year,&st_month,&st_day,&st_hour,&st_min);
		if(st_year<2016||st_month<1||st_month>12||st_day<1||st_day>31
	   		||st_hour<0||st_hour>23||st_min<0||st_min>59)
	    	printf("输入有误，请您重新输入！\n");
		else break;
	}
	
	//将出发时间存入全局变量结构数组
	stime[pcount].year  =st_year;
	stime[pcount].month =st_month;
	stime[pcount].day   =st_day;
	stime[pcount].hour  =st_hour;
	stime[pcount].minute=st_min;

	st_min=st_min+60*st_hour;
	//调用函数传参只传分钟数 不传小时

	printf("请输入起始城市和终止城市序号!\n");
	
	while(1)
	{
		scanf("%d %d",&start_city,&end_city);
    	if(start_city<1||start_city>city_num||end_city<1||end_city>city_num)
    		printf("输入有误，请您重新输入！\n");
		else break;
	}
    
    
	printf("您是否有必须途经的城市，有--1，没有--0!\n");
	
	while(1)
	{
		scanf("%d",&a);
		if(a==0||a==1)
		    break;
		else printf("输入有误，请您重新输入！\n");
	}
	

	//无途经
	if(a==0)
	{
	    printf("请选择您需要的策略(时间最短--1,费用最少--2,限时费用最少--3)。\n");
	    getchar();
		scanf("%d",&b);

		if(b==1) //无途经时间最短策略 
		{
		   	without_via_mintime(st_year,st_month,st_day,st_min,start_city,end_city);
		}
		else if(b==2) //无途经费用最少策略 
		{
			output_price(st_year,st_month,st_day,st_min,start_city,end_city);
		}
		else //无途经限时费用最少策略 
		{
		   	int limd,limh,limm;
		   	printf("请输入限制时间(x天-y小时-z分钟)\n");
		    scanf("%d %d %d",&limd,&limh,&limm);
		    limm=limh*60+limm;
		    no_via_city_timeprice(st_year,st_month,st_day,st_min,
			                      start_city,end_city,limd,limm);
		}
	}
	//有途径
	else
	{
		printf("请输入途径城市个数！\n");
		scanf("%d",&via_city_num);
		middle_city=(int*)malloc(via_city_num*sizeof(int));
		for(i=0;i<via_city_num;i++)
		{
			printf("请输入一个城市对应的代号！\n");
			scanf("%d",&middle_city[i]);
		}

	   	printf("请选择您需要的策略(时间最短--1,费用最少--2,限时费用最少--3)\n");
		scanf("%d",&b);
		if(b==1) //有途经时间最短策略
		{
		   	with_via_mintime(st_year,st_month,st_day,st_min,via_city_num,
				             middle_city,start_city,end_city);
		}
		else if(b==2)//有途经费用最少策略 
		{
		   	via_city_price(st_year,st_month,st_day,st_min,via_city_num,
				           middle_city,start_city,end_city);
		}
		else//有途经限时费用最少策略 
		{
			printf("总时间限制--1,两城市间时间限制--2\n");
			scanf("%d",&limit);
			getchar();
			
			if(limit==1)//有途经无序输入限时费用最少策略 
			{
				printf("请输入%s到%s限制时间(x天-y小时-z分钟)\n",city[start_city-1],city[end_city-1]);
		    	scanf("%d %d %d",&lim_d,&lim_h,&lim_m);
		    	lim_m=lim_h*60+lim_m;
		   		via_timeprice(st_year,st_month,st_day,st_min,via_city_num,
			              	  middle_city,start_city,end_city,lim_d,lim_m);
			}
			else if(limit==2)//有途经有序输入限时费用最少策略 
			{
				limd=(int*)malloc((via_city_num+1)*sizeof(int));
				limh=(int*)malloc((via_city_num+1)*sizeof(int));
				limm=(int*)malloc((via_city_num+1)*sizeof(int));
				
				printf("请输入%s到%s限制时间(x天-y小时-z分钟)\n",city[start_city-1],city[middle_city[0]-1]);
		    	scanf("%d %d %d",&limd[0],&limh[0],&limm[0]);
		    	limm[0]=limh[0]*60+limm[0];
				for(i=0,j=1;i<via_city_num-1;i++,j++)
				{
					printf("请输入%s到%s限制时间(x天-y小时-z分钟)\n",city[middle_city[i]-1],city[middle_city[i+1]-1]);
		    		scanf("%d %d %d",&limd[j],&limh[j],&limm[j]);
		    		limm[j]=limh[j]*60+limm[j];
				}
				printf("请输入%s到%s限制时间(x天-y小时-z分钟)\n",city[middle_city[i]-1],city[end_city-1]);
		    	scanf("%d %d %d",&limd[j],&limh[j],&limm[j]);
		    	limm[j]=limh[j]*60+limm[j];
				
		   		via_city_timeprice(st_year,st_month,st_day,st_min,via_city_num,
				               middle_city,start_city,end_city,limd,limm);
			}
			
		}
	}
}
