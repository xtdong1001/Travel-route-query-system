#include"travel.h"
/******将旅客请求，策略，状态等信息写入文件*******/
void print_message(void)
{
    pass a;
	int h,m;
	a=passengers[pcount];
	
	if ((fptr1= fopen ("record.txt", "a+")) == NULL)        
        printf ("error!File could not be opened.\n");

	fprintf(fptr1,"系统时间：%d-%d-%d %d:%d\n",system_t.year,system_t.month,
                                               system_t.day,system_t.hour,
                                               system_t.minute);

    if(s==1)
        fprintf(fptr1,"用户%d查询策略！\n",pcount);
    else if(s==2)
        fprintf(fptr1,"用户%d查询当前状态！\n",pcount);
    else if(s==3)
        fprintf(fptr1,"用户%d更改策略为：\n",pcount);

	for(;a->next!=NULL;a=a->next)
	{
		//旅客状态为在城市里
		if(a->passenger_state==2)
		{
			h=a->arrive_min/60;
			m=a->arrive_min%60;
			fprintf(fptr1,"旅客%d在城市%s停留到%d-%d-%d %d:%d\n",
			pcount,city[a->city_or_vehicle-1],a->arrive_year,
			a->arrive_month,a->arrive_day,h,m);
		}
		//旅客状态为在交通工具上
		else
		{
			h=a->arrive_min/60;
			m=a->arrive_min%60;
			fprintf(fptr1,"旅客登上从城市%s到城市%s的%s号列车,",city[a->pass_start_c-1],
			city[a->pass_arrive_c-1],Tnumber[a->city_or_vehicle-1].number);
			fprintf(fptr1,"价格为%lf元\n",a->pass_price);
			fprintf(fptr1,"%d-%d-%d %d:%d到达\n",
			a->arrive_year,a->arrive_month,a->arrive_day,h,m);
		}
	}
	fclose(fptr1);
}

