//LCD Functions Developed by electroSome
#include "Driver_LCD.h"
#include "mcc_generated_files/pin_manager.h"

#define _XTAL_FREQ 40000000


void DRV_LCD_Data(uint8_t data)
{
	if(data & 1)		
        D0_SetHigh();
	else	
        D0_SetLow();
	if(data & 2)		
        D1_SetHigh();
	else		
        D1_SetLow();
	if(data & 4)		
        D2_SetHigh();
	else		
        D2_SetLow();

	if(data & 8)		
        D3_SetHigh();      
	else		
        D3_SetLow();
}
void DRV_LCD_Cmd(uint8_t cmd)
{	
    RS_SetLow();
	DRV_LCD_Data(cmd);	
    EN_SetHigh();
    __delay_ms(4);       
    EN_SetLow();
}

 void DRV_LCD_Clear(void)
{
	DRV_LCD_Cmd(0x01); // Clear display command
    __delay_ms(2); // Delay after clear command execution
}

void DRV_LCD_SetCursor(uint8_t linha, uint8_t coluna, bool cursorOn)
{
    char temp,z,y;
	if(linha == 1)
	{
	  temp = 0x80 + coluna - 1;
		z = temp>>4;
		y = temp & 0x0F;
		DRV_LCD_Cmd(z);
		DRV_LCD_Cmd(y);        
	}
	else if(linha == 2)
	{
		temp = 0xC0 + coluna - 1;
		z = temp>>4;
		y = temp & 0x0F;
		DRV_LCD_Cmd(z);
		DRV_LCD_Cmd(y);
	}
    else if (linha == 3)
    {
        temp = 0x94 + coluna - 1;
        z = temp >> 4;
        y = temp & 0x0F;
        DRV_LCD_Cmd(z);
        DRV_LCD_Cmd(y);
    }
    else if (linha == 4)
    {
        temp = 0xD4 + coluna - 1;
        z = temp >> 4;
        y = temp & 0x0F;
        DRV_LCD_Cmd(z);
        DRV_LCD_Cmd(y);
    }    
    
    // Desliga o modo de escrita automática;
     DRV_LCD_Cmd(0xC0);

    // Habilita ou desabilita o cursor
    if (cursorOn)
    {   
        DRV_LCD_Cmd(0x0E); // Liga o cursor       
    }
    else
    {      
        DRV_LCD_Cmd(0x0C); // Desliga o cursor        
    }
}

void DRV_LCD_Init(void)
{
       DRV_LCD_Data(0x00);
    __delay_ms(20);
    DRV_LCD_Cmd(0x03);
    __delay_ms(5);
    DRV_LCD_Cmd(0x03);
    __delay_ms(11);
    DRV_LCD_Cmd(0x03);

    DRV_LCD_Cmd(0x02); // Initialize 4-bit mode
     __delay_ms(5);
    DRV_LCD_Cmd(0x02);
     __delay_ms(5);
    DRV_LCD_Cmd(0x08); // 4-bit mode, 2 lines, 5x8 font
     __delay_ms(5);
    DRV_LCD_Cmd(0x00); // Display off
     __delay_ms(5);
    DRV_LCD_Cmd(0x0C); // Display on, cursor off, blinking off
     __delay_ms(5);
    DRV_LCD_Cmd(0x00); // Entry mode: Cursor moves to the right
     __delay_ms(5);
    DRV_LCD_Cmd(0x06); // No shift, auto-increment cursor
     __delay_ms(5);
}

void DRV_LCD_WriteChar(uint8_t data)
{
   char temp,y;
   temp = data&0x0F;
   y = data&0xF0;             
   RS_SetHigh();  // => RS = 1
   DRV_LCD_Data(y>>4);             //Data transfer
   EN_SetHigh();
   __delay_us(40); 
   EN_SetLow();
   DRV_LCD_Data(temp);  
   EN_SetHigh();
   __delay_us(40);  
   EN_SetLow();
}

void DRV_LCD_WriteString(uint8_t *data)
{
	int i;
	for(i=0;data[i]!='\0';i++)
	   DRV_LCD_WriteChar(data[i]);
}

void DRV_LCD_ShiftRight(void)
{
	DRV_LCD_Cmd(0x01); // Shift display right command
    DRV_LCD_Cmd(0x0C); // Turn off cursor and blinking
}

void DRV_LCD_ShiftLeft(void)
{
	 DRV_LCD_Cmd(0x01); // Shift display left command
    DRV_LCD_Cmd(0x08); // Turn off cursor and blinking
}

void DRV_LCD_BLK(bool state)
{  
 // if(state == 1){BLK_SetHigh();}
  //else if(state == 0){BLK_SetLow();}     
}


