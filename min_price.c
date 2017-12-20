#include"travel.h"
/*计算两点之间交通工具的最少费用*/
void calcu_price()
{
	int i,j,k,count,transport_number;
	int min;

	new_price=(double **)malloc(sizeof(double *)*city_num);
	for(count=0;count<=city_num-1;count++)
	    new_price[count]=(double *)malloc(sizeof(double )*city_num);
		//new_price保存任意两点之间最少费用

	for(i=0;i<=city_num-1;i++)   //找到每两个城市间的最小费用,即所有车之间找一个费用最小值
	    for(j=0;j<=city_num-1;j++)
	    {
	   	    if(i!=j&&pm[i][j]>0)   //若两个城市不是同一个城市并且两城市之间有交通工具 ，则计算
	   	    {
	   	    	min=MAX2;
				for(k=0;k<pm[i][j];k++)  //若在两城市之间有车，pm[i][j]存的是两城市之间交通工具数量
				{
					if(Pmatrix[i][j][k].price<=min) //若不是同一个城市且价格不大于最小价格
	         		{
	         	 		min=Pmatrix[i][j][k].price;
	         	     	transport_number=Pmatrix[i][j][k].vehicle_number;
	         		}
				}
				//存 ij两个城市之间的最小费用，以及最小费用对应的车
				arcs[i][j].mini_price=min;
		        arcs[i][j].mini_pri_veh=transport_number;
			}
	    }

	 //找到任意两个直达城市之间的最小费用之后，以每一个城市为源调用DIJ计算任意两个城市之间的最小费用及路径
	 for(i=0;i<=city_num-1;i++)
	 {
	 	 ShortestPath_DIJ(i,arcs);
 	 	 for(j=0;j<=city_num-1;j++)
	 		 new_price[i][j]=D[j];
	 }
}

void via_city_price(int s_year,int s_month,int s_day,int s_min,
int via_city_num,int * middle_city,int start_city,int end_city)
//有途经城市的最小价钱
{
    int**full_per; //全排列的每一种情况
    int via_veh; //途经车辆
    int i,j,count=1,count_price=0,min_price_mid=1000000,condition;
    int p_days; //乘客出发时间
    int vehicle_go_minu,vehicle_arrive_minu; //列车开车时间
	int wait_vehi_days;  //乘客等待列车的天数
	int city1,via_c; //每一段交通工具的起始城市和到达城市
	int c;

	PASSENGER_LINK * tail, * p;
	p=(PASSENGER_LINK *)malloc(sizeof(PASSENGER_LINK));
	passengers[pcount]=p;
	tail=p;

    int y, m, d; //由天数转化而来的年月日

    for(i=2;i<=via_city_num;i++)
        count=count*i;

    full_per=(int**)malloc(count*sizeof(int*));
    for(i=0;i<count;i++)
    	full_per[i]=(int*)malloc(via_city_num*sizeof(int)); //动态申请

	full_permutation(via_city_num,full_per); //得到全排列

	for(i=0;i<count;i++)   //计算每一种全排列的价钱 找到最小价钱
	{
		count_price=new_price [start_city-1]
		[ middle_city [full_per [i] [0]-1] -1 ];
		for(j=0;j<via_city_num-1;j++)
			count_price=count_price+
			new_price [middle_city[full_per [i] [j]-1 ]-1]
			[middle_city[full_per [i] [j+1]-1 ]-1];

		count_price=count_price+
		new_price[middle_city[ full_per [i] [j]-1 ]-1] [end_city-1];
		if(count_price<min_price_mid)  //找到最小费用
		{
			min_price_mid=count_price;
			condition=i;
		}
	}
	p_days=cal_min_time(s_year,s_month,s_day);

	printf("乘客的旅行计划是:\n");

	city1=start_city;
	via_c= path[start_city-1][ middle_city [full_per[condition] [0]-1]-1] [0];
	for(i=0;via_c!=-1&&i<city_num;i++)
	{
	    via_veh=arcs[city1-1][via_c-1].mini_pri_veh;  //车号
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
	    if(via_c==middle_city[full_per[condition][0]-1]) //若st_city和第一个途经城市之间不需要倒车
			break;                        //结束本次循环

		city1=via_c;
		via_c=path[start_city-1] [middle_city[full_per[condition][0]-1]-1] [i+1];
		if(via_c==-1&&city1!=middle_city[full_per[condition][0]-1])
		    via_c=middle_city[full_per[condition][0]-1];
	}

	for(i=0;i<via_city_num-1;i++)
	{
		//出发城市和到达城市
		city1=middle_city[full_per[condition][i]-1];
		via_c=path [city1-1] [middle_city[full_per[condition][i+1]-1]-1] [0];

		for(j=0;via_c!=-1;j++)
		{
	        via_veh=arcs[city1-1] [via_c-1].mini_pri_veh;  //车号
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
			if(via_c==middle_city[full_per[condition] [i+1]-1])
			//若st_city和第一个途经城市之间不需要倒车 结束本次循环
			    break;

			city1=via_c;
			via_c=path[middle_city[full_per [condition] [i]-1]-1]
			[middle_city[full_per [condition] [i+1]-1] -1] [j+1];
			if(via_c==-1&&city1!=middle_city[full_per[condition] [i+1]-1])
		        via_c=middle_city[full_per[condition] [i+1]-1];
		}
	}

	city1=middle_city[full_per[condition][via_city_num-1]-1];
	via_c=path [city1-1] [end_city-1] [0];

	for(i=0;via_c!=-1&&i<city_num;i++)
	{
	    via_veh=arcs[city1-1] [via_c-1].mini_pri_veh;
		//车号
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
			break;    //结束本次循环

		city1=via_c;
		via_c=path [middle_city[full_per [condition] [via_city_num-1]-1] -1] [end_city-1] [i+1];
		if(via_c==-1&&city1!=end_city)
		    via_c=end_city;
	}
	print();
}

/*-----------------无途经城市的输出---------------------*/
void output_price(int s_year,int s_month,int s_day,int s_min,
                  int start_city,int end_city)
{

	int via_veh; //途经车辆
    int i;
    int p_days; //乘客出发时间
    int vehicle_go_minu,vehicle_arrive_minu; //列车开车时间
	int wait_vehi_days;  //乘客等待列车的天数
	int city1,via_c; //每一段交通工具的起始城市和到达城市
	PASSENGER_LINK* tail,*p;

	p=(PASSENGER_LINK *)malloc(sizeof(PASSENGER_LINK));
	passengers[pcount]=p;
	tail=p;

	int y, m, d; //由天数转化而来的年月日
	int c;
	printf("乘客的旅行计划是:\n");

	p_days=cal_min_time(s_year,s_month,s_day);

	city1=start_city;
	via_c= path[start_city-1] [end_city-1] [0];
	for(i=0;via_c!=-1&&i<city_num;i++)
	{
	    via_veh=arcs[city1-1][via_c-1].mini_pri_veh;  //车号
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
		via_c=path[start_city-1] [end_city-1] [i+1];

		if(via_c==-1&&city1!=end_city)
		    via_c=end_city;
	}
	print();
}

int need_day_to_go(int Day,int minute,int t_num,
int sta_city,int end_city,int*vehicle_go_minu,int*vehicle_arrive_minu)
{
	int startday,duringday;
	int i;
	int mol;     //表示开车时间距离此人到达时间的天数
	int tim1,tim2;
	startday=vehicle[t_num-1][0].minute;
	//每种交通工具的开车的天时间
	duringday=Tnumber[t_num-1].times;
	//每趟车的运行时间

	mol=(Day-startday)%duringday;

	//2i-2  2i-1对应i号车
	for(i=1;vehicle[2*t_num-2][i].via_city!=sta_city
		&&vehicle[2*t_num-2][i].via_city!=end_city;i++);
    if(vehicle[2*t_num-2][i].via_city==sta_city)
    {
		tim1=vehicle[2*t_num-2][i].minute;
		for(;vehicle[2*t_num-2][i].via_city!=end_city;i++);
		tim2=vehicle[2*t_num-2][i].minute;
	}
	else
	{
		for(i=1;vehicle[2*t_num-1][i].via_city!=sta_city;i++);
    	tim1=vehicle[2*t_num-1][i].minute;
    	for(;vehicle[2*t_num-1][i].via_city!=end_city;i++);
		tim2=vehicle[2*t_num-1][i].minute;
    }

	*vehicle_go_minu=tim1%(24*60);
	*vehicle_arrive_minu=tim2;

	if(mol==0&&*vehicle_go_minu>=minute)     //表示乘客可以坐今天的此班车
	    return 0;
	else if(mol==0&&*vehicle_go_minu<minute)   //表示乘客错过今天的这班车
	    return duringday;
	else                                 //这趟车在乘客到的这天没有
	    return duringday-mol;
}
