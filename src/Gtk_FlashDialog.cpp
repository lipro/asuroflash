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
#include "Gtk_FlashDialog.h"

#include <gtkmm/icontheme.h>
#include <sys/stat.h>
#include <string.h>

#define TTYS   0
#define TTYUSB 1

Gtk_FlashDialog::Gtk_FlashDialog()
{
	this->set_title("ASURO Flash Tool");
	this->set_default_size(392, 472);
	this->set_border_width(5);
	this->set_resizable(true); /* TODO: chenge to false */
	this->set_position(Gtk::WIN_POS_CENTER_ALWAYS);

	/* create logo */
	LOGO = new Gtk::Image(Gdk::Pixbuf::create_from_xpm_data(logo_data));
	LOGO->set_alignment(Gtk::ALIGN_CENTER, Gtk::ALIGN_TOP);

	/* create about */
	ABOUT = new Gtk::Label(ASUROAbout);
	ABOUT->set_alignment(Gtk::ALIGN_CENTER, Gtk::ALIGN_TOP);

	/* create port list and entry */
	PORT = new Gtk::ComboBoxText();
	PORT_TEXT = new Gtk::Entry();

	/* create image file browser */
	BROWSE = new Gtk::FileChooserButton("");
	BROWSE_FILTER = new Gtk::FileFilter();
	BROWSE_FILTER->add_mime_type("text/plain");
	BROWSE->set_filter(*BROWSE_FILTER);

	/* create programm button */
	PROGRAMM_ICON = new Gtk::Image(Gtk::Stock::CONNECT, Gtk::ICON_SIZE_BUTTON);
	PROGRAMM = new Gtk::Button("_Programm");
	PROGRAMM->set_image(*PROGRAMM_ICON);
	PROGRAMM->set_sensitive(false);

	/* create about */
	STATUS = new Gtk::Label("");
	STATUS->set_alignment(Gtk::ALIGN_CENTER, Gtk::ALIGN_CENTER);

	/* create process bar */
	PROGRESSBAR = new Gtk::ProgressBar();
	PROGRESSBAR->set_text("0%");

	/* create new text buffer with new section tags */
	TEXT_BUFFER = Gtk::TextBuffer::create();
	TEXT_BUFFER->set_text(LICENSE);
	TEXT_BUFFER->create_tag("normal");

	Glib::RefPtr<Gtk::TextTag> success_tag = TEXT_BUFFER->create_tag("success");
	success_tag->property_foreground() = "darkgreen";
	success_tag->property_weight() = Pango::WEIGHT_BOLD;

	Glib::RefPtr<Gtk::TextTag> warning_tag = TEXT_BUFFER->create_tag("warning");
	warning_tag->property_foreground() = "orange";
	warning_tag->property_weight() = Pango::WEIGHT_BOLD;

	Glib::RefPtr<Gtk::TextTag> error_tag = TEXT_BUFFER->create_tag("error");
	error_tag->property_foreground() = "red";
	error_tag->property_weight() = Pango::WEIGHT_BOLD;

	/* create multiple line text view */
	TEXT = new Gtk::TextView(TEXT_BUFFER);
	TEXT->set_editable(false);

	/* create scrolled text area */
	SCROLLEDTEXT = new Gtk::ScrolledWindow();
	SCROLLEDTEXT->set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_ALWAYS);
	SCROLLEDTEXT->set_shadow_type(Gtk::SHADOW_IN);
	SCROLLEDTEXT->add(*TEXT);

	/* create exit button */
	EXIT_ICON = new Gtk::Image(Gtk::Stock::CLOSE, Gtk::ICON_SIZE_BUTTON);
	EXIT = new Gtk::Button("_Exit");
	EXIT->set_image(*EXIT_ICON);

	/* create and arrange setup area */
	SETTINGS = new Gtk::Table(3, 3);
	SETTINGS->set_col_spacing(0, 5);
	SETTINGS->set_col_spacing(1, 5);
	SETTINGS->set_row_spacing(1, 5);
	SETTINGS->attach(*PORT, 0, 1, 0, 1, Gtk::FILL|Gtk::EXPAND, ~Gtk::FILL);
	SETTINGS->attach(*PORT_TEXT, 0, 1, 1, 2, Gtk::FILL|Gtk::EXPAND, ~Gtk::FILL);
	SETTINGS->attach(*LOGO, 1, 2, 0, 2, Gtk::FILL, ~Gtk::EXPAND);
	SETTINGS->attach(*ABOUT, 2, 3, 0, 2, Gtk::FILL, ~Gtk::EXPAND);
	SETTINGS->attach(*BROWSE, 0, 3, 2, 3, Gtk::FILL|Gtk::EXPAND, ~Gtk::FILL);

	/* create and arrange programm area */
	PROG = new Gtk::HBox(true, 5);
	PROG->pack_end(*PROGRAMM, false, false);

	/* create and arrange abort area */
	ABORT = new Gtk::HBox(true, 5);
	ABORT->pack_end(*EXIT, false, false);

	/* create and setup dialog content */
	MAIN = new Gtk::VBox(false, 5);
	MAIN->pack_start(*SETTINGS, false, false);
	MAIN->pack_start(*PROG, false, false);
	MAIN->pack_start(*STATUS, false, false);
	MAIN->pack_start(*PROGRESSBAR, false, false);
	MAIN->pack_start(*SCROLLEDTEXT, true, true);
	MAIN->pack_start(*ABORT, false, false);

	/* signals connections */
	PORT->signal_changed().connect(sigc::mem_fun(*this, &Gtk_FlashDialog::slotPort));
	PORT_TEXT->signal_changed().connect(sigc::mem_fun(*this, &Gtk_FlashDialog::slotNewPort));
	BROWSE->signal_file_set().connect(sigc::mem_fun(*this, &Gtk_FlashDialog::slotNewFileName));
	PROGRAMM->signal_clicked().connect(sigc::mem_fun(*this, &Gtk_FlashDialog::slotProgramm));
	EXIT->signal_clicked().connect(sigc::ptr_fun(&Gtk::Main::quit));
	TEXT->signal_size_request().connect(sigc::mem_fun(*this, &Gtk_FlashDialog::text_view_size_request));

	Glib::ustring tmp;

	/* prepare *.ini file location */
	tmp = Glib::get_current_dir() + "/AsuroFl.ini";
	strcpy(m_ASUROIniPath,Glib::locale_from_utf8(tmp).c_str());

	/* init ASURO Flash core (parse *.ini file) */
	InitCAsuro();

	m_fileName = m_ASUROfileName;
	m_portName = m_ASUROCOMPort;

	char portName[256];
	int p = 0;

	/* scan ports and sort into ComboBox */
	for (int i = 0; i < 255; i++)
		if (PortScan(portName,i,TTYS)) {
			PORT->append_text(portName);
			/* try to find port from *.ini file in ComboBox */
			if (portName == m_portName) PORT->set_active(p);
			p++;
		}
	for (int i = 0; i < 255; i++)
		if (PortScan(portName,i,TTYUSB)) {
			PORT->append_text(portName);
			/* try to find port from *.ini file in ComboBox */
			if (portName == m_portName) PORT->set_active(p);
			p++;
		}

	/* nothing found --> activate first entry in ComboBox */
	if (PORT->get_active_row_number() == -1) {
		PORT->set_active(0);
	}

	BROWSE->set_filename(m_ASUROfileName);
	if (m_fileName != "") PROGRAMM->set_sensitive(true);

	MAIN->show_all();
	this->add(*MAIN);
}

void Gtk_FlashDialog::slotPort()
{
	this->PORT_TEXT->set_text(this->PORT->get_active_text());
}

void Gtk_FlashDialog::slotNewPort()
{
	m_portName = this->PORT_TEXT->get_text();
	strcpy(m_ASUROCOMPort,Glib::locale_from_utf8(m_portName).c_str());
}

void Gtk_FlashDialog::slotNewFileName()
{
	m_fileName = this->BROWSE->get_filename();
	strcpy(m_ASUROfileName,Glib::locale_from_utf8(m_fileName).c_str());
}

void Gtk_FlashDialog::Programm()
{
	CAsuro::Programm();
	this->PROGRAMM->set_sensitive(true);
}

void Gtk_FlashDialog::slotProgramm()
{
	this->TEXT_BUFFER->set_text("");
	Glib::Thread::create(sigc::mem_fun(*this, &Gtk_FlashDialog::Programm), false);
	this->PROGRAMM->set_sensitive(false);
}

void Gtk_FlashDialog::text_view_size_request(Gtk::Requisition *req)
{
	Gtk::Adjustment *adjustment = this->SCROLLEDTEXT->get_vadjustment();
	adjustment->set_value(adjustment->get_upper());
	this->SCROLLEDTEXT->set_vadjustment(adjustment);
}

void Gtk_FlashDialog::text_buffer_print(Glib::ustring message, Glib::ustring tag) {
	this->TEXT_BUFFER->insert_with_tag(this->TEXT_BUFFER->end(), message, tag);
}

void Gtk_FlashDialog::Progress(unsigned int progress)
{
	char text[5];
	sprintf(text, "%u%%", progress);

	Glib::signal_idle().connect(sigc::bind_return(sigc::bind(
			sigc::mem_fun(*this->PROGRESSBAR, &Gtk::ProgressBar::set_text),
			std::string(text)), false));

	Glib::signal_idle().connect(sigc::bind_return(sigc::bind(
			sigc::mem_fun(*this->PROGRESSBAR, &Gtk::ProgressBar::set_fraction),
			((double)progress / 100.0)), false));
}

void Gtk_FlashDialog::Status(char* text)
{
	this->STATUS->set_text(text);
}

void Gtk_FlashDialog::MessageText(char* text)
{
	m_msg = Glib::ustring(text);
	Glib::signal_idle().connect(sigc::bind_return(sigc::bind(
			sigc::mem_fun(*this, &Gtk_FlashDialog::text_buffer_print),
			m_msg, "normal"), false));
}

void Gtk_FlashDialog::WarningText(char* text)
{
	m_msg = Glib::ustring(text);
	Glib::signal_idle().connect(sigc::bind_return(sigc::bind(
			sigc::mem_fun(*this, &Gtk_FlashDialog::text_buffer_print),
			m_msg, "warning"), false));
}

void Gtk_FlashDialog::SuccessText(char* text)
{
	m_msg = Glib::ustring(text) + "\n";
	Glib::signal_idle().connect(sigc::bind_return(sigc::bind(
			sigc::mem_fun(*this, &Gtk_FlashDialog::text_buffer_print),
			m_msg, "success"), false));
}

void Gtk_FlashDialog::ErrorText(char* text)
{
	m_msg = Glib::ustring(text) + "\n";
	Glib::signal_idle().connect(sigc::bind_return(sigc::bind(
			sigc::mem_fun(*this, &Gtk_FlashDialog::text_buffer_print),
			m_msg, "error"), false));
}

void Gtk_FlashDialog::TimeWait(unsigned int time) // msec
{
	Glib::usleep(time * 1000);
}
