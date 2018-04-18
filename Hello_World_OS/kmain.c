unsigned char cursor_x = 0;
unsigned char cursor_y = 0;

unsigned short * video_memory = (unsigned short *)0x000B8000;
unsigned char white_on_black = 15 | 0 << 4;

void outb(unsigned short port, unsigned char value)
{
	asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

void move_cursor()
{
	unsigned short cursorLocation = cursor_y * 80 + cursor_x;
	outb(0x3D4, 14);
	outb(0x3D5, cursorLocation >> 8);
	outb(0x3D4, 15);
	outb(0x3D5, cursorLocation);
}

void clear_screen()
{
	unsigned short blank = 0x20 | (white_on_black << 8);

	int i;
	for (i = 0; i < 80*25; i++)
	{
		video_memory[i] = blank;
	}

	cursor_x = 0;
	cursor_y = 0;
	move_cursor();
}

void putch(char c)
{
	if(c == '\n')
	{
		cursor_x = 0;
		cursor_y++;
	}
	else
	{
		int i = cursor_x + (cursor_y * 80);
		video_memory[i] = c | white_on_black << 8;
		cursor_x++;
	}

	if(cursor_x > 80)
	{
		cursor_x = 0;
		cursor_y++;
	}

	move_cursor();
}

int strlen(char *str)
{
	const char *s = str;
	for (s = str; *s; s++)
		;
	return (s - str);
}

void print(char *str)
{
	int len = strlen(str);

	int i;
	for (i = 0; i < len; i++)
		putch(str[i]);
}

void kmain()
{
	clear_screen();
	print("Hello World!\n");
}

