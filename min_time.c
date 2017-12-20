/*此函数可以计算在任意时间到达任意站之后 开始计时，
它到达其他所有站的时间中最早的*/
/*第二个策略：最短时间*/
#include"travel.h"
int cal_min_time(int start_year,int start_month,int start_day)
//start_city为0代表第一个城市
{
	int k,days,year;
	int month[13]={0,31,0,31,30,31,30,31,31,30,31,30,31};

	days=0;
	year=0;
	year=start_year-2016;
	switch(year%4)   //年
	{
	   	case 0:days=(year/4)*(365*3+366);break;
	   	case 1:days=(year/4)*(365*3+366)+365;break;
	   	case 2:days=(year/4)*(365*3+366)+365*2;break;
	   	case 3:days=(year/4)*(365*3+366)+365*3;break;
	}
	if(year%4==0) //月
	    month[2]=29;
	else
	    month[2]=28;

	for(k=1;k<=start_month-1;k++)  //日
	    days=days+month[k];

	days=days+start_day;
	//days表示上车时间距离1月1号的天数，若days=1说明是2016.1.1

    return days;
}

//start_city为0代表第一个城市
void cal_mini_minute(int start_city,int days,int start_time)
{
	int i,j;
	int everyTrans_startday,everyTrans_duringday,this_day_time;
	//this_day_time表示车在当天的开车时间
	int wait_time;              //乘客等待上车的时间
	int travel_time;            //车的行驶时间
	int total_time;             //抵达下一个城市所需的所有时间
	int mol;
	//mol表示车的开始时间与乘客键入时间差值对车频率的模
	int mintime_between_twocity=1000000;
	//表示从一个城市到达另一个城市的最早时间
	int mintime_transp;
	//表示从一个城市到达另一个城市的最早时间对应的车次 等于1表示序号为1的那趟车

	for(i=0;i<=city_num-1;i++)              //遍历其他所有城市
	{
		for(j=0;j<=num[start_city-1][i]-1;j++)
		//遍历两个城市之间的所有交通工具
		{
		    everyTrans_startday=
			(int)vehicle[Tmatrix[start_city-1][i][j].vehicle_number-1][0].minute;
			//每种交通工具的开车的天时间
		    everyTrans_duringday=
			Tnumber[Tmatrix[start_city-1][i][j].vehicle_number-1].times;
			//每趟车的运行频率

		    mol=(days-everyTrans_startday)%everyTrans_duringday;

		    this_day_time=(int)Tmatrix[start_city-1][i][j].start_min%(24*60);

		    //表示乘客可以坐今天的此班车
		    if(mol==0&&this_day_time>=start_time)
		    	wait_time=this_day_time-start_time;
		    //表示乘客错过了今天的车
		    if(mol==0&&this_day_time<start_time)
	            wait_time=everyTrans_duringday*24*60
	                      -start_time+this_day_time;
	        if(mol!=0)        //表示车还没到
	        	wait_time=(everyTrans_duringday-mol)*24*60+this_day_time-start_time;

			travel_time=(int)Tmatrix[start_city-1][i][j].end_min-
			            (int)Tmatrix[start_city-1][i][j].start_min;

			total_time=wait_time+travel_time;
			//算的是分钟数
			if(total_time<mintime_between_twocity)
			{
				mintime_between_twocity=total_time;
				mintime_transp=Tmatrix[start_city-1][i][j].vehicle_number;
			}

		}
		if(num[start_city-1][i]!=0)
		{
			time_matrix[start_city-1][i].mini_time=mintime_between_twocity;
	    	time_matrix[start_city-1][i].mini_time_veh=mintime_transp;
		}

		mintime_between_twocity=1000000;         //重新置为最大值
	}
}

//有途径的最短时间策略 输出
void with_via_mintime(int s_year,int s_month,int s_day,int s_min,
int via_city_num,int * middle_city,int start_city,int end_city)
{

    int**full_per; //全排列的每一种情况
    int via_veh; //途经车辆
    int i,j,k,count=1,count_time=0,min_time_mid=1000000;
    int p_day,p_min; //乘客出发时间
    int vehicle_go_minu,vehicle_arrive_minu; //列车开车时间
	int wait_vehi_days;  //乘客等待列车的天数
	int city1,city2,city3,via_c; //每一段交通工具的起始城市和到达城市
	int vindex,bestv;
	way buffw[100],bestww[100];

	PASSENGER_LINK * tail, * p;  //链表结点指针

	p=(PASSENGER_LINK *)malloc(sizeof(PASSENGER_LINK));
	passengers[pcount]=p;
	tail=p;

	int y, m, d; //由天数转化而来的年月日

	int c;
	int condition;

    for(i=2;i<=via_city_num;i++)
        count=count*i;

    full_per=(int**)malloc(count*sizeof(int*));
    for(i=0;i<count;i++)
    	full_per[i]=(int*)malloc(via_city_num*sizeof(int)); //动态申请

	full_permutation(via_city_num,full_per);
	//得到途经城市的全排列

/*计算每一种途经城市全排列的时间 找到最小时间
每一个必经城市调用一次迪杰斯特拉函数least_time，
得到该城市和它相邻的必经城市的路径,
将路径信息存储到结构数组中*/
         
    for(i=0;i<count;i++)   //计算每一种全排列的时间 找到最小时间
	{
		p_min=s_min;
    	p_day=cal_min_time(s_year,s_month,s_day);

    	//年月日转化为天时间
    	least_time(start_city,p_day,p_min);

		city1=start_city;
		city3=start_city;
		city2=middle_city[full_per [i] [0]-1];
		via_c=time_path[city1-1][city2-1][0];
		vindex=0;
		count_time=0;

		for(k=1;via_c!=-1;vindex++,k++)
		{
			buffw[vindex].city=city1;
			buffw[vindex].veh=time_matrix[city1-1][via_c-1].mini_time_veh;
			city1=via_c;
			via_c=time_path[city3-1][city2-1][k];
			if(via_c==-1&&city1!=city2)
				via_c=city2;
		}

		count_time= count_time+time_matrix [start_city-1]
		[ middle_city[full_per [i] [0]-1]-1].mini_time;

		p_min=p_min+count_time;
		p_day=p_day+p_min/(24*60);
		p_min=p_min%(24*60);

		for(j=0;j<via_city_num-1;j++)
		{
			least_time(middle_city[full_per [i] [j]-1],p_day,p_min);
			//调用dijkstra

			city1=middle_city[full_per [i] [j]-1];
			city3=city1;
			city2=middle_city[full_per [i] [j+1]-1];
			via_c=time_path[city3-1][city2-1][0];

			for(k=1;via_c!=-1;vindex++,k++)
			{
				buffw[vindex].city=city1;
				buffw[vindex].veh=time_matrix[city1-1][via_c-1].mini_time_veh;
				city1=via_c;
				via_c=time_path[city3-1][city2-1][k];
				if(via_c==-1&&city1!=city2)
					via_c=city2;
			}

			//计算时间和
			count_time=count_time+time_matrix[city3-1][city2-1].mini_time;

			//更新出发的day和minute
			p_min=p_min+time_matrix[city3-1][city2-1].mini_time;

			p_day=p_day+p_min/(24*60);
		    p_min=p_min%(24*60);
		}

		least_time(middle_city[full_per [i] [j]-1],p_day,p_min);

		city1=middle_city[full_per [i] [j]-1];
		city3=city1;
		city2=end_city;
		via_c=time_path[city1-1][city2-1][0];

		for(k=1;via_c!=-1;vindex++,k++)
		{
			buffw[vindex].city=city1;
			buffw[vindex].veh=time_matrix[city1-1][via_c-1].mini_time_veh;
			city1=via_c;
			via_c=time_path[city3-1][city2-1][k];
			if(via_c==-1&&city1!=end_city)
				via_c=end_city;
		}

		buffw[vindex].city=end_city;
		buffw[vindex].veh=-1;

		count_time=count_time+
		time_matrix[middle_city[full_per [i] [j]-1]-1]
		           [end_city-1].mini_time;

		if(count_time<min_time_mid) //找最短时间
		{
			min_time_mid=count_time;
			bestv=vindex;
			condition=i;
			for(k=0;k<=vindex;k++)
			    bestww[k]=buffw[k];
		}
	}

	printf("乘客的旅行计划是:\n");

	p_day=cal_min_time(s_year,s_month,s_day);
	p_min=s_min;

	for(i=0;i<bestv;i++)
	{
		city1=bestww[i].city;
		via_c=bestww[i+1].city;
		via_veh=bestww[i].veh;

		wait_vehi_days=need_day_to_go(p_day,p_min,via_veh,
		city1,via_c,&vehicle_go_minu,&vehicle_arrive_minu);

		time_switch(p_day+wait_vehi_days,&y,&m,&d);

		p_day=p_day+wait_vehi_days+(vehicle_arrive_minu/(24*60));
		     //新的p_day 要在旧的的基础上加上等车天数和坐车天数
	    p_min=vehicle_arrive_minu%(24*60);


/*----------将当前旅客状态和旅客到达状态入队列-----------*/
	    tail->passenger_state=2;
	    tail->city_or_vehicle=city1;
        tail->pass_start_c=0;
        tail->pass_arrive_c=0;
        tail->arrive_year=y;
        tail->arrive_month=m;
        tail->arrive_day=d;
        tail->arrive_min=vehicle_go_minu%(24*60);
        p=(PASSENGER_LINK *)malloc(sizeof(PASSENGER_LINK));
        tail->next=p;
        tail=tail->next;

	    time_switch(p_day,&y,&m,&d);
		tail->passenger_state=1;
	    tail->city_or_vehicle=via_veh;
        tail->pass_start_c=city1;
        tail->pass_arrive_c=via_c;
        tail->arrive_year=y;
        tail->arrive_month=m;
        tail->arrive_day=d;
        tail->arrive_min=p_min;

        for(c=0;Pmatrix[city1-1][via_c-1][c].vehicle_number!=via_veh;c++);
        tail->pass_price=Pmatrix[city1-1][via_c-1][c].price;

        p=(PASSENGER_LINK *)malloc(sizeof(PASSENGER_LINK));
        tail->next=p;
        tail=tail->next;
        tail->next=NULL;

/*--------------------------------------------------------*/
	}

	print();
}

//没有途径的最短时间策略 输出
void without_via_mintime(int s_year,int s_month,int s_day,int s_min,
                  int start_city,int end_city)
{
	int via_veh; //途经车辆
    int i;
    int p_days; //乘客出发时间
    int vehicle_go_minu,vehicle_arrive_minu; //列车开车时间
	int wait_vehi_days;  //乘客等待列车的天数
	int city1,via_c; //每一段交通工具的起始城市和到达城市
	PASSENGER_LINK* tail,*p;
	tail=passengers[pcount];

	int c;

	p=(PASSENGER_LINK *)malloc(sizeof(PASSENGER_LINK));
	passengers[pcount]=p;
	tail=p;

	int y,m,d; //由天数转化而来的年月日

    p_days=cal_min_time(s_year,s_month,s_day);
    least_time(start_city,p_days,s_min);

	printf("乘客的旅行计划是:\n");

	city1=start_city;
	via_c= time_path[start_city-1] [end_city-1] [0];
	for(i=0;via_c!=-1&&i<city_num;i++)
	{
	    via_veh=time_matrix[city1-1][via_c-1].mini_time_veh;  //车号
		wait_vehi_days=need_day_to_go(p_days,s_min,via_veh,
		city1,via_c,&vehicle_go_minu,&vehicle_arrive_minu);

	    time_switch(p_days+wait_vehi_days,&y,&m,&d);

	    p_days=p_days+wait_vehi_days+(vehicle_arrive_minu/(24*60));
		//新的p_days 要在旧的的基础上加上等车天数和坐车天数
	    s_min=vehicle_arrive_minu%(24*60);

/*----------将当前旅客状态和旅客到达状态入队列-----------*/
	    tail->passenger_state=2;
	    tail->city_or_vehicle=city1;
        tail->pass_start_c=0;
        tail->pass_arrive_c=0;
        tail->arrive_year=y;
        tail->arrive_month=m;
        tail->arrive_day=d;
        tail->arrive_min=vehicle_go_minu%(24*60);
        p=(PASSENGER_LINK *)malloc(sizeof(PASSENGER_LINK));
        tail->next=p;
        tail=tail->next;

	    time_switch(p_days,&y,&m,&d);
		tail->passenger_state=1;
	    tail->city_or_vehicle=via_veh;
        tail->pass_start_c=city1;
        tail->pass_arrive_c=via_c;
        tail->arrive_year=y;
        tail->arrive_month=m;
        tail->arrive_day=d;
        tail->arrive_min=s_min;

        for(c=0;Pmatrix[city1-1][via_c-1][c].vehicle_number!=via_veh;c++);
        tail->pass_price=Pmatrix[city1-1][via_c-1][c].price;

        p=(PASSENGER_LINK *)malloc(sizeof(PASSENGER_LINK));
        tail->next=p;
        tail=tail->next;
        tail->next=NULL;

/*--------------------------------------------------------*/
	    if(via_c==end_city) //若st_city和第一个途经城市之间不需要倒车
			break;                        //结束本次循环

		city1=via_c;
		via_c=time_path[start_city-1] [end_city-1] [i+1];
		if(via_c==-1&&city1!=end_city)
		    via_c=end_city;
	}
	print();
}
