# https://python-gtk-3-tutorial.readthedocs.io/pt_BR/latest/introduction.html

import gi, sys
gi.require_version("Gtk", "3.0")
from gi.repository import Gtk

class MyWindow(Gtk.Window):
	def __init__(self):
		super().__init__(title=sys.argv[0])
		self.btn = Gtk.Button(label="Close window")
		self.btn.connect("clicked", self.button_popup)
		self.mbar = Gtk.MenuBar()
		self.f_menu = Gtk.Menu()
		self.file_mi = Gtk.MenuItem(label="File")
		self.quit_mi = Gtk.MenuItem(label="Quit")
		self.quit_mi.connect("activate", Gtk.main_quit)
		self.file_mi.set_submenu(self.f_menu)
		self.f_menu.append(self.quit_mi)
		self.mbar.append(self.file_mi)
		self.tbl = Gtk.Grid()
		self.tbl.set_column_homogeneous(True)
		self.tbl.add(self.mbar)
		self.tbl.attach(self.btn, 0, 1, 1, 1)
		self.add(self.tbl)
		self.connect("destroy", Gtk.main_quit)
		self.show_all()
		Gtk.main()
	def button_popup(self, widget):
		new_f_menu = Gtk.Menu()
		new_quit_mi = Gtk.MenuItem(label="Quit")
		new_quit_mi.connect("activate", Gtk.main_quit)
		new_f_menu.append(new_quit_mi)
		new_f_menu.popup_at_pointer(None)
		new_f_menu.show_all()




win = MyWindow()