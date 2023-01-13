# https://python-gtk-3-tutorial.readthedocs.io/pt_BR/latest/introduction.html
import gi
gi.require_version("Gtk", "3.0")
from gi.repository import Gtk

win = Gtk.Window()
win.show_all()
Gtk.main()