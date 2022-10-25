# https://python-gtk-3-tutorial.readthedocs.io/pt_BR/latest/introduction.html

import gi, sys

gi.require_version("Gtk", "3.0")
from gi.repository import Gtk


class MyWindow(Gtk.Window):
	def __init__(self):
		super().__init__(title=sys.argv[0])
		self.btn = Gtk.Button(label="Close window")
		self.btn.connect("clicked", self.on_button_clicked)
		self.add(self.btn)
	def on_button_clicked(self, widget):
		Gtk.main_quit()


win = MyWindow()
win.show_all()
Gtk.main()