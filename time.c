#include"travel.h"
#include"egg.h"
/*ϵͳʱ�����*/ 
void system_time_count()
{
	while(1)
	{
		if(state!=QUERY) //��ǰ״̬���ǲ�ѯ״̬
		{
	    	Sleep(INTERVAL);  //ʱ��Ƭ�ƽ�
	    	time_count++;
			pull();//������

	    	system_t.minute=time_count*10;
			//����Ϊʮ���� 
	    	if(system_t.minute==60)  //���������㣬Сʱ��һ 
        	{
    	    	system_t.minute=0;
    	    	system_t.hour++;
    	    	time_count=0;
        	}
        	if(system_t.hour==24)//Сʱ���� ������һ 
        	{
    	    	system_t.hour=0;
    	    	system_t.day++;
        	}

        	switch(system_t.month){       //�������㣬�·ݼ�һ 
            	case 1:case 3:case 5:case 7:
	        	case 8:case 10:case 12:
	   	        	if(system_t.day==32)
		        	{
			        	system_t.day=1;
			        	system_t.month++;
		        	}
                	break;
            	case 2:
                	if((system_t.year%4==0&&system_t.year%100!=0)||system_t.year%400==0)
                	{
            	    	if(system_t.day==30)
            	    	{
            		    	system_t.day=1;
					    	system_t.month++;
            	    	}
                	}
                	else if(system_t.day==29)
                	{
            	    	system_t.day=1;
            	    	system_t.month++;
                	}
                	break;
            	case 4:case 6:case 9:case 11:
                	if(system_t.day==30)
			    	{
				    	system_t.day=1;
				    	system_t.month++;
			    	}
			    	break;
        	}

			if(system_t.month==13)
			{
		    	system_t.month=1;
		    	system_t.year++;
			}
			//ÿ��Сʱ��ӡһ��ϵͳʱ��
    		if(system_t.minute%30==0)
    	     	printf("%d��%d��%d�� %d:%d\n",system_t.year,system_t.month,system_t.day,
			        	system_t.hour,system_t.minute);
    	}
    	if(s==4)
    	    break;
	}
}


//ϵͳ���ƺ��� 
void start_system()
{
	start_date a;
	pass pl,ql;
	int pn,mark=1; 
	
	printf("��ѡ���Ƿ���Ҫͼ�λ������1--�ǣ�2--��\n"); 
    scanf("%d",&graphic1);
	getchar();
	
	if(graphic1==1)
	    drawmap();
		
	while(1)
	{
		printf("��������������\n"); 
		scanf("%d",&s);
		getchar();
		//ϵͳ״̬��ʼ����ΪMOVING 
		state=MOVING;
		//��������(����������ϵͳһֱ����) 
		
		//��ѯ���� 
    	if(s==1)
    	{
				//ϵͳʱ����ͣ���� 
				state=QUERY;
				Link();
				getInput();	 
				state=MOVING;
				//ϵͳ�������� 
    	}
    	
  			//��ѯ�ÿ�״̬ 
		else if(s==2)
		{
			state=SEARCH;
			query();
			state=MOVING;
		}
		
			//�������в��� 
		else if(s==3)
		{
			//�����ÿͺ��� 
			while(mark==1)
			{
				mark=0;
				printf("���������ĳ˿���ţ�\n");
		   		scanf("%d",&pn);
		   		if(pn>99||pn<1||pn>passen_count)
		   		{
		   			printf("����������������룡\n");
	    			mark=1;
	    		}    			
			}
			
				//ȫ�ֱ���pcount Ϊ��ѯ����ʱ�洢����ָ����±� 
			pcount=pn;
			if(passengers[pn]!=NULL) 
			{
				a.year=passengers[pn]->arrive_year;
				a.month=passengers[pn]->arrive_month;
				a.day=passengers[pn]->arrive_day;
				a.hour=passengers[pn]->arrive_min/60;
				a.minute=passengers[pn]->arrive_min%60;
				
					//��ʱ�˿��ڳ��� ��ȴ��������е��ÿ��³�Ϊֹ 
				if(passengers[pn]->passenger_state==1)     
					while(time_compare(a,system_t));
				
					//��ոó˿͵Ĳ������� 
				for(pl=passengers[pn];pl->next!=NULL;)
				{
					ql=pl->next;
					pl->next=ql->next;
					free(ql);
				}
				free(pl);
				passengers[pn]=NULL;
					//��ͣ�������� ���Բ�ѯ 
				state=QUERY;
				getInput();	
				state=MOVING;
					//������������ 
			}
		}
		else if(s==4)  //�˳� 
    	    break;
	} 
}


