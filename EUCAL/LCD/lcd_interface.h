

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_


/* Prototypes of the Function */

void EULLCD_voidLCDInit(void);
void EULCD_voidLCDWriteCommand(u8 copy_u8Command);
void EULCD_voidLCDWriteData(u8 copy_u8data);
s8 EULCD_voidLCDGoto (u8 copy_u8Row ,u8 copy_u8Column);
void EULCD_voidLCDWriteString (u8 * copy_u8PtrData);
void EULCD_voidLCDShiftRight(void);
void EULCD_voidLCDShiftLeft(void);
void EULCD_voidLCDDisplay_num (u8 copy_u8data );
void EULCD_voidLCDClearScreen (void);

/* Macros useful to make the code more readable */
#define			ERROR		-1
#define			NOT_ERROR	 1

#endif /* LCD_H_ */