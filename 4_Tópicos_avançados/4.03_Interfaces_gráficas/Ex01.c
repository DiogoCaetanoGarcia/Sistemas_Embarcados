#include <gtk/gtk.h>

int main(int argc, char *argv[])
{
	// Inicializar o GTK
	gtk_init(&argc, &argv);
	// Criar nova janela
	GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	// Mostrar nova janela
	gtk_widget_show(win);
	// Rodar loop principal
	gtk_main();
	return 0;
}