# https://python-gtk-3-tutorial.readthedocs.io/pt_BR/latest/introduction.html
import gi, sys
gi.require_version("Gtk", "3.0")
from gi.repository import Gtk

class MyWindow(Gtk.Window):
	def __init__(self):
		super().__init__(title=sys.argv[0])
		self.btn = Gtk.Button(label="Close window")
		self.btn.connect("clicked", Gtk.main_quit)
		self.fnt_btn = Gtk.FontButton()
		self.fnt_btn.connect("font-set", self.fnt_selected)
		self.tbl = Gtk.Grid()
		self.tbl.set_column_homogeneous(True)
		self.tbl.add(self.fnt_btn)
		self.tbl.attach(self.btn, 0, 1, 1, 1)
		self.add(self.tbl)
		self.connect("destroy", Gtk.main_quit)
		self.show_all()
		Gtk.main()
	def fnt_selected(self, widget):
		print("font = " + self.fnt_btn.get_font_name())

win = MyWindow()