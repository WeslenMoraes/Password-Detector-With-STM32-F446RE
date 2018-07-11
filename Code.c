/* Includes */
#include "stm32f4xx.h"
#define cathode_0                    ((uint32_t)0x03fc)
#define cathode_1                    ((uint32_t)0X0060)
#define cathode_2                    ((uint32_t)0X05b0)
#define cathode_3                    ((uint32_t)0X04f0)
#define cathode_4                    ((uint32_t)0X0660)
#define cathode_5                    ((uint32_t)0X06d0)
#define cathode_6                    ((uint32_t)0X07d0)
#define cathode_7                    ((uint32_t)0X0070)
#define cathode_8                    ((uint32_t)0X07fc)
#define cathode_9                    ((uint32_t)0X06f0)
#define cathode_A                    ((uint32_t)0X0770)
#define cathode_b                    ((uint32_t)0X07c0)
#define cathode_C                    ((uint32_t)0X0390)
#define cathode_d                    ((uint32_t)0X05e0)
#define cathode_E                    ((uint32_t)0X07b0)
#define cathode_F                    ((uint32_t)0X0710)

/**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/

int main(void)
{
	RCC->AHB1ENR=0X00000087;// Habilitar clocks dos GPIOs
	GPIOA->MODER|=0x00155505;//habilita os pinos como saídas digitais
	GPIOC->MODER&=0xfffc00ff;//habilita os pinos como entradas digitais
	int swValue;
	int btn;
	int lastBtn;
	int btnT;
	int verify;
	int estado=0;
	long int i;
  /* Infinite loop */
  while (1)
  {
	  btn=GPIOC->IDR;
	  btn&=0x0080;
	  btnT=btn&&!lastBtn;
	  lastBtn=btn;
	  swValue=GPIOC->IDR;
	  swValue&=0x0170;
	  if(swValue==0x0000)//chave em "0000", 0
		  GPIOA->ODR=cathode_0;
	  else if(swValue==0x0100)//chave em "0001", 1
	  	  GPIOA->ODR=cathode_1;
	  else if(swValue==0x0040)//chave em "0010", 2
	  	  GPIOA->ODR=cathode_2;
	  else if(swValue==0x0140)//chave em "0011", 3
	  	  GPIOA->ODR=cathode_3;
	  else if(swValue==0x0020)//chave em "0100", 4
	  	  GPIOA->ODR=cathode_4;
	  else if(swValue==0x0120)//chave em "0101", 5
	  	  GPIOA->ODR=cathode_5;
	  else if(swValue==0x0060)//chave em "0110", 6
	  	  GPIOA->ODR=cathode_6;
	  else if(swValue==0x0160)//chave em "0111", 7
	  	  GPIOA->ODR=cathode_7;
	  else if(swValue==0x0010)//chave em "1000", 8
		  GPIOA->ODR=cathode_8;
	  else if(swValue==0x0110)//chave em "1001", 9
	  	  GPIOA->ODR=cathode_9;
	  else if(swValue==0x0050)//chave em "1010", A
	  	  GPIOA->ODR=cathode_A;
	  else if(swValue==0x0150)//chave em "1011", b
	  	  GPIOA->ODR=cathode_b;
	  else if(swValue==0x0030)//chave em "1100", C
	  	  GPIOA->ODR=cathode_C;
	  else if(swValue==0x0130)//chave em "1101", d
	  	  GPIOA->ODR=cathode_d;
	  else if(swValue==0x0070)//chave em "1110", E
	  	  GPIOA->ODR=cathode_E;
	  else if(swValue==0x0170)//chave em "1111", F
	  	  GPIOA->ODR=cathode_F;
	  else
		  GPIOA->ODR=0X000;

	  verify=GPIOA->ODR;
/*    --------------------
	         ESTADOS
	  --------------------*/
	  switch(estado)
	  {
	  case 0:
		  if(btnT&&(verify==cathode_1)){
		  	  estado=2;
		      btnT=0;
		  }
		  else if(btnT){
			  estado=1;
	          btnT=0;
		  }
	  break;
	  case 1:
		  if(btnT)
			  estado=8;
	  break;
	  case  2:
		  if(btnT&&(verify==cathode_2))
			  estado=9;
	  break;
	  case 8:
		  GPIOA->ODR=0x0002;
	  break;
	  case 9:
		  GPIOA->ODR=0x0001;
	  break;
	  }
	  for(i=0;i<100000;i++);
}}
