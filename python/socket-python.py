import socket
import threading


def main():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect(('www.sina.com.cn', 80))
    s.send(b'GET / HTTP/1.1\r\nHost: www.sina.com.cn\r\nConnection: close\r\n\r\n')
    buffer = []
    while True:
        recv = s.recv(1024)
        if recv:
            buffer.append(recv)
        else:
            break
    data = b"".join(buffer)
    print (data)
    header, html = data.split(b'\r\n\r\n', 1)
    print (header.decode('utf-8'))
    s.close()


def handle_socket(sock, addr):
    print("accept the socket from %s:%s" % (addr))
    sock.send("Welcome to tcp.\n")
    while True:
        data = sock.recv(1024)
        if not data or data.decode("utf-8") == 'exit':
            break
        sock.send("Hello %s" % data.decode("utf-8").encode("utf-8"))
    sock.close()
    print ("close the socket from %s:%s.\n" % (addr))


def server_socket():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind(("127.0.0.1", 9998))
    s.listen(5)
    print("waiting to listen port 9999")
    while True:
        sock, addr = s.accept()
        t = threading.Thread(target=handle_socket, args=(sock, addr))
        t.start()


if __name__ == '__main__':
    server_socket()
