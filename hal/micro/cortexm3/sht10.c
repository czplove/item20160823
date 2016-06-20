
//文件包含----------------------------------------------------------------------
#include <math.h>
#include "sht10.h"
//全局变量定义------------------------------------------------------------------
int16u humi_val_i,temp_val_i;
float humi_val_f,temp_val_f;
//int temp_val_X10;
//int16u humi_val_X10;
//int16u humiString[4],tempString[5];

enum {TEMP,HUMI};//定义温度转换模式和湿度转换模式

int8u error=0; /*错误提示,全局变量*/
int8u error5=0;

//宏定义------------------------------------------------------------------------



#define noACK 0
#define ACK   1
//adr   command       r/w
#define STATUS_REG_W  0x06    //000    0011          0
#define STATUS_REG_R  0x07    //000    0011          1
#define MEASURE_TEMP  0x03    //000    0001          1
#define MEASURE_HUMI  0x05    //000    0010          1
#define RESET         0x1e    //000    1111          0





//函数定义----------------------------------------------------------------------

/*******************************************************************************
一个nop就是一条机器指令周期 = 1/24MHz
那24个nop就是1us啦
*******************************************************************************/ 
void Delay_1u(int16u microSecs) 
{
  while(microSecs--)
  {
    /* 32 NOPs == 1 usecs */
    asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
    asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
    asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
    asm("nop"); asm("nop"); asm("nop"); asm("nop"); asm("nop");
    asm("nop"); asm("nop"); asm("nop"); asm("nop");
    
  }
}

/*******************************************************************************
定义SDA线和SCL线的操作
*******************************************************************************/ 
void WriteSDA1(void)//SDA 输出1,相当于51里面的SDA=1    
{
  GPIO_A_MODE_SET(SDA,GPIOCFG_OUT);//设置SDA推挽输出
  SDA_SET_TO_1();
}

void WriteSDA0(void)//SDA 输出0    
{
  GPIO_A_MODE_SET(SDA,GPIOCFG_OUT);//设置SDA推挽输出
  SDA_SET_TO_0();
}

void WriteSCL1(void)//SCL 输出1    
{
  GPIO_A_MODE_SET(SCL,GPIOCFG_OUT);//设置SCL推挽输出
  SCL_SET_TO_1();
}

void WriteSCL0(void)//SCL 输出0   
{
  GPIO_A_MODE_SET(SCL,GPIOCFG_OUT);//设置SCL推挽输出
  SCL_SET_TO_0();
}

void ReadSDA(void)//设置SDA管脚为上拉输入 
{
  GPIO_A_MODE_SET(SDA,GPIOCFG_IN_PUD);//设置SDA为浮空输入，由外部上拉电阻进行上拉	
  SDA_SET_TO_1();		 
}

void ReadSCL(void)//设置SCL管脚为上拉输入 
{
  GPIO_A_MODE_SET(SCL,GPIOCFG_IN_PUD);//设置SCL为浮空输入，由外部上拉电阻进行上拉	
  SDA_SET_TO_1();		 
}






/*******************************************************************************
写一个字节数据并检查回应
*******************************************************************************/ 
int8u s_write_byte(int8u value)
{ 
  int8u i,error1=0;  
  
  for (i=0x80;i>0;i/=2)             //发送出一个数据的8个数据位
  { 
    if (i & value)  WS_DATA_H;    //masking value with i , write to SENSI-BUS
    else WS_DATA_L;    
    Delay_1u(10);  	  
    WS_SCK_H;                          //SCK高电平期间数据被读取
    Delay_1u(10);                    
    WS_SCK_L;
    Delay_1u(10);  
  }
  
  WS_DATA_read;               //设置数据线为输入线，带上拉电阻，准备接收芯片的回应ACK
  WS_SCK_H;                            //等待ack 
  if(READ_SDA()) error1=1;
  else error1=0;             //检查 ack (数据线会被SHT11拉低为低电平) 
  WS_SCK_L;  
  
  return error1;                     //error=1 in case of no acknowledge
}

/*******************************************************************************
读取一个字节，并在ACK=1的时候给出一个回应
*******************************************************************************/ 
int8u s_read_byte(int8u ack)

{ 
  int8u i,val=0;
  WS_DATA_read;                           //释放数据线，准备读取数据
  
  for (i=0x80;i>0;i/=2)             //读取数据的8个位
  {  
    WS_SCK_H;                          //在SCK为高电平期间进行数据读取
    Delay_1u(10); 
    if (READ_SDA())val=(val | i);        //read bit  
    WS_SCK_L;        
    Delay_1u(10);
  }
  
  if(ack==1)  WS_DATA_L;  //拉低数据线，进行回应ACK
  else if(ack==0) WS_DATA_H;  
  
  WS_SCK_H;                 //在ACK期间，sck应保持为高电平
  Delay_1u(10);            //pulswith approx. 5 us 
  WS_SCK_L;          
  WS_DATA_read;                //释放数据线
  return val;
}
/*******************************************************************************
启动数据通信
// DATA:      |_______|
//           ___     ___
// SCK : ___|   |___|   |______
*******************************************************************************/ 
void s_transstart(void)
{  
  WS_DATA_H;  //SDA先拉高
  WS_SCK_L;  //SCK先拉低
  Delay_1u(100);    
  WS_SCK_H;   //SCK拉高
  Delay_1u(100);
  WS_DATA_L;  //在SCK为高期间SDA变低
  Delay_1u(100);
  WS_SCK_L;   //然后SCK变低
  Delay_1u(200);
  WS_SCK_H;   //SCK再拉高
  Delay_1u(100);
  WS_DATA_H;    //SDA拉高
  Delay_1u(100);
  WS_SCK_L;    //SCL变低，完成启动时序
}
/*******************************************************************************
复位温湿度传感器
//       _____________________________________________________        ________
// DATA:                                                      |_______|
_    _    _    _    _    _    _    _    _        ___     ___
// SCK :__| |__| |__| |__| |__| |__| |__| |__| |__| |______|   |___|   |______
*******************************************************************************/ 
void s_connectionreset(void)
{ 
  
  int8u i;
  
  WS_DATA_H; 
  WS_SCK_L;                    //Initial state
  
  for(i=0;i<9;i++)                  //9 SCK cycles
  {
    WS_SCK_H;
    Delay_1u(10); 
    WS_SCK_L;
    Delay_1u(10); 
  }
  
  s_transstart();                   //transmission start
}
/*******************************************************************************
软件复位温湿度传感器
*******************************************************************************/ 
int8u s_softreset(void)
{ 
  int8u error2=0;  
  s_connectionreset();              //reset communication
  error2+=s_write_byte(RESET);       //send RESET-command to sensor
  return error2;                     //error=1 in case of no response form the sensor
}
/*******************************************************************************
读取温湿度传感器的状态寄存器
输入参数：用于存储读取数据的指针，用于存储校验码的指针
*******************************************************************************/ 
int8u s_read_statusreg(int8u *p_value, int8u *p_checksum)
{ 
  int8u error3=0;
  
  s_transstart();                   //transmission start
  error3=s_write_byte(STATUS_REG_R); //send command to sensor
  *p_value=s_read_byte(ACK);        //read status register (8-bit)
  *p_checksum=s_read_byte(noACK);   //read checksum (8-bit)  
  
  return error3;                     //error=1 in case of no response form the sensor
}
/*******************************************************************************
写温湿度传感器的配置寄存器
输入参数：指向等待写入的数据的指针
*******************************************************************************/ 
int8u s_write_statusreg(int8u *p_value)
{ 
  int8u error4=0;
  
  s_transstart();                   //transmission start
  error4+=s_write_byte(STATUS_REG_W);//send command to sensor
  error4+=s_write_byte(*p_value);    //send value of status register
  
  return error4;                     //error>=1 in case of no response form the sensor
}

/*******************************************************************************
开启温湿度传感器的转换功能并存储转换后得到的数据
输入参数：用于存储校验码的指针，指定转换温度或湿度的指定值
*******************************************************************************/ 
int8u s_measure(int8u *p_checksum, int8u mode)
{ 
  int16u i;
  error5 = 0;
  
  s_transstart();                   //transmission start
  
  switch(mode)
  {                     //send command to sensor
  case HUMI: 
    {
      error5+=s_write_byte(MEASURE_HUMI); 			  
      WS_DATA_read;
      for (i=0;i<65535;i++)//在转换期间，信号线被上拉为高电平
      { 
        Delay_1u(100);
        halResetWatchdog();   // Periodically reset the watchdog.周期性的重启看门狗
        if(READ_SDA()==0) break;  //wait until sensor has finished the measurement
      }	  
      if(READ_SDA()) error5+=1;                   // or timeout (~2 sec.) is reached		  			  		  
      humi_val_i=s_read_byte(ACK);                 //read the first byte (MSB)
      humi_val_i = (humi_val_i<<8) + s_read_byte(ACK);//read the second byte (LSB)
      *p_checksum =s_read_byte(noACK);       //read checksum
      break;
    } 
  case TEMP :
    {
      error5+=s_write_byte(MEASURE_TEMP);			  
      WS_DATA_read;     
      for (i=0;i<65535;i++)
      {
        halResetWatchdog();   // Periodically reset the watchdog.周期性的重启看门狗
        Delay_1u(100);
        if(READ_SDA()==0) break;  //wait until sensor has finished the measurement
      }		  
      if(READ_SDA()) error5+=1;               // or timeout (~2 sec.) is reached   
      temp_val_i=s_read_byte(ACK);                 //read the first byte (MSB)
      temp_val_i = (temp_val_i<<8) + s_read_byte(ACK);//read the second byte (LSB)
      *p_checksum =s_read_byte(noACK);       //read checksum
      break;
    }
  default     : break;  
  }
  
  return error5;
}


/*******************************************************************************
对得到的温度数据和适度数据进行校正
输入参数：指向存储温度数据和湿度数据的指针
// calculates temperature and humidity [%RH] 
// input :  humi [Ticks] (12 bit) 
//          temp [Ticks] (14 bit)
*******************************************************************************/ 
void calc_sth11(float *p_humidity ,float *p_temperature)
{ const float C1=-4.0;              // for 12 Bit
const float C2=+0.0405;           // for 12 Bit
const float C3=-0.0000028;        // for 12 Bit
const float T1=+0.01;             // for 14 Bit @ 5V
const float T2=+0.00008;           // for 14 Bit @ 5V
float rh=*p_humidity;             // rh:      Humidity [Ticks] 12 Bit 
float t=*p_temperature;           // t:       Temperature [Ticks] 14 Bit
float rh_lin;                     // rh_lin:  Humidity linear
float rh_true;                    // rh_true: Temperature compensated humidity
float t_C;                        // t_C   :  Temperature

t_C=t*0.01 - 39.62;                  //计算出实际的温度值
rh_lin=C3*rh*rh + C2*rh + C1;     //计算出实际的湿度数值 [%RH]
rh_true=(t_C-25)*(T1+T2*rh)+rh_lin;   //对湿度数值进行温度补偿 [%RH]
if(rh_true>100)rh_true=100;       //cut if the value is outside of
if(rh_true<0.1)rh_true=0.1;       //the physical possible range
*p_temperature=t_C;               //返回温度
*p_humidity=rh_true;              //返回湿度[%RH]
}
/*******************************************************************************
根据温度和湿度数据计算露点
输入参数：温度值和湿度值
*******************************************************************************/ 
float calc_dewpoint(float h,float t)
{ float logEx,dew_point;
logEx=0.66077+7.5*t/(237.3+t)+(log10(h)-2);
dew_point = (logEx - 0.66077)*237.3/(0.66077+7.5-logEx);
return dew_point;
}
/*******************************************************************************
进行温度和湿度转换，并得到最终数值
// 1. 首先复位连接并建立连接
// 2. 进行温度和湿度转换
// 3. 校正湿度 [%RH] 和温度 
// 4. 计算露点
// 5. 从串口输出温度、湿度、露点值
*******************************************************************************/ 
void calc_sth10_resault(int16s * TempValue, int16u * HumiValue)
{ 
  float dew_point;//露点
  int8u checksum;
  
  s_connectionreset();
  error=0;
  error+=s_measure(&checksum,HUMI);  //measure humidity
  error+=s_measure(&checksum,TEMP);  //measure temperature
  
  if(error!=0) s_connectionreset();                 //in case of an error: connection reset
  else
  {	 
    humi_val_f=(float)humi_val_i;                   //整数转换为float
    temp_val_f=(float)temp_val_i;                   //整数转换为float
    calc_sth11(&humi_val_f,&temp_val_f);            //计算湿度，温度
    dew_point=calc_dewpoint(humi_val_f,temp_val_f); //计算露点
    *TempValue = (int)(temp_val_f*100);
    *HumiValue = (int)(humi_val_f*100);
    emberSerialPrintf(APP_SERIAL,"temp: %d ℃ ； humi:%d %% RH； dew point: %d ℃\n",(int)temp_val_f,(int)humi_val_f,(int)dew_point);		
  }
}

/*
void result2string(float *p_humidity ,float *p_temperature)
{
//    humiString[4],tempString[5];
int tempX10,humiX10;
if(*p_temperature < 0)
{
tempString[0] = 1;//表示温度为负
  }
  else
{
tempString[0] = 0;//表示温度为正
  }
tempX10 = (int)fabs(*p_temperature) * 10;
tempString[1] = tempX10 / 100 ;//表示温度为正
tempString[1] = tempX10 / 100 ;//表示温度为正
tempString[1] = tempX10 / 100 ;//表示温度为正

}

*/