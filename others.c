#include"travel.h"
//将天数换算为年月日
void time_switch(int days,int* year,int* mon,int* day)
{
	int month[13]={0,31,0,31,30,31,30,31,31,30,31,30,31};
	int d,k;
	*year=days/365; //估算年份
	switch(*year%4)   //年
	{
	   	case 0:d=(*year/4)*(365*3+366);break;
	   	case 1:d=(*year/4)*(365*3+366)+365;break;
	   	case 2:d=(*year/4)*(365*3+366)+365*2;break;
	   	case 3:d=(*year/4)*(365*3+366)+365*3;break;
	}
	if(days<d)
	{
		(*year)--;
		if(*year%4==3)
		    d=d-366;
		else d=d-365;
		(*year)++;
	}
	days=days-d;
	*mon=days/28;
	if(*year%4==0) //月
	    month[2]=29;
	else
	    month[2]=28;
	for(k=1,d=0;k<=*mon;k++)
	    d=d+month[k];
	if(days<d)
	{
		(*mon)--;
		for(k=1,d=0;k<=*mon;k++)
	        d=d+month[k];
	}
	(*mon)++;
	*day=days-d;
	*year=*year+2016;
}

//比较a b时间大小 a大于b返回1  否则返回0
int time_compare(start_date a,start_date b)
{
	if(b.year<a.year||(b.year==a.year&&b.month<a.month)
	   ||(b.year==a.year&&b.month==a.month&&b.day<a.day)
	   ||(b.year==a.year&&b.month==a.month&&b.day==a.day&&b.hour<a.hour)
	   ||(b.year==a.year&&b.month==a.month&&b.day==a.day&&b.hour==a.hour&&b.minute<a.minute))
	    return 1;
	else
		return 0;
}

//全排列函数 将全排列得到的结果存入数组**a
void full_permutation(int numb,int ** a)
{
	int * perm;
	int i,j,k,r,s,count=1,temp;
	perm=(int*)malloc(numb*sizeof(int));  //下标从0开始
	for(i=0;i<numb;i++)   //创建字典序的第一个排序即12345....
	    perm[i]=i+1;

	for(i=2;i<=numb;i++)  //计算全排列个数
	    count=count*i;

	for(j=0;j<numb;j++)  //赋值
		a[0][j]=perm[j];

	for(i=1;i<count;i++)
	{
		j=numb-2;
	    while(perm[j]>perm[j+1])
	    {
	    	j--;
	    }
	    k=numb-1;
	    while(perm[j]>perm[k])
	    {
	    	k--;
	    }
	    temp=perm[j];  //交换
	    perm[j]=perm[k];
	    perm[k]=temp;

	    r=numb-1;
	    s=j+1;

	    while(r>s)
	    {
		    temp=perm[r];  //交换
	        perm[r]=perm[s];
	        perm[s]=temp;
	        r--;
			s++;
		}
		for(j=0;j<numb;j++)  //赋值
			a[i][j]=perm[j];
	}
}
