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
 

//��Ŷ���һ��ʼ �����±���0 ��ʼ
#define MAX 1000000
#define MAX2 1000000.0
#define INTERVAL 500

#define QUERY 1  //�ͻ���ѯ���мƻ�
#define MOVING 2  //��������
#define SEARCH 3  //��ѯ�ͻ���ǰ״̬

int state;  //��������״̬
int time_count;  //ʱ��Ƭ����

int city_num;
int vehicle_num;
int ** p;
int ** pm,**tm; //pm��pmatrixÿ�������м䳵�ĸ���
int *** path;
int *** time_path;
int graphic1;
int s;
FILE * fptr1,* fptr2;

double * D;

typedef struct{    //�ṹ��Ϊ���Σ�����Ƶ��  �±��0��ʼ
char number[4];
int times;
}train_num;
train_num *Tnumber ;

typedef struct{
int via_city;
int minute;
}Station;
//�ṹ��Ϊ;�����к͵�վʱ�� ���ļ�2��ȡ �±�Ϊ0 ��λ�ô���ʼ����
Station **vehicle;

typedef struct{
int vehicle_number;
double price;
} ticket_price;       //�ṹ��Ϊ���κ�Ʊ��
ticket_price ***Pmatrix;

typedef struct {       //���ʱ��������飬���Σ���ֹʱ��
int vehicle_number;
int start_min;
int end_min;
} timepoint;
timepoint ***Tmatrix;

typedef struct{     //���ٷ��ò������飬�������м���С���ü���Ӧ����
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
}start_date;   //�˿ͳ���ʱ�����飨��ͬ�˿ͳ���ʱ�䲻ͬ��
start_date stime[100],system_t;
//system_tΪϵͳʱ��

typedef struct{     //����ʱ��������飬�������м����ʱ�估��Ӧ����
int mini_time;
int mini_time_veh;
}time_arc;
time_arc **time_matrix;

struct pass_state{  //���� �ÿ��г�
int passenger_state;  //1��ʾ�ڳ��� 2��ʾ�ڳ�����ͣ��
int city_or_vehicle;
int pass_start_c;  //��������
int pass_arrive_c;  //�������
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

//��ָ������飬ָ��ָ��ÿ���˿͵Ľṹ  �˿�����Ƕ�Ӧ�±꣬��0���˿Ϳ�ʼ
int passen_count,pcount;
//��Ҫ��ʼ��Ϊ0����¼��ǰ�����н����±꣬
//���³˿�����ָ����Դ��������±�Ϊi��λ��


typedef struct Way{
	int city;
	int veh;
}way;

char **city;  //�������� �±���㿪ʼ
double ** new_price; //ÿ�������м����С����
int **num; //����Tmatrix�����Ĵ洢λ��


HEGG g_egg1[100],g_egg2[100],g_egg3[100],g_egg,temp_g_egg[100],end_egg[100],gg; 
int flag[100];   //ָʾ��ͨ���ߵ����� 
int termination[100];
int sx[100],sy[100],ex[100],ey[100];


void initial();//��ʼ��
void start_system();//ϵͳ����
void getInput();//��������
void Link();    //�ÿ��г�������
void pull();    //������
void query();   //��ѯ�ÿ�״̬
void system_time_count();//ϵͳʱ��
void ShortestPath_DIJ(int,price_arc**);
void calcu_price();//������С����
void time_switch(int,int*,int*,int*); //ʱ��ת��
void full_permutation(int,int **);   //;������ȫ����
void via_city_price(int,int,int,int,int,int *,int,int); //��;�����е����ټ�Ǯ
void output_price(int,int,int,int,int,int);             //��;�����е����ټ�Ǯ
int need_day_to_go(int,int,int,int,int,int *,int *);  //�ȳ�����
int cal_min_time(int,int,int);
void cal_mini_minute(int,int,int);
void print();  //��ӡ���в���
void dfs(int,int,int*,int);
void order(int,int,int,double *,int**,int***);
//void via_city_timeprice(int,int,int,int,int,int *,int,int,int*,int*);
void no_via_city_timeprice(int,int,int,int,int,int,int,int);//��������;��
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
