#include"travel.h" 
/*打印旅行策略*/
void print()
{
	pass a;
	int h,m;
	a=passengers[pcount];
	print_message(); 
	for(;a->next!=NULL;a=a->next)
	{
		//旅客状态为在城市里 
		if(a->passenger_state==2)
		{
			h=a->arrive_min/60;
			m=a->arrive_min%60;
			printf("旅客%d在城市%s停留到%d-%d-%d %d:%d\n",
			pcount,city[a->city_or_vehicle-1],a->arrive_year,
			a->arrive_month,a->arrive_day,h,m);
		}
		//旅客状态为在交通工具上 
		else
		{
			h=a->arrive_min/60;
			m=a->arrive_min%60;
			if(Tnumber[a->city_or_vehicle-1].number[0]=='k')
		    	printf("旅客登上从城市%s到城市%s的%s号列车,",city[a->pass_start_c-1],
				city[a->pass_arrive_c-1],Tnumber[a->city_or_vehicle-1].number);
			if(Tnumber[a->city_or_vehicle-1].number[0]=='f')
		    	printf("旅客登上从城市%s到城市%s的%s号飞机,",city[a->pass_start_c-1],
				city[a->pass_arrive_c-1],Tnumber[a->city_or_vehicle-1].number);
			if(Tnumber[a->city_or_vehicle-1].number[0]=='b')
		    	printf("旅客登上从城市%s到城市%s的%s号汽车,",city[a->pass_start_c-1],
				city[a->pass_arrive_c-1],Tnumber[a->city_or_vehicle-1].number);
			printf("价格为%lf元\n",a->pass_price); 
			printf("%d-%d-%d %d:%d到达\n",
			a->arrive_year,a->arrive_month,a->arrive_day,h,m); 
		} 
	}
}
