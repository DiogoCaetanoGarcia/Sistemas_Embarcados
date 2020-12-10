// Baseado em https://docs.opencv.org/master/db/df5/tutorial_linux_gcc_cmake.html

#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("Modo de uso: %s Nome_Imagem\n",
			argv[0]);
		return -1;
	}
	// Ler imagem e guardar em um objeto
	// da classe 'Mat'
	Mat image;
	image = imread(argv[1]);
	if (!image.data)
	{
		printf("Imagem não-encontrada\n");
		return -1;
	}
	// Criar janela
	namedWindow(argv[1], WINDOW_AUTOSIZE);
	// Mostrar imagem na janela
	imshow(argv[1], image);
	// Aguardar usuário pressionar
	// algum botão
	waitKey(0);
	return 0;
}