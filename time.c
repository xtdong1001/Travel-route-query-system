#include"travel.h"
#include"egg.h"
/*系统时间计算*/ 
void system_time_count()
{
	while(1)
	{
		if(state!=QUERY) //当前状态不是查询状态
		{
	    	Sleep(INTERVAL);  //时间片推进
	    	time_count++;
			pull();//出队列

	    	system_t.minute=time_count*10;
			//半秒为十分钟 
	    	if(system_t.minute==60)  //分钟数归零，小时加一 
        	{
    	    	system_t.minute=0;
    	    	system_t.hour++;
    	    	time_count=0;
        	}
        	if(system_t.hour==24)//小时归零 天数加一 
        	{
    	    	system_t.hour=0;
    	    	system_t.day++;
        	}

        	switch(system_t.month){       //天数归零，月份加一 
            	case 1:case 3:case 5:case 7:
	        	case 8:case 10:case 12:
	   	        	if(system_t.day==32)
		        	{
			        	system_t.day=1;
			        	system_t.month++;
		        	}
                	break;
            	case 2:
                	if((system_t.year%4==0&&system_t.year%100!=0)||system_t.year%400==0)
                	{
            	    	if(system_t.day==30)
            	    	{
            		    	system_t.day=1;
					    	system_t.month++;
            	    	}
                	}
                	else if(system_t.day==29)
                	{
            	    	system_t.day=1;
            	    	system_t.month++;
                	}
                	break;
            	case 4:case 6:case 9:case 11:
                	if(system_t.day==30)
			    	{
				    	system_t.day=1;
				    	system_t.month++;
			    	}
			    	break;
        	}

			if(system_t.month==13)
			{
		    	system_t.month=1;
		    	system_t.year++;
			}
			//每半小时打印一次系统时间
    		if(system_t.minute%30==0)
    	     	printf("%d年%d月%d日 %d:%d\n",system_t.year,system_t.month,system_t.day,
			        	system_t.hour,system_t.minute);
    	}
    	if(s==4)
    	    break;
	}
}


//系统控制函数 
void start_system()
{
	start_date a;
	pass pl,ql;
	int pn,mark=1; 
	
	printf("请选择是否需要图形化输出：1--是，2--否\n"); 
    scanf("%d",&graphic1);
	getchar();
	
	if(graphic1==1)
	    drawmap();
		
	while(1)
	{
		printf("请输入您的需求！\n"); 
		scanf("%d",&s);
		getchar();
		//系统状态初始设置为MOVING 
		state=MOVING;
		//输入需求(若不输入则系统一直运行) 
		
		//查询策略 
    	if(s==1)
    	{
				//系统时间暂停运行 
				state=QUERY;
				Link();
				getInput();	 
				state=MOVING;
				//系统重新运行 
    	}
    	
  			//查询旅客状态 
		else if(s==2)
		{
			state=SEARCH;
			query();
			state=MOVING;
		}
		
			//更改旅行策略 
		else if(s==3)
		{
			//输入旅客号码 
			while(mark==1)
			{
				mark=0;
				printf("请输入您的乘客序号！\n");
		   		scanf("%d",&pn);
		   		if(pn>99||pn<1||pn>passen_count)
		   		{
		   			printf("序号有误，请重新输入！\n");
	    			mark=1;
	    		}    			
			}
			
				//全局变量pcount 为查询策略时存储链表指针的下标 
			pcount=pn;
			if(passengers[pn]!=NULL) 
			{
				a.year=passengers[pn]->arrive_year;
				a.month=passengers[pn]->arrive_month;
				a.day=passengers[pn]->arrive_day;
				a.hour=passengers[pn]->arrive_min/60;
				a.minute=passengers[pn]->arrive_min%60;
				
					//此时乘客在车上 则等待程序运行到旅客下车为止 
				if(passengers[pn]->passenger_state==1)     
					while(time_compare(a,system_t));
				
					//清空该乘客的策略链表 
				for(pl=passengers[pn];pl->next!=NULL;)
				{
					ql=pl->next;
					pl->next=ql->next;
					free(ql);
				}
				free(pl);
				passengers[pn]=NULL;
					//暂停程序运行 策略查询 
				state=QUERY;
				getInput();	
				state=MOVING;
					//程序重新运行 
			}
		}
		else if(s==4)  //退出 
    	    break;
	} 
}


