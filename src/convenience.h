#ifndef convenience_h
#define convenience_h

#ifndef OUTPUT
#define OUTPUT 				1
#endif

#ifndef INPUT
#define INPUT  				0
#endif

#ifndef HIGH
#define HIGH 				1
#endif	

#ifndef LOW
#define LOW  				0
#endif

#ifndef ACTIVE
#define ACTIVE				1
#endif	

#ifndef INACTIVE
#define INACTIVE 			0
#endif

#ifdef LCD_DEFS

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

#ifndef LCD_LINE0
#define LCD_LINE0		 	0x00 
#endif

#ifndef LCD_X
#define LCD_X 				0x10
#endif			

#ifndef LCD_Y
#define LCD_Y 				0x02
#endif

#endif

#endif