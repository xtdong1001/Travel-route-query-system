/*�˺������Լ���������ʱ�䵽������վ֮�� ��ʼ��ʱ��
��������������վ��ʱ���������*/
/*�ڶ������ԣ����ʱ��*/
#include"travel.h"
int cal_min_time(int start_year,int start_month,int start_day)
//start_cityΪ0�����һ������
{
	int k,days,year;
	int month[13]={0,31,0,31,30,31,30,31,31,30,31,30,31};

	days=0;
	year=0;
	year=start_year-2016;
	switch(year%4)   //��
	{
	   	case 0:days=(year/4)*(365*3+366);break;
	   	case 1:days=(year/4)*(365*3+366)+365;break;
	   	case 2:days=(year/4)*(365*3+366)+365*2;break;
	   	case 3:days=(year/4)*(365*3+366)+365*3;break;
	}
	if(year%4==0) //��
	    month[2]=29;
	else
	    month[2]=28;

	for(k=1;k<=start_month-1;k++)  //��
	    days=days+month[k];

	days=days+start_day;
	//days��ʾ�ϳ�ʱ�����1��1�ŵ���������days=1˵����2016.1.1

    return days;
}

//start_cityΪ0�����һ������
void cal_mini_minute(int start_city,int days,int start_time)
{
	int i,j;
	int everyTrans_startday,everyTrans_duringday,this_day_time;
	//this_day_time��ʾ���ڵ���Ŀ���ʱ��
	int wait_time;              //�˿͵ȴ��ϳ���ʱ��
	int travel_time;            //������ʻʱ��
	int total_time;             //�ִ���һ���������������ʱ��
	int mol;
	//mol��ʾ���Ŀ�ʼʱ����˿ͼ���ʱ���ֵ�Գ�Ƶ�ʵ�ģ
	int mintime_between_twocity=1000000;
	//��ʾ��һ�����е�����һ�����е�����ʱ��
	int mintime_transp;
	//��ʾ��һ�����е�����һ�����е�����ʱ���Ӧ�ĳ��� ����1��ʾ���Ϊ1�����˳�

	for(i=0;i<=city_num-1;i++)              //�����������г���
	{
		for(j=0;j<=num[start_city-1][i]-1;j++)
		//������������֮������н�ͨ����
		{
		    everyTrans_startday=
			(int)vehicle[Tmatrix[start_city-1][i][j].vehicle_number-1][0].minute;
			//ÿ�ֽ�ͨ���ߵĿ�������ʱ��
		    everyTrans_duringday=
			Tnumber[Tmatrix[start_city-1][i][j].vehicle_number-1].times;
			//ÿ�˳�������Ƶ��

		    mol=(days-everyTrans_startday)%everyTrans_duringday;

		    this_day_time=(int)Tmatrix[start_city-1][i][j].start_min%(24*60);

		    //��ʾ�˿Ϳ���������Ĵ˰೵
		    if(mol==0&&this_day_time>=start_time)
		    	wait_time=this_day_time-start_time;
		    //��ʾ�˿ʹ���˽���ĳ�
		    if(mol==0&&this_day_time<start_time)
	            wait_time=everyTrans_duringday*24*60
	                      -start_time+this_day_time;
	        if(mol!=0)        //��ʾ����û��
	        	wait_time=(everyTrans_duringday-mol)*24*60+this_day_time-start_time;

			travel_time=(int)Tmatrix[start_city-1][i][j].end_min-
			            (int)Tmatrix[start_city-1][i][j].start_min;

			total_time=wait_time+travel_time;
			//����Ƿ�����
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

		mintime_between_twocity=1000000;         //������Ϊ���ֵ
	}
}

//��;�������ʱ����� ���
void with_via_mintime(int s_year,int s_month,int s_day,int s_min,
int via_city_num,int * middle_city,int start_city,int end_city)
{

    int**full_per; //ȫ���е�ÿһ�����
    int via_veh; //;������
    int i,j,k,count=1,count_time=0,min_time_mid=1000000;
    int p_day,p_min; //�˿ͳ���ʱ��
    int vehicle_go_minu,vehicle_arrive_minu; //�г�����ʱ��
	int wait_vehi_days;  //�˿͵ȴ��г�������
	int city1,city2,city3,via_c; //ÿһ�ν�ͨ���ߵ���ʼ���к͵������
	int vindex,bestv;
	way buffw[100],bestww[100];

	PASSENGER_LINK * tail, * p;  //������ָ��

	p=(PASSENGER_LINK *)malloc(sizeof(PASSENGER_LINK));
	passengers[pcount]=p;
	tail=p;

	int y, m, d; //������ת��������������

	int c;
	int condition;

    for(i=2;i<=via_city_num;i++)
        count=count*i;

    full_per=(int**)malloc(count*sizeof(int*));
    for(i=0;i<count;i++)
    	full_per[i]=(int*)malloc(via_city_num*sizeof(int)); //��̬����

	full_permutation(via_city_num,full_per);
	//�õ�;�����е�ȫ����

/*����ÿһ��;������ȫ���е�ʱ�� �ҵ���Сʱ��
ÿһ���ؾ����е���һ�εϽ�˹��������least_time��
�õ��ó��к������ڵıؾ����е�·��,
��·����Ϣ�洢���ṹ������*/
         
    for(i=0;i<count;i++)   //����ÿһ��ȫ���е�ʱ�� �ҵ���Сʱ��
	{
		p_min=s_min;
    	p_day=cal_min_time(s_year,s_month,s_day);

    	//������ת��Ϊ��ʱ��
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
			//����dijkstra

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

			//����ʱ���
			count_time=count_time+time_matrix[city3-1][city2-1].mini_time;

			//���³�����day��minute
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

		if(count_time<min_time_mid) //�����ʱ��
		{
			min_time_mid=count_time;
			bestv=vindex;
			condition=i;
			for(k=0;k<=vindex;k++)
			    bestww[k]=buffw[k];
		}
	}

	printf("�˿͵����мƻ���:\n");

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
		     //�µ�p_day Ҫ�ھɵĵĻ����ϼ��ϵȳ���������������
	    p_min=vehicle_arrive_minu%(24*60);


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

//û��;�������ʱ����� ���
void without_via_mintime(int s_year,int s_month,int s_day,int s_min,
                  int start_city,int end_city)
{
	int via_veh; //;������
    int i;
    int p_days; //�˿ͳ���ʱ��
    int vehicle_go_minu,vehicle_arrive_minu; //�г�����ʱ��
	int wait_vehi_days;  //�˿͵ȴ��г�������
	int city1,via_c; //ÿһ�ν�ͨ���ߵ���ʼ���к͵������
	PASSENGER_LINK* tail,*p;
	tail=passengers[pcount];

	int c;

	p=(PASSENGER_LINK *)malloc(sizeof(PASSENGER_LINK));
	passengers[pcount]=p;
	tail=p;

	int y,m,d; //������ת��������������

    p_days=cal_min_time(s_year,s_month,s_day);
    least_time(start_city,p_days,s_min);

	printf("�˿͵����мƻ���:\n");

	city1=start_city;
	via_c= time_path[start_city-1] [end_city-1] [0];
	for(i=0;via_c!=-1&&i<city_num;i++)
	{
	    via_veh=time_matrix[city1-1][via_c-1].mini_time_veh;  //����
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
		via_c=time_path[start_city-1] [end_city-1] [i+1];
		if(via_c==-1&&city1!=end_city)
		    via_c=end_city;
	}
	print();
}
