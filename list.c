#include"travel.h"
//�����к��� ����ʱ��״̬�����У��������һ��״̬
void pull()
{
	int i;
	int stopcity;
	start_date a;
	PASSENGER_LINK* p;
	HEGG tem;
	int city_vehicle_num;
	int start_city_num,end_city_num;
	//�������г˿͵Ķ���
	if ((fptr2= fopen ("record2.txt", "a+")) == NULL)        
        printf ("error!File could not be opened.\n");

	
	for(i=1;i<=passen_count;i++)
	{
		if(passengers[i]!=NULL&&passengers[i]->next!=NULL)
		{
			a.year=passengers[i]->arrive_year;
			a.month=passengers[i]->arrive_month;
			a.day=passengers[i]->arrive_day;
			a.hour=passengers[i]->arrive_min/60;
			a.minute=passengers[i]->arrive_min%60;
			//�Ƚ϶���ͷ��ʱ���ϵͳʱ��
			//������ͷʱ��С�ڵ���ϵͳʱ�� ˵����״̬����
			//ɾ����״̬ �����һ��״̬
			if(!time_compare(a,system_t))
			{
				
				p=passengers[i];
				passengers[i]=passengers[i]->next;
				free(p);
				fprintf(fptr1,"ϵͳʱ�䣺%d-%d-%d %d:%d\n",system_t.year,system_t.month,
                        system_t.day,system_t.hour,system_t.minute);
                        
				if(passengers[i]->passenger_state==1)     //������ʱ�˿��ڳ���
				{
					
					if(graphic1==1)
					{
						if(passengers[i]->pass_start_c==1)  
					{sx[i]=14.999999;sy[i]=11.00;}
					if(passengers[i]->pass_start_c==2)  
					{sx[i]=17.67;sy[i]=7.59;}
					if(passengers[i]->pass_start_c==3)  
					{sx[i]=14.84;sy[i]=3.28;}
					if(passengers[i]->pass_start_c==4)  
					{sx[i]=17.12;sy[i]=13.33;}
					if(passengers[i]->pass_start_c==5)  
					{sx[i]=10.93;sy[i]=9.47;}
					if(passengers[i]->pass_start_c==6)  
					{sx[i]=13.99;sy[i]=9.25;}
					if(passengers[i]->pass_start_c==7)  
					{sx[i]=12.00;sy[i]=7.09;}
					if(passengers[i]->pass_start_c==8)  
					{sx[i]=12.97;sy[i]=7.78;}
					if(passengers[i]->pass_start_c==9)  
					{sx[i]=5.53;sy[i]=10.92;}
					if(passengers[i]->pass_start_c==10)  
					{sx[i]=6.46;sy[i]=7.24;}
					if(passengers[i]->pass_start_c==11)  
					{sx[i]=10.32;sy[i]=4.71;}
							
					if(passengers[i]->pass_arrive_c==1)  
					{ex[i]=14.999999;ey[i]=11.00;}
					if(passengers[i]->pass_arrive_c==2)  
					{ex[i]=17.67;ey[i]=7.59;}
					if(passengers[i]->pass_arrive_c==3)  
					{ex[i]=14.84;ey[i]=3.28;}
					if(passengers[i]->pass_arrive_c==4)  
					{ex[i]=17.12;ey[i]=13.33;}
					if(passengers[i]->pass_arrive_c==5)  
					{ex[i]=10.93;ey[i]=9.47;}
					if(passengers[i]->pass_arrive_c==6)  
					{ex[i]=13.99;ey[i]=9.25;}
					if(passengers[i]->pass_arrive_c==7)  
					{ex[i]=12.00;ey[i]=7.09;}
					if(passengers[i]->pass_arrive_c==8)  
					{ex[i]=12.97;ey[i]=7.78;}
					if(passengers[i]->pass_arrive_c==9)  
		 			{ex[i]=9.53;ey[i]=10.92;}
					if(passengers[i]->pass_arrive_c==10)  
					{ex[i]=6.46;ey[i]=7.24;}
					if(passengers[i]->pass_arrive_c==11)  
					{ex[i]=10.32;ey[i]=4.71;}
							
						printmap(sx[i],sy[i],ex[i],ey[i]);
					} 
					
				
					start_city_num=passengers[i]->pass_start_c-1;
					end_city_num=passengers[i]->pass_arrive_c-1;
					city_vehicle_num=passengers[i]->city_or_vehicle-1;
					//д���ļ� 
					fprintf(fptr2,"�˿�%d����%s����%s��%s����!\n",i,city[start_city_num],
						city[end_city_num],Tnumber[city_vehicle_num].number);
					//��ӡ 
					if(Tnumber[city_vehicle_num].number[0]=='k')
		    			printf("�˿�%d����%s����%s��%s�Ż���!\n",i,city[start_city_num],
						city[end_city_num],Tnumber[city_vehicle_num].number);
					if(Tnumber[city_vehicle_num].number[0]=='b')
		    			printf("�˿�%d����%s����%s��%s�������ϣ�\n",i,city[start_city_num],
						city[end_city_num],Tnumber[city_vehicle_num].number);
					if	(Tnumber[city_vehicle_num].number[0]=='f')
		    			printf("�˿�%d����%s����%s��%s�ŷɻ��ϣ�\n",i,city[start_city_num],
						city[end_city_num],Tnumber[city_vehicle_num].number);
				}
				else if(passengers[i]->passenger_state==2)   //�˿���ĳһ������
				{
					
					city_vehicle_num=passengers[i]->city_or_vehicle-1;
	    			printf("�˿�%d��ǰ��%sͣ����\n",i,city[city_vehicle_num]);
                    fprintf(fptr2,"�˿�%d��ǰ��%sͣ����\n",i,city[city_vehicle_num]);
                    
					if(graphic1==1)
					{	
						if(tem!=gg)
						{
							SetActiveEgg(end_egg[pcount]);
							EatEgg();
						}
						SetActiveEgg(temp_g_egg[pcount]);
						EatEgg(); 
						if(flag[pcount]==1)      //��ͨ������ʧ 
						{SetActiveEgg(g_egg1[pcount]); EatEgg();}
						if(flag[pcount]==2) 
						{SetActiveEgg(g_egg2[pcount]); EatEgg();}   
						if(flag[pcount]==3)   
						{SetActiveEgg(g_egg3[pcount]); EatEgg();}
						
						stopcity=passengers[i]->city_or_vehicle;
						
						end_egg[pcount] = LayEgg();
						
						if(stopcity==1)
							MovePen(14.00,10.00);   
						if(stopcity==2)
							MovePen(16.67,7.59);
						if(stopcity==3)
							MovePen(13.84,3.28);
						if(stopcity==4)
							MovePen(16.12,13.33);
						if(stopcity==5)
							MovePen(9.93,9.47);
						if(stopcity==6)
							MovePen(12.99,9.25);
						if(stopcity==7)
							MovePen(11,7.09);
						if(stopcity==8)
							MovePen(11.97,7.78);
						if(stopcity==9)
							MovePen(8.53,10.92);
						if(stopcity==10)
							MovePen(5.46,7.24);
						if(stopcity==11)
							MovePen(9.32,4.71);
						
						SetPen(BLUE,0.3);
						DrawArc(0.1,0,360);
						
						if(passengers[i]->next->next==NULL)  //�����յ�(�±��1����0��ʼ)
						{
							passengers[i]==NULL;
						}
					} 
				}
				else//���� 
				{
					printf("�˿�%d����Ŀ�ĵأ�\n",i);
					fprintf(fptr2,"�˿�%d����Ŀ�ĵأ�\n",i);
					
					if(graphic1==1)
					{
						SetActiveEgg(end_egg[pcount]);
					EatEgg();
					SetActiveEgg(temp_g_egg[pcount]);
					EatEgg(); 
					if(flag[pcount]==1)      //��ͨ������ʧ 
					{SetActiveEgg(g_egg1[pcount]); EatEgg();}
					if(flag[pcount]==2) 
					{SetActiveEgg(g_egg2[pcount]); EatEgg();}   
					if(flag[pcount]==3)   
					{SetActiveEgg(g_egg3[pcount]); EatEgg();}
					}
					
				}
							
			}
					
    	}
	}
	
	fclose(fptr2);
}

/*�����µĳ˿�����*/ 
void Link()
{
	/*���˿͸�״̬����*/
	passen_count=(passen_count+1)%100;   //�ƶ�����һ��λ��
	if(passen_count==99)
	    printf("�ڴ�������\n");
	else
		printf("���ĳ˿ͱ��Ϊ%d,��ѯ�������ţ�\n",passen_count);
	pcount=passen_count;
}
