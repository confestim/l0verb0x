import socket

HOST = '0.0.0.0'
PORT = 8420
dataList = []

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    conn, addr = s.accept()
    
    with conn:
        print('Connected by', addr)
        while True:
            data = conn.recv(1024)
            dataList.append(data.decode('utf-8').replace("\n", ""))
            if not data:
                conn.sendall("Disconnected".encode("utf-8"))
                break
            conn.sendall(data)
            print(dataList)
