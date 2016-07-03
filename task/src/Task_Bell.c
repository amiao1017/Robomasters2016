
#define __TASK_BELL_GLOBALS

#include "Task_Bell.h"
#include "Driver_Bell.h"

#include "Config.h"

//蜂鸣器序列
static char Bell_WarningSerial[][20] = {{"0"},                          //0  无警告
                                        {"10101"},                      //1  开机初始化完成
                                        {"111100000000000000"},         //2  DBUS离线
                                        {"100100100000000000"},         //3  yaw云台电机离线
                                        {"100100111000000000"},         //4  pitch云台电机离线
                                        {"101110100000000000"},         //5  左3510离线(步兵不用)
                                        {"101110111000000000"},         //6  右3510离线(步兵不用)
                                        {"101010101000000000"},         //7  底盘陀螺仪离线
                                        {"111010100000000000"},         //8  左前底盘电机离线
                                        {"111010111000000000"},         //9  右前底盘电机离线
                                        {"111010101000000000"},         //10 左后底盘电机离线
                                        {"111010101110000000"},         //11 右后底盘电机离线
                                        };


/**
  * @brief  蜂鸣器鸣叫任务
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



