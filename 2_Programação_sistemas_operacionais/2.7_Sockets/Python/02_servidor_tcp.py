import socket, struct, sys

def print_client_message(socketCliente):
	length = struct.unpack('i', socketCliente.recv(4))[0]
	mensagem = socketCliente.recv(length).decode()
	print("Mensagem = " + mensagem)
	return mensagem=="sair"

if len(sys.argv) < 2:
	print("Modo de Uso:")
	print("%s PORT_NUM" % sys.argv[0])
	exit(1)

servidorPorta = int(sys.argv[1])
socket_id = socket.socket()
socket_id.bind(('', servidorPorta))
socket_id.listen(10)

end_server_ok = False
while end_server_ok==False:
	(socketCliente, addr) = socket_id.accept()
	print("Conexão do Cliente " + addr[0])	
	end_server_ok = print_client_message(socketCliente)
	socketCliente.close()
print("Fechando servidor")
socket_id.close()