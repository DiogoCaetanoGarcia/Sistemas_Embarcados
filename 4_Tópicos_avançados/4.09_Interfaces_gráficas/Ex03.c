#include <gtk/gtk.h>

void end_program(GtkWidget *wid, gpointer ptr)
{
	// Para de executar o
	// loop principal
	gtk_main_quit();
}

void main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);
	GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GtkWidget *btn = gtk_button_new_with_label("Close window");
	// Conecta o clique do botão
	// à execução da função
	// end_program()
	g_signal_connect(btn, "clicked", G_CALLBACK(end_program),
	NULL);
	gtk_container_add(GTK_CONTAINER(win), btn);
	gtk_widget_show_all(win);
	gtk_main();
}