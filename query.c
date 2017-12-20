/*可以根据查询时间得到用户当前所在位置或者正在乘坐的交通工具*/
/*此过程由系统完成，即系统查询顾客的状态*/
//在之前的调用它的函数中只需要键入模式，即是否要查询，如果需要，则调用这个函数
#include"travel.h"


/*建立存储乘客出行计划的链表数组*/
/*被输入函数调用，当有新的乘客有计划请求时，调用*/

//查询旅客状态
void query()
{
	int numb,mark=1;         //乘客编号
	int city_vehicle_num;
	int start_city_num,end_city_num;

	//输入分配的旅客号
	while(mark==1)
	{
		mark=0;
		printf("请输入您的乘客序号！\n");
		scanf("%d",&numb);
		if(numb>99||numb<1||numb>passen_count)
		{
			printf("序号有误，请重新输入！\n");
			mark=1;
		}
	}

	if(!time_compare(stime[numb],system_t))//系统时间晚于或等于出发时间
	{
		if(passengers[numb]->passenger_state==1)     //表明此时乘客在车上
		{
			start_city_num=passengers[numb]->pass_start_c-1;
			end_city_num=passengers[numb]->pass_arrive_c-1;
			city_vehicle_num=passengers[numb]->city_or_vehicle-1;
			if(Tnumber[city_vehicle_num].number[0]=='k')
		    	printf("此时乘客正在%s开往%s的%s号火车上！\n",city[start_city_num],
				city[end_city_num],Tnumber[city_vehicle_num].number);
			if(Tnumber[city_vehicle_num].number[0]=='b')
		    	printf("此时乘客正在%s开往%s的%s号汽车上！\n",city[start_city_num],
				city[end_city_num],Tnumber[city_vehicle_num].number);
			if(Tnumber[city_vehicle_num].number[0]=='f')
		    	printf("此时乘客正在%s开往%s的%s号飞机上！\n",city[start_city_num],
				city[end_city_num],Tnumber[city_vehicle_num].number);
		}
		else                          //乘客在某一个城市
		{
			city_vehicle_num=passengers[numb]->city_or_vehicle-1;
	    	printf("此刻该乘客正在%s停留！\n",city[city_vehicle_num]);
    	}
	}
	else
	    printf("乘客未出发！\n");

}

