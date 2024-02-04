from MotorControlShell import *
import math
import time
import numpy as np


class Robot:
    def __init__(self, port, baudrate):
        self.motor_control = MotorControl(port, baudrate)
        self.motor_list = list()
        self.encoder = pow(2, 15)


    def register_motor(self, motor_id, ratio):
        self.motor_control.check_id(motor_id)
        self.motor_list.append(dict(id=motor_id, ratio=ratio))

    
    def servo_enable(self):
        for motor in self.motor_list:
            self.motor_control.write_servo_state(motor["id"], True)


    def servo_disable(self):
        for motor in self.motor_list:
            self.motor_control.write_servo_state(motor["id"], False)


    def return_home(self):
        for motor in self.motor_list:
            self.motor_control.return_home(motor["id"])
        print("Running return home command ...")
        
        self.running_blocked()
        print("Return home complete!")


    def return_home_opt(self):
        encoder_motor = list()
        encoder_output = list()
        ratio = list()
        for motor in self.motor_list:
            encoder_motor.append(self.motor_control.read_position_motor(motor["id"]))
            eo = self.motor_control.read_position_output(motor["id"])
            encoder_output.append(eo if eo < 16384 else eo - 32767)
            ratio.append(motor["ratio"])
        encoder_motor = np.array(encoder_motor)
        encoder_output = np.array(encoder_output)
        ratio = np.array(ratio)
        offset = (-encoder_output * ratio + encoder_motor) * 2 * math.pi / (ratio * self.encoder)

        self.write_position(offset, np.ones(len(self.motor_list)) * 0.2)
        self.running_blocked()

        self.return_home()
        self.running_blocked()


    def read_position(self):
        pos = list()
        for motor in self.motor_list:
            pos.append(self.encoder_to_rad(self.motor_control.read_position_output(motor["id"])))
        return np.array(pos)
    
    
    def write_position(self, pos, vel):
        # pos: rad, vel: rad/s
        motor_count = len(self.motor_list)
        if motor_count != len(pos) or motor_count != len(vel):
            raise Exception("The number of pos/vel is inconsistent with the number of motors!")
        for i in range(motor_count):
            motor = self.motor_list[i]
            self.motor_control.write_position(motor["id"], int(motor["ratio"] * self.rad_to_encoder(pos[i])), int(vel[i] * motor["ratio"] * 60 / (2 * math.pi)))
        print("Running write position command ...")

        self.running_blocked()
        print("Return home complete!")


    def running_blocked(self):
        while (self.is_running()):
            time.sleep(0.02)


    def is_running (self):
        for motor in self.motor_list:
            if self.motor_control.read_running_state(motor["id"]):
                return True
        return False


    def rad_to_encoder(self, data):
        return self.encoder * data / (2 * math.pi)
    
    
    def encoder_to_rad(self, data):
        return data / self.encoder * 2 * math.pi


if __name__ == "__main__":
    robot = Robot("COM7", 2250000)
    robot.register_motor(56, 51)
    robot.register_motor(53, 101)
    robot.register_motor(54, 51)
    robot.register_motor(26, 51)
    robot.register_motor(24, 51)
    robot.register_motor(23, 101)
    robot.register_motor(25, 51)
    

    pos1 = np.array([0,
                      5.70257358 - 2*np.pi,
                      4.59216324 - 2*np.pi,
                      0.04506069,
                      0.08916263,
                      6.25288919 - 2*np.pi,
                      5.74533329- 2*np.pi])
    
    pos2 = np.array([-np.pi/3,
                      5.70257358 - 2*np.pi,
                      0,
                      0,
                      0,
                      0,
                      0])
    pos3 = np.array([-np.pi/3,
                      0,
                      0,
                      0,
                      0,
                      0,
                      0])
    vel = np.ones(7) * 0.3

    # robot.register_motor(3, 101)
    # pos = np.array([math.pi/3])
    # vel = np.ones(1) * 0.5

    robot.servo_enable()
    print(robot.read_position())

    robot.return_home_opt()
    print(robot.read_position())

    robot.write_position(pos1, vel)
    print(robot.read_position())
    
    robot.write_position(pos2, vel)
    print(robot.read_position())
    
    robot.write_position(pos3, vel)
    print(robot.read_position())
    
    # pos2 = np.array([0, -np.pi/3, np.pi/6, np.pi/6, np.pi/6, np.pi/6, np.pi/6])
    # robot.write_position(pos2, vel)
    # print(robot.read_position())

    # robot.servo_disable()
