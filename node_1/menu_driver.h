#ifndef MENU_DRIVER_H_
#define MENU_DRIVER_H_



typedef struct menu{
	char *name;
	struct menu *parent;
	struct menu *children[4];
}menu;

int show_menu(void);
void menu_init(void);
void navigate_menu(joystick_position position);
void update_currentmenu(void);

menu current_menu;

#endif