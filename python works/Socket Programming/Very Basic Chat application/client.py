import socket
import sys
import errno

HEADER = 1024
HOST = '127.0.0.1'
PORT = 2345
encoding = "utf-8"

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s1:
    s1.connect((HOST, PORT))
    s1.setblocking(False)
    username = input("username : ")
    s1.send(bytes(username, encoding))
    while True:
        msg = input(f"{username}:> ")
        if len(msg) != 0 :
            s1.send(bytes(f"{username}:> " + msg, encoding))
            if msg == '<close>':
                sys.exit()
        try:
            while True:
                data = s1.recv(HEADER).decode(encoding)
                if data is not None:
                    print(f"{data}")

        except IOError as e:
            if e.errno != errno.EAGAIN and e.errno != errno.EWOULDBLOCK:
                print(f"Some reading error : {str(e)}")
                sys.exit()
            continue

        except Exception as  e:
            print(f"General error : {e}")
            sys.exit()
