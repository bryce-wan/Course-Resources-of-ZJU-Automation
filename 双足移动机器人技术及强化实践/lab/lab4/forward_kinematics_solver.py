import numpy as np
import math


def solve(T):
    x = np.arctan2(-T[1, 2], T[2, 2])/np.pi*180
    y = np.arcsin(T[0, 2])/np.pi*180
    z = np.arctan2(-T[0, 1], T[0, 0])/np.pi*180
    euler = np.array([x, y, z])
    return euler

# get the transformation matrix of the i-th joint with DH parameters


def DH2T(a, alpha, d, theta):
    return np.array([[np.cos(theta), -np.cos(alpha) * np.sin(theta), np.sin(alpha) * np.sin(theta), a * np.cos(theta)],
                    [np.sin(theta), np.cos(alpha) * np.cos(theta), -
                     np.sin(alpha) * np.cos(theta), a * np.sin(theta)],
                    [0, np.sin(alpha), np.cos(alpha), d],
                    [0, 0, 0, 1]])


# get the final transformation matrix of the end effector
def getT(a, alpha, d, theta):
    T = np.eye(4)
    for i in range(len(a)):
        tmp = DH2T(a[i], alpha[i], d[i], theta[i])
        T = T @ tmp
    return T


if __name__ == "__main__":
    theta_list = [np.array([np.pi/6, 0, np.pi/6, 0, np.pi/3, 0]),
                  np.array([np.pi/6, np.pi/6, np.pi/3, 0, np.pi/3, np.pi/6]),
                  np.array([np.pi/6, np.pi/6, np.pi/3,
                           np.pi/6, np.pi/3, np.pi/6]),
                  np.array([np.pi/2, 0, np.pi/2, -np.pi/3, np.pi/3, np.pi/6]),
                  np.array([-np.pi/6, -np.pi/6, -np.pi /
                           3, 0, np.pi/12, np.pi/2]),
                  np.array([np.pi/12, np.pi/12, np.pi/12, np.pi/12, np.pi/12, np.pi/12])]

    a = [0, 185, 170, 0, 0, 0]
    alpha = [-np.pi/2, 0, 0, np.pi/2, np.pi/2, 0]
    d = [230, -54, 0, 77, 77, 85.5]
    init_theta = [0, -np.pi/2, 0, np.pi/2, np.pi/2, 0]

    for theta in theta_list:
        for i in range(len(theta)):
            theta[i] += init_theta[i]
        T = getT(a, alpha, d, theta)
        print("Theta: ", theta * 180 / np.pi)
        print("T: \n", T)
        res = solve(T)
        print("Position: ", T[:3, 3]/1000)  # convert to meter
        print("Euler Angle: ", res)
        print("\n")
