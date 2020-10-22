#ifndef OLED_DRIVER_H
#define OLED_DRIVER_H

void oled_init(void);
int oled_print_char(char c);
int oled_home(void);
int oled_reset(void);
int oled_goto_line(uint8_t line);
int oled_pos(uint8_t line, uint8_t column);
int oled_clear_line(uint8_t line);
void oled_print(char *c);


#endif