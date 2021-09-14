

#include  "../../LIB/BIT_MATH.h"
#include  "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/MDIO_interface.h"
#include "lcd_interface.h"
#include "lcd_config.h"
#include <util/delay.h>



/******************************************************************************************
* Parameters(in) : NONE
* Parameters(out): NONE
* Return value	 : NONE
* Description	 : Initiliaze of the Character LCD 16*2 Based on the Configuration file .
******************************************************************************************/
void EULLCD_voidLCDInit(void)
{
	#if (LCD_MODE == _8_BIT)
	/* Make Data Port Output */
	MDIO_voidSetPortDirection(LCD_DATA_PORT_8_BIT,HIGH);
	/* Make Configuration Port Output */
	MDIO_voidSetPinDirection(LCD_Config_Port_8_BIT,RS,HIGH);
	MDIO_voidSetPinDirection(LCD_Config_Port_8_BIT,RW,HIGH);
	MDIO_voidSetPinDirection(LCD_Config_Port_8_BIT,EN,HIGH);
	
	/* Wait for more than 30 ms */
		_delay_ms(50);
	/* Write Command Function Set */
	EULCD_voidLCDWriteCommand(FUNCTION_SET_8_BIT);
	/* wait more than 39us */
	_delay_ms(2);
	/* Write Command Display ON/OFF */
	EULCD_voidLCDWriteCommand(DISPLAY_ON_OFF_8_BIT);
	/* wait more than 39us */
	_delay_ms(2);
	/* Write Command Display Clear */
	EULCD_voidLCDWriteCommand(DISPLAY_CLEAR_8_BIT);
	/* Wait for more than 1.53 ms */
	_delay_ms(5);
	EULCD_voidLCDWriteCommand(RETURN_HOME_8_BIT);
	
	#elif ( LCD_MODE == _4_BIT )
	
	/* Make Configuration Port Output */
	MDIO_voidSetPinDirection(LCD_Config_Port_4_BIT,RS,HIGH);
	MDIO_voidSetPinDirection(LCD_Config_Port_4_BIT,RW,HIGH);
	MDIO_voidSetPinDirection(LCD_Config_Port_4_BIT,EN,HIGH);
	/* Make Data Port Output */
	MDIO_voidSetPinDirection(LCD_DATA_PORT_4_BIT,LCD_D4_PORT,HIGH);
	MDIO_voidSetPinDirection(LCD_DATA_PORT_4_BIT,LCD_D5_PORT,HIGH);
	MDIO_voidSetPinDirection(LCD_DATA_PORT_4_BIT,LCD_D6_PORT,HIGH);
	MDIO_voidSetPinDirection(LCD_DATA_PORT_4_BIT,LCD_D7_PORT,HIGH);
	
	/* Wait for more than 30 ms */
	_delay_ms(50);
  /* Send for 4 bit initialization of LCD  */
	EULCD_voidLCDWriteCommand(0x02);
	/* 2 line, 5*7 matrix in 4-bit mode */
	EULCD_voidLCDWriteCommand(FUNCTION_SET_4_BIT);
	/* wait for more than 39 us */
	_delay_ms(1);
	/* Display on cursor off */	
	EULCD_voidLCDWriteCommand(DISPLAY_ON_OFF_4_BIT);	
	/* wait for more than 39 us */
	_delay_ms(1);
	/* Clear display screen */
	EULCD_voidLCDWriteCommand(DISPLAY_CLEAR_4_BIT);	
	/* wait for more than 1.53ms */
	_delay_ms(5);
	
	#endif
}


/******************************************************************************************
* Parameters(in) : Variable holds Command
* Parameters(out): NONE
* Return value	 : NONE
* Description	 : Check if the Mode 4 bit or 8 bit and then Send Command To LCD
******************************************************************************************/
void EULCD_voidLCDWriteCommand(u8 copy_u8Command)
{
	# if (LCD_MODE == _8_BIT)
	/* Reset RS Pin */
	MDIO_voidSetPinValue(LCD_Config_Port_8_BIT,RS,LOW);
	/* Reset RW Pin  */
	MDIO_voidSetPinValue(LCD_Config_Port_8_BIT,RW,LOW);
	/* Send Command Through LCD Data Port */
	MDIO_voidSetPortValue(LCD_DATA_PORT_8_BIT,copy_u8Command);
	/* Set Enable Pin For High */ 
	MDIO_voidSetPinValue(LCD_Config_Port_8_BIT,EN,HIGH);
	/* Wait at least 1ms */
	_delay_ms(5);
	/* Set Enable Pin For LOW */
	MDIO_voidSetPinValue(LCD_Config_Port_8_BIT,EN,LOW);
	/* Wait at least 5ms */
	_delay_ms(10);
	
	
	#elif (LCD_MODE == _4_BIT)
	
	u8 local_u8Low4 , local_u8High4 ;
	//Get Lower 4_Bit Data
	local_u8Low4 = copy_u8Command & 0x0F ;
	//Get Higher 4_Bit Data
	local_u8High4 = copy_u8Command & 0xF0 ;
	// Make RS Low
	MDIO_voidSetPinValue(LCD_Config_Port_4_BIT,RS,LOW);
	/* Reset RW Pin  */
	MDIO_voidSetPinValue(LCD_Config_Port_4_BIT,RW,LOW);
	// write Command To Data Port
	MDIO_voidSetPortValue(LCD_DATA_PORT_4_BIT,(LCD_DATA_PORT_4_BIT & 0x0F) | (local_u8High4));

	/* Set Enable Pin For High */
	MDIO_voidSetPinValue(LCD_Config_Port_4_BIT,EN,HIGH);
	/* Wait at least 1ms */
	_delay_ms(5);
	/* Set Enable Pin For LOW */
	MDIO_voidSetPinValue(LCD_Config_Port_4_BIT,EN,LOW);
	/* Wait at least 5ms */
	_delay_ms(10);
	// write LOW 4_bit Data To Data Port
	MDIO_voidSetPortValue(LCD_DATA_PORT_4_BIT,(LCD_DATA_PORT_4_BIT & 0x0F) | (local_u8Low4<<4));
	
	/* Set Enable Pin For High */
	MDIO_voidSetPinValue(LCD_Config_Port_4_BIT,EN,HIGH);
	/* Wait at least 1ms */
	_delay_ms(5);
	/* Set Enable Pin For LOW */
	MDIO_voidSetPinValue(LCD_Config_Port_4_BIT,EN,LOW);
	/* Wait at least 5ms */
	_delay_ms(10);
	
	#endif
}

/******************************************************************************************
* Parameters(in) : Variable holds Data to Send To LCD
* Parameters(out): NONE
* Return value	 : NONE
* Description	 : Check if the Mode 4 bit or 8 bit and then Send Data To LCD
******************************************************************************************/
void EULCD_voidLCDWriteData(u8 copy_u8data)
{
	# if (LCD_MODE == _8_BIT)
	/* Set Rs Pin to High */
	MDIO_voidSetPinValue(LCD_Config_Port_8_BIT,RS,HIGH);
	/* Reset RW Pin  */
	MDIO_voidSetPinValue(LCD_Config_Port_8_BIT,RW,LOW);
	/* Send Command Through LCD Data Port */
	MDIO_voidSetPortValue(LCD_DATA_PORT_8_BIT,copy_u8data);
	/* Set Enable Pin For High */
	MDIO_voidSetPinValue(LCD_Config_Port_8_BIT,EN,HIGH);
	/* Wait at least 1ms */
	_delay_ms(5);
	/* Set Enable Pin For LOW */
	MDIO_voidSetPinValue(LCD_Config_Port_8_BIT,EN,LOW);
	/* Wait at least 5ms */
	_delay_ms(10);
	
	#elif (LCD_MODE == _4_BIT)
	
	u8 local_u8Low4 , local_u8High4 ;
	//Get Lower 4_Bit Data
	local_u8Low4 = copy_u8data & 0x0F ;
	//Get Higher 4_Bit Data
	local_u8High4 = copy_u8data & 0xF0 ;
	// Make RS High
	MDIO_voidSetPinValue(LCD_Config_Port_4_BIT,RS,HIGH);
	/* Reset RW Pin  */
	MDIO_voidSetPinValue(LCD_Config_Port_4_BIT,RW,LOW);
	// write Command To Data Port
	MDIO_voidSetPortValue(LCD_DATA_PORT_4_BIT,(LCD_DATA_PORT_4_BIT & 0x0F) | (local_u8High4));
	/* Set Enable Pin For High */
	MDIO_voidSetPinValue(LCD_Config_Port_4_BIT,EN,HIGH);
	/* Wait at least 1ms */
	_delay_ms(5);
	/* Set Enable Pin For LOW */
	MDIO_voidSetPinValue(LCD_Config_Port_4_BIT,EN,LOW);
	/* Wait at least 5ms */
	_delay_ms(10);
	
	// write LOW 4_bit Data To Data Port
	MDIO_voidSetPortValue(LCD_DATA_PORT_4_BIT,(LCD_DATA_PORT_4_BIT & 0x0F) | (local_u8Low4<<4));
	/* Set Enable Pin For High */
	MDIO_voidSetPinValue(LCD_Config_Port_4_BIT,EN,HIGH);
	/* Wait at least 1ms */
	_delay_ms(5);
	/* Set Enable Pin For LOW */
	MDIO_voidSetPinValue(LCD_Config_Port_4_BIT,EN,LOW);
	/* Wait at least 5ms */
	_delay_ms(10);
	#endif
}


/******************************************************************************************
* Parameters(in) : Row , Column
* Parameters(out): NONE
* Return value	 : 8-bit Signed Char , Return -1 if the Pararmeter is Not Okay 
* Description	 : Go to The Location in the Screen Based on the Rom and Column Parameters
******************************************************************************************/
s8 EULCD_voidLCDGoto (u8 copy_u8Row,u8 copy_u8Column)
{
	/* Check for the Range */
	if (copy_u8Column >0 && copy_u8Column<=16)
	{
		switch(copy_u8Row)
		{
			/* Case Row 1 */
			case 1:
			EULCD_voidLCDWriteCommand(copy_u8Column+127);
			break;
			/* Case Row 2 */
			case 2:
			EULCD_voidLCDWriteCommand(copy_u8Column+191);
			break;
			default:
			break;
		}
	}
	else 
	return ERROR ;
}


/******************************************************************************************
* Parameters(in) : Pointer to Unsigned char points to Series of Characters
* Parameters(out): NONE
* Return value	 : NONE
* Description	 : Loop On the Input Characters and Write Every char on the LCD Screen 
******************************************************************************************/
void EULCD_voidLCDWriteString (u8 *copy_u8PtrData )
{
	for (u8 i =0 ; copy_u8PtrData[i]!='\0' ; i++)
	{
		EULCD_voidLCDWriteData(copy_u8PtrData[i]) ;
		_delay_ms(1);
	}
}


/******************************************************************************************
* Parameters(in) : NONE
* Parameters(out): NONE
* Return value	 : NONE
* Description	 : Shift The Displayed Data to The Right One Step
******************************************************************************************/

void EULCD_voidLCDShiftRight(void)
{
   EULCD_voidLCDWriteCommand(0x1C);
}

/******************************************************************************************
* Parameters(in) : NONE
* Parameters(out): NONE
* Return value	 : NONE
* Description	 : Shift The Displayed Data to The Left One Step
******************************************************************************************/
void EULCD_voidLCDShiftLeft(void)
{
	EULCD_voidLCDWriteCommand(0x18);
}


/******************************************************************************************
* Parameters(in) : NONE
* Parameters(out): NONE
* Return value	 : NONE
* Description	 : Clear The Screen
******************************************************************************************/
void EULCD_voidLCDClearScreen (void)
{
	EULCD_voidLCDWriteCommand(DISPLAY_CLEAR_8_BIT);
}

/*********************************************************************************************************
* Parameters(in) : 8-bit Numbers
* Parameters(out): NONE
* Return value	 : NONE
* Description	 : Take  the Numbers that need to display and Do some operation to Display on the Sceen 
***********************************************************************************************************/
void EULCD_voidLCDDisplay_num (u8 copy_u8data )
{
	/* Temporary Empty String */
	u8 str_Arry [3] ;
	/* Hold The Number That More than one Hundred*/
	str_Arry[2] = (copy_u8data /100) + 48 ;
	/* Hold The Number That More than Ten and less than one hundred */
	str_Arry[1] = (copy_u8data % 100)/10 +48 ;
	/* holds the number that less tan ten */
	str_Arry[0] = (copy_u8data % 10) +48 ;
	/* Display the Numbers */
	if (copy_u8data <10 )
	{
		EULCD_voidLCDWriteData(str_Arry[0]);
	}
	else if ((copy_u8data >=10 )& (copy_u8data <100))
	{
		EULCD_voidLCDWriteData(str_Arry[1]);
		EULCD_voidLCDWriteData(str_Arry[0]);
	}
	else 
	{
		EULCD_voidLCDWriteData(str_Arry[2]);
		EULCD_voidLCDWriteData(str_Arry[1]);
		EULCD_voidLCDWriteData(str_Arry[0]);
	}
	
}

