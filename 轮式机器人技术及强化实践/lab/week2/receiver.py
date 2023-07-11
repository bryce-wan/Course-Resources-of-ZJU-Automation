import socket
import threading
import json
import matplotlib
import matplotlib.pyplot as plt
import numpy as np
from config import ENDPOINT as _ENDPOINT

# plt.rcParams["figure.figsize"] = [8.0,8.0]
# plt.rcParams["figure.autolayout"] = True
# plt.rcParams['keymap.save'].remove('s')

vel = {
    "x": 0.0,
    "w": 0.0
}

dt = 0.1

pos = {
    "x": 0.0,
    "y": 0.0,
    "theta": 0.0
}

x_traj=[]
y_traj=[]

def receive():
    global vel
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)
    sock.bind(_ENDPOINT)
    while True:
        data, addr = sock.recvfrom(65535)
        data = data.decode()
        vel = json.loads(data)
        # print(vel["x"],vel["w"])

def trans(vel,theta):
    vel_r=np.array([vel['x'],0,vel['w']]).T

    R=np.array([
        [np.cos(theta), -np.sin(theta), 0],
        [np.sin(theta), np.cos(theta), 0],
        [0, 0, 1]])
    
    vel_i=np.linalg.inv(R).dot(vel_r)
    return vel_i

def draw(pos,x_traj,y_traj):
    p1=[pos['x']+5*np.cos(pos['theta']),pos['y']-5*np.sin(pos['theta'])]
    p2=[pos['x']+2*np.cos(pos['theta']+2.5),pos['y']-2*np.sin(pos['theta']+2.5)]
    p3=[pos['x']+2*np.cos(pos['theta']-2.5),pos['y']-2*np.sin(pos['theta']-2.5)]
    
    plt.plot([p1[0], p2[0]], [p1[1], p2[1]], 'k-')
    plt.plot([p2[0], p3[0]], [p2[1], p3[1]], 'k-')
    plt.plot([p3[0], p1[0]], [p3[1], p1[1]], 'k-')

    if len(x_traj) > 0:
        plt.plot(x_traj, y_traj, 'r-')
    print(pos)
    plt.plot(pos['x'],pos['y'],marker='*', color='red')
    plt.xlim(-20, 20)
    plt.ylim(-20, 20)
    plt.pause(dt)
    plt.cla()
    

# def plot_vehicle(x, y, theta, x_traj, y_traj):
    # p1_i = np.array([0.5, 0, 1]).T
    # p2_i = np.array([-0.5, 0.25, 1]).T
    # p3_i = np.array([-0.5, -0.25, 1]).T

    # T = transformation_matrix(x, y, theta)
    # p1 = np.matmul(T, p1_i)
    # p2 = np.matmul(T, p2_i)
    # p3 = np.matmul(T, p3_i)

    # plt.plot([p1[0], p2[0]], [p1[1], p2[1]], 'k-')
    # plt.plot([p2[0], p3[0]], [p2[1], p3[1]], 'k-')
    # plt.plot([p3[0], p1[0]], [p3[1], p1[1]], 'k-')

    # plt.plot(x_traj, y_traj, 'b--')

    # plt.xlim(0, 20)
    # plt.ylim(0, 20)

    # plt.pause(dt)

def calc(pos,vel,dt):
    vel_i=trans(vel,pos['theta'])
    delta_pos=vel_i*dt
    global x_traj,y_traj
    x_traj.append(pos['x'])
    y_traj.append(pos['y'])
    pos['x']=pos['x']+delta_pos[0]
    pos['y']=pos['y']+delta_pos[1]
    pos['theta']=pos['theta']+delta_pos[2]
    # print(delta_pos)
    return pos

if __name__ == "__main__":
    t = threading.Thread(target=receive)
    t.start()
    while True:
        pos = calc(pos,vel,dt)
        # draw(pos,traj,pause_t)
        draw(pos,x_traj,y_traj)




# if __name__ == "__main__":
#     sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
#     sock.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)
#     sock.bind(_ENDPOINT)

#     while True:
#         # data, addr = sock.recvfrom(65535)
#         # string = data.decode()
#         # print("{}:{}".format(addr,string))
#         data, addr = sock.recvfrom(65535)
#         data = data.decode()
#         vel = json.loads(data)
#         print(vel["x"],vel["w"])

