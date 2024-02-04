import time
import numpy as np
from math import *
from coppeliasim_zmqremoteapi_client import RemoteAPIClient
from matplotlib import pyplot as plt

print("Program started")

""" --------------------------- quintic curve plannning--------------------------- """


def quinticCurvePlanning(startPosition, endPosition, startVelocity, endVelocity, time):
    timeMatrix = np.matrix(
        [
            [0, 0, 0, 0, 0, 1],
            [time**5, time**4, time**3, time**2, time, 1],
            [0, 0, 0, 0, 1, 0],
            [5 * time**4, 4 * time**3, 3 * time**2, 2 * time, 1, 0],
            [0, 0, 0, 2, 0, 0],
            [20 * time**3, 12 * time**2, 6 * time, 2, 0, 0],
        ]
    )
    invTimeMatrix = np.linalg.inv(timeMatrix)
    kArray = []
    for i in range(len(startPosition)):
        X = np.matrix(
            [startPosition[i], endPosition[i],
                startVelocity[i], endVelocity[i], 0, 0]
        ).T
        k = np.dot(invTimeMatrix, X)
        kArray.append(k)
    return kArray


def quinticCurveExcute(kArray, time):
    timeVector = np.matrix([time**5, time**4, time**3, time**2, time, 1]).T
    jointPositions = []
    for i in range(7):
        jointPosition = np.dot(kArray[i].T, timeVector)
        jointPositions.append(jointPosition[0, 0])
    return np.array(jointPositions)

# 三点间五次多项式轨迹规划，返回值kArray为多项式系数，其中起点终点速度均为零，中间点速度可以规划，为入参midVel
# 其中time为起点到中间点的运动时间，time1为起始点到终点的运动时间（即整段规划的运动时间）


def quinticCurvePlanning2(startPosition, middlePosition, endPosition, midVel, time, time1):
    timeMatrix = np.matrix([
        [0,            0,              0,           0,        0,   1],
        [time**5,      time**4,        time**3,     time**2,     time,   1],
        [time1**5,     time1**4,       time1**3,    time1**2,    time1,   1],
        [0,            0,              0,           0,        1,   0],
        [5*time**4,    4*time**3,      3*time**2,      2*time,        1,   0],
        [5*time1**4,   4*time1**3,     3*time1**2,     2*time1,        1,   0],
    ])
    invTimeMatrix = np.linalg.inv(timeMatrix)
    kArray = []
    for i in range(len(startPosition)):
        X = np.matrix([startPosition[i], middlePosition[i],
                      endPosition[i], 0, midVel, 0]).T
        k = np.dot(invTimeMatrix, X)
        kArray.append(k)
    return kArray

# 三点间规划，带入当前时间time，求得当前时刻下的关节位置值


def quinticCurveExcute2(kArray, time):
    timeVector = np.matrix(
        [time**5,     time**4,       time**3,    time**2,     time,   1]).T
    jointPositions = []
    for i in range(7):
        jointPosition = np.dot(kArray[i].T, timeVector)
        jointPositions.append(jointPosition[0, 0])
    return np.array(jointPositions)


""" --------------------------- virtual environment --------------------------- """


class rbenv:
    def __init__(self):
        self.client = RemoteAPIClient()
        self.sim = self.client.getObject("sim")

        self.defaultIdleFps = self.sim.getInt32Param(
            self.sim.intparam_idle_fps)
        self.sim.setInt32Param(self.sim.intparam_idle_fps, 0)

        # Run a simulation in stepping mode:
        self.client.setStepping(True)
        self.sim.startSimulation()

        self.joint = np.zeros(7)
        self.l_base = self.sim.getObject("./L_Base")  # 16
        self.joint[0] = self.l_joint1 = self.sim.getObject("./L_Joint1")  # 17
        self.l_link1 = self.sim.getObject("./L_Link1")  # 18
        self.joint[1] = self.l_joint2 = self.sim.getObject("./L_Joint2")  # 19
        self.l_link2 = self.sim.getObject("./L_Link2")  # 20
        self.joint[2] = self.l_joint3 = self.sim.getObject("./L_Joint3")  # 21
        self.l_link3 = self.sim.getObject("./L_Link3")  # 22
        self.joint[3] = self.joint4 = self.sim.getObject("./Joint4")  # 23
        self.r_link3 = self.sim.getObject("./R_Link3")  # 24
        self.joint[4] = self.r_joint3 = self.sim.getObject("./R_Joint3")  # 25
        self.r_link2 = self.sim.getObject("./R_Link2")  # 26
        self.joint[5] = self.r_joint2 = self.sim.getObject("./R_Joint2")  # 27
        self.r_link1 = self.sim.getObject("./R_Link1")  # 28
        self.joint[6] = self.r_joint1 = self.sim.getObject("./R_Joint1")  # 29
        self.r_base = self.sim.getObject("./R_Base")  # 30
        self.base = "A"
        self.matrix_l = []
        self.matrix_r = []
        for i in range(16, 30):
            self.matrix_l.append(self.sim.getObjectMatrix(i, i + 1))
        for i in range(16, 30):
            self.matrix_r.append(self.sim.getObjectMatrix(i + 1, i))

        for i in range(0, 7):
            self.sim.setJointPosition(self.joint[i], 0)

    def switch_base(self, op):
        if self.base == op:
            return
        pos_now = np.zeros(7)
        for i in range(0, 7):
            pos_now[i] = self.sim.getJointPosition(self.joint[i])

        if op == "A":
            self.sim.setObjectParent(self.l_base, -1)
            for i in range(16, 30):
                self.sim.setObjectParent(i + 1, i)
                self.sim.setObjectMatrix(i + 1, i, self.matrix_r[i - 16])
                if i % 2 == 1:      # is joint
                    self.sim.setJointPosition(i, -pos_now[(i - 17) // 2])
            self.base = op
            return
        if op == "B":
            self.sim.setObjectParent(self.r_base, -1)
            for i in range(29, 15, -1):
                self.sim.setObjectParent(i, i + 1)
                self.sim.setObjectMatrix(i, i + 1, self.matrix_l[i - 16])
                if i % 2 == 1:      # is joint
                    self.sim.setJointPosition(i, -pos_now[(i - 17) // 2])
            self.base = op
            return
        pass

    def move(self, q):
        if self.base == "A":
            for i in range(0, 7):
                self.sim.setJointPosition(self.joint[i], q[i])
            return
        if self.base == "B":
            for i in range(0, 7):
                self.sim.setJointPosition(self.joint[i], q[6 - i])
            return

    def printjoint(self):
        print("Print joint position: ")
        for i in range(0, 7):
            print(self.sim.getJointPosition(self.joint[i]))
        pass


rb = rbenv()
''' --------------------------- inverse kinematics --------------------------- '''
q0 = [0, 0, 0, 0, 0, 0, 0]
q1 = [
    (120) / 180 * np.pi,
    0,
    -(2 * np.arcsin(150 * np.sqrt(3) / 400)) / 2,
    -(2 * np.arcsin(150 * np.sqrt(3) / 400)),
    (2 * np.arcsin(150 * np.sqrt(3) / 400)) / 2,
    0,
    -(120) / 180 * np.pi,
]
q1_ = [-x for x in list(reversed(q1))]
# 400(sin(th2+th1)-sin(th1)) = (400^2+(100+120)^2-300^2)^(0.5)-(100)
# 400(cos(th2+th1)-cos(th1)) = 100+120-100
a = ((400 ** 2 + (100 + 120) ** 2 - 300 ** 2) ** 0.5 - (100)) / 400
b = (100 + 120 - 100) / 400
th1 = -2*atan((2*a - (-(a**2 + b**2)*(a**2 + b**2 - 4))
              ** (1/2))/(a**2 + b**2 - 2*b))
th2 = 2*atan((2*a - (-(a**2 + b**2)*(a**2 + b**2 - 4))
             ** (1/2))/(a**2 + b**2 + 2*b)) - th1
th3 = - atan((100+120)/400) - acos(300 / (400**2+(100+120)**2)**0.5)
q2 = [th3 + 2*pi,
      0,
      th1,  # th1
      th2,  # th2
      th1 + th2 - pi/2,
      -th3,
      0]
q21 = [th3 + 2*pi,
       0,
       th1,  # th1
       th2-2*pi,  # th2
       th1 + th2 - pi/2,
       -th3,
       0]
q2_ = [-x for x in list(reversed(q21))]
q3 = [0, 0, 0, 0, 0, 0, 0]

''' --------------------------- quintic curve plannning--------------------------- '''
t01 = t12 = t23 = 10
t_tot = t01 + t12 + t23
b0 = 'B'
k01 = quinticCurvePlanning(q0, q1, np.zeros(7), np.zeros(7), t01)

b1 = 'A'
q12 = q1_.copy()
q12[0] += 0.5
# k12 = quinticCurvePlanning2(q1_, q12, q2, 0.1, 3, t12)
k12 = quinticCurvePlanning(q1_, q2, np.zeros(7), np.zeros(7), t12)
b23 = 'B'
k23 = quinticCurvePlanning(q2_, q3, np.zeros(7), np.zeros(7), t23)

''' --------------------------- simulation --------------------------- '''
plt.ion()
t_list = []
joint = [[], [], [], [], [], [], []]
while (t := rb.sim.getSimulationTime()) < t_tot:
    if t < t01:
        rb.switch_base(b0)
        q = quinticCurveExcute(k01, t)
    elif t < t01 + t12:
        rb.switch_base(b1)
        q = quinticCurveExcute(k12, t - t01)
    elif t < t01 + t12 + t23:
        rb.switch_base(b23)
        q = quinticCurveExcute(k23, t - t01 - t12)

    rb.move(q)
    t_list.append(t)
    for i in range(0, 7):
        joint[i].append(q[i])
    plt.clf()
    for i in range(0, 7):
        # plt.plot(t_list, joint[i], label=f"joint{i+1}")
        pass
    # plt.legend()
    # plt.pause(0.001)
    # plt.ioff()

    message = f'Simulation time: {t:.2f} s'
    # print(message)
    rb.sim.addLog(rb.sim.verbosity_scriptinfos, message)
    rb.client.step()  # triggers next simulation step
    time.sleep(0.01)

time.sleep(1)
# Stop simulation
rb.sim.stopSimulation()

plt.clf()
for i in range(0, 7):
    plt.plot(t_list, joint[i], label=f"joint{i+1}")
plt.legend()
plt.pause(5)

# Restore the original idle loop frequency:
rb.sim.setInt32Param(rb.sim.intparam_idle_fps, rb.defaultIdleFps)

print("Program ended")
