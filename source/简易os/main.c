#include "core.h"
#include "task_switch.h"
#include "reg51.h"

/*设置两个LED GPIO口*/
sbit led1 = P1^4;
sbit led2 = P1^5;

/* 系统初始化 */
void system_init(void)
{
	P1M1 = 0;	P1M0 = 0;	//设置为准双向口
}

void test(void)
{
	char i = 0;
	
	os_delay(10);	
	i++;
	i++;
}

void task_0(void)
{
	while(1)
	{
		led1 = 0;
		test();
		os_delay(3000);
		led1 = 1;
		os_delay(3000);
	}
}

void task_1(void)
{
	while(1)
	{
		led2 = 0;
		os_delay(100);
		led2 = 1;
		os_delay(100);
	}
}

int main(void)
{
	system_init();
	os_init();
	os_task_create(1,task_1,(unsigned char)os_tsak_stack[1]);
	os_task_create(0,task_0,(unsigned char)os_tsak_stack[0]);
	os_start();

	return 0;
}


