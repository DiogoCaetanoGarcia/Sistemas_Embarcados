# https://python-gtk-3-tutorial.readthedocs.io/pt_BR/latest/introduction.html
import gi, sys
gi.require_version("Gtk", "3.0")
from gi.repository import Gtk

class DialogExample(Gtk.Dialog):
	def __init__(self, parent):
		super().__init__(title="My Dialog", transient_for=parent, flags=0)
		self.add_buttons(Gtk.STOCK_CANCEL, 0, Gtk.STOCK_OK, 1)
		self.show_all()

class MyWindow(Gtk.Window):
	def __init__(self):
		super().__init__(title=sys.argv[0])
		self.btn = Gtk.Button(label="Botão")
		self.btn.connect("clicked", self.open_dialog)
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
	def open_dialog(self, widget):
		dialog = DialogExample(self)
		result = dialog.run()
		print("Return code = %d" % result)
		dialog.destroy()

win = MyWindow()