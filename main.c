#include"travel.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[])
{
	time_count=0;
	state=MOVING;
	passen_count=0;
	
	//ϵͳʱ���ʼ�� 
	system_t.year=2016;
	system_t.month=1;
	system_t.day=1;
	system_t.hour=0;
	system_t.minute=0;
	//�����ڱ������м�¼���ļ�
	initial();
    calcu_price();   //�������������м����С����

    system("color 2F");
    
	printf("                    *****************************************\n");
	printf("                    *                                       *\n");
	printf("                    *       ��ӭʹ�ñ�����·�߲�ѯϵͳ      *\n");
	printf("                    *           ������ѡ�������ʽ          *\n");
	printf("                    *          (1--�����У�2--ͼ�λ�)       *\n");
	printf("                    *          Ȼ���ղ˵�ѡ������         *\n");
	printf("                    *                 �˵���                *\n");
	printf("                    *                                       *\n");
	printf("                    *      -->1.------��ѯ���в���------    *\n");
	printf("                    *      -->2.------��ѯ��ǰ״̬------    *\n");
	printf("                    *      -->3.------�������в���------    *\n");
	printf("                    *      -->4.------    �˳�    ------    *\n");
	printf("                    *                                       *\n");
	printf("                    * ��ܰ��ʾ�����кͶ�Ӧ��Ŷ��ڴ�����ʾŶ*\n");
	printf("                    *    ������ʾ�����벽��͸�ʽ���뼴��   *\n");
	printf("                    *                                       *\n");
	printf("                    *      ף��ʹ�����O(  �� _  ��)O~      *\n");
	printf("                    *****************************************\n");


    /*�����߳�1��ʱ��Ƭ�ƽ�*/
	DWORD ThreadID1 = 1;
    HANDLE hRead1 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)system_time_count,
                                NULL,0,&ThreadID1);
	
	start_system();
	
	
	while(1)
	{
		if(s==4)
		    break; 
	}
	return 0;
}
