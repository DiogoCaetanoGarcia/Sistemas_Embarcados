#include <gtk/gtk.h>

void end_program(GtkWidget *wid, gpointer ptr)
{
	gtk_main_quit();
}

void main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);
	GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GtkWidget *btn = gtk_button_new_with_label("Close window");
	g_signal_connect(btn, "clicked", G_CALLBACK(end_program), NULL);
	g_signal_connect(win, "delete_event", G_CALLBACK(end_program), NULL);
	GtkWidget *lbl = gtk_label_new("My label");
	GtkWidget *rad1 = gtk_radio_button_new_with_label(NULL, "Button 1");
	GSList *group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(rad1));
	GtkWidget *rad2 = gtk_radio_button_new_with_label(group, "Button 2");
	GtkObject *adj = gtk_adjustment_new(0, -10, 10, 1, 0, 0);
	GtkWidget *txt = gtk_spin_button_new(GTK_ADJUSTMENT(adj), 0, 0);
	GtkWidget *tab = gtk_table_new(2, 2, TRUE);
	gtk_table_attach_defaults(GTK_TABLE(tab), rad1, 0, 1, 0, 1);
	gtk_table_attach_defaults(GTK_TABLE(tab), rad2, 1, 2, 0, 1);
	gtk_table_attach_defaults(GTK_TABLE(tab), btn, 0, 1, 1, 2);
	gtk_table_attach_defaults(GTK_TABLE(tab), txt, 1, 2, 1, 2);
	gtk_container_add(GTK_CONTAINER(win), tab);
	gtk_widget_show_all(win);
	gtk_main();
}