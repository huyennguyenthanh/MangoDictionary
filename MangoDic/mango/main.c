#include <stdio.h>
#include <stdlib.h>
#include "gtk/gtk.h"
#include "main.h"
#include "btree.h"
#include "giao_dien.h"
#include "init.h"


//int main(int argc,int *argv[])
int main(int argc,char *argv[])
{
	btinit();
	gtk_init(&argc, &argv);
	init();
	load_giao_dien();
	load_dialog();

	gtk_main();


}
