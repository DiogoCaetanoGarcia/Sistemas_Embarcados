# https://python-gtk-3-tutorial.readthedocs.io/pt_BR/latest/introduction.html

import gi, sys

gi.require_version("Gtk", "3.0")
from gi.repository import Gtk


class MyWindow(Gtk.Window):
	def __init__(self):
		super().__init__(title=sys.argv[0])
		self.btn = Gtk.Button(label="Close window")
		self.btn.connect("clicked", Gtk.main_quit)
		self.ls = Gtk.ListStore(int, str)
		self.ls.append([0, "Option 1"])
		self.ls.append([1, "Option 2"])
		self.ls.append([2, "Option 3"])
		self.tv = Gtk.TreeView(model=self.ls)
		crp = Gtk.CellRendererPixbuf()
		crp.props.icon_name = 'selection-checked'
		self.tv.append_column(Gtk.TreeViewColumn("Icon", crp))
		self.tv.append_column(Gtk.TreeViewColumn("Option", Gtk.CellRendererText(), text=1))
		self.tbl = Gtk.Grid()
		self.tbl.set_column_homogeneous(True)
		self.tbl.add(self.tv)
		self.tbl.attach(self.btn, 0, 1, 1, 1)
		self.add(self.tbl)
		self.connect("destroy", Gtk.main_quit)
		self.show_all()
		Gtk.main()

win = MyWindow()