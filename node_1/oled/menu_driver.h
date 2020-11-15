#ifndef MENU_DRIVER_H_
#define MENU_DRIVER_H_



typedef struct menu{
	char *name;
	struct menu *parent;
	struct menu *children[4];
}menu;

int show_menu(void);
void menu_init(void);
void navigate_menu(int button_l, int button_r);
void update_currentmenu(void);
uint8_t game_started(void);

uint8_t game_status;

menu current_menu;

#endif