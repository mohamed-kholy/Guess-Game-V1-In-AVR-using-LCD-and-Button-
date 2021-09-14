
#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_


/*
	OPTIONS :
	_8_BIT
	_4_BIT
*/
#define 	LCD_MODE		_4_BIT

#define 	RS			0
#define 	RW			1
#define 	EN			2

/*
	OPTIONS : 
	GPIOA
	GPIOB
	GPIOC
	GPIOD
*/

/* in Case of 8 Bit */
#define		LCD_DATA_PORT_8_BIT	    	GPIOA
#define		LCD_Config_Port_8_BIT		GPIOB

/* In case of 4_bit Mode */
#define		LCD_DATA_PORT_4_BIT		GPIOA
#define		LCD_Config_Port_4_BIT	GPIOB

#define		LCD_D7_PORT 	 7
#define		LCD_D6_PORT 	 6
#define		LCD_D5_PORT 	 5
#define		LCD_D4_PORT 	 4


#if  (LCD_MODE == _8_BIT)

#define 	DL							1 	// 1 for 8_bit Mode 0 for 4_bit Mode
#define 	N							1 	// Num Of Display   1 for 2-lines , 0 for 1-Line
#define 	F							0 	// 1 for 5×11 Dots  0 for  5×8 Dots 
#define 	FUNCTION_SET_8_BIT			0b00100000|(DL<<4)|(N<<3)|(F<<2)
#define 	D							1 // 1 for ON entire Display , 0 for OFF Entire Display
#define 	C							0 // 1 for ON Cursor , 0 for OFF Cursor
#define 	B							0 // 1 for ON Cursor Blink , 0 for OFF Cursor Blink
#define		ID							0 // 1 for ON increment mode +1 , 0 for Disable
#define		SH							0 // 1 for On SHIFT , 0 for Disable
#define 	DISPLAY_ON_OFF_8_BIT		0b00001000 |(D<<2) | (C << 1) | (B << 0)
#define 	DISPLAY_CLEAR_8_BIT			0b00000001
#define 	RETURN_HOME_8_BIT			0b00000010
#define		ENTRY_MODE_8_BIT			0b00000100 | (ID << 1) | (SH << 0)

#endif 

#if (LCD_MODE == _4_BIT)

	#define 	N						1 	// Num Of Display   1 for 2-lines , 0 for 1-Line
	#define 	F						0 	// 1 for 5×11 Dots  0 for  5×8 Dots
	#define 	FUNCTION_SET_4_BIT		0b00100000|(N<<3)|(F<<2)
	#define 	D						1 // 1 for ON entire Display , 0 for OFF Entire Display
	#define 	C						0 // 1 for ON Cursor , 0 for OFF Cursor
	#define 	B						0 // 1 for ON Cursor Blink , 0 for OFF Cursor Blink
	#define		ID						0 // 1 for ON increment mode +1 , 0 for Disable 
	#define		SH						0 // 1 for On SHIFT , 0 for Disable 
	#define 	DISPLAY_ON_OFF_4_BIT	0b00001000 |(D<<2) | (C << 1) | (B << 0)
	#define 	DISPLAY_CLEAR_4_BIT		0b00000001
	#define 	RETURN_HOME_4_BIT		0b00000010
	#define		ENTRY_MODE_4_BIT		0b00000100 | (ID << 1) | (SH << 0)

#endif 

#define		_8_BIT			0
#define		_4_BIT			1


#endif /* LCD_CONFIG_H_ */