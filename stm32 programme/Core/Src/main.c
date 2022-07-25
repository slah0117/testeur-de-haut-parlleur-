/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_host.h"
#include "i2c-lcd.h"
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
uint8_t data[] = "61940024";

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
 ADC_HandleTypeDef hadc1;

I2C_HandleTypeDef hi2c2;

UART_HandleTypeDef huart2;
UART_HandleTypeDef huart6;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART6_UART_Init(void);
static void MX_I2C2_Init(void);
static void MX_ADC1_Init(void);
void MX_USB_HOST_Process(void);

/* USER CODE BEGIN PFP */
#include "usbh_hid.h"
static int32_t uart_length=0;
int k =0 ;
const int sampleWindow = 100;                              // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
unsigned long  startMillis;
unsigned longstartMillis ;                  // Start of sample window
float peakToPeak = 0;                                  // peak-to-peak level
unsigned int signalMax = 0;                            //minimum value
unsigned int signalMin = 1024;
int db = 0;
double raw_value;
char msg[20]="";
uint16_t raw;
double Reavoltage;

const int SAMPLE_TIME = 10;
 unsigned long millisCurrent;
 unsigned long millisLast = 0;
 unsigned long millisElapsed = 0;
 int sampleBufferValue = 0;
int c=0;
 int num_Measure = 128 ; // Set the number of measurements
 // pin connected to pin O module sound sensor
 int redLed = 5;
 long Sound_signal;    // Store the value read Sound Sensor
 long sum = 0 ; // Store the total value of n measurements
int level = 0 ; // Store the average value
 int soundlow = 40;
 int soundmedium = 500;

bool teste ;
 char  uart_tx_buffer[100];
char buffer1[100];
char buffer2[100];
char rx_buffer[100];
uint8_t data2[100] ;
char rx_buffer2[100];
char rx_buffer4[100];
char rx_buffer5[100];
char rx_buffer6[100];
char rx_buffer7[100];
char rx_buffer11[100];
char buffer5[100]="a/";
char buffer6[100]="/1";
uint8_t data3[] = " \r\n slahO WORLD \r\n";
uint8_t data4[] = " \r\n slah5 WORLD \r\n";
char position[100]="0";
uint8_t str[100];
uint8_t ch[100];
uint8_t keycode;
char str1[]="01XY";
int i =0  ;
float val = 0;
int toggle = 0;
extern HID_MOUSE_Info_TypeDef mouse_info;
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
bool startsWith(const char *haystack, const char *needle) {
    for (size_t i = 0; needle[i] != '\0'; i++) {
        if (haystack[i] != needle[i]) {
            return false;
        }
    }

    return true;
}

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}




//(startsWith(buffer1, "5")==true)



void USBH_HID_EventCallback(USBH_HandleTypeDef *phost)
{
HID_KEYBD_Info_TypeDef *keybd_info;

HID_HandleTypeDef *HID_Handle = (HID_HandleTypeDef *) phost->pActiveClass->pData;
if(HID_Handle->Init == USBH_HID_KeybdInit){
keybd_info = USBH_HID_GetKeybdInfo(phost);
keycode = USBH_HID_GetASCIICode(keybd_info);
uart_length=sprintf(uart_tx_buffer,"%c",keycode);
strcat(buffer1,uart_tx_buffer);
}}






/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_USB_HOST_Init();
  MX_USART6_UART_Init();
  MX_I2C2_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
  lcd_init ();
  lcd_send_string ("sagemcom");

  HAL_Delay(1000);
  lcd_clear ();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    MX_USB_HOST_Process();

    if(strcmp(uart_tx_buffer,"Y")== 0){
    	if((startsWith(buffer1, "0")==true)){
    		if(strcmp(buffer1,"00000001XY")== 0){


    			HAL_UART_Transmit(&huart2,(uint8_t*)"position 1  \r\n",sizeof ("position 1  \r\n"), 1000);
    			lcd_put_cur(0, 0);
    			lcd_send_string("position 1");
    			lcd_put_cur(1, 0);
    			lcd_send_string(buffer1);
    			HAL_Delay(1000);
    			strncpy(position, "machine1", sizeof(position));
    			strncpy(buffer1, "", sizeof(buffer1));
    			i=1;
            									}

            if (strcmp(buffer1,"00000002XY")== 0){
            	 HAL_UART_Transmit(&huart2,(uint8_t*)"position 2  \r\n",sizeof ("position 2  \r\n"), 1000);
            	 lcd_put_cur(0, 0);
            	 lcd_send_string("position 2");
            	 lcd_put_cur(1, 0);
            	 lcd_send_string(buffer1);
            	 HAL_Delay(1000);

            	 strncpy(position, "machine2", sizeof(position));


            	 strncpy(buffer1, "", sizeof(buffer1));
            	 i=2;
            									}
           	   	   	   	   	   	   	   	   }




    	if (strcmp(buffer1,"")!= 0)
                       	   	   	   {
    			char buffer5[100]="/a/";
    			char buffer8[100]="/a/";
    			char buffer10[100]="/a/";
    			char buffer6[100]="/teste1";
    			char buffer7[100]="/teste2/validation";
    			char buffer4[100]="/teste2/position";
    			strcat(buffer5,buffer1);
    			strcat(buffer5,buffer6);
    			strcat(buffer8,buffer1);
    			strcat(buffer8,buffer7);
    			strcat(buffer10,buffer1);
    			strcat(buffer10,buffer4);
    			HAL_UART_Transmit(&huart2,(uint8_t*)buffer5,sizeof(buffer5),1000);
    			HAL_UART_Transmit(&huart6,(uint8_t*)buffer5,sizeof(buffer5), 3000);
    			HAL_UART_Receive(&huart6,(uint8_t*)rx_buffer,20,3000);
    			while (strcmp(rx_buffer,"")== 0 ){
    				HAL_UART_Receive(&huart6,(uint8_t*)rx_buffer,5,3000);
    				HAL_Delay(50);

    											}



    			HAL_UART_Transmit(&huart2,(uint8_t*)rx_buffer,sizeof(rx_buffer),1000);
    			HAL_UART_Transmit(&huart2,(uint8_t*)"\r\n",sizeof("\r\n"),1000);
    			lcd_clear ();
    			lcd_put_cur(0, 0);
    			lcd_send_string(rx_buffer);
            	lcd_put_cur(1, 0);
            	lcd_send_string(buffer1);
            	HAL_Delay(2000);
            	lcd_clear ();
            	if ((startsWith(rx_buffer, "e")==true )){

            	        		lcd_send_string("l'article nexis-");


            	        		lcd_put_cur(1, 0);
            	        		lcd_send_string("te pas dans la DB");
            	        		HAL_Delay(2000);

            	        }
            	if ((startsWith(rx_buffer, "f")==true )){

            	        	        		lcd_send_string("le teste precident");


            	        	        		lcd_put_cur(1, 0);
            	        	        		lcd_send_string("n'est pas valide");
            	        	        		HAL_Delay(2000);

            	        	        }
            	if ((startsWith(rx_buffer, "t")==true ) && ( i==0 )){
            		HAL_UART_Transmit(&huart6,(uint8_t*)"555",sizeof ("555"), 3000);
            		lcd_put_cur(0, 0);
            		lcd_send_string("teste");
            		HAL_UART_Receive(&huart6,(uint8_t*)rx_buffer2,3,3000);
            		HAL_UART_Transmit(&huart2,(uint8_t*)rx_buffer2,sizeof(rx_buffer2),1000);
            		lcd_clear ();
            		lcd_put_cur(0, 0);
            		lcd_send_string(rx_buffer2);
            		lcd_put_cur(1, 0);
            		lcd_send_string(buffer1);
            		HAL_Delay(2000);


            }





            if ((startsWith(rx_buffer, "t")==true ) && ( i==1 )){
            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 1);
            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, 1);

            	lcd_clear ();
            	 lcd_put_cur(0, 0);
            	            lcd_send_string("validation?");
            	            lcd_put_cur(1, 0);
            	            lcd_send_string(buffer1);
            	            HAL_Delay(1000);
            	            lcd_clear ();
            //	while ((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2)== 0) &&  (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)== 0)     ){


          //  }
 while (( db < 90) )
 {
HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1);
HAL_Delay(500);

float peakToPeak = 0;                                  // peak-to-peak level

unsigned int signalMax = 0;                            //minimum value
unsigned int signalMin = 1024;
unsigned long startMillis=HAL_GetTick();
 while (((HAL_GetTick() - startMillis) < sampleWindow))
{
HAL_ADC_Start(&hadc1);
HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
sample  = HAL_ADC_GetValue(&hadc1 ) ;
HAL_ADC_Stop(&hadc1);

            	                                         //get reading from microphone
 if (sample < 1024)                                  // toss out spurious readings
 {
if (sample > signalMax)
{
signalMax = sample;                           // save just the max levels
 }
else if (sample < signalMin)
{
signalMin = sample;                           // save just the min levels
}
}
}


 peakToPeak = signalMax - signalMin;                    // max - min = peak-peak amplitude
db = map(peakToPeak,20,900,49.5,90);   //(long x, long in_min, long in_max, long out_min, long out_max)
lcd_clear ();
lcd_put_cur(0,0);
lcd_send_string ("bd = ");
lcd_put_cur(0,4);
k++;

if (db <= 80)
{
sprintf ( msg , "%hu\r\n " , db ) ;
lcd_put_cur(0,4);
lcd_send_string (msg);


if (k>=20)
{ teste = false ;
break;
}


}


else
{  sprintf ( msg , "%hu\r\n " , db ) ;

lcd_put_cur(0,4);
lcd_send_string (msg);
 teste = true;
break;
 }

HAL_Delay(100);
 }
if (teste==true){
lcd_clear ();
lcd_put_cur(0,0);
lcd_send_string ("bd = ");
lcd_put_cur(0,4);
lcd_send_string (msg);
lcd_put_cur(1,0);
lcd_send_string ("teste valide");
 HAL_Delay(500);
 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0);

}

else if (teste==false ){
lcd_clear ();
lcd_put_cur(0,0);
lcd_send_string ("bd = ");
lcd_put_cur(0,4);
lcd_send_string (msg);
lcd_put_cur(1,0);
lcd_send_string ("teste non valide");
HAL_Delay(500);
 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0);

 }

            if(teste==true)
            {
            lcd_clear ();
            HAL_UART_Transmit(&huart6,(uint8_t*)"ook",sizeof ("ook"), 3000);
            lcd_put_cur(0, 0);
            lcd_send_string("oui");
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, 0);


             HAL_UART_Receive(&huart6,(uint8_t*)rx_buffer2,3,3000);

            HAL_UART_Transmit(&huart2,(uint8_t*)rx_buffer2,sizeof(rx_buffer2),1000);
            lcd_clear ();
            lcd_put_cur(0, 0);
            lcd_send_string(rx_buffer2);
            HAL_Delay(2000);



            HAL_UART_Transmit(&huart2,(uint8_t*)buffer8,sizeof(buffer8),1000);
            HAL_UART_Transmit(&huart6,(uint8_t*)buffer8,sizeof(buffer8),3000);
            HAL_UART_Receive(&huart6,(uint8_t*)rx_buffer4,3,3000);

            HAL_UART_Transmit(&huart2,(uint8_t*)rx_buffer4,sizeof(rx_buffer4),1000);
            lcd_clear ();
            lcd_put_cur(0, 0);
            lcd_send_string(rx_buffer4);
            HAL_UART_Receive(&huart6,(uint8_t*)rx_buffer5,3,3000);

            HAL_UART_Transmit(&huart2,(uint8_t*)rx_buffer5,sizeof(rx_buffer5),1000);
            lcd_clear ();
            lcd_put_cur(0, 0);
            lcd_send_string(rx_buffer5);
            HAL_UART_Transmit(&huart6,(uint8_t*)buffer10,sizeof (buffer10), 3000);
            HAL_UART_Receive(&huart6,(uint8_t*)rx_buffer6,3,3000);

            HAL_UART_Transmit(&huart2,(uint8_t*)rx_buffer6,sizeof(rx_buffer6),1000);

            lcd_clear ();
            lcd_put_cur(0, 0);
            lcd_send_string(rx_buffer6);
            HAL_Delay(2000);
            HAL_UART_Transmit(&huart6,(uint8_t*)position,sizeof (position), 3000);

            HAL_UART_Receive(&huart6,(uint8_t*)rx_buffer7,6,3000);
            HAL_UART_Transmit(&huart2,(uint8_t*)"coooo",sizeof("coooo"),1000);
                   HAL_UART_Transmit(&huart2,(uint8_t*)rx_buffer7,sizeof(rx_buffer7),1000);
            HAL_UART_Receive(&huart6,(uint8_t*)rx_buffer11,3,3000);





            lcd_clear ();
            lcd_put_cur(0, 0);
            lcd_send_string(rx_buffer7);
            lcd_put_cur(1, 0);
            lcd_send_string("BD update ");





            }






            if(teste==false)
            {

            lcd_clear ();

            HAL_UART_Transmit(&huart6,(uint8_t*)"non",sizeof ("non"), 3000);
            lcd_put_cur(0, 0);
            lcd_send_string("non");
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, 0);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, 0);


            HAL_UART_Receive(&huart6,(uint8_t*)rx_buffer2,3,3000);

            HAL_UART_Transmit(&huart2,(uint8_t*)rx_buffer2,sizeof(rx_buffer2),1000);
            lcd_clear ();
            lcd_put_cur(0, 0);
            lcd_send_string(rx_buffer2);
            HAL_Delay(2000);



            HAL_UART_Transmit(&huart2,(uint8_t*)buffer8,sizeof(buffer8),1000);
            HAL_UART_Transmit(&huart6,(uint8_t*)buffer8,sizeof(buffer8),3000);
            HAL_UART_Receive(&huart6,(uint8_t*)rx_buffer4,3,3000);

            HAL_UART_Transmit(&huart2,(uint8_t*)rx_buffer4,sizeof(rx_buffer4),1000);
            lcd_clear ();
            lcd_put_cur(0, 0);
            lcd_send_string(rx_buffer4);
            HAL_UART_Receive(&huart6,(uint8_t*)rx_buffer5,3,3000);

            HAL_UART_Transmit(&huart2,(uint8_t*)rx_buffer5,sizeof(rx_buffer5),1000);
            lcd_clear ();
            lcd_put_cur(0, 0);
            lcd_send_string(rx_buffer5);
            HAL_UART_Transmit(&huart6,(uint8_t*)buffer10,sizeof (buffer10), 3000);
            HAL_UART_Receive(&huart6,(uint8_t*)rx_buffer6,3,3000);

            HAL_UART_Transmit(&huart2,(uint8_t*)rx_buffer6,sizeof(rx_buffer6),1000);
            lcd_clear ();
            lcd_put_cur(0, 0);
            lcd_send_string(rx_buffer6);
            HAL_Delay(2000);

            HAL_UART_Transmit(&huart6,(uint8_t*)position,sizeof (position), 3000);

                   HAL_UART_Receive(&huart6,(uint8_t*)rx_buffer7,6,3000);
                   HAL_UART_Transmit(&huart2,(uint8_t*)"coooo",sizeof("coooo"),1000);
                          HAL_UART_Transmit(&huart2,(uint8_t*)rx_buffer7,sizeof(rx_buffer7),1000);
                   HAL_UART_Receive(&huart6,(uint8_t*)rx_buffer11,3,3000);

            lcd_clear ();
            lcd_put_cur(0, 0);
            lcd_send_string(rx_buffer7);
            lcd_put_cur(1, 0);
            lcd_send_string("BD update ");

            }

            }


            if ((startsWith(rx_buffer, "t")==true ) && ( i==2 )){
            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 1);
            	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 1);

            	lcd_clear ();

          //  	while ((HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2)== 0) &&  (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)== 0)     ){

            lcd_put_cur(0, 0);
            lcd_send_string("validation?");
            lcd_put_cur(1, 0);
                    lcd_send_string(buffer1);
                    HAL_Delay(500);
                    lcd_clear ();
         //   }
                    while (( db < 90) )
                    {
                   HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 1);
                   HAL_Delay(500);

                   float peakToPeak = 0;                                  // peak-to-peak level

                   unsigned int signalMax = 0;                            //minimum value
                   unsigned int signalMin = 1024;
                   unsigned long startMillis=HAL_GetTick();
                    while (((HAL_GetTick() - startMillis) < sampleWindow))
                   {
                   HAL_ADC_Start(&hadc1);
                   HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
                   sample  = HAL_ADC_GetValue(&hadc1 ) ;
                   HAL_ADC_Stop(&hadc1);

                               	                                         //get reading from microphone
                    if (sample < 1024)                                  // toss out spurious readings
                    {
                   if (sample > signalMax)
                   {
                   signalMax = sample;                           // save just the max levels
                    }
                   else if (sample < signalMin)
                   {
                   signalMin = sample;                           // save just the min levels
                   }
                   }
                   }


                    peakToPeak = signalMax - signalMin;                    // max - min = peak-peak amplitude
                   db = map(peakToPeak,20,900,49.5,90);   //(long x, long in_min, long in_max, long out_min, long out_max)
                   lcd_clear ();
                   lcd_put_cur(0,0);
                   lcd_send_string ("bd = ");
                   lcd_put_cur(0,4);
                   k++;

                   if (db <= 80)
                   {
                   sprintf ( msg , "%hu\r\n " , db ) ;
                   lcd_put_cur(0,4);
                   lcd_send_string (msg);


                   if (k>=20)
                   { teste = false ;
                   break;
                   }


                   }


                   else
                   {  sprintf ( msg , "%hu\r\n " , db ) ;

                   lcd_put_cur(0,4);
                   lcd_send_string (msg);
                    teste = true;
                   break;
                    }

                   HAL_Delay(100);
                    }
                   if (teste==true){
                   lcd_clear ();
                   lcd_put_cur(0,0);
                   lcd_send_string ("bd = ");
                   lcd_put_cur(0,4);
                   lcd_send_string (msg);
                   lcd_put_cur(1,0);
                   lcd_send_string ("teste valide");
                    HAL_Delay(500);
                    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0);

                   }

                   else if (teste==false ){
                   lcd_clear ();
                   lcd_put_cur(0,0);
                   lcd_send_string ("bd = ");
                   lcd_put_cur(0,4);
                   lcd_send_string (msg);
                   lcd_put_cur(1,0);
                   lcd_send_string ("teste non valide");
                   HAL_Delay(500);
                    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, 0);

                    }



            if(teste==true)
            {
            lcd_clear ();
            HAL_UART_Transmit(&huart6,(uint8_t*)"ook",sizeof ("ook"), 3000);
            lcd_put_cur(0, 0);
            lcd_send_string("oui");
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 0);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 0);


             HAL_UART_Receive(&huart6,(uint8_t*)rx_buffer2,3,3000);

            HAL_UART_Transmit(&huart2,(uint8_t*)rx_buffer2,sizeof(rx_buffer2),1000);
            lcd_clear ();
            lcd_put_cur(0, 0);
            lcd_send_string(rx_buffer2);
            HAL_Delay(2000);



            HAL_UART_Transmit(&huart2,(uint8_t*)buffer8,sizeof(buffer8),1000);
            HAL_UART_Transmit(&huart6,(uint8_t*)buffer8,sizeof(buffer8),3000);
            HAL_UART_Receive(&huart6,(uint8_t*)rx_buffer4,3,3000);

            HAL_UART_Transmit(&huart2,(uint8_t*)rx_buffer4,sizeof(rx_buffer4),1000);
            lcd_clear ();
            lcd_put_cur(0, 0);
            lcd_send_string(rx_buffer4);
            HAL_UART_Receive(&huart6,(uint8_t*)rx_buffer5,3,3000);

            HAL_UART_Transmit(&huart2,(uint8_t*)rx_buffer5,sizeof(rx_buffer5),1000);
            lcd_clear ();
            lcd_put_cur(0, 0);
            lcd_send_string(rx_buffer5);
            HAL_UART_Transmit(&huart6,(uint8_t*)buffer10,sizeof (buffer10), 3000);
            HAL_UART_Receive(&huart6,(uint8_t*)rx_buffer6,3,3000);

            HAL_UART_Transmit(&huart2,(uint8_t*)rx_buffer6,sizeof(rx_buffer6),1000);
            lcd_clear ();
            lcd_put_cur(0, 0);
            lcd_send_string(rx_buffer6);
            HAL_Delay(2000);
            HAL_UART_Transmit(&huart6,(uint8_t*)position,sizeof (position), 3000);

                   HAL_UART_Receive(&huart6,(uint8_t*)rx_buffer7,6,3000);
                   HAL_UART_Transmit(&huart2,(uint8_t*)"coooo",sizeof("coooo"),1000);
                          HAL_UART_Transmit(&huart2,(uint8_t*)rx_buffer7,sizeof(rx_buffer7),1000);
                   HAL_UART_Receive(&huart6,(uint8_t*)rx_buffer11,3,3000);

            lcd_clear ();
            lcd_put_cur(0, 0);
            lcd_send_string(rx_buffer7);
            lcd_put_cur(1, 0);
            lcd_send_string("BD update ");




            }






            if(teste==false)
            {

            lcd_clear ();

            HAL_UART_Transmit(&huart6,(uint8_t*)"non",sizeof ("non"), 3000);
            lcd_put_cur(0, 0);
            lcd_send_string("non");
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 0);
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 0);


            HAL_UART_Receive(&huart6,(uint8_t*)rx_buffer2,3,3000);

            HAL_UART_Transmit(&huart2,(uint8_t*)rx_buffer2,sizeof(rx_buffer2),1000);
            lcd_clear ();
            lcd_put_cur(0, 0);
            lcd_send_string(rx_buffer2);
            HAL_Delay(2000);



            HAL_UART_Transmit(&huart2,(uint8_t*)buffer8,sizeof(buffer8),1000);
            HAL_UART_Transmit(&huart6,(uint8_t*)buffer8,sizeof(buffer8),3000);
            HAL_UART_Receive(&huart6,(uint8_t*)rx_buffer4,3,3000);

            HAL_UART_Transmit(&huart2,(uint8_t*)rx_buffer4,sizeof(rx_buffer4),1000);
            lcd_clear ();
            lcd_put_cur(0, 0);
            lcd_send_string(rx_buffer4);
            HAL_UART_Receive(&huart6,(uint8_t*)rx_buffer5,3,3000);

            HAL_UART_Transmit(&huart2,(uint8_t*)rx_buffer5,sizeof(rx_buffer5),1000);
            lcd_clear ();
            lcd_put_cur(0, 0);
            lcd_send_string(rx_buffer5);
            HAL_UART_Transmit(&huart6,(uint8_t*)buffer10,sizeof (buffer10), 3000);
            HAL_UART_Receive(&huart6,(uint8_t*)rx_buffer6,3,3000);

            HAL_UART_Transmit(&huart2,(uint8_t*)rx_buffer6,sizeof(rx_buffer6),1000);
            lcd_clear ();
            lcd_put_cur(0, 0);
            lcd_send_string(rx_buffer6);
            HAL_Delay(2000);
            HAL_UART_Transmit(&huart6,(uint8_t*)position,sizeof (position), 3000);

                   HAL_UART_Receive(&huart6,(uint8_t*)rx_buffer7,6,3000);
                   HAL_UART_Transmit(&huart2,(uint8_t*)"coooo",sizeof("coooo"),1000);
                          HAL_UART_Transmit(&huart2,(uint8_t*)rx_buffer7,sizeof(rx_buffer7),1000);
                   HAL_UART_Receive(&huart6,(uint8_t*)rx_buffer11,3,3000);

            lcd_clear ();
            lcd_put_cur(0, 0);
            lcd_send_string(rx_buffer7);
            lcd_put_cur(1, 0);
            lcd_send_string("BD update ");

            }

            }

        strncpy(position, "", sizeof(position));
        strncpy(rx_buffer, "", sizeof(rx_buffer));
        strncpy(rx_buffer, "", sizeof(rx_buffer));
        strncpy(rx_buffer2, "", sizeof(rx_buffer2));
        strncpy(rx_buffer5, "", sizeof(rx_buffer5));
        strncpy(rx_buffer4, "", sizeof(rx_buffer4));
        strncpy(rx_buffer6, "", sizeof(rx_buffer6));
        strncpy(rx_buffer7, "", sizeof(rx_buffer7));
        strncpy(rx_buffer11, "", sizeof(rx_buffer11));
        strncpy(uart_tx_buffer, "", sizeof(uart_tx_buffer));
        strncpy(buffer8, "", sizeof(buffer8));
        strncpy(buffer7, "", sizeof(buffer7));
        strncpy(uart_tx_buffer, "", sizeof(uart_tx_buffer));
        strncpy(buffer1, "", sizeof(buffer1));
        strncpy(buffer5, "", sizeof(buffer5));
        strncpy(buffer6, "", sizeof(buffer6));
        strncpy(rx_buffer, "", sizeof(rx_buffer));
        strncpy(buffer8, "", sizeof(buffer8));
        strncpy(buffer7, "", sizeof(buffer7));
        strncpy(buffer4, "", sizeof(buffer4));
        strncpy(buffer10, "", sizeof(buffer10));
    i=0;





        }
        }


    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.ClockSpeed = 100000;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART6_UART_Init(void)
{

  /* USER CODE BEGIN USART6_Init 0 */

  /* USER CODE END USART6_Init 0 */

  /* USER CODE BEGIN USART6_Init 1 */

  /* USER CODE END USART6_Init 1 */
  huart6.Instance = USART6;
  huart6.Init.BaudRate = 115200;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART6_Init 2 */

  /* USER CODE END USART6_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5|GPIO_PIN_10, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15
                          |GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA5 PA10 */
  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB1 PB2 PB4 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB12 PB13 PB14 PB15
                           PB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15
                          |GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
