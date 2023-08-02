# https://python-gtk-3-tutorial.readthedocs.io/pt_BR/latest/introduction.html
import gi, sys
gi.require_version("Gtk", "3.0")
from gi.repository import Gtk

class MyWindow(Gtk.Window):
	def __init__(self):
		super().__init__(title=sys.argv[0])
		self.btn = Gtk.Button(label="Close window")
		self.btn.connect("clicked", Gtk.main_quit)
		self.fc_btn = Gtk.Button(label="Select file")
		self.fc_btn.connect("clicked", self.save_file)
		self.tbl = Gtk.Grid()
		self.tbl.set_column_homogeneous(True)
		self.tbl.add(self.fc_btn)
		self.tbl.attach(self.btn, 0, 1, 1, 1)
		self.add(self.tbl)
		self.connect("destroy", Gtk.main_quit)
		self.show_all()
		Gtk.main()
	def save_file(self, widget):
		sch = Gtk.FileChooserDialog(title="Save file", parent=None,
			action=Gtk.FileChooserAction.OPEN)
		sch.add_buttons("Ok", Gtk.ResponseType.OK)
		sch.add_buttons("Cancel", Gtk.ResponseType.CANCEL)
		sch.set_default_response(Gtk.ResponseType.OK)
		if sch.run()==Gtk.ResponseType.OK:
			print("%s selected" % sch.get_filename())
		sch.destroy()

win = MyWindow()