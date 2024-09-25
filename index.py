import socket
import threading

def handle_client(client_socket):
    # Получаем данные от клиента
    data = client_socket.recv(1024).decode()
    print(f"Received data from client: {data}")
    client_socket.close()

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(("0.0.0.0", 8080))
server.listen(5)
print("Server listening on port 8080")

while True:
    client_socket, addr = server.accept()
    print(f"Accepted connection from {addr}")
    client_handler = threading.Thread(target=handle_client, args=(client_socket,))
    client_handler.start()