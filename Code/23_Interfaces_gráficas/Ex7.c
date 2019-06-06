#include <gtk/gtk.h>

int count = 0;

void end_program (GtkWidget *wid, gpointer ptr)
{
	gtk_main_quit ();
}

void count_button (GtkWidget *wid, gpointer ptr)
{
	char buffer[30];
	count++;
	sprintf (buffer, "Button pressed %d times", count);
	gtk_label_set_text (GTK_LABEL (ptr), buffer);
}

void main (int argc, char *argv[])
{
	gtk_init (&argc, &argv);
	GtkWidget *win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	GtkWidget *btn = gtk_button_new_with_label ("Close window");
	g_signal_connect (btn, "clicked", G_CALLBACK (end_program),
	NULL);
	g_signal_connect (win, "delete_event", G_CALLBACK (end_program),
	NULL);
	GtkWidget *lbl = gtk_label_new ("My label");
	GtkWidget *btn2 = gtk_button_new_with_label ("Count button");
	g_signal_connect (btn2, "clicked", G_CALLBACK (count_button),
	lbl);
	GtkWidget *tbl = gtk_table_new (2, 2, TRUE);
	gtk_table_attach_defaults (GTK_TABLE (tbl), lbl, 0, 1, 0, 1);
	gtk_table_attach_defaults (GTK_TABLE (tbl), btn2, 1, 2, 0, 1);
	gtk_table_attach_defaults (GTK_TABLE (tbl), btn, 0, 2, 1, 2);
	gtk_container_add (GTK_CONTAINER (win), tbl);
	gtk_widget_show_all (win);
	gtk_main ();
}