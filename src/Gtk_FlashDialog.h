/*
 * Gtk_FlashDialog
 * This file is part of ASURO Flash Tool
 *
 * Copyright (C) 2011 Li-Pro.Net, Stephan Linz <linz@li-pro.net>
 *
 * inspirit by Pavels ASURO Tools (http://gna.org/projects/asuro-tools/)
 * Copyright (C) 2006 - Pavel Rojtberg
 *
 * Asuro Flash Tool is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Asuro Flash Tool is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Asuro Flash Tool; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 */

#ifndef GTK_FLASHDIALOG_H
#define GTK_FLASHDIALOG_H

#include <gtkmm.h>

#include "Picture.h"
#include "Asuro.h"

class Gtk_FlashDialog: public Gtk::Window, public CAsuro
{
	public:
		Gtk_FlashDialog();
		void Status(char* text);
		void MessageText(char* text);
		void WarningText(char* text);
		void SuccessText(char* text);
		void ErrorText(char* text);
		void Progress(unsigned int progress);
		void Programm();
		void TimeWait(unsigned int time); // msec
	protected:
		Gtk::VBox *MAIN;
		Gtk::HBox *PROG;
		Gtk::HBox *ABORT;
		Gtk::Table *SETTINGS;
		Gtk::Image *LOGO;
		Gtk::Label *ABOUT;
		Gtk::ComboBoxText *PORT;
		Gtk::Entry *PORT_TEXT;
		Gtk::FileChooserButton *BROWSE;
		Gtk::FileFilter *BROWSE_FILTER;
		Gtk::Image *PROGCANCEL_ICON;
		Gtk::Image *PROGRAMM_ICON;
		Gtk::Button *PROGRAMM;
		Gtk::Label *STATUS;
		Gtk::ProgressBar *PROGRESSBAR;
		Glib::RefPtr<Gtk::TextBuffer> TEXT_BUFFER;
		Gtk::TextView *TEXT;
		Gtk::ScrolledWindow *SCROLLEDTEXT;
		Gtk::Image *EXIT_ICON;
		Gtk::Button *EXIT;
		Glib::ustring m_fileName, m_portName, m_msg;
		void slotPort();
		void slotNewPort();
		void slotNewFileName();
		void slotProgramm();
		void text_view_size_request(Gtk::Requisition *req);
		void text_buffer_print(Glib::ustring message, Glib::ustring tag);
};

#endif /* GTK_FLASHDIALOG_H */
