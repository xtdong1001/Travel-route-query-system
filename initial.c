#include"travel.h"
//参数读取和初始化
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
		fscanf(fptr1,"%d",&city_num); //读取城市个数
		fseek(fptr1,1,SEEK_CUR);

		city=(char**)malloc(city_num*sizeof(char*));
		//读取city.txt 将城市及对应编号保存
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


		fscanf(fptr2,"%d",&vehicle_num); //读取交通工具个数

		fseek(fptr2,1,SEEK_CUR);

		via_num=(int*)malloc(vehicle_num*sizeof(int));
		//动态申请记录途经城市个数数组

		Tnumber=(train_num*)malloc(vehicle_num*sizeof(train_num));
		//动态申请车次数组

		vehicle=(Station**)malloc(2*vehicle_num*sizeof(Station*));
		/*动态申请交通工具途经数组
		结构内为途径城市和到站时间 从文件2读取 下标为0的位置存起始天数 */

		for(counter=0;counter<vehicle_num;counter++)
		{
			fscanf(fptr2,"%d",&car_num);
			fseek(fptr2,1,SEEK_CUR);

			fscanf(fptr2,"%s",&Tnumber[counter].number);  //读取车次
			fseek(fptr2,1,SEEK_CUR);

			fscanf(fptr2,"%d",&via_num[counter]);  //读取城市个数
			fseek(fptr2,1,SEEK_CUR);

			vehicle[2*counter]=(Station*)malloc((via_num[counter]+1)*sizeof(Station));
			//动态申请途经城市（来回）
			vehicle[2*counter+1]=(Station*)malloc((via_num[counter]+1)*sizeof(Station));
			//下标为零的位置存储列车起始时间

			fscanf(fptr2,"%d",&vehicle[2*counter][0].minute);    //读取起始时间
			fseek(fptr2,1,SEEK_CUR);

			fscanf(fptr2,"%d",&Tnumber[counter].times);  //读取发车频率
			fseek(fptr2,1,SEEK_CUR);

			for(counter2=1;counter2<=via_num[counter];counter2++)
			{
				fscanf(fptr2,"%d",&vehicle[2*counter][counter2].via_city);
				//读取城市序号
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
				//计算开车时间 （分钟为单位）
			}

			fscanf(fptr2,"%d",&vehicle[2*counter+1][0].minute);
			//读取起始时间
			fseek(fptr2,1,SEEK_CUR);

			for(counter2=1;counter2<=via_num[counter];counter2++)
			{
				fscanf(fptr2,"%d",&vehicle[2*counter+1][counter2].via_city);
				//读取城市序号
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
				//计算开车时间
			}
		}

		fclose(fptr2);

		Tmatrix=(timepoint***)malloc(city_num*sizeof(timepoint**));
		//动态申请起止时间矩阵

		for(counter=0;counter<city_num;counter++)
			Tmatrix[counter]=(timepoint**)malloc(city_num*sizeof(timepoint*));

		Pmatrix=(ticket_price***)malloc(city_num*sizeof(ticket_price**));
		//动态申请价格矩阵

		for(counter=0;counter<city_num;counter++)
			Pmatrix[counter]=(ticket_price**)malloc(city_num*sizeof(ticket_price*));

        while(1)   //ij表示两个城市，k表示两城市之间车的个数
        {
        	fscanf(fptr3,"%d",&i);  //读取城市1
        	fseek(fptr3,1,SEEK_CUR);

			fscanf(fptr3,"%d",&j);  //读取城市2
        	fseek(fptr3,1,SEEK_CUR);

        	fscanf(fptr3,"%d",&k);  //读取交通工具个数
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
				//读取列车车次
        		fseek(fptr3,1,SEEK_CUR);

        		fscanf(fptr3,"%lf",&Pmatrix[i-1][j-1][counter].price);
				//读取车票价格
        		fseek(fptr3,1,SEEK_CUR);
        	}

			fscanf(fptr3,"%c",&end_ch);   //再读取一个字符判断是否到文件尾

			if(!feof(fptr3)) //若不到文件尾则回退一个字符 判断文件结束
			    fseek(fptr3,-1,SEEK_CUR);
			else
			    break;
        }

        fclose(fptr3);

        num=(int**)malloc(city_num*sizeof(int*));
		//动态申请二维数组保存Tmatrix上最里层的存储位置
        for(counter=0;counter<city_num;counter++)
        {
        	num[counter]=(int*)malloc(city_num*sizeof(int));

        	for(counter2=0;counter2<city_num;counter2++)   //初始化为0
        	    num[counter][counter2]=0;
        }


        for(counter=0;counter<2*vehicle_num;counter++)
		{
			for(counter2=1;counter2<via_num[counter/2];counter2++)
			{
				i=vehicle[counter][counter2].via_city-1;  //得到起止城市序号
				j=vehicle[counter][counter2+1].via_city-1;

				tm[i][j]=1;
				Tmatrix[i][j][num[i][j]].vehicle_number=counter/2+1;
				//得到车次序号

				Tmatrix[i][j][num[i][j]].start_min=
				vehicle[counter][counter2].minute;
				//得到起止时间
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
	//动态申请二维数组arcs保存两点之间

		//所有交通工具之中的最少费用

    //动态申请记录最少费用策略和最短时间策略路径的矩阵 并初始化
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
	//动态申请二维数组time_matrix保存两点之间
	//所有交通工具之中的最短时间


    passen_count=0;
}
