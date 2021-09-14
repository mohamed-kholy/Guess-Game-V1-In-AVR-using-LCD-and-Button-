

#ifndef APP_H_
#define APP_H_

/* Prototype of the functions */
void APP_init (void);
void APP_update(void);
u8 RandomNum (u8 copy_u8MinValue , u8 copy_u8MaxValue , u8 copy_u8IteratorNum) ;
void Interrupt(void); 
void InvalidRange (void);
void NoInput (void);
void loser (void);
void Winner (void );
void Screen_Update(void);


/* Macro for the Delay that user must wait to show ther result */
#define		SECOUNDS_DELAY		4


#endif /* APP_H_ */