#include"travel.h"
//������ȡ�ͳ�ʼ��
void initial()
{
	int car_num,i,j,k,a,s;
	int *via_num,hour,min,counter=0,counter2,count1,count2,count3;
	char h1,h2,m1,m2,end_ch;

	FILE *fptr1,*fptr2,*fptr3;
	if((fptr1=fopen("city.txt","r"))==NULL)
	    printf("File could not be opened\n");
	else if((fptr2=fopen("timetable.txt","r"))==NULL)
	    printf("File could not be opened\n");
	else if((fptr3=fopen("price.txt","r"))==NULL)
	    printf("File could not be opened\n");
	else
	{
		fscanf(fptr1,"%d",&city_num); //��ȡ���и���
		fseek(fptr1,1,SEEK_CUR);

		city=(char**)malloc(city_num*sizeof(char*));
		//��ȡcity.txt �����м���Ӧ��ű���
		for(counter=0;counter<city_num;counter++)
		{
			fscanf(fptr1,"%d",&a);
			fseek(fptr1,1,SEEK_CUR);
			city[counter]=(char*)malloc(10*sizeof(char));
			fgets(city[a-1],100,fptr1);
			for(count1=0;count1<10;count1++)
            {
                if(city[a-1][count1]=='\n')
                    city[a-1][count1]='\0';
            }
		}
		fclose(fptr1);

		pm=(int **)malloc(city_num*sizeof(int*));
		tm=(int **)malloc(city_num*sizeof(int*));
		for(counter=0;counter<city_num;counter++)
		{
			pm[counter]=(int*)malloc(city_num*sizeof(int));
			tm[counter]=(int*)malloc(city_num*sizeof(int));
			for(count1=0;count1<city_num;count1++)
			{
				pm[counter][count1]=0;
				tm[counter][count1]=0;
			}
		}


		fscanf(fptr2,"%d",&vehicle_num); //��ȡ��ͨ���߸���

		fseek(fptr2,1,SEEK_CUR);

		via_num=(int*)malloc(vehicle_num*sizeof(int));
		//��̬�����¼;�����и�������

		Tnumber=(train_num*)malloc(vehicle_num*sizeof(train_num));
		//��̬���복������

		vehicle=(Station**)malloc(2*vehicle_num*sizeof(Station*));
		/*��̬���뽻ͨ����;������
		�ṹ��Ϊ;�����к͵�վʱ�� ���ļ�2��ȡ �±�Ϊ0��λ�ô���ʼ���� */

		for(counter=0;counter<vehicle_num;counter++)
		{
			fscanf(fptr2,"%d",&car_num);
			fseek(fptr2,1,SEEK_CUR);

			fscanf(fptr2,"%s",&Tnumber[counter].number);  //��ȡ����
			fseek(fptr2,1,SEEK_CUR);

			fscanf(fptr2,"%d",&via_num[counter]);  //��ȡ���и���
			fseek(fptr2,1,SEEK_CUR);

			vehicle[2*counter]=(Station*)malloc((via_num[counter]+1)*sizeof(Station));
			//��̬����;�����У����أ�
			vehicle[2*counter+1]=(Station*)malloc((via_num[counter]+1)*sizeof(Station));
			//�±�Ϊ���λ�ô洢�г���ʼʱ��

			fscanf(fptr2,"%d",&vehicle[2*counter][0].minute);    //��ȡ��ʼʱ��
			fseek(fptr2,1,SEEK_CUR);

			fscanf(fptr2,"%d",&Tnumber[counter].times);  //��ȡ����Ƶ��
			fseek(fptr2,1,SEEK_CUR);

			for(counter2=1;counter2<=via_num[counter];counter2++)
			{
				fscanf(fptr2,"%d",&vehicle[2*counter][counter2].via_city);
				//��ȡ�������
				fseek(fptr2,1,SEEK_CUR);

				fscanf(fptr2,"%c",&h1);
				fscanf(fptr2,"%c",&h2);
				fseek(fptr2,1,SEEK_CUR);
				hour=(h1-'0')*10+(h2-'0');

				fscanf(fptr2,"%c",&m1);
				fscanf(fptr2,"%c",&m2);
				fseek(fptr2,1,SEEK_CUR);
				min=(m1-'0')*10+(m2-'0');

				vehicle[2*counter][counter2].minute=hour*60+min;
				//���㿪��ʱ�� ������Ϊ��λ��
			}

			fscanf(fptr2,"%d",&vehicle[2*counter+1][0].minute);
			//��ȡ��ʼʱ��
			fseek(fptr2,1,SEEK_CUR);

			for(counter2=1;counter2<=via_num[counter];counter2++)
			{
				fscanf(fptr2,"%d",&vehicle[2*counter+1][counter2].via_city);
				//��ȡ�������
				fseek(fptr2,1,SEEK_CUR);

				fscanf(fptr2,"%c",&h1);
				fscanf(fptr2,"%c",&h2);
				fseek(fptr2,1,SEEK_CUR);
				hour=(h1-'0')*10+h2-'0';

				fscanf(fptr2,"%c",&m1);
				fscanf(fptr2,"%c",&m2);
				fseek(fptr2,1,SEEK_CUR);
				min=(m1-'0')*10+m2-'0';

				vehicle[2*counter+1][counter2].minute=(double)hour*60+min;
				//���㿪��ʱ��
			}
		}

		fclose(fptr2);

		Tmatrix=(timepoint***)malloc(city_num*sizeof(timepoint**));
		//��̬������ֹʱ�����

		for(counter=0;counter<city_num;counter++)
			Tmatrix[counter]=(timepoint**)malloc(city_num*sizeof(timepoint*));

		Pmatrix=(ticket_price***)malloc(city_num*sizeof(ticket_price**));
		//��̬����۸����

		for(counter=0;counter<city_num;counter++)
			Pmatrix[counter]=(ticket_price**)malloc(city_num*sizeof(ticket_price*));

        while(1)   //ij��ʾ�������У�k��ʾ������֮�䳵�ĸ���
        {
        	fscanf(fptr3,"%d",&i);  //��ȡ����1
        	fseek(fptr3,1,SEEK_CUR);

			fscanf(fptr3,"%d",&j);  //��ȡ����2
        	fseek(fptr3,1,SEEK_CUR);

        	fscanf(fptr3,"%d",&k);  //��ȡ��ͨ���߸���
        	fseek(fptr3,1,SEEK_CUR);

        	Pmatrix[i-1][j-1]=(ticket_price*)malloc(k*sizeof(ticket_price));
        	for(s=0;s<k;s++)
        	{
        		Pmatrix[i-1][j-1][s].price=-1;
        		Pmatrix[i-1][j-1][s].vehicle_number=-1;
        	}

        	Tmatrix[i-1][j-1]=(timepoint*)malloc(k*sizeof(timepoint));
        	pm[i-1][j-1]=k;


			for(counter=0;counter<k;counter++)
        	{
        		fscanf(fptr3,"%d",&Pmatrix[i-1][j-1][counter].vehicle_number);
				//��ȡ�г�����
        		fseek(fptr3,1,SEEK_CUR);

        		fscanf(fptr3,"%lf",&Pmatrix[i-1][j-1][counter].price);
				//��ȡ��Ʊ�۸�
        		fseek(fptr3,1,SEEK_CUR);
        	}

			fscanf(fptr3,"%c",&end_ch);   //�ٶ�ȡһ���ַ��ж��Ƿ��ļ�β

			if(!feof(fptr3)) //�������ļ�β�����һ���ַ� �ж��ļ�����
			    fseek(fptr3,-1,SEEK_CUR);
			else
			    break;
        }

        fclose(fptr3);

        num=(int**)malloc(city_num*sizeof(int*));
		//��̬�����ά���鱣��Tmatrix�������Ĵ洢λ��
        for(counter=0;counter<city_num;counter++)
        {
        	num[counter]=(int*)malloc(city_num*sizeof(int));

        	for(counter2=0;counter2<city_num;counter2++)   //��ʼ��Ϊ0
        	    num[counter][counter2]=0;
        }


        for(counter=0;counter<2*vehicle_num;counter++)
		{
			for(counter2=1;counter2<via_num[counter/2];counter2++)
			{
				i=vehicle[counter][counter2].via_city-1;  //�õ���ֹ�������
				j=vehicle[counter][counter2+1].via_city-1;

				tm[i][j]=1;
				Tmatrix[i][j][num[i][j]].vehicle_number=counter/2+1;
				//�õ��������

				Tmatrix[i][j][num[i][j]].start_min=
				vehicle[counter][counter2].minute;
				//�õ���ֹʱ��
				Tmatrix[i][j][num[i][j]].end_min=
				vehicle[counter][counter2+1].minute;
				num[i][j]++;
			}
		}
	}

	arcs=(price_arc **)malloc(sizeof(price_arc *)*city_num);
	for(counter=0;counter<city_num;counter++)
	{
		arcs[counter]=(price_arc *)malloc(sizeof(price_arc )*city_num);
		for(i=0;i<city_num;i++)
		    arcs[counter][i].mini_price=-1;
	}
	//��̬�����ά����arcs��������֮��

		//���н�ͨ����֮�е����ٷ���

    //��̬�����¼���ٷ��ò��Ժ����ʱ�����·���ľ��� ����ʼ��
    path=(int***)malloc(city_num*sizeof(int**));
    time_path=(int***)malloc(city_num*sizeof(int**));
	for(count1=0;count1<city_num;count1++)
	{
		path[count1]=(int**)malloc(city_num*sizeof(int*));
		time_path[count1]=(int**)malloc(city_num*sizeof(int*));
		for(count2=0;count2<city_num;count2++)
		{
			path[count1][count2]=(int*)malloc(city_num*sizeof(int));
			time_path[count1][count2]=(int*)malloc(city_num*sizeof(int));
			for(count3=0;count3<city_num;count3++)
			{
				path[count1][count2][count3]=-1;
				time_path[count1][count2][count3]=-1;
			}
		}
	}

	D=(double*)malloc(city_num*sizeof(double));

	p=(int **)malloc(sizeof(int *)*city_num);

	for(counter=0;counter<city_num;counter++)
	    p[counter]=(int *)malloc(sizeof(int )*city_num);

	time_matrix=(time_arc **)malloc(sizeof(time_arc *)*city_num);
	//��̬�����ά����time_matrix��������֮��
	//���н�ͨ����֮�е����ʱ��


    passen_count=0;
}
