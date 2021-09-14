#include "../../Lib/STD_TYPES.h"
#include "../../Lib/BIT_MATH.h"
#include "BUTTON_interface.h"
#include "../../MCAl/DIO/MDIO_interface.h"


/************************************************************************************
* Parameters  :(in): PORT Name , Pin Number , Type OF the Connection (Pull Up or Pull Down )
* Parameters  :(out):NONE
* Return value: 8-bit signed Char , if the passed Parameter is OK  Return 1 , otherwise return -1
* Description : Initialize Specific Button based on given parameters
************************************************************************************/

s8 EUButton_init(u8 copy_u8Port , u8 copy_u8Pin , u8 copy_u8ConnectionType ) 
{
		/* if the Parameters is Ok */
	if ( ((copy_u8Port == GPIOA ) || (copy_u8Port== GPIOB) || (copy_u8Port == GPIOC) || (copy_u8Port == GPIOD)) && ((copy_u8Pin <=7)))
	{
		/* MAke the Pin input */
		MDIO_voidSetPinDirection(copy_u8Port,copy_u8Pin,LOW);
		/* In Case of Pull up */
		if ( copy_u8ConnectionType == PULL_UP )
		{
			MDIO_voidSetPinValue ( copy_u8Port , copy_u8Pin , HIGH ) ;
		}
		/* In case of pull down */
		else if  ( copy_u8ConnectionType == PULL_DOWN )
		{
			MDIO_voidSetPinValue ( copy_u8Port , copy_u8Pin , LOW ) ;
		}
		return NOT_ERROR ;
		
	}
	else 
	{
		return ERROR ;
	}
}


/************************************************************************************
* Parameters  :(in): PORT Name , Pin Number , Type OF the Connection (Pull Up or Pull Down )
* Parameters  :(out): Button Pressed or None 
* Return value: 8-bit signed Char , if Pressed return 1 , not pressed return 0 otherwise return -1 
* Description : Check If the Button Pressed Or Not 
************************************************************************************/

s8	EUButtonPressed(u8 copy_u8Port , u8 copy_u8Pin , u8 copy_u8ConnectionType )
{
	/* Local Variable hold the Return Value */
	u8 copy_u8LocalReturn = 0 ;
	/* In case of Pull Up Connection */
	if (copy_u8ConnectionType == PULL_UP)
	{	
		/* Read the Value */ 
		copy_u8LocalReturn=MDIO_voidGetPinValue(copy_u8Port,copy_u8Pin);
		/* If Pressed Return  */
		if (copy_u8LocalReturn == 0 )
			return NOT_ERROR ;
		/* Otherwise Return 0 */
		else 
			return 	 OK ;
	}
	/* In case of PULL Down */
	else if (copy_u8ConnectionType == PULL_DOWN)
	{
		/* Read the Value */ 
		copy_u8LocalReturn=MDIO_voidGetPinValue(copy_u8Port,copy_u8Pin);
		/* If Pressed */
		if (copy_u8LocalReturn == 1 )
			return NOT_ERROR ;
		/* Otherwise */
		else 
			return 	OK ;
		
	}
	/* if Error */
	else 
		return ERROR ;
	
}