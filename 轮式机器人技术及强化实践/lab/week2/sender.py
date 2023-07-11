import socket
import json
from config import ENDPOINT as _ENDPOINT

vel = {
        "x":0.0, # m/s
        "w":0.0, # rad/s
        }

if __name__ == "__main__":
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    def main1():
        while True:
            vel = {
            "x":0.0, # m/s
            "w":0.0, # rad/s
            }
            data = json.dumps(vel)
            print(data)
            sock.sendto(data.encode('utf-8'), _ENDPOINT)
    
    def main2():
        from pynput.keyboard import Key, Listener
  
        def on_press(key):
            if hasattr(key,"name"):
                if(key==Key.down):
                    vel['x']=vel['x']-1.0
                    vel['w']=vel['w']+0.0 
                elif(key==Key.up):
                    vel['x']=vel['x']+1.0
                    vel['w']=vel['w']+0.0 
                elif(key==Key.left):
                    vel['x']=vel['x']+0.0
                    vel['w']=vel['w']-1.0 
                elif(key==Key.right):
                    vel['x']=vel['x']+0.0
                    vel['w']=vel['w']+1.0  
                data = json.dumps(vel)
                # print(data)
                sock.sendto(data.encode('utf-8'), _ENDPOINT)
            else:
                pass
        with Listener(on_press=on_press) as listener:
            listener.join()
    # main1()
    main2()