import socket, struct, sys

def build_get_query(host, page):
	query = "GET %s HTTP/1.0\r\nHost: %s\r\nUser-Agent: HTMLGET 1.1\r\nAccept: */*\r\n\r\n" % (page, host);
	return query

if len(sys.argv) < 3:
	print("Modo de Uso:")
	print("%s host pagina" % sys.argv[0])
	exit(-1)

host = sys.argv[1]
page = sys.argv[2]
get_req = build_get_query(host, page)
print("Pedido HTTP:")
print("-"*40)
print(get_req)
print("-"*40)

socket_id = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socket_id.connect((host, 80))
socket_id.send(get_req.encode('utf-8'))

print("Recebendo o resultado HTML e o escrevendo no arquivo 'saida.html'...")
fp  = open("saida.html", "w")
buf = socket_id.recv(1024).decode("utf-8")
while(buf.find("\r\n\r\n")==-1):
	buf = socket_id.recv(1024).decode("utf-8")
buf = buf[buf.find("\r\n\r\n")+4:]
fp.write(buf)
while(len(buf)):
	fp.write(buf)
	buf = socket_id.recv(1024).decode("utf-8")
socket_id.close()
fp.close()