#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/stat.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sistemas Embarcados");
MODULE_DESCRIPTION("Ola Linux Kernel Module!");

// Variáveis globais usadas como parametros de entrada.
// Este modulo do kernel vai ser linkado com outros modulos,
// e estas variaveis estarao disponiveis (veja o arquivo /proc/kallsyms).
// Sendo assim, use nomes que provavelmente nao serao usados
// em outros lugares. Aqui, usei o prefixo "hello_" para evitar este problema.
static int hello_int = 0;
static char *hello_str  = "Bla bla bla";

// module_param(foo, int, 0000)
//    1o parametro: nome
//    2o parametro: tipo
//    3o parametro: bits de permissao no sistema de arquivos sysfs

module_param(hello_int, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(hello_int, "Um inteiro de entrada para o modulo");
module_param(hello_str, charp, 0000);
MODULE_PARM_DESC(hello_str, "Uma string de entrada para o modulo");

//static int __init hello_init(void)
int hello_init(void)
{
	printk(KERN_INFO "Hello World, hello_int = %d, hello_str[] = %s\n", hello_int, hello_str);
	return 0;
}

//static void __exit hello_exit(void)
void hello_exit(void)
{
	pr_alert("Goodbye World!\n");
}
module_init(hello_init);
module_exit(hello_exit);
