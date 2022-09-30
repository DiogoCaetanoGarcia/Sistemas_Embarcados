import socket, struct, sys

if len(sys.argv) < 3:
	print("Modo de Uso:")
	print("%s NOME_SOCKET MSG" % sys.argv[0])
	exit(1)

socket_name = sys.argv[1]
mensagem    = sys.argv[2]

socket_id = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
socket_id.connect("\0" + socket_name)
length = int(len(mensagem))
socket_id.send(struct.pack('i',length))
socket_id.send(mensagem.encode('utf-8'))
socket_id.close()