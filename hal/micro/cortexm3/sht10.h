

#ifndef __SHT10_H 
#define __SHT10_H 

//文件包含----------------------------------------------------------------------
#include "app/framework/include/af.h"
#include "app/framework/util/attribute-storage.h"
#include "GPIO_Control.h"
//iic管脚配置-------------------------------------------------------------------
#define SCL PA4
#define SDA PA3

//函数声明----------------------------------------------------------------------
#define SDA_SET_TO_1()  GPIO_A_SET(SDA)
#define SDA_SET_TO_0()  GPIO_A_CLR(SDA)
#define SCL_SET_TO_1()  GPIO_A_SET(SCL)
#define SCL_SET_TO_0()  GPIO_A_CLR(SCL)
#define READ_SDA()      GPIO_A_READ(SDA)


#define WS_SCK_H         WriteSCL1()
#define WS_SCK_L         WriteSCL0()  
    
#define WS_DATA_H        WriteSDA1() 
#define WS_DATA_L        WriteSDA0()

#define WS_DATA_read     ReadSDA() 

extern void WriteSDA1(void);
extern void WriteSDA0(void);
extern void WriteSCL1(void);
extern void WriteSCL0(void);
extern void ReadSDA(void);
extern void ReadSCL(void);
extern int8u s_write_byte( int8u value);
extern int8u s_read_byte( int8u ack);
extern void s_transstart(void);
extern void s_connectionreset(void);
extern int8u s_softreset(void);
extern int8u s_read_statusreg( int8u *p_value,  int8u *p_checksum);
extern int8u s_write_statusreg( int8u *p_value);
extern int8u s_measure( int8u *p_checksum,  int8u mode);

extern void calc_sth11(float *p_humidity ,float *p_temperature);
extern void result2string(float *p_humidity ,float *p_temperature);
extern float calc_dewpoint(float h,float t);

void calc_sth10_resault(int16s * TempValue, int16u * HumiValue);
extern int16u humi_val_i,temp_val_i;
 
extern float humi_val_f,temp_val_f;
extern int temp_val_X10;
extern int16u humi_val_X10;

extern int16u humiString[4],tempString[5];

extern void Delay_1u(int16u microSecs); 

#endif 
