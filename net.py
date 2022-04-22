import socket

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client:
    client.connect(("127.0.0.1", 6697))

    # client.send(b"PONG\r\n")
    client.send(b"PASS pass\r\n")

    response = client.recv(512)
    if response != "":
        print(f"Response: {response}")
