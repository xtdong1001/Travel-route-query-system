#include"travel.h" 
/*��ӡ���в���*/
void print()
{
	pass a;
	int h,m;
	a=passengers[pcount];
	print_message(); 
	for(;a->next!=NULL;a=a->next)
	{
		//�ÿ�״̬Ϊ�ڳ����� 
		if(a->passenger_state==2)
		{
			h=a->arrive_min/60;
			m=a->arrive_min%60;
			printf("�ÿ�%d�ڳ���%sͣ����%d-%d-%d %d:%d\n",
			pcount,city[a->city_or_vehicle-1],a->arrive_year,
			a->arrive_month,a->arrive_day,h,m);
		}
		//�ÿ�״̬Ϊ�ڽ�ͨ������ 
		else
		{
			h=a->arrive_min/60;
			m=a->arrive_min%60;
			if(Tnumber[a->city_or_vehicle-1].number[0]=='k')
		    	printf("�ÿ͵��ϴӳ���%s������%s��%s���г�,",city[a->pass_start_c-1],
				city[a->pass_arrive_c-1],Tnumber[a->city_or_vehicle-1].number);
			if(Tnumber[a->city_or_vehicle-1].number[0]=='f')
		    	printf("�ÿ͵��ϴӳ���%s������%s��%s�ŷɻ�,",city[a->pass_start_c-1],
				city[a->pass_arrive_c-1],Tnumber[a->city_or_vehicle-1].number);
			if(Tnumber[a->city_or_vehicle-1].number[0]=='b')
		    	printf("�ÿ͵��ϴӳ���%s������%s��%s������,",city[a->pass_start_c-1],
				city[a->pass_arrive_c-1],Tnumber[a->city_or_vehicle-1].number);
			printf("�۸�Ϊ%lfԪ\n",a->pass_price); 
			printf("%d-%d-%d %d:%d����\n",
			a->arrive_year,a->arrive_month,a->arrive_day,h,m); 
		} 
	}
}
