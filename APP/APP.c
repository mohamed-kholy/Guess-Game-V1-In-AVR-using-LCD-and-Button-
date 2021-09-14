
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../MCAL/DIO/MDIO_interface.h"
#include "../EUCAL/BUTTON/BUTTON_interface.h"
#include "../EUCAL/LCD/lcd_interface.h"
#include "../MCAL/TIMER/Timer_interface.h"
#include "APP.h"
#include <stdlib.h>
#include <util/delay.h>


/* global counter holds number of Seconds */
u8 global_u8SecoundsCounter = 0 ;
/* global counter holds number of Button Pressed */
u8 global_u8counter = 0 ;
/* global Variable holds Random Number */
u8 global_u8Random  ;
/* global variable holds The Iterator Number */
u8 global_u8RandIterator = 1 ;

/*********************************************************************
* Parameters:(in) : None
* Parameters:(out): NONE
* Return value	  : None
* Description	  : Initialize The APplication
***********************************************************************/

void APP_init (void)
{
	/* Initialize The LCD Screen */
	EULLCD_voidLCDInit();
	/* Initialize The Button */
	EUButton_init(GPIOC,PIN0,PULL_DOWN);
	/* Write Guess The Number on the Screen */
	EULCD_voidLCDWriteString("Guess The Number");
	/* Go to Row 2 and Column 8 */
	EULCD_voidLCDGoto(2,8);
	/* Initialize The Timer ON 
	*	Normal Mode 
	*	Timer 1
	*	OverFLow Interrupt 
	*   1 MHZ Crystal 
	*	64  Prescaler		. */
	MTimer_voidInit();
	/* Make The Timer Interrupt Every 1 Second */
	MTimer_s8SetValue(49911);
	/* Set Call Back Function to be Executed on the ISR */
	MTimer_voidSetCallBack(Interrupt);
	/* Get Random Number */
	global_u8Random = RandomNum(0,15,6);

}

/**********************************************************************************
* Parameters:(in) : None
* Parameters:(out): NONE
* Return value	  : None
* Description	  : Update The Application
************************************************************************************/

void APP_update(void)
{
	/* Get The Input From the Button */
	u8 local_u8ReturnButtonValue = EUButtonPressed(GPIOC,PIN0,PULL_DOWN) ;
	/* if the Button Pressed */
	if (local_u8ReturnButtonValue == 1)
	{
		/* Ignore Hold Press */
		while (EUButtonPressed(GPIOC,PIN0,PULL_DOWN) );
		/* increment The Counter */
		global_u8counter ++ ;
	}

}

/*****************************************************************************
* Parameters:(in) : None
* Parameters:(out): NONE
* Return value	  : None
* Description	  : Update The Screen After Every Guess
*******************************************************************************/

void Screen_Update(void)
{
	/* Wait Some MILLI Seconds */
	_delay_ms(1000);
	/* Reset The Seconds Counter */
	global_u8SecoundsCounter = 0 ;
	/* Reset The Iterator */
	global_u8RandIterator ++ ;
	/* Go to The First Position on the Screen */
	EULCD_voidLCDGoto(1,1);
	/* Write Guess The Number String */
	EULCD_voidLCDWriteString("Guess The Number");
	/* Generate Random Number of Range between 1 and 15 */
	global_u8Random =  RandomNum(0,15,global_u8RandIterator);
	/* Go To ROW 2 and Column 8*/
	EULCD_voidLCDGoto(2,8);

}


/********************************************************************************************
* Parameters:(in) : NONE
* Parameters:(out): NONE
* Return value	  : NONE
* Description	  : Function that Call Every 1 Second and Execute the Condition every Call 
**********************************************************************************************/

void Interrupt(void)
{
	/* Increment The seconds */
	global_u8SecoundsCounter ++ ;
	/* Check if the Seconds Reach to The Seconds Defined Macro */
	if (global_u8SecoundsCounter == SECOUNDS_DELAY )
	{
		if ((global_u8counter <= 15) && ((global_u8counter !=0) ))
		{
			
			/* First Clear The Screen */
			EULCD_voidLCDClearScreen();
			/* Reset The Cursor */
			EULCD_voidLCDGoto(1,1);
			/* Write The Actual and Guess Value on the Screen */
			EULCD_voidLCDWriteString("Your Guess: ");
			EULCD_voidLCDDisplay_num(global_u8counter);
			EULCD_voidLCDGoto(2,1);
			EULCD_voidLCDWriteString("Actual    : ");
			EULCD_voidLCDDisplay_num(global_u8Random);
			_delay_ms(1000);
			
			/* in case of the Guess is Correct */
			if (global_u8counter == global_u8Random)
			{
				Winner();
				
			}
			/* in case of the guess is not correct */
			else if (global_u8counter !=global_u8Random)  
			{
				loser();
			}
		}
		/* in case of The button Dose not Pressed */
		if (global_u8counter == 0)
		{
			NoInput();
		}
		/* in case of The Number of The Pressing is more than the Random Number Range */
		if (global_u8counter > 15)
		{
			InvalidRange();
			
		}
		/* Reset The Pressed Counter */
		global_u8counter = 0 ;
	}
	
}
/*****************************************************************************
* Parameters:(in) : None
* Parameters:(out): NONE
* Return value	  : None
* Description	  : Inform the User That he is Winner
*******************************************************************************/
void Winner (void )
{
	/* Clear The Screen */
	EULCD_voidLCDClearScreen ();
	/* go to ROW 1 and Column 4 */
	EULCD_voidLCDGoto(1,4);
	/* Display " YOU WON !" */
	EULCD_voidLCDWriteString("YOU WON !");
	/* Update the Screen */
	Screen_Update();
}


/*****************************************************************************
* Parameters:(in) : None
* Parameters:(out): NONE
* Return value	  : None
* Description	  : Inform the User That he is Loser
*******************************************************************************/
void loser (void)
{
	/* Clear The Screen */
	EULCD_voidLCDClearScreen ();
	/* go to ROW 1 and Column 4 */
	EULCD_voidLCDGoto(1,4);
	/* Display " YOU LOSE !" */
	EULCD_voidLCDWriteString("YOU LOSE !");
	/* Update the Screen */
	Screen_Update();
	
}


/*****************************************************************************
* Parameters:(in) : None
* Parameters:(out): NONE
* Return value	  : None
* Description	  : Inform the User That There's No Input Done
*******************************************************************************/
void NoInput (void)
{
	/* Clear The Screen */
	EULCD_voidLCDClearScreen ();
	/* go to ROW 1 and Column 1*/
	EULCD_voidLCDGoto(1,1);
	/* Inform the User  */
	EULCD_voidLCDWriteString("You Must Press");
	/* Update the Screen */
	Screen_Update();
}


/*****************************************************************************
* Parameters:(in) : None
* Parameters:(out): NONE
* Return value	  : None
* Description	  : Inform the User That he Entered Invalid Range
*******************************************************************************/
void InvalidRange (void)
{
	/* Clear The Screen */
	EULCD_voidLCDClearScreen ();
	/* go to ROW 1 and Column 1*/
	EULCD_voidLCDGoto(1,1);
	/* Inform the User  */
	EULCD_voidLCDWriteString("Not Valid Range");
	/* Update the Screen */
	Screen_Update();
}


/**************************************************************************************
* Parameters:(in) : Minimum Value , Maximum Value , Number Of iteration
* Parameters:(out): NONE
* Return value	  : 8-bit unsigned char NONE
* Description	  : Generate Random Number Between Min and Max Valued
****************************************************************************************/

u8 RandomNum (u8 copy_u8MinValue , u8 copy_u8MaxValue , u8 copy_u8IteratorNum)
{
	/* local Variable holds The Return */
	u8 local_u8Random ;
	u8 local_u8Iterator ;
	for (local_u8Iterator =0 ; local_u8Iterator <=copy_u8IteratorNum ; local_u8Iterator ++ )
	{
		/* Generate Random Number Between Min and Max Valued */
		local_u8Random = rand() % ((copy_u8MaxValue+1)-copy_u8MinValue);
	}
	/* return the random number */
	return local_u8Random ;
}