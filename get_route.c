#include"travel.h"
//��ó˿����� �õ�·��
void getInput()
{
    int start_city;
    int end_city;
    int via_city_num; //;�����и���
    int st_year,st_month,st_day,st_hour,st_min;  //�˿ͳ���ʱ��
    int * middle_city;   //;�����б��
    int a,b;                  //a,b����ģʽѡ��
    int i=0,j;             //����middle_city�ļ�����
    int lim_d,lim_h,lim_m;//����������ʱ��
    int limit;
    int *limd,*limh,*limm;//����������ʱ�� 

	//��ӡ��ѡ���кͶ�Ӧ��� �ÿͽ���ѡ��
	for(i=0;i<city_num;i++)
		printf("%d %s\n",i+1,city[i]);

	printf("���������ĳ���ʱ��(x��-x��-x��-xʱ-x��)��\n");
	
	while(1)
	{
		scanf("%d-%d-%d-%d-%d",&st_year,&st_month,&st_day,&st_hour,&st_min);
		if(st_year<2016||st_month<1||st_month>12||st_day<1||st_day>31
	   		||st_hour<0||st_hour>23||st_min<0||st_min>59)
	    	printf("�������������������룡\n");
		else break;
	}
	
	//������ʱ�����ȫ�ֱ����ṹ����
	stime[pcount].year  =st_year;
	stime[pcount].month =st_month;
	stime[pcount].day   =st_day;
	stime[pcount].hour  =st_hour;
	stime[pcount].minute=st_min;

	st_min=st_min+60*st_hour;
	//���ú�������ֻ�������� ����Сʱ

	printf("��������ʼ���к���ֹ�������!\n");
	
	while(1)
	{
		scanf("%d %d",&start_city,&end_city);
    	if(start_city<1||start_city>city_num||end_city<1||end_city>city_num)
    		printf("�������������������룡\n");
		else break;
	}
    
    
	printf("���Ƿ��б���;���ĳ��У���--1��û��--0!\n");
	
	while(1)
	{
		scanf("%d",&a);
		if(a==0||a==1)
		    break;
		else printf("�������������������룡\n");
	}
	

	//��;��
	if(a==0)
	{
	    printf("��ѡ������Ҫ�Ĳ���(ʱ�����--1,��������--2,��ʱ��������--3)��\n");
	    getchar();
		scanf("%d",&b);

		if(b==1) //��;��ʱ����̲��� 
		{
		   	without_via_mintime(st_year,st_month,st_day,st_min,start_city,end_city);
		}
		else if(b==2) //��;���������ٲ��� 
		{
			output_price(st_year,st_month,st_day,st_min,start_city,end_city);
		}
		else //��;����ʱ�������ٲ��� 
		{
		   	int limd,limh,limm;
		   	printf("����������ʱ��(x��-yСʱ-z����)\n");
		    scanf("%d %d %d",&limd,&limh,&limm);
		    limm=limh*60+limm;
		    no_via_city_timeprice(st_year,st_month,st_day,st_min,
			                      start_city,end_city,limd,limm);
		}
	}
	//��;��
	else
	{
		printf("������;�����и�����\n");
		scanf("%d",&via_city_num);
		middle_city=(int*)malloc(via_city_num*sizeof(int));
		for(i=0;i<via_city_num;i++)
		{
			printf("������һ�����ж�Ӧ�Ĵ��ţ�\n");
			scanf("%d",&middle_city[i]);
		}

	   	printf("��ѡ������Ҫ�Ĳ���(ʱ�����--1,��������--2,��ʱ��������--3)\n");
		scanf("%d",&b);
		if(b==1) //��;��ʱ����̲���
		{
		   	with_via_mintime(st_year,st_month,st_day,st_min,via_city_num,
				             middle_city,start_city,end_city);
		}
		else if(b==2)//��;���������ٲ��� 
		{
		   	via_city_price(st_year,st_month,st_day,st_min,via_city_num,
				           middle_city,start_city,end_city);
		}
		else//��;����ʱ�������ٲ��� 
		{
			printf("��ʱ������--1,�����м�ʱ������--2\n");
			scanf("%d",&limit);
			getchar();
			
			if(limit==1)//��;������������ʱ�������ٲ��� 
			{
				printf("������%s��%s����ʱ��(x��-yСʱ-z����)\n",city[start_city-1],city[end_city-1]);
		    	scanf("%d %d %d",&lim_d,&lim_h,&lim_m);
		    	lim_m=lim_h*60+lim_m;
		   		via_timeprice(st_year,st_month,st_day,st_min,via_city_num,
			              	  middle_city,start_city,end_city,lim_d,lim_m);
			}
			else if(limit==2)//��;������������ʱ�������ٲ��� 
			{
				limd=(int*)malloc((via_city_num+1)*sizeof(int));
				limh=(int*)malloc((via_city_num+1)*sizeof(int));
				limm=(int*)malloc((via_city_num+1)*sizeof(int));
				
				printf("������%s��%s����ʱ��(x��-yСʱ-z����)\n",city[start_city-1],city[middle_city[0]-1]);
		    	scanf("%d %d %d",&limd[0],&limh[0],&limm[0]);
		    	limm[0]=limh[0]*60+limm[0];
				for(i=0,j=1;i<via_city_num-1;i++,j++)
				{
					printf("������%s��%s����ʱ��(x��-yСʱ-z����)\n",city[middle_city[i]-1],city[middle_city[i+1]-1]);
		    		scanf("%d %d %d",&limd[j],&limh[j],&limm[j]);
		    		limm[j]=limh[j]*60+limm[j];
				}
				printf("������%s��%s����ʱ��(x��-yСʱ-z����)\n",city[middle_city[i]-1],city[end_city-1]);
		    	scanf("%d %d %d",&limd[j],&limh[j],&limm[j]);
		    	limm[j]=limh[j]*60+limm[j];
				
		   		via_city_timeprice(st_year,st_month,st_day,st_min,via_city_num,
				               middle_city,start_city,end_city,limd,limm);
			}
			
		}
	}
}
