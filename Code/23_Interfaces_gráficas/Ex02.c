#include <gtk/gtk.h>

void main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);
	GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	// Criar nova botão
	GtkWidget *btn = gtk_button_new_with_label("Close window");
	// Adicionar botão à janela
	gtk_container_add(GTK_CONTAINER(win), btn);
	// Mostrar janela e tudo aquilo
	// que a janela conter
	gtk_widget_show_all(win);
	gtk_main();
}