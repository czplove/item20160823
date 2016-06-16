
//�ļ�����----------------------------------------------------------------------
#include <math.h>
#include "sht10.h"
//ȫ�ֱ�������------------------------------------------------------------------
int16u humi_val_i,temp_val_i;
float humi_val_f,temp_val_f;
//int temp_val_X10;
//int16u humi_val_X10;
//int16u humiString[4],tempString[5];

enum {TEMP,HUMI};//�����¶�ת��ģʽ��ʪ��ת��ģʽ

int8u error=0; /*������ʾ,ȫ�ֱ���*/
int8u error5=0;

//�궨��------------------------------------------------------------------------



#define noACK 0
#define ACK   1
//adr   command       r/w
#define STATUS_REG_W  0x06    //000    0011          0
#define STATUS_REG_R  0x07    //000    0011          1
#define MEASURE_TEMP  0x03    //000    0001          1
#define MEASURE_HUMI  0x05    //000    0010          1
#define RESET         0x1e    //000    1111          0





//��������----------------------------------------------------------------------

/*******************************************************************************
һ��nop����һ������ָ������ = 1/24MHz
��24��nop����1us��
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
����SDA�ߺ�SCL�ߵĲ���
*******************************************************************************/ 
void WriteSDA1(void)//SDA ���1,�൱��51�����SDA=1    
{
  GPIO_A_MODE_SET(SDA,GPIOCFG_OUT);//����SDA�������
  SDA_SET_TO_1();
}

void WriteSDA0(void)//SDA ���0    
{
  GPIO_A_MODE_SET(SDA,GPIOCFG_OUT);//����SDA�������
  SDA_SET_TO_0();
}

void WriteSCL1(void)//SCL ���1    
{
  GPIO_A_MODE_SET(SCL,GPIOCFG_OUT);//����SCL�������
  SCL_SET_TO_1();
}

void WriteSCL0(void)//SCL ���0   
{
  GPIO_A_MODE_SET(SCL,GPIOCFG_OUT);//����SCL�������
  SCL_SET_TO_0();
}

void ReadSDA(void)//����SDA�ܽ�Ϊ�������� 
{
  GPIO_A_MODE_SET(SDA,GPIOCFG_IN_PUD);//����SDAΪ�������룬���ⲿ���������������	
  SDA_SET_TO_1();		 
}

void ReadSCL(void)//����SCL�ܽ�Ϊ�������� 
{
  GPIO_A_MODE_SET(SCL,GPIOCFG_IN_PUD);//����SCLΪ�������룬���ⲿ���������������	
  SDA_SET_TO_1();		 
}






/*******************************************************************************
дһ���ֽ����ݲ�����Ӧ
*******************************************************************************/ 
int8u s_write_byte(int8u value)
{ 
  int8u i,error1=0;  
  
  for (i=0x80;i>0;i/=2)             //���ͳ�һ�����ݵ�8������λ
  { 
    if (i & value)  WS_DATA_H;    //masking value with i , write to SENSI-BUS
    else WS_DATA_L;    
    Delay_1u(10);  	  
    WS_SCK_H;                          //SCK�ߵ�ƽ�ڼ����ݱ���ȡ
    Delay_1u(10);                    
    WS_SCK_L;
    Delay_1u(10);  
  }
  
  WS_DATA_read;               //����������Ϊ�����ߣ����������裬׼������оƬ�Ļ�ӦACK
  WS_SCK_H;                            //�ȴ�ack 
  if(READ_SDA()) error1=1;
  else error1=0;             //��� ack (�����߻ᱻSHT11����Ϊ�͵�ƽ) 
  WS_SCK_L;  
  
  return error1;                     //error=1 in case of no acknowledge
}

/*******************************************************************************
��ȡһ���ֽڣ�����ACK=1��ʱ�����һ����Ӧ
*******************************************************************************/ 
int8u s_read_byte(int8u ack)

{ 
  int8u i,val=0;
  WS_DATA_read;                           //�ͷ������ߣ�׼����ȡ����
  
  for (i=0x80;i>0;i/=2)             //��ȡ���ݵ�8��λ
  {  
    WS_SCK_H;                          //��SCKΪ�ߵ�ƽ�ڼ�������ݶ�ȡ
    Delay_1u(10); 
    if (READ_SDA())val=(val | i);        //read bit  
    WS_SCK_L;        
    Delay_1u(10);
  }
  
  if(ack==1)  WS_DATA_L;  //���������ߣ����л�ӦACK
  else if(ack==0) WS_DATA_H;  
  
  WS_SCK_H;                 //��ACK�ڼ䣬sckӦ����Ϊ�ߵ�ƽ
  Delay_1u(10);            //pulswith approx. 5 us 
  WS_SCK_L;          
  WS_DATA_read;                //�ͷ�������
  return val;
}
/*******************************************************************************
��������ͨ��
// DATA:      |_______|
//           ___     ___
// SCK : ___|   |___|   |______
*******************************************************************************/ 
void s_transstart(void)
{  
  WS_DATA_H;  //SDA������
  WS_SCK_L;  //SCK������
  Delay_1u(100);    
  WS_SCK_H;   //SCK����
  Delay_1u(100);
  WS_DATA_L;  //��SCKΪ���ڼ�SDA���
  Delay_1u(100);
  WS_SCK_L;   //Ȼ��SCK���
  Delay_1u(200);
  WS_SCK_H;   //SCK������
  Delay_1u(100);
  WS_DATA_H;    //SDA����
  Delay_1u(100);
  WS_SCK_L;    //SCL��ͣ��������ʱ��
}
/*******************************************************************************
��λ��ʪ�ȴ�����
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
�����λ��ʪ�ȴ�����
*******************************************************************************/ 
int8u s_softreset(void)
{ 
  int8u error2=0;  
  s_connectionreset();              //reset communication
  error2+=s_write_byte(RESET);       //send RESET-command to sensor
  return error2;                     //error=1 in case of no response form the sensor
}
/*******************************************************************************
��ȡ��ʪ�ȴ�������״̬�Ĵ���
������������ڴ洢��ȡ���ݵ�ָ�룬���ڴ洢У�����ָ��
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
д��ʪ�ȴ����������üĴ���
���������ָ��ȴ�д������ݵ�ָ��
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
������ʪ�ȴ�������ת�����ܲ��洢ת����õ�������
������������ڴ洢У�����ָ�룬ָ��ת���¶Ȼ�ʪ�ȵ�ָ��ֵ
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
      for (i=0;i<65535;i++)//��ת���ڼ䣬�ź��߱�����Ϊ�ߵ�ƽ
      { 
        Delay_1u(100);
        halResetWatchdog();   // Periodically reset the watchdog.�����Ե��������Ź�
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
        halResetWatchdog();   // Periodically reset the watchdog.�����Ե��������Ź�
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
�Եõ����¶����ݺ��ʶ����ݽ���У��
���������ָ��洢�¶����ݺ�ʪ�����ݵ�ָ��
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

t_C=t*0.01 - 39.62;                  //�����ʵ�ʵ��¶�ֵ
rh_lin=C3*rh*rh + C2*rh + C1;     //�����ʵ�ʵ�ʪ����ֵ [%RH]
rh_true=(t_C-25)*(T1+T2*rh)+rh_lin;   //��ʪ����ֵ�����¶Ȳ��� [%RH]
if(rh_true>100)rh_true=100;       //cut if the value is outside of
if(rh_true<0.1)rh_true=0.1;       //the physical possible range
*p_temperature=t_C;               //�����¶�
*p_humidity=rh_true;              //����ʪ��[%RH]
}
/*******************************************************************************
�����¶Ⱥ�ʪ�����ݼ���¶��
����������¶�ֵ��ʪ��ֵ
*******************************************************************************/ 
float calc_dewpoint(float h,float t)
{ float logEx,dew_point;
logEx=0.66077+7.5*t/(237.3+t)+(log10(h)-2);
dew_point = (logEx - 0.66077)*237.3/(0.66077+7.5-logEx);
return dew_point;
}
/*******************************************************************************
�����¶Ⱥ�ʪ��ת�������õ�������ֵ
// 1. ���ȸ�λ���Ӳ���������
// 2. �����¶Ⱥ�ʪ��ת��
// 3. У��ʪ�� [%RH] ���¶� 
// 4. ����¶��
// 5. �Ӵ�������¶ȡ�ʪ�ȡ�¶��ֵ
*******************************************************************************/ 
void calc_sth10_resault(int16s * TempValue, int16u * HumiValue)
{ 
  float dew_point;//¶��
  int8u checksum;
  
  s_connectionreset();
  error=0;
  error+=s_measure(&checksum,HUMI);  //measure humidity
  error+=s_measure(&checksum,TEMP);  //measure temperature
  
  if(error!=0) s_connectionreset();                 //in case of an error: connection reset
  else
  {	 
    humi_val_f=(float)humi_val_i;                   //����ת��Ϊfloat
    temp_val_f=(float)temp_val_i;                   //����ת��Ϊfloat
    calc_sth11(&humi_val_f,&temp_val_f);            //����ʪ�ȣ��¶�
    dew_point=calc_dewpoint(humi_val_f,temp_val_f); //����¶��
    *TempValue = (int)(temp_val_f*100);
    *HumiValue = (int)(humi_val_f*100);
    emberSerialPrintf(APP_SERIAL,"temp: %d �� �� humi:%d %% RH�� dew point: %d ��\n",(int)temp_val_f,(int)humi_val_f,(int)dew_point);		
  }
}

/*
void result2string(float *p_humidity ,float *p_temperature)
{
//    humiString[4],tempString[5];
int tempX10,humiX10;
if(*p_temperature < 0)
{
tempString[0] = 1;//��ʾ�¶�Ϊ��
  }
  else
{
tempString[0] = 0;//��ʾ�¶�Ϊ��
  }
tempX10 = (int)fabs(*p_temperature) * 10;
tempString[1] = tempX10 / 100 ;//��ʾ�¶�Ϊ��
tempString[1] = tempX10 / 100 ;//��ʾ�¶�Ϊ��
tempString[1] = tempX10 / 100 ;//��ʾ�¶�Ϊ��

}

*/