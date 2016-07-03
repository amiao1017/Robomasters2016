
#ifndef __DRIVER_VISION_H
#define __DRIVER_VISION_H


#include "stm32f4xx.h"
#include "OSinclude.h"


#define PCDATALENGTH            26  //帧长
#define ENEMYDATABUFFERLENGHT   30 //敌人数据帧
#define FITDATANUMMIN           8   //最小拟合数据数据量


#ifdef  __DRIVER_VISION_GLOBALS
#define __DRIVER_VISION_EXT 
#else
#define __DRIVER_VISION_EXT extern
#endif


//视觉数据结构
typedef struct
{
    float X;
    float Y;
    float Z;
    float TimeStamp;
    int Time;
    char ID;
}Enemy_Struct;

//格式转换联合体
typedef union
{
    uint8_t u8[4];
    float F;
    int I;
}FormatTrans;

//点数据结构
typedef struct
{
    float X;
    float Y;
    float Z;
}Point_Struct;

//角数据结构(浮点型用于实际角度）
typedef struct
{
    float H;
    float V;
}AngleF_Struct;

//角数据结构(整型用于编码器角度）
typedef struct
{
    int16_t H;
    int16_t V;
}AngleI_Struct;

//预判控制数据结构
typedef struct
{
    AngleI_Struct Target;       //目标角度（编码器单位，中间为0，左正右负）
    portTickType TargetTick;         //在此绝对时间到达目标角度
}ForcastControl_Struct;


//主机原始数据缓存
__DRIVER_VISION_EXT uint8_t PCDataBuffer[PCDATALENGTH];
//主机原始数据缓存指针
__DRIVER_VISION_EXT uint8_t PCDataBufferPoint;
//主机解码数据缓存
__DRIVER_VISION_EXT Enemy_Struct EnemyDataBuffer[ENEMYDATABUFFERLENGHT];
//主机解码数据缓存指针
__DRIVER_VISION_EXT uint8_t EnemyDataBufferPoint;
//预判目标数据
__DRIVER_VISION_EXT ForcastControl_Struct ForcastTarget;
//数据更新标志
__DRIVER_VISION_EXT uint8_t VisionUpdataFlag;



//帧数统计
__DRIVER_VISION_EXT int16_t PCFrameCounter;
//帧率统计
__DRIVER_VISION_EXT int16_t PCFrameRate;


void Vision_InitConfig(void);
AngleI_Struct RecToPolar(float X, float Y, float Z, float RealPitch, uint16_t PitchEncoder, uint8_t mode);
uint8_t ForcastCore(uint16_t SampleTime, uint16_t ForcastTime, Point_Struct *ForcastPoint);
uint8_t ForcastOnce(uint16_t SampleTime, uint16_t ForcastTime, AngleI_Struct *ForcastAngle, uint8_t TimeMode);


#endif
