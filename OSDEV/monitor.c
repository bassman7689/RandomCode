#include "monitor.h"

unsigned char cursor_x = 0;
unsigned char cursor_y = 0;

unsigned short * video_memory = (unsigned short *)0x0B8000;

static void move_cursor()
{
	unsigned short cursorLocation = cursor_y * 80 + cursor_x;
	outb(0x3D4, 14);
	outb(0x3D5, cursorLocation >> 8);
	outb(0x3D4, 15);
	outb(0x3D5, cursorLocation);
}

static void scroll()
{
	unsigned char attributeByte = (0 << 4) | (15 & 0x0F);
	unsigned short blank = 0x20 | (attributeByte << 8);

	if(cursor_y >= 25)
	{
		int i;
		for (i = 0*80; i < 24*80; i++)
		{
			video_memory[i] = video_memory[i+80];
		}

		for (i = 24*80; i < 25*80; i++)
		{
			video_memory[i] = blank;
		}

	cursor_y=24;
	}
}

void monitor_put(char c)
{
	unsigned char backColor = 0;
	unsigned char foreColor = 15;
	unsigned char attributeByte = (backColor << 4) | (foreColor & 0x0F);
	unsigned short attribute = attributeByte << 8;
	unsigned short *location;	

	if (c == 0x08 && cursor_x)
	{
		cursor_x--;
	}

	else if (c == 0x09)
	{
		cursor_x = (cursor_x+8) & ~(8-1);
	}

	else if (c == '\r')
	{
		cursor_x = 0;
	}

	else if (c == '\n')
	{
		cursor_x = 0;
		cursor_y++;
	}

	else if (c >= ' ')
	{
		location = video_memory + (cursor_y*80 + cursor_x);
		*location = c | attribute;
		cursor_x++;
	}

	if (cursor_x >= 80)
	{
		cursor_x = 0;
		cursor_y++;
	}

	scroll();
	move_cursor();
}

void monitor_clear()
{
	unsigned char attributeByte = (0 << 4) | (15 & 0x0F);
	unsigned short blank = 0x20 | (attributeByte << 8);

	int i;
	for (i = 0; i < 80*25; i++)
	{
		video_memory[i] = blank;
	}

	cursor_x = 0;
	cursor_y = 0;
	move_cursor();
}

void monitor_write(char *c)
{
	int i = 0;
	while(c[i])
	{
		monitor_put(c[i++]);
	}
}

void monitor_write_hex(unsigned int  n)
{
	signed int tmp;

	monitor_write("0x");

	char noZeroes = 1;

	int i;
	for (i = 28; i > 0; i -= 4)
	{
		tmp = (n >> i) & 0xF;
		if (tmp == 0 && noZeroes != 0)
		{
			continue;
		}

		if (tmp >= 0xA)
		{
			noZeroes = 0;
			monitor_put (tmp-0xA+'a' );
		}
		else
		{
			noZeroes = 0;
			monitor_put( tmp+'0' );
		}
	}

	tmp = n & 0xF;
	if (tmp >= 0xA)
	{
		monitor_put (tmp-0xA+'a');
	}
    else
	{
		monitor_put (tmp+'0');
	}

}

void monitor_write_dec(unsigned int n)
{
	if (n == 0)
	{
		monitor_put('0');
		return;
	}

	signed int acc = n;
	char c[32];
	int i = 0;
	while (acc > 0)
	{
		c[i] = '0' + acc % 10;
		acc /= 10;
		i++;
	}
	c[i] = 0;

	char c2[32];
	c2[i--] = 0;
	int j = 0;
	while(i >= 0)
	{
		c2[i--] = c[j++];
	}
	monitor_write(c2);
}
