# https://python-gtk-3-tutorial.readthedocs.io/pt_BR/latest/introduction.html

import gi, sys

gi.require_version("Gtk", "3.0")
from gi.repository import Gtk


class MyWindow(Gtk.Window):
	def __init__(self):
		super().__init__(title=sys.argv[0])
		self.btn = Gtk.Button(label="Close window")
		self.btn.connect("clicked", Gtk.main_quit)
		self.rad1 = Gtk.RadioButton(label="Button 1")
		self.rad2 = Gtk.RadioButton.new_from_widget(self.rad1)
		self.rad2.set_label("Button 2")
		self.comb = Gtk.ComboBoxText()
		self.comb.set_entry_text_column(0)
		self.comb.append_text("Option 1")
		self.comb.append_text("Option 2")
		self.comb.append_text("Option 3")
		self.comb.set_active(0)
		self.comb.connect("changed", self.combo_changed)
		self.tbl = Gtk.Grid()
		self.tbl.set_column_homogeneous(True)
		self.tbl.add(self.rad1)
		self.tbl.attach(self.rad2, 1, 0, 1, 1)
		self.tbl.attach(self.btn, 0, 1, 1, 1)
		self.tbl.attach(self.comb, 1, 1, 1, 1)
		self.add(self.tbl)
		self.connect("destroy", Gtk.main_quit)
		self.show_all()
		Gtk.main()
	def combo_changed(self, widget):
		print("O valor do combo é: posição %d (opção '%s')" %
			(self.comb.get_active(), self.comb.get_active_text()))

win = MyWindow()