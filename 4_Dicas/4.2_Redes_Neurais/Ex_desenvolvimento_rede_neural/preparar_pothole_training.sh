#!/bin/bash

function show_box()
{
	SHOW_BOX_MSG=$1
	SHOW_BOX_L=${#SHOW_BOX_MSG}
	SHOW_BOX_L=$((SHOW_BOX_L+4))
	SHOW_BOX_LINE=""
	for SHOW_BOX_i in $(seq $SHOW_BOX_L)
	do
		SHOW_BOX_LINE=${SHOW_BOX_LINE}"-"
	done
	echo
	echo ${SHOW_BOX_LINE}
	echo \| $SHOW_BOX_MSG \|
	echo ${SHOW_BOX_LINE}
	echo
}

show_box "Instruções para treinar rede Yolo-Tiny v7 para detectar buracos na rua"
show_box "https://learnopencv.com/pothole-detection-using-yolov4-and-darknet/"

show_box "Download de base de dados (2.3 GB!)"
# wget https://learnopencv.s3.us-west-2.amazonaws.com/pothole-dataset.zip

show_box "Unzip da base de dados (2.4 GB)"
# unzip pothole-dataset.zip

show_box "Remover base de dados zipada"
# rm pothole-dataset.zip

show_box "Download da rede YOLO/Darknet"
git clone https://github.com/AlexeyAB/darknet.git

show_box "Copiar rede pré-treinada"
echo "Origem: https://github.com/AlexeyAB/darknet/releases/download/darknet_yolo_v4_pre/yolov4-tiny.conv.29"
cp yolov4-tiny.conv.29 darknet

show_box "Criar train.txt, valid.txt e test.txt "
cp prepare_darknet_image_txt_paths.py darknet/prepare_darknet_image_txt_paths.py
cd darknet
python3 prepare_darknet_image_txt_paths.py
cd ..

show_box "Copiar arquivos para executar treinamento"
cd darknet
mkdir backup
cd backup
mkdir backup_yolov4_tiny
mkdir backup_yolov4_tiny_multi_res
cd ../../
cp pothole.names darknet/build/darknet/x64/data
cp pothole_yolov4_tiny.data darknet/build/darknet/x64/data
cp pothole_yolov4_tiny_multi_res.data darknet/build/darknet/x64/data
cp yolov4-tiny-pothole.cfg darknet/cfg
cp yolov4-tiny-multi-res-pothole.cfg darknet/cfg

show_box "Atualizar Makefile da darknet"
cd darknet
sed -i "s/GPU=0/GPU=1/" Makefile
sed -i "s/CUDNN=0/CUDNN=1/" Makefile
sed -i "s/CUDNN_HALF=0/CUDNN_HALF=1/" Makefile
sed -i "s/OPENCV=0/OPENCV=1/" Makefile
sed -i "s/AVX=0/AVX=1/" Makefile
sed -i "s/OPENMP=0/OPENMP=1/" Makefile
sed -i "s/LIBSO=0/LIBSO=1/" Makefile
cd ..

show_box "Compilar darknet"
cd darknet
make

show_box "Treinamento da rede"
echo "Execute o comando a seguir para calcular os pesos (demora bastante):"
echo "   ./darknet detector train build/darknet/x64/data/pothole_yolov4_tiny.data cfg/yolov4-tiny-pothole.cfg yolov4-tiny.conv.29"
echo
echo "Execute o comando a seguir para avaliar a qualidade da predição:"
echo "   ./darknet detector map build/darknet/x64/data/pothole_test.data cfg/yolov4-tiny-pothole.cfg backup_yolov4_tiny/yolov4-tiny-pothole_final.weights"
echo
echo "Execute o comando a seguir para calcular os pesos usando múltiplas resoluções (demora mais ainda):"
echo "   ./darknet detector train build/darknet/x64/data/pothole_yolov4_tiny_multi_res.data cfg/yolov4-tiny-multi-res-pothole.cfg yolov4-tiny.conv.29"
echo
echo "Execute o comando a seguir para avaliar a qualidade da predição usando múltiplas resoluções:"
echo "   ./darknet detector map build/darknet/x64/data/pothole_test.data cfg/yolov4-tiny-multi-res-pothole.cfg backup_yolov4_tiny_multi_res/yolov4-tiny-multi-res-pothole_final.weights"
echo