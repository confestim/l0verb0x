import socket
import time 

print("What message do you want to send? (14 chars)")
message = input()
HOST = '0.0.0.0'
PORT = 1337
dataList = []
print(f"Server started at {PORT}")

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    conn, addr = s.accept()
    
    while True:

        try:
            with conn:
                print('Connected by', addr)
                data = conn.recv(1024)
                dataList.append(data.decode('utf-8').replace("\n", ""))
                if not data:
                   conn.sendall("Disconnected".encode("utf-8"))
                   break
                conn.sendall(f"{message}".encode("utf-8"))
                print(dataList)

        except OSError:
            print("Provide me another message?")
            message = input()
            s.close()
            s = socket.socket()
            s.bind((HOST, PORT))
            s.listen()
            conn, addr = s.accept()
            time.sleep(3600)
            print("server started again")
            continue

