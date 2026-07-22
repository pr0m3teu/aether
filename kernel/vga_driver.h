#ifndef VGA_DRIVER_H_
#define VGA_DRIVER_H_

#define VGA_VIDEO_MEM ((volatile char*) 0xb8000)
#define VGA_LINES 25
#define VGA_COLS  80
#define VGA_CRT_INDEX 0x3d4
#define VGA_CRT_DATA  0x3d5
#define VGA_CURSOR_HIGH 0xe
#define VGA_CURSOR_LOW  0xf

#define VGA_WHITE 0x0f 


void vga_set_cursor(unsigned short offset);
unsigned short vga_get_cursor();
void vga_clear_screen();
void vga_putc(char c);

int vga_print_string(const char * cstring);

#endif // VGA_DRIVER_H_
