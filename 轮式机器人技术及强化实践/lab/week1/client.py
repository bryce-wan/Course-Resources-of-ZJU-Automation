from socket import socket,  AF_INET, SOCK_STREAM

def main():
    serve=socket(family=AF_INET,type=SOCK_STREAM)
    serve.bind(('127.0.0.1', 6739))
    serve.listen()
    print("start connection.")

    tick=True
    while(tick):
        client,addr=serve.accept()
        print(str(addr)+"connected to the server!")
        print(client.recv(1024).decode('utf-8'))
        client.close()

if __name__== '__main__':
    main()
    print('server closed.')

