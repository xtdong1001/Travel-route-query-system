/*���Ը��ݲ�ѯʱ��õ��û���ǰ����λ�û������ڳ����Ľ�ͨ����*/
/*�˹�����ϵͳ��ɣ���ϵͳ��ѯ�˿͵�״̬*/
//��֮ǰ�ĵ������ĺ�����ֻ��Ҫ����ģʽ�����Ƿ�Ҫ��ѯ�������Ҫ��������������
#include"travel.h"


/*�����洢�˿ͳ��мƻ�����������*/
/*�����뺯�����ã������µĳ˿��мƻ�����ʱ������*/

//��ѯ�ÿ�״̬
void query()
{
	int numb,mark=1;         //�˿ͱ��
	int city_vehicle_num;
	int start_city_num,end_city_num;

	//���������ÿͺ�
	while(mark==1)
	{
		mark=0;
		printf("���������ĳ˿���ţ�\n");
		scanf("%d",&numb);
		if(numb>99||numb<1||numb>passen_count)
		{
			printf("����������������룡\n");
			mark=1;
		}
	}

	if(!time_compare(stime[numb],system_t))//ϵͳʱ�����ڻ���ڳ���ʱ��
	{
		if(passengers[numb]->passenger_state==1)     //������ʱ�˿��ڳ���
		{
			start_city_num=passengers[numb]->pass_start_c-1;
			end_city_num=passengers[numb]->pass_arrive_c-1;
			city_vehicle_num=passengers[numb]->city_or_vehicle-1;
			if(Tnumber[city_vehicle_num].number[0]=='k')
		    	printf("��ʱ�˿�����%s����%s��%s�Ż��ϣ�\n",city[start_city_num],
				city[end_city_num],Tnumber[city_vehicle_num].number);
			if(Tnumber[city_vehicle_num].number[0]=='b')
		    	printf("��ʱ�˿�����%s����%s��%s�������ϣ�\n",city[start_city_num],
				city[end_city_num],Tnumber[city_vehicle_num].number);
			if(Tnumber[city_vehicle_num].number[0]=='f')
		    	printf("��ʱ�˿�����%s����%s��%s�ŷɻ��ϣ�\n",city[start_city_num],
				city[end_city_num],Tnumber[city_vehicle_num].number);
		}
		else                          //�˿���ĳһ������
		{
			city_vehicle_num=passengers[numb]->city_or_vehicle-1;
	    	printf("�˿̸ó˿�����%sͣ����\n",city[city_vehicle_num]);
    	}
	}
	else
	    printf("�˿�δ������\n");

}

