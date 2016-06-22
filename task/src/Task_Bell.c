
#define __TASK_BELL_GLOBALS

#include "Task_Bell.h"
#include "Driver_Bell.h"

#include "Config.h"

//����������
static char Bell_WarningSerial[][20] = {{"0"},                      //0 �޾���
                                        {"10101"},                  //1 ������ʼ�����
                                        {"111100000000000000"},        //2 DBUS����
                                        {"100100100000000000"},        //3 yaw��̨�������
                                        {"100100111000000000"},        //4 pitch��̨�������
                                        {"101110100000000000"},        //5 ��3510����
                                        {"101110111000000000"},        //6 ��3510����
                                        {"101010101000000000"}};       //7 ��������������


/**
  * @brief  ��������������
  * @param  unused
  * @retval void
  */
void Task_BellBark(void *Parameters)
{
	uint8_t SerialPoint = 0;
	
	while(1)
	{
        Bell_Bark(Bell_WarningSerial[BellWarningNum][SerialPoint]);
        if(Bell_WarningSerial[BellWarningNum][SerialPoint + 1] != 0)
        {
            SerialPoint++;
        }
        else
        {
            SerialPoint = 0;
            if(BellWarningCount > 1)
            {
                BellWarningCount--;
            }
            else
            {
                BellWarningNum = 0;
            }
        }
		vTaskDelay(BELLBARKPeriod);
	}
}


