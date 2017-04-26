//    "With small keypad" 
#include "TM4C123GH6PM.h"
#include "servo.h"
#include "lcd.h"
#include "delay.h"
#include "spi.h"
#include "keypad.h"
#include "uart_5.h"
#include "timer.h"
#include <string.h>
#define LED_RED     (1U<<1)
#define LED_BLUE     (1U<<2)
#define LED_GREEN     (1U<<3)
uint8_t  buff ;
uint8_t  buff1 ;
uint8_t  password[8];
uint16_t i=0;
uint32_t period = 5000; //20ms (16Mhz / 64pwm_divider / 50)
uint32_t duty = 250;    //1.5ms pulse width
void ucKeypadScanTail(void);
void ucKeypadScanTail_2(void);
void Haramy(void);
int main()
{       
        servo_init(); 
        timer_init();
        timer_init_2();
        spi_init();
        vKeypadInit();
        uart_init_5(4800,16000000UL);
        vLCDInit();
        
        uint8_t  user[160];
        uint8_t  name[10][9];
	uint8_t  pass[10][8];
        memset(name, 255, sizeof(name[0][0]) * 10 * 9);
        memset(pass, 255, sizeof(pass[0][0]) * 10 * 8);

	uint16_t j=0;
        uint16_t p=0;
        uint16_t p1=0;
	unsigned char f=0;
        unsigned char one_time=0;
        char flag=0;
        
        memset(password,255,8);
        uint8_t  EE_PROM[2048];
        int l=0;
        int v=0;
        unsigned char privilege1=0;
        unsigned char privilege2=0;
        uint8_t  password_buffer[8];
        memset(password_buffer,255,8);
        uint8_t  name_buffer[8];
        memset(name_buffer,255,8);
        unsigned char counter=0;
        char flag2=0;
        SYSCTL->RCGCGPIO  |=0x20;
        GPIOF->LOCK=0x4C4F434B;
        GPIOF->CR=0xff;
        GPIOF->DEN |= LED_RED|LED_GREEN|LED_BLUE;
        GPIOF->DIR |= LED_RED|LED_GREEN|LED_BLUE;
        uint8_t  bluetooth_password[8];
        memset(bluetooth_password,255,8);
        uint8_t number[5];
        memset(number,0,5);
        char flag3=0;
        char flag4=0;
        unsigned char hour, mint, second, day, month, year;
        
        int seconds=3;
	int mintues=0;
	int hours=0;
	int days=0;
	int months=0;
	int years=0;
   while (1)
   {  
        flag=spi_tranceiver(1);

   if(flag==190)
   {     
        spi_tranceiver('N');
	while(j<2)
	{
		if(f==0)
		{
			vLCDClearDisplay();
			vLCDWriteString("Welcome");
			delay(MS(1000));
			vLCDClearDisplay();
			vLCDWriteString("Admins Please");
			delay(MS(1000));
		}
		vLCDClearDisplay();
		vLCDWriteString("Enter name: ");
                cLCDGotoXY(0,1);
		 for (i=0;(i<8);i++)
		 {
			 buff = ucKeypadScan();
                         ucKeypadScanTail_2();
                         if (((buff)!=13)&&((buff)!=0))
			 {
                                 
				 name[j][i]=buff;
				 vLCDWriteCharacter(name[j][i]);
			 }
			else 
				break;
		 }
		 delay(US(10));
		 vLCDClearDisplay();
	
                 vLCDWriteString("Enter password: ");
                 cLCDGotoXY(0,1);
		for (i=0;i<7;i++)
		{
			 buff = ucKeypadScan();
                         ucKeypadScanTail_2();
			 if (((buff)!=13)&&((buff)!=0))
			 {
                                 
				 pass[j][i]=buff;
				 vLCDWriteCharacter(pass[j][i]);
			 }
			 else
				break;
		}
		delay(US(10));
		vLCDClearDisplay();
		
		
		if(f==0)
		{
			for (i=0;(i<8)&&(name[i]!='\0');i++)
			{
				user[i]=name[0][i];
			}
			for (i=0;(i<8)&&(pass[i]!='\0');i++)
			{
				user[i+8]=pass[0][i];
			}
			
			for(i=0;i<16;i++)
			{
				spi_tranceiver( user[i]);
				delay(MS(10));
			}
		}
		
		if(f==1)
		{
			for (i=0;(i<8)&&(name[i]!='\0');i++)
			{
				user[i+16]=name[1][i];
			}
			for (i=0;(i<8)&&(pass[i]!='\0');i++)
			{
				user[i+24]=pass[1][i];
			}
			
			for(i=16;i<32;i++)
			{
				spi_tranceiver( user[i]);
				delay(MS(10));
			}
		}
		
		
		
		if (f==0)
		{
			vLCDWriteString("Enter more Admins(Y/N)?");
			buff=ucKeypadScan();
                        ucKeypadScanTail_2();
		}
		  
		
		if ((buff=='y')||(buff=='Y'))
		{
			f++;
			j++;
			continue;
		}
		      else 
			{
				if (f==0)
				{
					j=2;
					f=2;
					continue;
				}
				
			}
                
                 		  
		}
                                 vLCDClearDisplay();
                                  vLCDWriteString("Thank You!");
                                  delay(MS(1000));
		
   }
   
   if(counter<4)
   {
        flag3=0;
        memset(password,255,8);
	vLCDClearDisplay();
        vLCDWriteString("Enter your pass!");
        cLCDGotoXY(0,1);
                  flag2=0;
                 for (i=0;(i<8);i++)
		 {    
                       if(i<7)
			 buff1 = ucKeypadScan();
                       if(i==7)
                       {
                         while((buff1!=13)&&(buff1!=127))
                         {
                           buff1 = ucKeypadScan();
                         }
                       }
                       start_timer_40s();
                       ucKeypadScanTail();
                        if (((buff1)!=13)&&((buff1)!=127)&&((buff1)!=0))
			 {
                                 
                                 flag2++;
				 password[i]=buff1;
                                 if(i<7){
                                   vLCDWriteCharacter(password[i]);
                                   delay(MS(300));
                                   cLCDGotoXY(i,1);
                                 vLCDWriteCharacter('*');
                                 }
                               if (i==7)
                                {
                                   if(one_time==0)
                                     spi_tranceiver('/');
                                }
			 }
                        
			else if (((buff1)==13)&&(flag2>0)) 
                        {    
                             if(one_time==0)
                                spi_tranceiver('/');
                                break;
                        }
                        
			else if (((buff1)==127)) 
                        { 
                          cLCDGotoXY(0,1);
                           vLCDWriteString("                ");
                           cLCDGotoXY(0,1);
                           memset(password,255,8);
                           i=-1;
                        }
                        else 
                            i=-1;
                 }
                 
                 
                 if(one_time==0)
                 {  
                        delay(MS(1000));
                        vLCDClearDisplay();
                        vLCDWriteString("Wait seconds");
                        cLCDGotoXY(0,1);
                        vLCDWriteString("please !");
                        one_time=1;
                        spi_tranceiver(0);
                        spi_tranceiver(0);
                          for(l=-2;l<1024;l++)
                               {
                                 EE_PROM[l]= spi_tranceiver(0);
                                 delay(MS(20));
                                 if((l%8==0)&&(((l/8)%2)==0))
					{
                                          if(EE_PROM[l]==255){
                                            break;
                                          }
					}
                               }
                 }
     p=0;
     for(l=0;l<2048;l++)
      {
        memset(password_buffer,255,8);
         if((l%8==0)&&(((l/8)%2)!=0))
         {
             p++;             
             for(i=0,v=l;(i<8)&&(v<(l+8));i++,v++)
             {
                password_buffer[i]= EE_PROM[v];
                   
                   
                   
                   
                   
             }
            
         }
         if((l%8==0)&&(((l/8)%2)==0))
         {
              memset(name_buffer,255,8);
             for(i=0,v=l;(i<8)&&(v<(l+8));i++,v++)
             {
                name_buffer[i]= EE_PROM[v];
                   
                   
                   
                   
                   
             }
            
         }
         if(memcmp(password,password_buffer,7)==0)
         {
           counter=5;
           switch(p){
                 case 1:
                 case 2:
                     privilege1='A'; 
                     break;
                 case 3:
                 case 4:
                 case 5:
                 case 6:
                     privilege1='S';
                     break;
                 default:
                     privilege1='U';
                     break;
           }
           
           
           
           vLCDClearDisplay();
           vLCDWriteString("Welcome ");
           for(i=0;(i<8)&&(name_buffer[i]!=255);i++)
           {
             vLCDWriteCharacter(name_buffer[i]);
           }
             
           delay(MS(1500));
           
           
           for(i=0;(i<8)&&(name_buffer[i]!=255);i++)
           {
              UART_Write_5(name_buffer[i]);
           }
           
           uart_write_string_5(" comes on  ");
           spi_tranceiver('g');
           delay(MS(20));
           spi_tranceiver(0);
           delay(MS(20));
           second = spi_tranceiver(0);
           delay(MS(20));
           mint = spi_tranceiver(0);
           delay(MS(20));
           hour = spi_tranceiver(0);
           delay(MS(20));
           day = spi_tranceiver(0);
           delay(MS(20));
           month = spi_tranceiver(0);
           delay(MS(20));
           year = spi_tranceiver(0);
           delay(MS(20));
           
           seconds = ((second & 0xF0) >> 4) * 10 + (second & 0x0F);
           mintues = ((mint & 0xF0) >> 4) * 10 + (mint & 0x0F);
           hours =  ((hour & 0xF0) >> 4) * 10 + (hour & 0x0F);
           days = ((day & 0xF0) >> 4) * 10 + (day & 0x0F);
           months = ((month & 0xF0) >> 4) * 10 + (month & 0x0F);
           years = ((year & 0xF0) >> 4) * 10 + (year & 0x0F);
           		
           uart_write_int_5(hours);
           UART_Write_5(':');
           uart_write_int_5(mintues);	
           UART_Write_5(':');
           uart_write_int_5(seconds);
           
           uart_write_string_5("  at  ");
           
           uart_write_int_5(days);
           UART_Write_5('/');
           uart_write_int_5(months);
           UART_Write_5('/');
           UART_Write_5('2');
           UART_Write_5('0');
           uart_write_int_5(years);
           uart_write_string_5("\r\n");
           
           vLCDClearDisplay();
           vLCDWriteString("opening ... ");
           open();
           cLCDGotoXY(0,0);
           vLCDWriteString("opened       ");
           cLCDGotoXY(0,1);
           vLCDWriteString("enter please ..       ");
           delay(MS(3000));
           vLCDClearDisplay();
           cLCDGotoXY(0,0);
           vLCDWriteString("closing ...  ");
           close();
           
           break;
         }
         
      }
     
     if(memcmp(password,password_buffer,7)!=0)
            {
               counter++;
               vLCDClearDisplay();
               vLCDWriteString("Attempts=");
               cLCDShowInt(9,0,counter,1);
               delay(MS(1500));
            }
     
   }     
           if(counter==4)
           {
             flag3=1;
             TIMER2->CTL |=(1U<<TAEN);
             delay(MS(200));
             spi_tranceiver('b');
              memset(bluetooth_password,255,8); 
              vLCDClearDisplay();
              vLCDWriteString("bluetooth Time ");
              cLCDGotoXY(0,1);
              for (i=0;i<9;i++)
                 {
                    buff = UART_Read_5();
                             if (((buff)!=13)&&((buff)!=10)&&((buff)!=0)&&((buff)!=255))
                             {
                                        bluetooth_password[i]=buff;          
                                        vLCDWriteCharacter(bluetooth_password[i]);
                                        
                             }
                            
                            else if ((buff)==13) 
                            {       
                                    break;
                            }
                            
                            else 
                                i=-1;
                 }
                        
                        p1=0;
                        for(l=0;l<96;l++)
                          {
                            memset(password_buffer,255,8);
                             if((l%8==0)&&(((l/8)%2)!=0))
                             {
                                 p1++;
                                 for(i=0,v=l;(i<8)&&(v<(l+8));i++,v++)
                                 {
                                    password_buffer[i]= EE_PROM[v];
                                       
                                       
                                       
                                       
                                       
                                 }
                                
                             }
                             if((l%8==0)&&(((l/8)%2)==0))
                             {
                                  memset(name_buffer,255,8);
                                 for(i=0,v=l;(i<8)&&(v<(l+8));i++,v++)
                                 {
                                    name_buffer[i]= EE_PROM[v];
                                       
                                       
                                       
                                       
                                       
                                 }
                                
                             }
                             
                             if((memcmp(bluetooth_password,password_buffer,7)==0)&&(bluetooth_password[0]!=255))
                             {
                               counter=5;
                               switch(p1){
                                     case 1:
                                     case 2:
                                         privilege2='A'; 
                                         break;
                                     case 3:
                                     case 4:
                                     case 5:
                                     case 6:
                                         privilege2='S';
                                         break;
                                     default:
                                         privilege2='U';
                                         break;
                               }
                                
                                
                               vLCDClearDisplay();
                                vLCDWriteString("Welcome ");
                                for(i=0;(i<8)&&(name_buffer[i]!=255);i++)
                                {
                                  vLCDWriteCharacter(name_buffer[i]);
                                }
                                delay(MS(1500));
                                
                                
                                for(i=0;(i<8)&&(name_buffer[i]!=255);i++)
                                {
                                   UART_Write_5(name_buffer[i]);
                                }
                                uart_write_string_5(" unlock system on  ");
                                spi_tranceiver('g');
                                delay(MS(20));
                                spi_tranceiver(0);
                                delay(MS(20));
                                second = spi_tranceiver(0);
                                delay(MS(20));
                                mint = spi_tranceiver(0);
                                delay(MS(20));
                                hour = spi_tranceiver(0);
                                delay(MS(20));
                                day = spi_tranceiver(0);
                                delay(MS(20));
                                month = spi_tranceiver(0);
                                delay(MS(20));
                                year = spi_tranceiver(0);
                                delay(MS(20));
                                
                                seconds = ((second & 0xF0) >> 4) * 10 + (second & 0x0F);
                                mintues = ((mint & 0xF0) >> 4) * 10 + (mint & 0x0F);
                                hours =  ((hour & 0xF0) >> 4) * 10 + (hour & 0x0F);
                                days = ((day & 0xF0) >> 4) * 10 + (day & 0x0F);
                                months = ((month & 0xF0) >> 4) * 10 + (month & 0x0F);
                                years = ((year & 0xF0) >> 4) * 10 + (year & 0x0F);
                                		
                                uart_write_int_5(hours);
                                UART_Write_5(':');
                                uart_write_int_5(mintues);	
                                UART_Write_5(':');
                                uart_write_int_5(seconds);
                                
                                uart_write_string_5("  at  ");
                                
                                uart_write_int_5(days);
                                UART_Write_5('/');
                                uart_write_int_5(months);
                                UART_Write_5('/');
                                UART_Write_5('2');
                                UART_Write_5('0');
                                uart_write_int_5(years);
                                uart_write_string_5("\r\n");
                               break;
                             }
                             
                          }                    
           }
   
   if(counter==5){
           if((privilege2=='A')||(privilege1=='A'))
           {
              memset(name, 255, sizeof(name[0][0]) * 10 * 9);
              memset(pass, 255, sizeof(pass[0][0]) * 10 * 8);
              memset(user,255,16);
             if (flag3==1)
          {
               
             uart_write_string_5("\r\n1:Turn off stuff");
             delay(MS(200));
             uart_write_string_5("\r\n2:Add user ");
             delay(MS(200));
             uart_write_string_5("\r\n3:Modify user ");
             delay(MS(200));
             uart_write_string_5("\r\n4:Delete user\r\n");
             delay(MS(200));
             uart_write_string_5("5:View all users\r\n");
             delay(MS(200));
             uart_write_string_5("6:Delete all users\r\n");
             delay(MS(200));
          }
          else if (flag3==0)
          {
             uart_write_string_5("\r\n1:Exit\r\n");
             delay(MS(200));
             uart_write_string_5("2:Add user\r\n");
             delay(MS(200));
             uart_write_string_5("3:Modify user\r\n");
             delay(MS(200));
             uart_write_string_5("4:Delete user\r\n");
             delay(MS(200));
             uart_write_string_5("5:View all users\r\n");
             delay(MS(200));
             uart_write_string_5("6:Delete all users\r\n");
             delay(MS(200));
          }
              
              while(1)
               {
                  buff = UART_Read_5();
                  if((buff>48)&&(buff<55)||(buff==0))
                    break;
               }
              if(buff== '1')
              {
                GPIOF->DATA &=~ LED_RED;
                TIMER2->CTL &=~(1U<<TAEN);
                spi_tranceiver('c');  
                
                counter=0;
                privilege1='U';
                privilege2='U';
              }
              if(buff== '2')
              {
                spi_tranceiver('d');                 
                delay(MS(100));
                vLCDClearDisplay();
                vLCDWriteString("Enter name: ");
                for (i=0;(i<8);i++)
                      {
                        name[0][i]=255;
                        pass[0][i]=255;
                      }
                    
                cLCDGotoXY(0,1);
                for (i=0;(i<8);i++)
		 {
			 buff = ucKeypadScan();
                         ucKeypadScanTail_2();
                         if (((buff)!=13)&&((buff)!=0))
			 {
                                 
				 name[0][i]=buff;
				 vLCDWriteCharacter(name[0][i]);
			 }
			else 
				break;
		 }
                  vLCDClearDisplay();
                  vLCDWriteString("Enter password: ");
                  cLCDGotoXY(0,1);
                  for (i=0;i<7;i++)
                  {
                           buff = ucKeypadScan();
                           ucKeypadScanTail_2();
                           if (((buff)!=13)&&((buff)!=0))
                           {
                                   
                                   pass[0][i]=buff;
                                   vLCDWriteCharacter(pass[0][i]);
                           }
                           else
                                  break;
                  }
                  
                        for (i=0;(i<8)&&(name[i]!='\0');i++)
			{
				user[i]=name[0][i];
			}
			for (i=0;(i<8)&&(pass[i]!='\0');i++)
			{
				user[i+8]=pass[0][i];
			}
			
			for(i=0;i<15;i++)
			{
				spi_tranceiver( user[i]);
				delay(MS(10));
			}
                        
                  vLCDClearDisplay();
                  vLCDWriteString("Done");
                  delay(MS(1500));
               counter=0;
               one_time=0;
               privilege1='U';
                privilege2='U';
              }
              if(buff== '3')
              {
                 spi_tranceiver('e');
                 vLCDClearDisplay();
                 vLCDWriteString("Enter name: ");
                 cLCDGotoXY(0,1);
                for (i=0;(i<8);i++)
		 {
			 buff = ucKeypadScan();
                         ucKeypadScanTail_2();
                         if (((buff)!=13)&&((buff)!=0))
			 {
                                 
				 name[0][i]=buff;
				 vLCDWriteCharacter(name[0][i]);
			 }
			else 
				break;
		 }
                
                for(l=32;l<2048;l++)
                  {
                      if((l%8==0)&&(((l/8)%2)==0))
                             {
                                  memset(name_buffer,255,8);
                                 for(i=0,v=l;(i<8)&&(v<(l+8));i++,v++)
                                 {
                                    name_buffer[i]= EE_PROM[v];
                                       
                                       
                                       
                                       
                                       
                                 }
                                
                             }
                      
                      if(memcmp(name[0],name_buffer,7)==0)
                        {
                          spi_tranceiver('E');
                          memset(number,0,5);
                          for(i=4;(i>=0)&&(l > 0);i--)
                          {
                              number[i] = l % 10;
                              l = l / 10;
                              
                          }
                          for(i=0;(i<5);i++)
                          {
                            spi_tranceiver(number[i]);
                          }
                    vLCDClearDisplay();      
                    vLCDWriteString("Enter new name: ");
                    for (i=0;(i<8);i++)
                      {
                        name[0][i]=255;
                        pass[0][i]=255;
                      }
                    
                    cLCDGotoXY(0,1);
                    for (i=0;(i<8);i++)
                      {
                              buff = ucKeypadScan();
                              ucKeypadScanTail_2();
                              if (((buff)!=13)&&((buff)!=0))
                              {
                                      
                                      name[0][i]=buff;
                                      vLCDWriteCharacter(name[0][i]);
                              }
                              else 
                                      break;
                      }
                      vLCDClearDisplay();  
                      vLCDWriteString("Enter new pass: ");
                      cLCDGotoXY(0,1);
                      for (i=0;i<7;i++)
                      {
                                buff = ucKeypadScan();
                                ucKeypadScanTail_2();
                                if (((buff)!=13)&&((buff)!=0))
                                {
                                        
                                        pass[0][i]=buff;
                                        vLCDWriteCharacter(pass[0][i]);
                                }
                                else
                                      break;
                      }
                      
                            for (i=0;(i<8)&&(name[i]!='\0');i++)
                              {
                                      user[i]=name[0][i];
                              }
                              for (i=0;(i<8)&&(pass[i]!='\0');i++)
                              {
                                      user[i+8]=pass[0][i];
                              }
                              
                              for(i=0;i<15;i++)
                              {
                                      spi_tranceiver( user[i]);
                                      delay(MS(10));
                              }
                      vLCDClearDisplay();
                      vLCDWriteString("Done");
                      delay(MS(1500));
                      one_time=0;
                      flag4=1;
                          break;
                        }
                  }
                
                if(flag4==0)
                {
                      vLCDClearDisplay();
                vLCDWriteString("Not found");
                      delay(MS(1500));
                }   
                counter=0;
                privilege1='U';
                privilege2='U';
              }
              if(buff== '4')
              {
                 spi_tranceiver('f');
                 vLCDClearDisplay();
                 vLCDWriteString("Enter name: ");
                 cLCDGotoXY(0,1);
                for (i=0;(i<8);i++)
		 {
			 buff = ucKeypadScan();
                         ucKeypadScanTail_2();
                         if (((buff)!=13)&&((buff)!=0))
			 {
                                 
				 name[0][i]=buff;
				 vLCDWriteCharacter(name[0][i]);
			 }
			else 
				break;
		 }
                
                for(l=32;l<2048;l++)
                  {
                      if((l%8==0)&&(((l/8)%2)==0))
                             {
                                  memset(name_buffer,255,8);
                                 for(i=0,v=l;(i<8)&&(v<(l+8));i++,v++)
                                 {
                                    name_buffer[i]= EE_PROM[v];
                                       
                                       
                                       
                                       
                                       
                                 }
                                
                             }
                      
                      if(memcmp(name[0],name_buffer,7)==0)
                        {
                          spi_tranceiver('E');
                          memset(number,0,5);
                          for(i=4;(i>=0)&&(l > 0);i--)
                          {
                              number[i] = l % 10;
                              l = l / 10;
                              
                          }
                          for(i=0;(i<5);i++)
                          {
                            spi_tranceiver(number[i]);
                          }
                          
                    for (i=1;(i<8);i++)
                      {
                              buff = 255;
                              name[0][i]=buff;
                              name[0][0]='S';
                      }
                    
                      for (i=0;i<7;i++)
                      {
                                buff = 255;
                                pass[0][i]=buff;
                      }
                      
                            for (i=0;(i<8)&&(name[i]!='\0');i++)
                              {
                                      user[i]=name[0][i];
                              }
                              for (i=0;(i<8)&&(pass[i]!='\0');i++)
                              {
                                      user[i+8]=pass[0][i];
                              }
                              
                              for(i=0;i<15;i++)
                              {
                                      spi_tranceiver( user[i]);
                                      delay(MS(10));
                              }
                
                          vLCDClearDisplay();
                          vLCDWriteString("Done");
                          delay(MS(1500));
                          one_time=0;
                          flag4=1;
                          break;
                        }
                  }
                if(flag4==0)
                {
                vLCDClearDisplay();
                vLCDWriteString("Not found");        
                delay(MS(1500));
                }
                privilege1='U';
                privilege2='U';
                counter=0;
                
              }
              if(buff== '5')
              {
                for(l=0;l<1024;l++)
                  {
                      if((l%8==0)&&(((l/8)%2)==0)&&(EE_PROM[l]!='S'))
                             {
                               if((EE_PROM[l]==255))
                                {
                                  break;
                                }
                               vLCDClearDisplay();
                               uart_write_string_5("\r\nname ");
                                 for(i=0,v=l;(i<8)&&(v<(l+8))&&(EE_PROM[v]!=255);i++,v++)
                                 {    
                                       UART_Write_5(EE_PROM[v]);
                                 }
                             }
                      
                      if((l%8==0)&&(((l/8)%2)!=0)&&(EE_PROM[l]!=255))
                             {
                               cLCDGotoXY(0,1);
                               uart_write_string_5("\r\npass ");
                                 for(i=0,v=l;(i<8)&&(v<(l+8))&&(EE_PROM[v]!=255);i++,v++)
                                 {    
                                       UART_Write_5(EE_PROM[v]);
                                 }
                             }
                      delay(MS(150));
                      uart_write_string_5("\r\n");
                  }
                counter=0;
                privilege1='U';
                privilege2='U';
              }
              if(buff== '6')
              {
                spi_tranceiver('h');
                delay(MS(20));
                counter=0;
                one_time=0;
                privilege1='U';
                privilege2='U';
                vLCDClearDisplay();
                vLCDWriteString("Done");
                delay(MS(1500));
                
              }
              
           }
           if((privilege2=='S')||(privilege1=='S'))
           {
             if(flag3==1)
             {
                uart_write_string_5("1:Trun off stuff\r\n");
                
                 while(1)
               {
                  buff = UART_Read_5();
                  if((buff>48)&&(buff<50))
                    break;
               }
             }
             else if(flag3==0)
             {
                counter=0;
             }
            
              if(buff== '1')
              {
                GPIOF->DATA &=~ LED_RED;
                TIMER2->CTL &=~(1U<<TAEN);
                spi_tranceiver('c');
                
                counter=0;
                privilege1='U';
                privilege2='U';
              }
              
           }
           if((privilege2=='U')||(privilege1=='U'))
           {
               counter=0;
               privilege1='U';
                privilege2='U';
           }
   }
           
  }
  return 0;
}
void ucKeypadScanTail(void)
{
   while (((buff1)==0))
     {
       buff1=ucKeypadScan();
       if ((buff1!=0))
         {
           break;
         }
       
       
       if((TIMER0->RIS&(1U<<TATORIS))==(1U<<TATORIS))
       {
         
         cLCDGotoXY(0,1);
          vLCDWriteString("                ");
          cLCDGotoXY(0,1);
          memset(password,255,8);
          i=-1;
          stop_timer_40s();
         break;
       }
        
      }
}
void ucKeypadScanTail_2(void)
{
   while (((buff)==0))
     {
       buff=ucKeypadScan();
       if ((buff!=0))
         {
           break;
         }
        
      }
}
void Haramy(void)
{
  TIMER2->ICR |=(1U<<TATOCINT);
  GPIOF->DATA ^=LED_RED;
  spi_tranceiver('b');
}
void delayMS(int ms) {
    SysCtlDelay( (SysCtlClockGet()/(3*1000))*ms ) ;
}
void servo_init(void)
{
    //Set the clock
   SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC |   SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

   //Configure PWM Clock divide system clock by 64
   SysCtlPWMClockSet(SYSCTL_PWMDIV_64);

   // Enable the peripherals used by this program.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);  //The Tiva Launchpad has two modules (0 and 1). Module 1 covers the LED pins

    //Configure PF1,PF2,PF3 Pins as PWM
    GPIOPinConfigure(GPIO_PF3_M1PWM7);
    GPIOPinTypePWM(GPIO_PORTF_BASE,  GPIO_PIN_3);

    //Configure PWM Options
    //PWM_GEN_2 Covers M1PWM4 and M1PWM5
    //PWM_GEN_3 Covers M1PWM6 and M1PWM7
    PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC); 

    //Set the Period (expressed in clock ticks)
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, period);

    //Set PWM duty
    PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7,duty);

    // Enable the PWM generator
    PWMGenEnable(PWM1_BASE, PWM_GEN_3);

    // Turn on the Output pins
    PWMOutputState(PWM1_BASE, PWM_OUT_7_BIT, true);

    
}
void open(void)
{
  for(i=duty;i<(1.75*duty);i++)
    {
      PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7 , i);
      delayMS(10);
      GPIOF->DATA |= LED_BLUE;
    }
  delayMS(2000);
}
void close(void)
{
  for(i=(1.75*duty);i>(duty);i--)
    {
      PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7 , i);
      delayMS(10);
      GPIOF->DATA &=~ LED_BLUE;
    }
    delayMS(2000);
    
}

