# https://python-gtk-3-tutorial.readthedocs.io/pt_BR/latest/introduction.html
import gi, sys
gi.require_version("Gtk", "3.0")
from gi.repository import Gtk

class MyWindow(Gtk.Window):
	def __init__(self):
		super().__init__(title=sys.argv[0])
		self.lbl = Gtk.Label(label="My label")
		self.adj = Gtk.Adjustment(upper=10, lower=-10, step_increment=1, page_increment=0)
		self.txt = Gtk.SpinButton()
		self.txt.set_adjustment(self.adj)
		self.btn = Gtk.Button(label="Close window")
		self.btn.connect("clicked", Gtk.main_quit)
		self.btn2 = Gtk.Button(label="Copy button")
		self.btn2.connect("clicked", self.copy_text)
		self.tbl = Gtk.Grid()
		self.tbl.set_column_homogeneous(True)
		self.tbl.add(self.lbl)
		self.tbl.attach(self.btn2, 1, 0, 1, 1)
		self.tbl.attach(self.btn,  0, 1, 1, 1)
		self.tbl.attach(self.txt,  1, 1, 1, 1)
		self.add(self.tbl)
		self.connect("destroy", Gtk.main_quit)
		self.show_all()
		Gtk.main()
	def copy_text(self, widget):
		self.lbl.set_text("%d" % self.txt.get_value())

win = MyWindow()