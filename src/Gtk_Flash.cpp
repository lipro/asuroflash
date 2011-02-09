/***************************************************************************
                                 main.cpp
                             -------------------
    begin                : Son Feb 06 10:09:42 CET 2011
    copyright            : (C) 2011 Li-Pro.Net by Stephan Linz
    email                : linz@li-pro.net
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 +   any later version.                                                    *
 ***************************************************************************/

/***************************************************************************
	Ver      date       Author        comment
	--------------------------------------------------------------------------
	1.0   06.02.2011    Stephan Linz  build
 ***************************************************************************/
#include <gtkmm.h>
#include "Gtk_FlashDialog.h"


int main (int argc, char **argv)
{
	Gtk::Main app(argc, argv);
	Glib::thread_init();

	Gtk_FlashDialog dialog;

	dialog.set_icon(Gdk::Pixbuf::create_from_xpm_data(icon_data));
	app.run(dialog);

	return 0;
}
