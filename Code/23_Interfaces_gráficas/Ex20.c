#include <gtk/gtk.h>

void end_program(GtkWidget *wid, gpointer ptr)
{
	gtk_main_quit();
}

static void save_file(GtkWidget *btn, gpointer ptr)
{
	GtkWidget *sch = gtk_file_chooser_dialog_new("Save file",
	GTK_WINDOW(ptr), GTK_FILE_CHOOSER_ACTION_SAVE, "Cancel", 0, "OK", 1, NULL);
	if(gtk_dialog_run(GTK_DIALOG(sch)) == 1)
	{
		printf("%s selected\n", gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(sch)));
	}
	gtk_widget_destroy(sch);
}

void main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);
	GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GtkWidget *btn = gtk_button_new_with_label("Close window");
	g_signal_connect(btn, "clicked", G_CALLBACK(end_program), NULL);
	g_signal_connect(win, "delete_event", G_CALLBACK(end_program), NULL);
	GtkWidget *vbox = gtk_vbox_new(FALSE, 5);
	gtk_container_add(GTK_CONTAINER(win), vbox);
	GtkWidget *fc_btn = gtk_button_new_with_label("Select file");
	g_signal_connect(fc_btn, "clicked", G_CALLBACK(save_file), win);
	gtk_box_pack_start(GTK_BOX(vbox), fc_btn, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), btn, TRUE, TRUE, 0);
	gtk_widget_show_all(win);
	gtk_main();
}