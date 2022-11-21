/*============================================================
LPC1768 ѧϰ�� IAP������ʾ
����: Mingtree	ycxms88@163.com   http://www.mcu123.com
==============================================================
*/


#include "iap.h"
#include "rtc.h"

#define IAP_LOCATION 0x7FFFFFF1 // IAP ������� ��1��
typedef void (*IAP) (unsigned int [ ] , unsigned int [ ]); // ���庯������ָ��




/*����CCLK ֵ��С����λΪKHz*/
#define IAP_FCCLK 96000
#define IAP_ENTER_ADR 0x1FFF1FF1 // IAP ��ڵ�ַ����
uint32 paramin[8]; // IAP ��ڲ���������
uint32 paramout[8]; // IAP ���ڲ���������
 uint8  buf_Read[512];


#define IAP_SELECTOR  50
#define IAP_RAMTOFLASH	51
#define IAP_ERASESECTOR	52
#define IAP_BLANKCHECKSECTOR 53
#define READPARTID 54
#define READBOOTCODEVERSION 55
#define IAP_COMPARE 56
			                                                  
extern __align(4) uint8 Parameter[ParameterNumMax];
extern __align(4) uint8 ParameterBak[ParameterInitNumMax];
/******************************************************************************************
** �������ƣ� SelSector
** �������ܣ� IAP ����������ѡ�񣬴���Ϊ50��
** ��ڲ����� sec1 ��ʼ����
** sec2 ��ֹ����
** ���ڲ����� IAP ����״̬��
** IAP ����ֵ��paramout ��������
******************************************************************************************/
uint32 SelSector(uint8 sec1,uint8 sec2)
{
paramin[0] = IAP_SELECTOR; // ����������
paramin[1] = sec1; // ���ò���
paramin[2] = sec2;
(*(void(*)())IAP_ENTER_ADR)(paramin,paramout); // ����IAP �������
return(paramout[0]); // ����״̬��
}

/******************************************************************************************
** �������ƣ� EraseSector
** �������ܣ� �����������������52��
** ��ڲ����� sec1 ��ʼ����
** sec2 ��ֹ����
** ���ڲ����� IAP ����״̬��
** IAP ����ֵ��paramout ��������
******************************************************************************************/
uint32 EraseSector(uint32 sec1,uint32 sec2)
{
paramin[0] = IAP_ERASESECTOR; // ����������
paramin[1] = sec1; // ���ò���
paramin[2] = sec2;
paramin[3] = IAP_FCCLK;
(*(void(*)())IAP_ENTER_ADR)(paramin,paramout); // ����IAP �������
return(paramout[0]); // ����״̬��
}

/******************************************************************************************
** �������ƣ� RamToFlash
** �������ܣ� ����RAM �����ݵ�FLASH���������51��
** ��ڲ����� dst Ŀ���ַ����FLASH ��ʼ��ַ����256 �ֽ�Ϊ�ֽ�
** src Դ��ַ����RAM ��ַ����ַ�����ֶ���
** no �����ֽڸ�����Ϊ256/512/1024/4096
** ���ڲ����� IAP ����״̬��
** IAP ����ֵ��paramout ��������
******************************************************************************************/
uint32 RamToFlash(uint32 dst, uint32 src, uint32 no)
{
paramin[0] = IAP_RAMTOFLASH; //����������
paramin[1] = dst; //���ò���
paramin[2] = src;
paramin[3] = no;
paramin[4] = IAP_FCCLK;
(*(void(*)())IAP_ENTER_ADR)(paramin,paramout); //����IAP �������
return(paramout[0]); //����״̬��
}

/******************************************************************************************
** �������ƣ� Compare
** �������ܣ� У�����ݣ��������56��
** ��ڲ����� dst Ŀ���ַ����RAM/FLASH ��ʼ��ַ����ַ�����ֶ���
** src Դ��ַ����RAM/RAM ��ַ����ַ�����ֶ���
** no �Ƚ��ֽڸ����������ܱ�4 ����
** ���ڲ����� IAP ����״̬��
** IAP ����ֵ��paramout ��������
******************************************************************************************/
uint32 Compare(uint32 dst, uint32 src, uint32 no)
{
paramin[0] = IAP_COMPARE; // ����������
paramin[1] = dst; // ���ò���
paramin[2] = src;
paramin[3] = no;
(*(void(*)())IAP_ENTER_ADR)(paramin,paramout); // ����IAP �������
return(paramout[0]); // ����״̬��
}

#define DestAddr 0x00078000 // ����29����ʼ��ַ
#define DestAddr1 0x00070000 // ����28����ʼ��ַ  TT
#define DestAddr2 0x00068000 //����27����ʼ��ַ

/*void read_sec(void)
{
 uint32 i;
 volatile int8 *wr_ptr; 
 wr_ptr = (volatile int8 *)DestAddr;
 for ( i= 0; i < ParameterInitNumMax; i++ ){main_parameterbak[i]=*wr_ptr++ ;}
}*/
