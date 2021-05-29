#include <gtk/gtk.h>

// Variável global para
// contar quantas vezes
// um dos botões foi pressionado
int count = 0;

void end_program(GtkWidget *wid, gpointer ptr)
{
	gtk_main_quit();
}

void count_button(GtkWidget *wid, gpointer ptr)
{
	char buffer[30];
	// Incrementa contagem do botão
	count++;
	// Escreve resultado numa string
	sprintf(buffer, "Button pressed %d times", count);
	// Atualiza resultado no
	// 'label' da janela
	gtk_label_set_text(GTK_LABEL(ptr), buffer);
}

void main(int argc, char *argv[])
{
	gtk_init(&argc, &argv);
	GtkWidget *win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GtkWidget *btn = gtk_button_new_with_label("Close window");
	g_signal_connect(btn, "clicked", G_CALLBACK(end_program),
	NULL);
	g_signal_connect(win, "delete_event", G_CALLBACK(end_program),
	NULL);
	GtkWidget *lbl = gtk_label_new("My label");
	// Adicionar um botão que conta
	// quantas vezes foi pressionado
	// via a função count_button()
	GtkWidget *btn2 = gtk_button_new_with_label("Count button");
	g_signal_connect(btn2, "clicked", G_CALLBACK(count_button), lbl);
	GtkWidget *box = gtk_vbox_new(FALSE, 5);
	gtk_box_pack_start(GTK_BOX(box), btn2, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(box), lbl, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(box), btn, TRUE, TRUE, 0);
	gtk_container_add(GTK_CONTAINER(win), box);
	gtk_widget_show_all(win);
	gtk_main();
}