#include <gtk/gtk.h>

void end_program(GtkWidget *wid, gpointer ptr)
{
	gtk_main_quit();
}

void open_dialog(GtkWidget *wid, gpointer ptr)
{
	// Abrir caixa de diálogo
	GtkWidget *dlg = gtk_dialog_new_with_buttons("My dialog",
		GTK_WINDOW(ptr), GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
		"Cancel", 0, "OK", 1, NULL);
	int result = gtk_dialog_run(GTK_DIALOG(dlg));
	gtk_widget_destroy(dlg);
	// Mostrar no terminal o resultado
	// escolhido pelo usuário
	printf("Return code = %d\n", result);
}

void main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);
	GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GtkWidget *btn = gtk_button_new_with_label("Botão");
	g_signal_connect(btn, "clicked", G_CALLBACK(open_dialog), NULL);
	g_signal_connect(win, "delete_event", G_CALLBACK(end_program), NULL);
	GtkWidget *mbar = gtk_menu_bar_new();
	GtkWidget *vbox = gtk_vbox_new(FALSE, 5);
	gtk_box_pack_start(GTK_BOX(vbox), mbar, TRUE, TRUE, 0);
	gtk_container_add(GTK_CONTAINER(win), vbox);
	GtkWidget *file_mi = gtk_menu_item_new_with_label("File");
	gtk_menu_shell_append(GTK_MENU_SHELL(mbar), file_mi);
	GtkWidget *f_menu = gtk_menu_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_mi), f_menu);
	GtkWidget *quit_mi = gtk_menu_item_new_with_label("Quit");
	gtk_menu_shell_append(GTK_MENU_SHELL(f_menu), quit_mi);
	g_signal_connect(quit_mi, "activate", G_CALLBACK(end_program), NULL);
	gtk_box_pack_start(GTK_BOX(vbox), btn, TRUE, TRUE, 0);
	gtk_widget_show_all(win);
	gtk_main();
}