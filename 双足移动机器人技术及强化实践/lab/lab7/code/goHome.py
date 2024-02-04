from Robot import Robot


if __name__ == '__main__':
    # 打开设备管理器确定连接的COM口，linux和mac只要选择对应串口就行，需要根据具体的串口进行更改，但是波特率不要改
    r = Robot(com='COM6', baud=250000)
    # 连接到真实机器人
    r.connect()
    # 使用该函数可以使机械臂回到零位
    r.go_home()
