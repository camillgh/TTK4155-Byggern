#ifndef MENU_H
#endif MENU_H

struct menu{
	char *name;
	struct menu *parent;
	struct menu *child[4];

};
