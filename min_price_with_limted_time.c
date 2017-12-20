#include"travel.h"

/*限时最小费用*/
int veh_ful_perm[5000],fpindex=0;
//存放无途经的起点到终点的坐车的所有可能和可能的个数
int arrive_day,arrive_min;
PASSENGER_LINK buff_state[30],buff_state2[30];
//有时间限制的最小费用策略中最小费用路线状态缓存 以及最短时间路线状态缓存
int sta_num=0;//记录状态数

double bestc=-1;
double cc=0,ccd=0,ccm=0;
int *x;         //一种顺序


way w[100],bestw[100];
int windex=0,bestindex=0;

int v_city_num;
int lim_day,lim_min;
int st_day,st_min;

int tlim_num=0;//时间限制数组下标 

void via_city_timeprice(int s_year,    int s_month,     int s_day,
                        int s_min,     int via_city_num,int * middle_city,
						int start_city,int end_city,    int* lim_day,
						int* lim_min)
{	
	int**full_per; //全排列的每一种情况 
    int via_veh;   //途经车辆 
    int *price;    //存储所有排列的价格和 
    int i=0,j=0,count=1,count_price=0;
    int p_day,p_min; //乘客出发时间 
    int vehicle_go_minu,vehicle_arrive_minu; //列车开车时间
	int wait_vehi_days;  //乘客等待列车的天数 
	int city1,via_c;     //每一段交通工具的起始城市和到达城市 
	int mid_price;
	int start_day;
	int min_price=1000000;
	int no_way=0;
	int min_state_num;
	PASSENGER_LINK min_state[30];
	
	PASSENGER_LINK * tail, * p;
	
	p=(PASSENGER_LINK *)malloc(sizeof(PASSENGER_LINK));
	passengers[pcount]=p;
	tail=p;
	   
    
    price= (int*)malloc(count*sizeof(int));
   
	start_day=cal_min_time(s_year,s_month,s_day);
	
	sta_num=0;
	p_day=start_day;
	mid_price=timeprice_without_via(p_day,s_min,start_city,middle_city [i],
	                                lim_day[i],lim_min[i]);
	i++;
	count_price+=mid_price;
	if(mid_price==0)
	    no_way=1;
	else
	{
		for(j=0;j<via_city_num-1;j++)
	    {
		    p_day=arrive_day;
		    p_min=arrive_min;
		    mid_price=timeprice_without_via(p_day,p_min,middle_city [i],
			          middle_city [i+1],lim_day[i],lim_min[i]);
	        i++;
			if(mid_price==0)
			{
				no_way=1;
				break;
			}
	        else count_price+=mid_price;
	    }
		
		if(mid_price!=0||via_city_num==1)
		{
			p_day=arrive_day;
		    p_min=arrive_min;
			mid_price=timeprice_without_via
	        (p_day,p_min,middle_city [full_per [i] [j]-1],
			end_city,lim_day[i],lim_min[i]);
			i++;
			if(mid_price!=0)
				count_price+=mid_price;
			else 
				no_way=1;
		}
	}
		
	if(no_way==0)
	{
		for(j=0;j<sta_num;j++)
			min_state[j]=buff_state[j];
		min_state_num=sta_num;
	}
	
	for(i=0;i<min_state_num;i++)  //上面的j 表示最小费用下的缓存状态数 
	{
		*tail=min_state[i];
        p=(PASSENGER_LINK *)malloc(sizeof(PASSENGER_LINK));
        tail->next=p;
        tail=tail->next;
        tail->next=NULL;
	}
	if(i!=0)	
	    print();
	else printf("不存在满足要求的路线！\n");
} 


void via_timeprice(int s_year,    int s_month,     int s_day,
                        int s_min,     int via_city_num,int * middle_city,
						int start_city,int end_city,    int limd,
						int limm)
{
	int**full_per; //全排列的每一种情况
    int via_veh;   //途经车辆
    int i,j,count=1;
    int p_day,p_min; //乘客出发时间
    int vehicle_go_minu,vehicle_arrive_minu; //列车开车时间
	int wait_vehi_days;  //乘客等待列车的天数
	int city1,via_c;     //每一段交通工具的起始城市和到达城市
	int min_price=1000000;
	way minw[100];
	int bestin=0;
	int y,m,d;
	int c;

	PASSENGER_LINK * tail, * p;

	p=(PASSENGER_LINK *)malloc(sizeof(PASSENGER_LINK));
	passengers[pcount]=p;
	tail=p;
	tail->next=NULL;

    for(i=2;i<=via_city_num;i++)
        count=count*i;

    full_per=(int**)malloc(count*sizeof(int*));
    for(i=0;i<count;i++)
    	full_per[i]=(int*)malloc(via_city_num*sizeof(int)); //动态申请

	full_permutation(via_city_num,full_per); //得到全排列

	//全局变量赋值
	x=(int*)malloc((via_city_num+2)*sizeof(int));

	v_city_num=via_city_num;
	st_day=cal_min_time(s_year,s_month,s_day);
	st_min=s_min;

	lim_day=limd;
	lim_min=limm;

	for(i=0;i<count;i++)
	{
		windex=0;
		cc=0;
		ccd=0;
		ccm=0;
		x[0]=start_city;
		x[via_city_num+1]=end_city;
		for(j=1;j<=via_city_num;j++)
		    x[j]=middle_city [full_per [i] [j-1]-1];
		BackTrack(0);
		if(bestc<min_price&&bestc>0)
		{
			min_price=bestc;
			bestin=bestindex;
			for(j=0;j<=bestindex;j++)
			    minw[j]=bestw[j];
		}
	}

	printf("乘客的旅行计划是:\n");

	if(bestin==0)
		printf("不存在满足要求的路线！\n");


	else
	{
		p_day=cal_min_time(s_year,s_month,s_day);
		p_min=s_min;

		for(i=0;i<bestin;i++)
		{
			city1=minw[i].city;
			via_c=minw[i+1].city;
			via_veh=minw[i].veh;

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
}


void BackTrack(int t)
{
	int via_veh; //途经车辆
    int i,j;
    int p_day,p_min; //乘客出发时间
    int vehicle_go_minu, vehicle_arrive_minu; //列车开车时间
	int wait_vehi_days;  //乘客等待列车的天数
	int city1,via_c; //每一段交通工具的起始城市和到达城市
	int delta_day,delta_min;
	int pass_city_num;
	int buff_day,buff_min;
	//途径城市个数
	//排好序的价格和 对应的情况的下标

	int wi=0;

	if(t==v_city_num+1)
    {
		//从第p_num-1个点到p_num点有边 从第p_num个点到1点有边
		//且总路径和小于最优解  或目前还不存在最优解
		if((cc<bestc || bestc<0)&&(ccd<lim_day || (ccd==lim_day&&ccm<lim_min)))
        {
			w[windex].city=x[t];
	        w[windex].veh=-1;

			for(i=0;i<=windex;i++)
                bestw[i]=w[i];
            bestc=cc;
			bestindex=windex;
        }
    }
	else
	{
		/*找第一条较优路线上所有的乘车情况
		（通过最短费用策略path得到路线）通过dfs函数找到所有乘车情况*/ 
		int city_path[10]={0};

		for(i=0;path[x[t]-1] [x[t+1]-1] [i]!=-1
		    &&i<city_num&&path[x[t]-1] [x[t+1]-1] [i]!=x[t+1];i++)
			city_path[i]=path[x[t]-1] [x[t+1]-1] [i];
		pass_city_num=i;
	    fpindex=0;
		int pop_vel[30];           //每一维存两个城市之间的车数
		int sum=1;
		double ordered_price1[1000],ordered_price2[1000];               //车组合的总数
		city1=x[t];
	    via_c= path[city1-1] [x[t+1]-1] [0];

		for(i=0;i<=pass_city_num;i++)
		{
			pop_vel[i]=pm[city1-1][via_c-1];
			sum*=pop_vel[i];
			city1= via_c;
			via_c= path[x[t]-1] [x[t+1]-1] [i+1];
			if(via_c==-1&&city1!=x[t+1]) via_c=x[t+1];
		}

		dfs(pass_city_num+1,pass_city_num+1,pop_vel,0); //递归找出遍历
		int **v_f_p;
		v_f_p=(int**)malloc(sizeof(int*)*fpindex);
		for(i=0;i<fpindex;i++)
	    	v_f_p[i]=(int*)malloc(sizeof(int)*(pass_city_num+1));
		order(pass_city_num,x[t],x[t+1],ordered_price1,v_f_p,path);
		//排序遍历结果的价格
		int fpindex_buff=fpindex;
		for(j=0;j<fpindex_buff;j++)
		{
			wi=0;
			p_min=st_min;
	        p_day=st_day;

	        city1=x[t];
	        via_c= path[x[t]-1] [x[t+1]-1] [0];
	        for(i=0;via_c!=-1&&i<=pass_city_num;i++)
	        {
				via_veh=Pmatrix[city1-1][via_c-1][ v_f_p[j][i] ].vehicle_number;
				//车号
				wait_vehi_days=need_day_to_go(p_day,p_min,via_veh,
		        city1,via_c,&vehicle_go_minu,&vehicle_arrive_minu);

	            p_day=p_day+wait_vehi_days+(vehicle_arrive_minu/(24*60));

	            w[windex].city=city1;
	            w[windex].veh=via_veh;
	            windex++;
	            wi++;

	            if(via_c==x[t+1]) //若start_city和第一个途经城市之间不需要倒车
		            break;          //结束本次循环

		        city1=via_c;
		        via_c=path[x[t]-1] [x[t+1]-1] [i+1];

		        if(via_c==-1&&city1!=x[t+1])
		            via_c=x[t+1];
	        }
            delta_day=p_day-st_day; //计算所需时间
            delta_min=p_min-st_min;
            if(delta_min<0)
            {
                delta_day--;
    	        delta_min=delta_min+1440;
            }
            
            //所需时间小于限制时间且价格小于目前已有的最小价格 
	        if((delta_day+ccd<lim_day || (delta_day+ccd==lim_day&&delta_min+ccm<lim_min))
	           &&((cc+ordered_price1[j])<bestc||bestc<0))
			{
	        	/*保存现场*/
				ccd+=delta_day;
	        	ccm+=delta_min;
				cc+=ordered_price1[j];
				buff_day=st_day;
				buff_min=st_min;
				st_day=p_day;
				st_min=p_min;

                BackTrack(t+1);
				windex-=wi;
				/*取出现场*/ 
				st_day=buff_day;
				st_min=buff_min;

                cc-=ordered_price1[j];
                ccd-=delta_day;
	        	ccm-=delta_min;
	        }
	        else windex-=wi;
		}

		//以下为最短时间路线遍历找最小价格
		//寻找途径城市个数
		/*找第二条较优路线上所有的乘车情况
		（通过最小时间策略time_path得到路线）
		通过dfs函数找到所有乘车情况*/ 
		least_time(x[t],st_day,st_min);
		int ***time_path_buff;
		int count1,count2,count3;

		time_path_buff=(int***)malloc(city_num*sizeof(int**));
		for(count1=0;count1<city_num;count1++)
		{
			time_path_buff[count1]=(int**)malloc(city_num*sizeof(int*));
			for(count2=0;count2<city_num;count2++)
			{
				time_path_buff[count1][count2]=(int*)malloc(city_num*sizeof(int));
				for(count3=0;count3<city_num;count3++)
					time_path_buff[count1][count2][count3]=
					time_path[count1][count2][count3];
			}
		}

		for(i=0;time_path_buff[x[t]-1] [x[t+1]-1] [i]!=-1
		    &&i<city_num&&time_path_buff[x[t]-1] [x[t+1]-1] [i]!=x[t+1];i++);
			pass_city_num=i;

			sum=1;                   //车组合的总数
			city1=x[t];
			via_c= time_path_buff[x[t]-1] [x[t+1]-1] [0];

			for(i=0;i<=pass_city_num;i++)
			{
				pop_vel[i]=pm[city1-1][via_c-1];
				sum*=pop_vel[i];
				city1= via_c;
				via_c= time_path_buff[x[t]-1] [x[t+1]-1] [i+1];
				if(via_c==-1&&city1!=x[t+1]) via_c=x[t+1];
			}
			fpindex=0;
			dfs(pass_city_num+1,pass_city_num+1,pop_vel,0); //递归找出遍历

			int **v_f_p1;
			v_f_p1=(int**)malloc(sizeof(int*)*fpindex);
			for(i=0;i<fpindex;i++)
	    		v_f_p1[i]=(int*)malloc(sizeof(int)*(pass_city_num+1));

			order(pass_city_num,x[t],x[t+1],ordered_price2,v_f_p1,time_path_buff);
			//排序遍历结果的价格

			int fpindex_buff1=fpindex;
			for(j=0;j<fpindex_buff1;j++)
			{
				wi=0;
				p_min=st_min;
	        	p_day=st_day;

	        	city1=x[t];
	        	via_c= time_path_buff[x[t]-1] [x[t+1]-1] [0];
	        	for(i=0;via_c!=-1&&i<=pass_city_num;i++)
	        	{
	            	via_veh=Pmatrix[city1-1][via_c-1][ v_f_p1[j][i] ].vehicle_number;
					//车号

					w[windex].city=city1;
	            	w[windex].veh=via_veh;
	            	windex++;
	            	wi++;

		        	wait_vehi_days=need_day_to_go(p_day,p_min,via_veh,
		        	city1,via_c,&vehicle_go_minu,&vehicle_arrive_minu);

	            	p_day=p_day+wait_vehi_days+(vehicle_arrive_minu/(24*60));
		        //新的p_days 要在旧的的基础上加上等车天数和坐车天数
	            	p_min=vehicle_arrive_minu%(24*60);

	            	if(via_c==x[t+1]) //若start_city和第一个途经城市之间不需要倒车
		            	break;          //结束本次循环

		        	city1=via_c;
		        	via_c=time_path_buff[x[t]-1] [x[t+1]-1] [i+1];

		        	if(via_c==-1&&city1!=x[t+1])
		            	via_c=x[t+1];
	        	}
            	delta_day=p_day-st_day; //计算所需时间
            	delta_min=p_min-st_min;
            	if(delta_min<0)
            	{
                	delta_day--;
    	        	delta_min=delta_min+1440;
            	}
            	//所需时间小于限制时间且价格小于目前已有的最小价格 
	        	if((delta_day+ccd<lim_day || (delta_day+ccd==lim_day&&delta_min+ccm<lim_min))
	           	&&(cc+ordered_price2[j]<bestc||bestc<0))
				{
	        		ccd+=delta_day;
	        		ccm+=delta_min;
					cc+=ordered_price2[j];

					buff_day=st_day;
					buff_min=st_min;

					st_day=p_day;
					st_min=p_min;
					/*保存当前现场 递归*/
                	BackTrack(t+1);

					windex-=wi;
					st_day=buff_day;
					st_min=buff_min;

                	cc-=ordered_price2[j];
                	ccd-=delta_day;
	        		ccm-=delta_min;
	        	}
	        	else windex-=wi;
			}
	}
}

/*无途经限时最小费用策略
调用一次timeprice_without_via
得到最小费用mid_price
*/
void no_via_city_timeprice(int s_year,    int s_month,     int s_day,
                           int s_min,     int start_city,int end_city,
						   int lim_day,   int lim_min)
{
    int i,j;
    int p_day; //乘客出发时间
	int mid_price=0;

	PASSENGER_LINK min_state[30];

	PASSENGER_LINK * tail, * p;

	p=(PASSENGER_LINK *)malloc(sizeof(PASSENGER_LINK));
	passengers[pcount]=p;
	tail=p;

	p_day=cal_min_time(s_year,s_month,s_day);

	j=0;
	sta_num=0;
	mid_price=timeprice_without_via(p_day,s_min,start_city,end_city,lim_day,lim_min);

	if(mid_price>0)
	{
		for(j=0;j<sta_num;j++)
			min_state[j]=buff_state[j];
	}

	for(i=0;i<sta_num;i++)  //上面的j 表示最小费用下的缓存状态数
	{
		*tail=min_state[i];
        p=(PASSENGER_LINK *)malloc(sizeof(PASSENGER_LINK));
        tail->next=p;
        tail=tail->next;
        tail->next=NULL;
	}

	if(i!=0)
	    print();
	else printf("不存在满足要求的路线！\n");
}


/*两城市之间（无途经）的限时最小费用计算*/
int timeprice_without_via(int s_day,int s_min,int start_city,
                  int end_city,int lim_day,int lim_min)
{
	int via_veh; //途经车辆
    int i,j;
    int p_days,p0_days; //乘客出发时间
    int vehicle_go_minu, vehicle_arrive_minu; //列车开车时间
	int wait_vehi_days;  //乘客等待列车的天数
	int city1,via_c; //每一段交通工具的起始城市和到达城市
	int s1_min;
	int delta_day,delta_min;
	int sta_num_buff;
	int min_price1=100000,min_price2=100000;
	int arrive_day_buff,arrive_day_buff2,arrive_min_buff,arrive_min_buff2;

	int mid_num=sta_num;//中间状态数（缓存状态）
	int c;
	int pass_city_num;
	//途径城市个数
	//排好序的价格和 对应的情况的下标

	double ordered_price[1000];

	int year,mon,day;
/*计算最小费用策略路线时间
若所需时间小于限制时间则得到最小费用*/	
	
	s1_min=s_min;
	p_days=s_day;
	p0_days=s_day;
	city1=start_city;
	via_c= path[start_city-1] [end_city-1] [0];
	
	for(i=0;via_c!=-1&&i<city_num;i++)
	{
	    via_veh=arcs[city1-1][via_c-1].mini_pri_veh;  //车号
		wait_vehi_days=need_day_to_go(p_days,s_min,via_veh,
		city1,via_c,&vehicle_go_minu,&vehicle_arrive_minu);

		time_switch(p_days+wait_vehi_days,&year,&mon,&day);
	    buff_state[mid_num].arrive_min     =s_min;
		buff_state[mid_num].arrive_day     =day;
		buff_state[mid_num].arrive_month   =mon;
		buff_state[mid_num].arrive_year    =year;
		buff_state[mid_num].city_or_vehicle=city1;
		buff_state[mid_num].passenger_state=2;
		buff_state[mid_num].pass_start_c   =0;
		buff_state[mid_num].pass_arrive_c  =0;

		mid_num++;

	    p_days=p_days+wait_vehi_days+(vehicle_arrive_minu/(24*60));
		//新的p_days 要在旧的的基础上加上等车天数和坐车天数
	    s_min=vehicle_arrive_minu%(24*60);

	    time_switch(p_days,&year,&mon,&day);
		buff_state[mid_num].passenger_state=1;
	    buff_state[mid_num].city_or_vehicle=via_veh;
        buff_state[mid_num].pass_start_c   =city1;
        buff_state[mid_num].pass_arrive_c  =via_c;
        buff_state[mid_num].arrive_year    =year;
        buff_state[mid_num].arrive_month   =mon;
        buff_state[mid_num].arrive_day     =day;
        buff_state[mid_num].arrive_min     =s_min;
		buff_state[mid_num].next           =NULL;
        for(c=0;Pmatrix[city1-1][via_c-1][c].vehicle_number!=via_veh;c++);
        buff_state[mid_num].pass_price=Pmatrix[city1-1][via_c-1][c].price;

	    mid_num++;

	    if(via_c==end_city) //若start_city和第一个途经城市之间不需要倒车
		    break;                        //结束本次循环

		city1=via_c;
		via_c=path[start_city-1] [end_city-1] [i+1];

		if(via_c==-1&&city1!=end_city)
		    via_c=end_city;
	}
    delta_day=p_days-p0_days;
    delta_min=s_min-s1_min;
    if(delta_min<0)
    {
        delta_day--;
    	delta_min=delta_min+1440;
    }
	if(delta_day<lim_day || (delta_day==lim_day&&delta_min<lim_min))
	//若最小值小于时间限制 则不需要进行递归
	{
		arrive_day=p_days;
		arrive_min=s_min;
		sta_num=mid_num;
		return new_price[start_city-1][end_city-1];
	}
	
	/*最小费用策略的最优解不满足时间限制*/ 
	else
	{
		/*找第一条较优路线上所有的乘车情况
		（通过最短费用策略path得到路线）
		通过dfs函数找到所有乘车情况,计算出每一种情况的费用，
		并对费用和对应的乘车情况排序*/ 
		
		//寻找途径城市个数
		for(i=0;path[start_city-1] [end_city-1] [i]!=-1
		&&i<city_num&&path[start_city-1] [end_city-1] [i]!=end_city;i++);
		pass_city_num=i;
	    fpindex=0;
		int pop_vel[30];           //每一维存两个城市之间的车数
		int sum=1;                   //车组合的总数
		city1=start_city;
		via_c= path[start_city-1] [end_city-1] [0];
		for(i=0;i<=pass_city_num;i++)
		{
			pop_vel[i]=pm[city1-1][via_c-1];
			sum*=pop_vel[i];
			city1= via_c;
			via_c= path[start_city-1] [end_city-1] [i+1];
			if(via_c==-1&&city1!=end_city) via_c=end_city;
		}

		dfs(pass_city_num+1,pass_city_num+1,pop_vel,0); //递归找出遍历
		int **v_f_p;
		v_f_p=(int**)malloc(sizeof(int*)*fpindex);
		for(i=0;i<fpindex;i++)
	    	v_f_p[i]=(int*)malloc(sizeof(int)*(pass_city_num+1));
		order(pass_city_num,start_city,end_city,ordered_price,v_f_p,path);
		//排序遍历结果的价格
		//费用从小到大计算每一种情况所需时间
		for(j=0;j<fpindex;j++)
		{
			mid_num=sta_num;
			s1_min=s_min;
	        p_days=s_day;
	        p0_days=p_days;
	        city1=start_city;
	        via_c= path[start_city-1] [end_city-1] [0];
	        for(i=0;via_c!=-1&&i<city_num;i++)
	        {
				via_veh=Pmatrix[city1-1][via_c-1][ v_f_p[j][i] ].vehicle_number;
				//车号
				wait_vehi_days=need_day_to_go(p_days,s_min,via_veh,
		        city1,via_c,&vehicle_go_minu,&vehicle_arrive_minu);

				time_switch(p_days+wait_vehi_days,&year,&mon,&day);
	            buff_state[mid_num].arrive_min     =s_min;
		        buff_state[mid_num].arrive_day     =day;
		        buff_state[mid_num].arrive_month   =mon;
		        buff_state[mid_num].arrive_year    =year;
		        buff_state[mid_num].city_or_vehicle=city1;
		        buff_state[mid_num].passenger_state=2;
		        buff_state[mid_num].pass_start_c   =0;
		        buff_state[mid_num].pass_arrive_c  =0;

		        mid_num++;

	            p_days=p_days+wait_vehi_days+(vehicle_arrive_minu/(24*60));
		        //新的p_days 要在旧的的基础上加上等车天数和坐车天数
	            s_min=vehicle_arrive_minu%(24*60);

	            time_switch(p_days,&year,&mon,&day);
		        buff_state[mid_num].passenger_state=1;
	            buff_state[mid_num].city_or_vehicle=via_veh;
                buff_state[mid_num].pass_start_c   =city1;
                buff_state[mid_num].pass_arrive_c  =via_c;
                buff_state[mid_num].arrive_year    =year;
                buff_state[mid_num].arrive_month   =mon;
                buff_state[mid_num].arrive_day     =day;
                buff_state[mid_num].arrive_min     =s_min;
				buff_state[mid_num].next           =NULL;
                for(c=0;Pmatrix[city1-1][via_c-1][c].vehicle_number!=via_veh;c++);
                buff_state[mid_num].pass_price=Pmatrix[city1-1][via_c-1][c].price;

	            mid_num++;

	            if(via_c==end_city) //若start_city和第一个途经城市之间不需要倒车
		            break;          //结束本次循环

		        city1=via_c;
		        via_c=path[start_city-1] [end_city-1] [i+1];

		        if(via_c==-1&&city1!=end_city)
		            via_c=end_city;
	        }
	        
            delta_day=p_days-p0_days; //计算所需时间
            delta_min=s_min-s1_min;
            if(delta_min<0)
            {
                delta_day--;
    	        delta_min=delta_min+1440;
            }
            
            /*若所需时间小于限制时间
            保存价格和路线 结束循环
        最后得到最小价格price1*/

	        if(delta_day<lim_day || (delta_day==lim_day&&delta_min<lim_min))
	        {
	        	arrive_day_buff=p_days;
		        arrive_min_buff=s_min;
		        sta_num_buff=mid_num;
		        min_price1=ordered_price[j]; //存储当前的最小费用
		        break;
	        }
	              //若找到小于限制时间的时间 结束循环
		}

		//以下为最短时间路线遍历找最小价格
		//寻找途径城市个数
		
/*找第二条较优路线上所有的乘车情况（通过最小时间策略time_path得到路线）
通过dfs函数找到所有乘车情况计算出每一种情况的费用，
并对费用和对应的乘车情况排序*/ 
		
		least_time(start_city,s_day,s_min);
		for(i=0;time_path[start_city-1] [end_city-1] [i]!=-1
		    &&i<city_num&&time_path[start_city-1] [end_city-1] [i]!=end_city;i++);
		pass_city_num=i;

		sum=1;                   //车组合的总数
		city1=start_city;
		via_c= time_path[start_city-1] [end_city-1] [0];

		for(i=0;i<=pass_city_num;i++)
		{
			pop_vel[i]=pm[city1-1][via_c-1];
			sum*=pop_vel[i];
			city1= via_c;
			via_c= time_path[start_city-1] [end_city-1] [i+1];
			if(via_c==-1&&city1!=end_city) via_c=end_city;
		}
		fpindex=0;
		dfs(pass_city_num+1,pass_city_num+1,pop_vel,0); //递归找出遍历
		int **v_f_p1;
		v_f_p1=(int**)malloc(sizeof(int*)*fpindex);
		for(i=0;i<fpindex;i++)
	    	v_f_p1[i]=(int*)malloc(sizeof(int)*(pass_city_num+1));
		order(pass_city_num,start_city,end_city,ordered_price,v_f_p1,time_path);
		//排序遍历结果的价格
//费用从小到大计算每一种情况所需时间
		for(j=0;j<fpindex;j++)
		{
			mid_num=sta_num;
			s1_min=s_min;
	        p_days=s_day;
	        p0_days=p_days;
	        city1=start_city;
	        via_c= time_path[start_city-1] [end_city-1] [0];
	        for(i=0;via_c!=-1&&i<city_num;i++)
	        {
	            via_veh=Pmatrix[city1-1][via_c-1][ v_f_p1[j][i] ].vehicle_number;
				//车号
		        wait_vehi_days=need_day_to_go(p_days,s_min,via_veh,
		        city1,via_c,&vehicle_go_minu,&vehicle_arrive_minu);

				time_switch(p_days+wait_vehi_days,&year,&mon,&day);
	            buff_state2[mid_num].arrive_min		=s_min;
		        buff_state2[mid_num].arrive_day		=day;
		        buff_state2[mid_num].arrive_month   =mon;
		        buff_state2[mid_num].arrive_year    =year;
		        buff_state2[mid_num].city_or_vehicle=city1;
		        buff_state2[mid_num].passenger_state=2;
		        buff_state2[mid_num].pass_start_c	=0;
		        buff_state2[mid_num].pass_arrive_c	=0;

		        mid_num++;

	            p_days=p_days+wait_vehi_days+(vehicle_arrive_minu/(24*60));
		        //新的p_days 要在旧的的基础上加上等车天数和坐车天数
	            s_min=vehicle_arrive_minu%(24*60);

	            time_switch(p_days,&year,&mon,&day);
		        buff_state2[mid_num].passenger_state=1;
	            buff_state2[mid_num].city_or_vehicle=via_veh;
                buff_state2[mid_num].pass_start_c	=city1;
                buff_state2[mid_num].pass_arrive_c	=via_c;
                buff_state2[mid_num].arrive_year	=year;
                buff_state2[mid_num].arrive_month	=mon;
                buff_state2[mid_num].arrive_day		=day;
                buff_state2[mid_num].arrive_min		=s_min;
				buff_state2[mid_num].next           =NULL;
                for(c=0;Pmatrix[city1-1][via_c-1][c].vehicle_number!=via_veh;c++);
                buff_state2[mid_num].pass_price=Pmatrix[city1-1][via_c-1][c].price;

	            mid_num++;

	            if(via_c==end_city) //若start_city和第一个途经城市之间不需要倒车
		            break;          //结束本次循环

		        city1=via_c;
		        via_c=time_path[start_city-1] [end_city-1] [i+1];

		        if(via_c==-1&&city1!=end_city)
		            via_c=end_city;
	        }
            delta_day=p_days-p0_days; //计算所需时间
            delta_min=s_min-s1_min;
            if(delta_min<0)
            {
                delta_day--;
    	        delta_min=delta_min+1440;
            }
            
	        if(delta_day<lim_day || (delta_day==lim_day&&delta_min<lim_min))
	        {
	        	arrive_day_buff2=p_days;
		        arrive_min_buff2=s_min;
		        min_price2=ordered_price[j];
		        break;
	        }
	              //若找到小于限制时间的时间 结束循环
		}
		//若两种路线都没有符合要求的路线则没有符合要求的路线 
		if(min_price2==min_price1&&min_price2==100000)
		    return 0;
		//找出价格较小的一种路线 保存路线信息 
		else if(min_price2<min_price1)
		{
			for(i=sta_num;i<mid_num;i++)
			    buff_state[i]=buff_state2[i];
			sta_num=mid_num;
			arrive_day=arrive_day_buff2;
		    arrive_min=arrive_min_buff2;
			return min_price2;
		}
		else
		{
			arrive_day=arrive_day_buff;
		    arrive_min=arrive_min_buff;
			sta_num=sta_num_buff;
			return min_price1;
		}
	}
}

void dfs(int hop,int m,int* num,int per)  //递归求出所有城市之间所有车的全排列
{
	int i;
	if(m==0)
	{
		veh_ful_perm[fpindex]=per;//veh_ful_perm是一维数组，存全排列所有情况
		fpindex++;                //fpindex为该数组下标
		return;
	}
	for(i=1;i<=num[hop-m];i++)
	{
		per=per*10+i;
		dfs(hop,m-1,num,per);
		per=(per-i)/10;
	}
}


void swap_double(double *a, double *b)
{
	double temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
void swap_int(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void order(int sum,int start_city,int end_city,double * will_be_sorted,int** vfp,int***tem_path)
{
	int i,j,via_c,city1;
	int h,n;
	double temp;
	int base;
	for(i=0;i<fpindex;i++)              //计算每种车的排列对应的钱数
	{
		base=(int)pow(10,(double)sum);
		city1=start_city;
    	via_c= tem_path[start_city-1] [end_city-1] [0];
    	temp=0;
    	n=veh_ful_perm[i];
		for(j=0;n>0;j++)
		{
			h=n/base;
	    	temp+=Pmatrix[city1-1][via_c-1][h-1].price;
	    	city1= via_c;
			via_c= tem_path[start_city-1] [end_city-1] [j+1];
			if(via_c==-1) via_c=end_city;
			n=n%base;
			base=base/10;
		}
		will_be_sorted[i]=temp;
	}
	for (i = 0; i < fpindex; i++)             //冒泡排序，最小的在第一个
	{
		//每一次由底至上地上升
		for (j = fpindex-1; j > i; j--)
		{
			if (will_be_sorted[j] < will_be_sorted[j-1])
			{
				swap_double(&will_be_sorted[j], &will_be_sorted[j-1]);
				swap_int(&veh_ful_perm[j],&veh_ful_perm[j-1]);     //价格排序的同时将对应的车 的排列进行排序
			}
		}
	}
	for(i=0;i<fpindex;i++)              //计算每种车的排列对应的钱数
	{
		base=(int)pow(10,(double)sum);
		city1=start_city;
    	via_c= tem_path[start_city-1] [end_city-1] [0];
    	n=veh_ful_perm[i];
		for(j=0;n>0;j++)
		{
			h=n/base;
	    	city1= via_c;
			via_c= tem_path[start_city-1] [end_city-1] [j+1];
			if(via_c==-1) via_c=end_city;
			n=n%base;
			base=base/10;
			vfp[i][j]=h-1;
		}
	}
}

