
void memcpy (char * dest, char * source, int numbytes) 
{
	int i;
	for (i=0; i<numbytes; i++)
		dest[i]=source[i];
}

/* funtions test :
	int i,j;
	for (i=0; i<25; i++)
		for (j=0; j<80; j++)
			putchar('A'+(i+j)%25);

	clear();
	putchar('A');
	memcpy(get_screen_address_at(1,0),(char *) VIDEO_ADDRESS_START, 8);

*/