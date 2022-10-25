# https://python-gtk-3-tutorial.readthedocs.io/pt_BR/latest/introduction.html

import gi, sys

gi.require_version("Gtk", "3.0")
from gi.repository import Gtk


class MyWindow(Gtk.Window):
	def __init__(self):
		super().__init__(title=sys.argv[0])
		self.adj = Gtk.Adjustment(upper=10, lower=-10, step_increment=1, page_increment=0)
		self.txt = Gtk.SpinButton()
		self.txt.set_adjustment(self.adj)
		self.btn = Gtk.Button(label="Close window")
		self.btn.connect("clicked", Gtk.main_quit)
		self.rad1 = Gtk.RadioButton(label="Button 1")
		self.rad2 = Gtk.RadioButton.new_from_widget(self.rad1)
		self.rad2.set_label("Button 2")
		self.tbl = Gtk.Grid()
		self.tbl.set_column_homogeneous(True)
		self.tbl.add(self.rad1)
		self.tbl.attach(self.rad2, 1, 0, 1, 1)
		self.tbl.attach(self.btn, 0, 1, 1, 1)
		self.tbl.attach(self.txt, 1, 1, 1, 1)
		self.add(self.tbl)
		self.connect("destroy", Gtk.main_quit)
		self.show_all()
		Gtk.main()
	def check_toggled(self, widget):
		print("The state of the button is %d" % self.chk.get_active())

win = MyWindow()