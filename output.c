#include"travel.h"
/******���ÿ����󣬲��ԣ�״̬����Ϣд���ļ�*******/
void print_message(void)
{
    pass a;
	int h,m;
	a=passengers[pcount];
	
	if ((fptr1= fopen ("record.txt", "a+")) == NULL)        
        printf ("error!File could not be opened.\n");

	fprintf(fptr1,"ϵͳʱ�䣺%d-%d-%d %d:%d\n",system_t.year,system_t.month,
                                               system_t.day,system_t.hour,
                                               system_t.minute);

    if(s==1)
        fprintf(fptr1,"�û�%d��ѯ���ԣ�\n",pcount);
    else if(s==2)
        fprintf(fptr1,"�û�%d��ѯ��ǰ״̬��\n",pcount);
    else if(s==3)
        fprintf(fptr1,"�û�%d���Ĳ���Ϊ��\n",pcount);

	for(;a->next!=NULL;a=a->next)
	{
		//�ÿ�״̬Ϊ�ڳ�����
		if(a->passenger_state==2)
		{
			h=a->arrive_min/60;
			m=a->arrive_min%60;
			fprintf(fptr1,"�ÿ�%d�ڳ���%sͣ����%d-%d-%d %d:%d\n",
			pcount,city[a->city_or_vehicle-1],a->arrive_year,
			a->arrive_month,a->arrive_day,h,m);
		}
		//�ÿ�״̬Ϊ�ڽ�ͨ������
		else
		{
			h=a->arrive_min/60;
			m=a->arrive_min%60;
			fprintf(fptr1,"�ÿ͵��ϴӳ���%s������%s��%s���г�,",city[a->pass_start_c-1],
			city[a->pass_arrive_c-1],Tnumber[a->city_or_vehicle-1].number);
			fprintf(fptr1,"�۸�Ϊ%lfԪ\n",a->pass_price);
			fprintf(fptr1,"%d-%d-%d %d:%d����\n",
			a->arrive_year,a->arrive_month,a->arrive_day,h,m);
		}
	}
	fclose(fptr1);
}

