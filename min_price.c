#include"travel.h"
/*��������֮�佻ͨ���ߵ����ٷ���*/
void calcu_price()
{
	int i,j,k,count,transport_number;
	int min;

	new_price=(double **)malloc(sizeof(double *)*city_num);
	for(count=0;count<=city_num-1;count++)
	    new_price[count]=(double *)malloc(sizeof(double )*city_num);
		//new_price������������֮�����ٷ���

	for(i=0;i<=city_num-1;i++)   //�ҵ�ÿ�������м����С����,�����г�֮����һ��������Сֵ
	    for(j=0;j<=city_num-1;j++)
	    {
	   	    if(i!=j&&pm[i][j]>0)   //���������в���ͬһ�����в���������֮���н�ͨ���� �������
	   	    {
	   	    	min=MAX2;
				for(k=0;k<pm[i][j];k++)  //����������֮���г���pm[i][j]�����������֮�佻ͨ��������
				{
					if(Pmatrix[i][j][k].price<=min) //������ͬһ�������Ҽ۸񲻴�����С�۸�
	         		{
	         	 		min=Pmatrix[i][j][k].price;
	         	     	transport_number=Pmatrix[i][j][k].vehicle_number;
	         		}
				}
				//�� ij��������֮�����С���ã��Լ���С���ö�Ӧ�ĳ�
				arcs[i][j].mini_price=min;
		        arcs[i][j].mini_pri_veh=transport_number;
			}
	    }

	 //�ҵ���������ֱ�����֮�����С����֮����ÿһ������ΪԴ����DIJ����������������֮�����С���ü�·��
	 for(i=0;i<=city_num-1;i++)
	 {
	 	 ShortestPath_DIJ(i,arcs);
 	 	 for(j=0;j<=city_num-1;j++)
	 		 new_price[i][j]=D[j];
	 }
}

void via_city_price(int s_year,int s_month,int s_day,int s_min,
int via_city_num,int * middle_city,int start_city,int end_city)
//��;�����е���С��Ǯ
{
    int**full_per; //ȫ���е�ÿһ�����
    int via_veh; //;������
    int i,j,count=1,count_price=0,min_price_mid=1000000,condition;
    int p_days; //�˿ͳ���ʱ��
    int vehicle_go_minu,vehicle_arrive_minu; //�г�����ʱ��
	int wait_vehi_days;  //�˿͵ȴ��г�������
	int city1,via_c; //ÿһ�ν�ͨ���ߵ���ʼ���к͵������
	int c;

	PASSENGER_LINK * tail, * p;
	p=(PASSENGER_LINK *)malloc(sizeof(PASSENGER_LINK));
	passengers[pcount]=p;
	tail=p;

    int y, m, d; //������ת��������������

    for(i=2;i<=via_city_num;i++)
        count=count*i;

    full_per=(int**)malloc(count*sizeof(int*));
    for(i=0;i<count;i++)
    	full_per[i]=(int*)malloc(via_city_num*sizeof(int)); //��̬����

	full_permutation(via_city_num,full_per); //�õ�ȫ����

	for(i=0;i<count;i++)   //����ÿһ��ȫ���еļ�Ǯ �ҵ���С��Ǯ
	{
		count_price=new_price [start_city-1]
		[ middle_city [full_per [i] [0]-1] -1 ];
		for(j=0;j<via_city_num-1;j++)
			count_price=count_price+
			new_price [middle_city[full_per [i] [j]-1 ]-1]
			[middle_city[full_per [i] [j+1]-1 ]-1];

		count_price=count_price+
		new_price[middle_city[ full_per [i] [j]-1 ]-1] [end_city-1];
		if(count_price<min_price_mid)  //�ҵ���С����
		{
			min_price_mid=count_price;
			condition=i;
		}
	}
	p_days=cal_min_time(s_year,s_month,s_day);

	printf("�˿͵����мƻ���:\n");

	city1=start_city;
	via_c= path[start_city-1][ middle_city [full_per[condition] [0]-1]-1] [0];
	for(i=0;via_c!=-1&&i<city_num;i++)
	{
	    via_veh=arcs[city1-1][via_c-1].mini_pri_veh;  //����
		wait_vehi_days=need_day_to_go(p_days,s_min,via_veh,
		city1,via_c,&vehicle_go_minu,&vehicle_arrive_minu);

	    time_switch(p_days+wait_vehi_days,&y,&m,&d);

	    p_days=p_days+wait_vehi_days+(vehicle_arrive_minu/(24*60));
		//�µ�p_days Ҫ�ھɵĵĻ����ϼ��ϵȳ���������������
	    s_min=vehicle_arrive_minu%(24*60);

/*----------����ǰ�ÿ�״̬���ÿ͵���״̬�����-----------*/

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
	    if(via_c==middle_city[full_per[condition][0]-1]) //��st_city�͵�һ��;������֮�䲻��Ҫ����
			break;                        //��������ѭ��

		city1=via_c;
		via_c=path[start_city-1] [middle_city[full_per[condition][0]-1]-1] [i+1];
		if(via_c==-1&&city1!=middle_city[full_per[condition][0]-1])
		    via_c=middle_city[full_per[condition][0]-1];
	}

	for(i=0;i<via_city_num-1;i++)
	{
		//�������к͵������
		city1=middle_city[full_per[condition][i]-1];
		via_c=path [city1-1] [middle_city[full_per[condition][i+1]-1]-1] [0];

		for(j=0;via_c!=-1;j++)
		{
	        via_veh=arcs[city1-1] [via_c-1].mini_pri_veh;  //����
			wait_vehi_days=need_day_to_go(p_days,s_min,via_veh,
			city1,via_c,&vehicle_go_minu,&vehicle_arrive_minu);

		    time_switch(p_days+wait_vehi_days,&y,&m,&d);

	        p_days=p_days+wait_vehi_days+(vehicle_arrive_minu/(24*60));
			//�µ�p_days Ҫ�ھɵĵĻ����ϼ��ϵȳ���������������
	        s_min=vehicle_arrive_minu%(24*60);

/*----------����ǰ�ÿ�״̬���ÿ͵���״̬�����-----------*/
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
			//��st_city�͵�һ��;������֮�䲻��Ҫ���� ��������ѭ��
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
		//����
		wait_vehi_days=need_day_to_go(p_days,s_min,via_veh,
		city1,via_c,&vehicle_go_minu,&vehicle_arrive_minu);

	    time_switch(p_days+wait_vehi_days,&y,&m,&d);

	    p_days=p_days+wait_vehi_days+(vehicle_arrive_minu/(24*60));
		//�µ�p_days Ҫ�ھɵĵĻ����ϼ��ϵȳ���������������
	    s_min=vehicle_arrive_minu%(24*60);

/*----------����ǰ�ÿ�״̬���ÿ͵���״̬�����-----------*/
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

	    if(via_c==end_city) //��st_city�͵�һ��;������֮�䲻��Ҫ����
			break;    //��������ѭ��

		city1=via_c;
		via_c=path [middle_city[full_per [condition] [via_city_num-1]-1] -1] [end_city-1] [i+1];
		if(via_c==-1&&city1!=end_city)
		    via_c=end_city;
	}
	print();
}

/*-----------------��;�����е����---------------------*/
void output_price(int s_year,int s_month,int s_day,int s_min,
                  int start_city,int end_city)
{

	int via_veh; //;������
    int i;
    int p_days; //�˿ͳ���ʱ��
    int vehicle_go_minu,vehicle_arrive_minu; //�г�����ʱ��
	int wait_vehi_days;  //�˿͵ȴ��г�������
	int city1,via_c; //ÿһ�ν�ͨ���ߵ���ʼ���к͵������
	PASSENGER_LINK* tail,*p;

	p=(PASSENGER_LINK *)malloc(sizeof(PASSENGER_LINK));
	passengers[pcount]=p;
	tail=p;

	int y, m, d; //������ת��������������
	int c;
	printf("�˿͵����мƻ���:\n");

	p_days=cal_min_time(s_year,s_month,s_day);

	city1=start_city;
	via_c= path[start_city-1] [end_city-1] [0];
	for(i=0;via_c!=-1&&i<city_num;i++)
	{
	    via_veh=arcs[city1-1][via_c-1].mini_pri_veh;  //����
		wait_vehi_days=need_day_to_go(p_days,s_min,via_veh,
		city1,via_c,&vehicle_go_minu,&vehicle_arrive_minu);

	    time_switch(p_days+wait_vehi_days,&y,&m,&d);

	    p_days=p_days+wait_vehi_days+(vehicle_arrive_minu/(24*60));
		//�µ�p_days Ҫ�ھɵĵĻ����ϼ��ϵȳ���������������
	    s_min=vehicle_arrive_minu%(24*60);

/*----------����ǰ�ÿ�״̬���ÿ͵���״̬�����-----------*/
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
	    if(via_c==end_city) //��st_city�͵�һ��;������֮�䲻��Ҫ����
			break;                        //��������ѭ��

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
	int mol;     //��ʾ����ʱ�������˵���ʱ�������
	int tim1,tim2;
	startday=vehicle[t_num-1][0].minute;
	//ÿ�ֽ�ͨ���ߵĿ�������ʱ��
	duringday=Tnumber[t_num-1].times;
	//ÿ�˳�������ʱ��

	mol=(Day-startday)%duringday;

	//2i-2  2i-1��Ӧi�ų�
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

	if(mol==0&&*vehicle_go_minu>=minute)     //��ʾ�˿Ϳ���������Ĵ˰೵
	    return 0;
	else if(mol==0&&*vehicle_go_minu<minute)   //��ʾ�˿ʹ���������೵
	    return duringday;
	else                                 //���˳��ڳ˿͵�������û��
	    return duringday-mol;
}
