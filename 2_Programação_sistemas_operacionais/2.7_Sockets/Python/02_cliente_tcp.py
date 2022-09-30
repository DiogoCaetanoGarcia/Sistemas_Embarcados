import socket, struct, sys

if len(sys.argv) < 4:
	print("Modo de Uso:")
	print("%s SERVER_IP SERVER_PORT MSG" % sys.argv[0])
	exit(1)

IP_Servidor   = sys.argv[1]
servidorPorta = int(sys.argv[2])
mensagem      = sys.argv[3]

socket_id = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socket_id.connect((IP_Servidor, servidorPorta))
length = int(len(mensagem))
socket_id.send(struct.pack('i',length))
socket_id.send(mensagem.encode('utf-8'))
socket_id.close()