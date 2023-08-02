#include <string>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <opencv2/opencv.hpp>
using namespace std;

cv::Mat input_img_process(cv::Mat img, int fator_upscale);
tesseract::TessBaseAPI *config_tesseract(cv::Mat img);
void write_tesseract_results(tesseract::TessBaseAPI *ocr);

int main(int argc, char* argv[])
{
	if(argc<2)
	{
		cout << "Indique o caminho da imagem a ser analisada.\n";
		return -1;
	}
	tesseract::TessBaseAPI *ocr;
	int fator_upscale = 3;
	cv::Mat img = input_img_process(
		cv::imread(argv[1], cv::IMREAD_COLOR),
		fator_upscale);
	ocr = config_tesseract(img);
	ocr->Recognize(0); // Executa o reconhecimento de caracteres
	write_tesseract_results(ocr);
	ocr->End(); // Libera a memória de uso do Tesseract
	return 0;
}

// Para a imagem de entrada:
//    - Converte a imagem para tons de cinza
//    - Muda a resolução da imagem pelo fator 'fator_upscale'
cv::Mat input_img_process(cv::Mat img, int fator_upscale)
{
	cv::Mat im_gray, im_gray_resized;
	cv::cvtColor(img, im_gray, cv::COLOR_BGR2GRAY);
	cv::resize(im_gray,
		im_gray_resized,
		cv::Size(im_gray.cols*fator_upscale, im_gray.rows*fator_upscale),
		cv::INTER_LANCZOS4);
	return im_gray_resized;
}

// Configura o Tesseract:
//    - Usa redes neurais LSTM (tesseract::OEM_LSTM_ONLY)
//    - Procura o máximo de textos esparsos na imagem (tesseract::PSM_SPARSE_TEXT)
//    - Usa a língua inglesa a partir do dicionário em './tessdata_best'
//    - Procura somente os caracteres "0123456789qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM"
//    - Define resolução da imagem de entrada em 300 dpi
tesseract::TessBaseAPI *config_tesseract(cv::Mat img)
{
	tesseract::TessBaseAPI *ocr = new tesseract::TessBaseAPI();
	ocr->Init("./tessdata_best", "eng", tesseract::OEM_LSTM_ONLY);
	ocr->SetPageSegMode(tesseract::PSM_SPARSE_TEXT);
	ocr->SetVariable("tessedit_char_whitelist", 
		"0123456789qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM");
	ocr->SetImage(img.data,
		img.cols,
		img.rows,
		1,
		img.step);
	ocr->SetSourceResolution(300);
	return ocr;
}

// Para cada uma das detecções do Tesseract:
//    - Escreve qual foi a palavra detectada,
//    - Escreve qual foi o valor de confiança e
//    - Escreve as coordenadas XY da caixa onde o texto foi detectado
void write_tesseract_results(tesseract::TessBaseAPI *ocr)
{
	tesseract::ResultIterator* ri = ocr->GetIterator();
	tesseract::PageIteratorLevel level = tesseract::RIL_WORD;
 	if(ri != 0)
 	{
 		do
 		{
 			const char* word = ri->GetUTF8Text(level);
			float conf = ri->Confidence(level);
			int x1, y1, x2, y2;
			ri->BoundingBox(level, &x1, &y1, &x2, &y2);
			printf("Palavra: '%s'\nConfiança: %.2f\nBoundingBox: (%d-%d,%d-%d)\n\n",
				word, conf, x1, x2, y1, y2);
			delete[] word;
		} while(ri->Next(level));
 	}
}
