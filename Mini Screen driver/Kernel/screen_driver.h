
#define VIDEO_ADDRESS_START 0xB8000
// screen device I/O ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

#define MAX_ROWS 25
#define MAX_COLS 80

// Colors
#define FB_Black 0 
#define FB_Red 4 
#define FB_Blue 1 
#define FB_Green 2
#define FB_Cyan 3 
#define FB_Magenta 5
#define FB_Brown 6
#define FB_Light_grey 7 
#define FB_Dark_grey 8 
#define FB_Light_blue 9
#define FB_Light_green 10 
#define FB_Light_cyan 11 
#define FB_Light_red 12
#define FB_Light_magenta 13
#define FB_Light_brown 14
#define FB_White 15


/*
1) print
2) clear
3) scroll
*/

int x=0,y=0;

short int  get_cursor () { // return pos in 25*80 matrix 
	short int pos=0;
	outb(REG_SCREEN_CTRL,14);
	pos = inb(REG_SCREEN_DATA) << 8;
	outb(REG_SCREEN_CTRL,15);
	pos |= inb(REG_SCREEN_DATA);
	return pos;
} 

void setcursor (short int pos) //pos in 25*80 matrix; pos = 1...25*80
{
	outb(REG_SCREEN_CTRL,14); //14 tells the framebuffer to expect the highest 8 bits of the position
	outb(REG_SCREEN_DATA,(char) pos>>8);
	outb(REG_SCREEN_CTRL,15);
	outb(REG_SCREEN_DATA, (char) pos);
}


void setcursor_at (int x, int y) //pos in 25*80 matrix; pos = 1...25*80
{	
	short int pos = x*80+y;

	outb(REG_SCREEN_CTRL,14); //14 tells the framebuffer to expect the highest 8 bits of the position
	outb(REG_SCREEN_DATA,(char) pos>>8);
	outb(REG_SCREEN_CTRL,15);
	outb(REG_SCREEN_DATA, (char) pos);
}


char * get_screen_address_at (int x, int y) 
{
	return (char *) VIDEO_ADDRESS_START + (x*80+y)*2;
}

void putchar_at(char c, int x, int y)
{
	char * screen = get_screen_address_at(x,y);
	screen[0]=c;
	screen[1]=FB_Black <<4 | FB_White;
	setcursor(pos_in_screen(x,y+1));
}

void putchar (char c) {

	char * screen = get_screen_address_at(x,y);
	screen[0]=c;
	screen[1]=FB_Black << 4 | FB_White;

	 if (y==79) 
	 	{ x++;y=0; }
	 else
	 	y++;

	 //scroll();
}

void puts(char * s){
	int i;
	for (i=0; i<strlen(s); i++)
	{
		putchar(s[i]);
	}
}

void clear () {
	int i;
	int n=x*80+y;
	x=y=0;
	for (i=0; i<n;i++)
		putchar(' ');
	x=y=0;
}


int pos_in_screen(x,y)
{
	return x*MAX_COLS+y;
}

void scroll(){

	if (x==25 && y==0)
	{
		memcpy((char*) VIDEO_ADDRESS_START, get_screen_address_at(1,0),80*24*2);
		x=24,y=0;
	}	
	int i;
	for (i=0; i<80; i++)
		putchar(' ');
	
	x=24, y=0;

}


void fb_print_rectangule () {

	int i=0; char c='*'; char bg=0; char fg=2; 
	int j;
	unsigned short * screen = (unsigned short*) VIDEO_ADDRESS_START;  //screen = direccion de primer byte de fb : char * = (char * ) 0x12312 es una manera de guardar direcciones
	
	for (i=0; i<25;i++)
		for (j=0; j<80; j++)
		{
			if (i==0 || i==24 || j==0 || j==79) 
				screen[i*80+j]= ((bg<<4 | fg) << 8) | c;
		}		
}

void fb_write_shell (unsigned int i, unsigned char c, unsigned char fg, unsigned char bg)
{
	//char * screen = (char *) VIDEO_ADDRESS_START;  //screen = direccion de primer byte de fb : char * = (char * ) 0x12312 es una manera de guardar direcciones
	//	screen[i] = ((bg << 4 | fg) << 8 ) | c; o tambien screen[i] = (bg << 12 | (fg << 8) ) | c;

	unsigned short * screen = (unsigned short *) VIDEO_ADDRESS_START;
	screen[i]=((bg<<12) | (fg<<8)) | c;

}
