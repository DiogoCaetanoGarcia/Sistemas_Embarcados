import socket, struct, sys

def print_client_message(socketCliente):
	length = struct.unpack('i', socketCliente.recv(4))[0]
	mensagem = socketCliente.recv(length).decode()
	print("Mensagem = " + mensagem)
	return mensagem=="sair"

if len(sys.argv) < 2:
	print("Modo de Uso:")
	print("%s NOME_SOCKET" % sys.argv[0])
	exit(1)

socket_id = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
socket_id.bind('\0' + sys.argv[1])
socket_id.listen(1)
end_server_ok = False
while end_server_ok==False:
	(socketCliente, addr) = socket_id.accept()
	end_server_ok = print_client_message(socketCliente)
	socketCliente.close()
print("Fechando servidor")
socket_id.close()