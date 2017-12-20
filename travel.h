#include<stdio.h>
#include<stdlib.h>
#include <conio.h>
#include <winsock.h>
#include <winbase.h>
#include <time.h>
#include<conio.h>
#include<string.h>
#include<math.h>
#include"egg.h"
 

//编号都从一开始 数组下表都从0 开始
#define MAX 1000000
#define MAX2 1000000.0
#define INTERVAL 500

#define QUERY 1  //客户查询旅行计划
#define MOVING 2  //程序运行
#define SEARCH 3  //查询客户当前状态

int state;  //程序运行状态
int time_count;  //时间片计数

int city_num;
int vehicle_num;
int ** p;
int ** pm,**tm; //pm是pmatrix每两个城市间车的个数
int *** path;
int *** time_path;
int graphic1;
int s;
FILE * fptr1,* fptr2;

double * D;

typedef struct{    //结构内为车次，发车频率  下表从0开始
char number[4];
int times;
}train_num;
train_num *Tnumber ;

typedef struct{
int via_city;
int minute;
}Station;
//结构内为途径城市和到站时间 从文件2读取 下标为0 的位置存起始天数
Station **vehicle;

typedef struct{
int vehicle_number;
double price;
} ticket_price;       //结构内为车次和票价
ticket_price ***Pmatrix;

typedef struct {       //最短时间策略数组，车次，起止时间
int vehicle_number;
int start_min;
int end_min;
} timepoint;
timepoint ***Tmatrix;

typedef struct{     //最少费用策略数组，存两城市间最小费用及对应车次
double mini_price;
int mini_pri_veh;
}price_arc;
price_arc **arcs;

typedef struct{
int year;
int month;
int day;
int hour;
int minute;
}start_date;   //乘客出发时间数组（不同乘客出发时间不同）
start_date stime[100],system_t;
//system_t为系统时间

typedef struct{     //最少时间策略数组，存两城市间最短时间及对应车次
int mini_time;
int mini_time_veh;
}time_arc;
time_arc **time_matrix;

struct pass_state{  //队列 旅客行程
int passenger_state;  //1表示在车上 2表示在城市里停留
int city_or_vehicle;
int pass_start_c;  //出发城市
int pass_arrive_c;  //到达城市
int arrive_year;
int arrive_month;
int arrive_day;
int arrive_min;
double pass_price;
struct pass_state * next;
};
typedef struct pass_state PASSENGER_LINK;
typedef struct pass_state* pass;
pass passengers[100];

//存指针的数组，指针指向每个乘客的结构  乘客序号是对应下标，第0个乘客开始
int passen_count,pcount;
//需要初始化为0，记录当前数组行进的下标，
//即新乘客链表指针可以存在数组下标为i的位置


typedef struct Way{
	int city;
	int veh;
}way;

char **city;  //城市数组 下标从零开始
double ** new_price; //每两个城市间的最小费用
int **num; //保存Tmatrix最里层的存储位置


HEGG g_egg1[100],g_egg2[100],g_egg3[100],g_egg,temp_g_egg[100],end_egg[100],gg; 
int flag[100];   //指示交通工具的数组 
int termination[100];
int sx[100],sy[100],ex[100],ey[100];


void initial();//初始化
void start_system();//系统控制
void getInput();//策略输入
void Link();    //旅客行程链表创建
void pull();    //出队列
void query();   //查询旅客状态
void system_time_count();//系统时间
void ShortestPath_DIJ(int,price_arc**);
void calcu_price();//计算最小费用
void time_switch(int,int*,int*,int*); //时间转换
void full_permutation(int,int **);   //途经城市全排列
void via_city_price(int,int,int,int,int,int *,int,int); //有途径城市的最少价钱
void output_price(int,int,int,int,int,int);             //无途经城市的最少价钱
int need_day_to_go(int,int,int,int,int,int *,int *);  //等车天数
int cal_min_time(int,int,int);
void cal_mini_minute(int,int,int);
void print();  //打印旅行策略
void dfs(int,int,int*,int);
void order(int,int,int,double *,int**,int***);
//void via_city_timeprice(int,int,int,int,int,int *,int,int,int*,int*);
void no_via_city_timeprice(int,int,int,int,int,int,int,int);//策略三无途经
void search_t_Path(int*,int,int);
void search_p_Path(int*,int,int);
void via_timeprice(int,int,int,int,int,int*,int,int,int,int);
void BackTrack(int);
void without_via_mintime(int,int,int,int,int,int);
void with_via_mintime(int,int,int,int,int,int *,int,int);
void least_time(int,int,int);
int timeprice_without_via(int,int,int,int,int,int);
int time_compare(start_date,start_date);
void drawmap();
void printmap(int,int,int,int);
void print_message(void);
void swap_double(double *, double *);
void swap_int(int *, int *);
