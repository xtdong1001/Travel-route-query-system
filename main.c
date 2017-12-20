#include"travel.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[])
{
	time_count=0;
	state=MOVING;
	passen_count=0;
	
	//系统时间初始化 
	system_t.year=2016;
	system_t.month=1;
	system_t.day=1;
	system_t.hour=0;
	system_t.minute=0;
	//打开用于保存运行记录的文件
	initial();
    calcu_price();   //计算任意两城市间的最小费用

    system("color 2F");
    
	printf("                    *****************************************\n");
	printf("                    *                                       *\n");
	printf("                    *       欢迎使用本旅游路线查询系统      *\n");
	printf("                    *           可以先选择输出方式          *\n");
	printf("                    *          (1--命令行，2--图形化)       *\n");
	printf("                    *          然后按照菜单选择请求         *\n");
	printf("                    *                 菜单：                *\n");
	printf("                    *                                       *\n");
	printf("                    *      -->1.------查询旅行策略------    *\n");
	printf("                    *      -->2.------查询当前状态------    *\n");
	printf("                    *      -->3.------更改旅行策略------    *\n");
	printf("                    *      -->4.------    退出    ------    *\n");
	printf("                    *                                       *\n");
	printf("                    * 温馨提示：城市和对应序号都在窗口显示哦*\n");
	printf("                    *    按照提示的输入步骤和格式输入即可   *\n");
	printf("                    *                                       *\n");
	printf("                    *      祝您使用愉快O(  ∩ _  ∩)O~      *\n");
	printf("                    *****************************************\n");


    /*创建线程1：时间片推进*/
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
