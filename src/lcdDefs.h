#ifndef lcdDefs_h
#define lcdDefs_h

/* Convenience for functions */
#ifndef AUTO
#define AUTO 				1
#endif	

#ifndef MANUAL 
#define MANUAL 				0
#endif	

#ifndef GUARD
#define GUARD 				1
#endif

#ifndef FREE 			
#define FREE 				1
#endif	

#ifndef CLEAR			
#define CLEAR				1
#endif	

#ifndef KEEP
#define KEEP 				0
#endif

/****************************/

#ifndef LCD_RESET
#define LCD_RESET 			0x30
#endif

#ifndef LCD_DISPLAY_OFF
#define LCD_DISPLAY_OFF	 	0x08
#endif

#ifndef LCD_DISPLAY_ON
#define LCD_DISPLAY_ON 		0x0C
#endif

#ifndef LCD_ENTRY_MODE
#define LCD_ENTRY_MODE 		0x06
#endif	

#ifndef LCD_CURSOR
#define LCD_CURSOR 			0x80
#endif

#ifndef LCD_X
#define LCD_X 				0x10
#endif			

#ifndef LCD_Y
#define LCD_Y 				0x02
#endif

#ifndef LCD_FUNCTION_SET_8
#define LCD_FUNCTION_SET_8 0x38
#endif

#endif
