# https://python-gtk-3-tutorial.readthedocs.io/pt_BR/latest/introduction.html
import gi, sys
gi.require_version("Gtk", "3.0")
from gi.repository import Gtk

class MyWindow(Gtk.Window):
	def __init__(self):
		super().__init__(title=sys.argv[0])
		self.btn = Gtk.Button(label="Close window")
		self.btn.connect("clicked", Gtk.main_quit)
		self.col_btn = Gtk.ColorButton()
		self.col_btn.connect("color-set", self.col_selected)
		self.tbl = Gtk.Grid()
		self.tbl.set_column_homogeneous(True)
		self.tbl.add(self.col_btn)
		self.tbl.attach(self.btn, 0, 1, 1, 1)
		self.add(self.tbl)
		self.connect("destroy", Gtk.main_quit)
		self.show_all()
		Gtk.main()
	def col_selected(self, widget):
		col = self.col_btn.get_rgba()
		print("red = %d; green = %d; blue = %d" % (col.red*65535, col.green*65535, col.blue*65535))

win = MyWindow()