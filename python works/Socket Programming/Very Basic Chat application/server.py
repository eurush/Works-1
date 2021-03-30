import socket
import select
import time

class DATA:
    def __init__(self,sockethere, addr, username):
        self.data = []
        self.socket = sockethere
        self.addr = addr
        self.data_len = []
        self.username = username
    def update(self,data):
        self.data.append(data)
        self.data_len.append(len(data))
    def clearall(self):
        self.data = []
        self.data_len = []

HEADER = 1024
HOST = '127.0.0.1'
PORT = 2345
clients_datas = {}
clients_socks =[]
encoding = "utf-8"

def broadcast(serverhere, clienthere, msg):
    for c1 in clients_socks:
        if c1 is not clienthere and c1 is not serverhere:
            c1.send(bytes(msg,encoding))

def talk_to_client(server, clienthere, addr):
    if clienthere not in clients_datas:
        client_username = clienthere.recv(HEADER).decode(encoding)
        clients_datas[clienthere] = DATA(clients_socks,addr,client_username)
        msg = f"new user has joined : username = {client_username}, port = {addr[1]}\n"
        print(msg)
        broadcast(server, clienthere,msg)
    data = clienthere.recv(HEADER).decode(encoding)
    if data == f"{clients_datas[clienthere].username}:> <close>":
        clients_socks.remove(clienthere)
        msg = f"{clients_datas[clienthere].username} has logged out"
        print(msg)
        broadcast(server, clienthere, msg)
    elif data == f"{clients_datas[clienthere].username}:> <clear>":
        clients_datas[clienthere].clearall()
        clienthere.send(bytes("data cleared",encoding))
    elif data == f"{clients_datas[clienthere].username}:> <delete me>":
        del clients_datas[clienthere]
    elif data is not None:
        msg = data
        print(msg)
        broadcast(server, clienthere, msg)
        clients_datas[clienthere].update(data)


with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s1:
    s1.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)
    s1.bind((HOST,PORT))
    s1.listen()
    clients_socks.append(s1)
    while True:
        active_socks, _, error_socks = select.select(clients_socks,[], clients_socks)

        for sockshere in active_socks:
            if sockshere == s1:
                clienthere, addr = s1.accept()
                clients_socks.append(clienthere)
                talk_to_client(s1, clienthere, addr)
                continue
            talk_to_client(s1, sockshere, clients_datas[sockshere].addr)
