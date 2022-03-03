import socket 

sock = socket.socket()

sock.connect(("127.0.0.1", 5566))
sock.send(b"download")

print(sock.recv(1024)) 