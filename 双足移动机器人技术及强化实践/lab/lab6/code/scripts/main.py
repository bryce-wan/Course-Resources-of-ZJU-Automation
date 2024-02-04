#python
# from IK.IKSolver import IKSolver
import numpy as np
import sys, getpass 
sys.path.append(f"C:/Users/{getpass.getuser()}/Documents/IK")
print(f"C:/Users/{getpass.getuser()}/Documents/IK")
from myIK import IKSolver

####################################
### You Can Write Your Code Here ###
####################################

def sysCall_init():
    # initialization the simulation
    doSomeInit()    # must have    
    
    #------------------------------------------------------------------------
    # using the codes, you can obtain the poses and positions of four blocks
    pointHandles = []
    for i in range(2):
        pointHandles.append(sim.getObject('::/Platform1/Cuboid' + str(i+1) + '/SuckPoint'))
    for i in range(2):
        pointHandles.append(sim.getObject('::/Platform1/Prism' + str(i+1) + '/SuckPoint'))
    # get the pose of Cuboid/SuckPoint
    for i in range(4):
        print(sim.getObjectPose(pointHandles[i], -1))
    #-------------------------------------------------------------------------
        
        
    #-------------------------------------------------------------------------
    # following codes show how to call the build-in inverse kinematics solver
    # you may call the codes, or write your own IK solver
    # before you use the codes, you need to convert the above quaternions to X-Y'-Z' Euler angels 
    # you may write your own codes to do the conversion, or you can use other tools (e.g. matlab)

    iks = IKSolver()
    # return the joint angle vector q which belongs to [-PI, PI]
    # Position and orientation of the end-effector are defined by [x, y, z, rx, ry, rz]
    # x,y,z are in meters; rx,ry,rz are X-Y'-Z'Euler angles in radian
    #---------------------------------------------------------------------------
    
    """ this demo program shows a 3-postion picking task
    step1: the robot stats to run from the rest position (q0)
    step2: the robot moves to the picking position (q1) in 5s
    step3: turn on the vacumm gripper and picking in 0.5s
    step4: lift a block to position (q2) in 3s
    step5: the robot moves from q2 back to the rest positon q0
    q0 - initial joint angles of the robot
    q1 - joint angles when the robot contacts with a block
    q2 - final joint angels of the robot
    """
    global q0, q1, q2, q3, q4, q5, q6, q7, q8, q9, q10, q11, q12, q13, q14, q15, q16
    global l, r, left, right
    q0 = np.zeros(6) # initialize q0 with all zeros
    # angles of joint 1-6 obtained by solving the inverse kinematics

    l = np.array([0.1, 0.35, 0.2])
    r = np.array([-0.1, 0.35, 0.2])
    left = iks.solve(np.array([0.1, 0.35, 0.2, np.pi, 0, -np.pi/2]))[:,2]
    print("left")
    print(left)
    right = iks.solve(np.array([-0.1, 0.35, 0.2, np.pi, 0, -np.pi/2]))[:,2]
    print("right")
    print(right)

    # 1st block
    q1 = iks.solve(np.array([0.4, 0.12, 0.15, np.pi, 0, -93/180*np.pi]))[:,2] # pick
    # print("q1")
    # print(q1)
    q2 = iks.solve(np.array([0.4, 0.12, 0.16, np.pi, 0, -np.pi/2]))[:,2]
    # print("q2")
    # print(q2)
    q3 = iks.solve(np.array([-0.35, 0, 0.25, np.pi, 0, -np.pi/2]))[:,2]
    # print("q3")
    # print(q3)
    q4 = iks.solve(np.array([-0.35, 0, 0.2, np.pi, 0, -np.pi/2]))[:,2]    # place 
    # print("q4")
    # print(q4)

    # 2nd block
    q5 = iks.solve(np.array([0.4, -0.04, 0.125, -140.4/180*np.pi, 23.4/180*np.pi, -154.36/180*np.pi]))[:,2] # pick
    # print("q5")
    # print(q5)
    q6 = iks.solve(np.array([0.4, -0.04, 0.25, np.pi, 0, -np.pi/2]))[:,2]
    # print("q6")
    # print(q6)    
    q7 = iks.solve(np.array([-0.35, -0.05, 0.3, -0.75 * np.pi, 0, np.pi]))[:,2]
    q7[0] += 2*np.pi
    # print("q7")
    # print(q7)
    q8 = iks.solve(np.array([-0.3488, -0.05, 0.195, -0.75 * np.pi, 0, np.pi]))[:,2]    # place  
    q8[0] += 2*np.pi
    # print("q8")
    # print(q8)

    # 3rd block
    q9 = iks.solve(np.array([0.4, 0.04, 0.125, 145.6/180*np.pi, 31.05/180*np.pi, -37/180*np.pi]))[:,2]
    # print("q9")
    # print(q9)
    q10 = iks.solve(np.array([0.4, 0.04, 0.16, np.pi, 0, -np.pi/2]))[:,2]
    # print("q10")
    # print(q10)
    q11 = iks.solve(np.array([-0.35, 0.05, 0.3, 0.75 * np.pi, 0, -np.pi]))[:,2]
    # print("q11")
    # print(q11)
    q12 = iks.solve(np.array([-0.3485, 0.05, 0.177, 0.75 * np.pi, 0, -np.pi]))[:,2]
    # print("q12")
    # print(q12)

    #4th block
    q13 = iks.solve(np.array([0.4, -0.12, 0.15, np.pi, 0, -88/180*np.pi]))[:,2]
    # print("q13")
    # print(q13)
    q14 = iks.solve(np.array([0.4, -0.12, 0.16, np.pi, 0, -np.pi/2]))[:,2]
    # print("q14")
    # print(q14)
    q15 = iks.solve(np.array([-0.35, 0, 0.3, np.pi, 0, -np.pi/2]))[:,2]
    # print("q15")
    # print(q15)
    q16 = iks.solve(np.array([-0.35, 0, 0.255, np.pi, 0, -np.pi/2]))[:,2]
    # print("q16")
    # print(q16)
    print("!!!!!!!!!!!!!!!!!!!!!!!!!")
    print("!!!!!!!!!!!!!!!!!!!!!!!!!")

    global mt, lt, wt, st, rt
    mt = 2          # move t 
    lt = 2        # lift t 
    wt = 0.1        # wait t
    st = 0.1        # state t
    rt = 4          # q0 t

    global spline_points, spline_q_lists, num_line_points
    num_line_points = 1000
    spline_points=[]
    spline_q_lists=[]
    spline_points = [(l + (r - l) * i / num_line_points) for i in range(num_line_points)]
    for i in range(num_line_points):
        spline_q_lists.append(iks.solve(np.append(spline_points[i], [np.pi, 0, -np.pi/2]))[:,2])
        contains_nan = np.isnan(spline_q_lists[i]).any()
        if contains_nan:
            spline_q_lists[i] = spline_q_lists[i-1]

def sysCall_actuation():
    # put your actuation code in this function   

    # get absolute time, t
    t = sim.getSimulationTime()
    
    # 1st block
    offset = 0
    if  offset <= t:
        if t < offset + mt * 1 - st:
            q = trajPlaningDemo(q0, q1, t-offset, mt-wt-st, 2)
            state = False
        elif t < offset + mt * 1:
            q = q1
            state = True
        elif t < offset + mt * 1 + lt * 1:
            q = trajPlaningDemo(q1, q2, t-(offset + mt * 1), lt-wt, 2)
            state = True
        elif t < offset + mt * 2 + lt * 1:
            q = trajPlaningDemo(q2, left, t-(offset + mt * 1 + lt * 1), mt-wt, 1)
            state = True
        elif t < offset + mt * 3 + lt * 1:
            q = trajPlaning(l, r, t-(offset + mt * 2 + lt * 1), mt)
            state = True
        elif t < offset + mt * 4 + lt * 1:
            q = trajPlaningDemo(right, q3, t-(offset + mt * 3 + lt * 1), mt-wt, -1)
            state = True
        elif t < offset + mt * 4 + lt * 2 - st:
            q = trajPlaningDemo(q3, q4, t-(offset + mt * 4 + lt * 1), lt-wt-st, 2)
            state = True
        elif t < offset + mt * 4 + lt * 2:
            q = q4
            state = False
        elif t < offset + mt * 4 + lt * 2 + rt:
            q = trajPlaningDemo(q4, q0, t-(offset + mt * 4 + lt * 2), rt-wt, 2)
            state = False
    
    # 2nd block
    offset = (mt * 4 + lt * 2 + rt)
    if  offset <= t:
        if  t < offset + mt * 1 - st:
            q = trajPlaningDemo(q0, q5, t-offset, mt-wt-st, 2)
            state = False
        elif t < offset + mt * 1:
            q = q5
            state = True
        elif t < offset + mt * 1 + lt * 1:
            q = trajPlaningDemo(q5, q6, t-(offset + mt * 1), lt-wt, 2)
            state = True
        elif t < offset + mt * 2 + lt * 1:
            q = trajPlaningDemo(q6, left, t-(offset + mt * 1 + lt * 1), mt-wt, 1)
            state = True
        elif t < offset + mt * 3 + lt * 1:
            q = trajPlaning(l, r, t-(offset + mt * 2 + lt * 1), mt)
            state = True
        elif t < offset + mt * 4 + lt * 1:
            q = trajPlaningDemo(right, q7, t-(offset + mt * 3 + lt * 1), mt-wt, -1)
            state = True
        elif t < offset + mt * 4 + lt * 2 - st:
            q = trajPlaningDemo(q7, q8, t-(offset + mt * 4 + lt * 1), lt-wt-st, 2)
            state = True
        elif t < offset + mt * 4 + lt * 2:
            q = q8
            state = False
        elif t < offset + mt * 4 + lt * 2 + rt:
            q = trajPlaningDemo(q8, q0, t-(offset + mt * 4 + lt * 2), rt-wt, 2)
            state = False
    
    # 3rd block
    offset = (mt * 4 + lt * 2 + rt) * 2
    if  offset <= t:
        if  t < offset + mt * 1 - st:
            q = trajPlaningDemo(q0, q9, t-offset, mt-wt-st, 2)
            state = False
        elif t < offset + mt * 1:
            q = q9
            state = True
        elif t < offset + mt * 1 + lt * 1:
            q = trajPlaningDemo(q9, q10, t-(offset + mt * 1), lt-wt, 2)
            state = True
        elif t < offset + mt * 2 + lt * 1:
            q = trajPlaningDemo(q10, left, t-(offset + mt * 1 + lt * 1), mt-wt, 1)
            state = True
        elif t < offset + mt * 3 + lt * 1:
            q = trajPlaning(l, r, t-(offset + mt * 2 + lt * 1), mt)
            state = True
        elif t < offset + mt * 4 + lt * 1:
            q = trajPlaningDemo(right, q11, t-(offset + mt * 3 + lt * 1), mt-wt, -1)
            state = True
        elif t < offset + mt * 4 + lt * 2 - st:
            q = trajPlaningDemo(q11, q12, t-(offset + mt * 4 + lt * 1), lt-wt-st, 2)
            state = True
        elif t < offset + mt * 4 + lt * 2:
            q = q12
            state = False
        elif t < offset + mt * 4 + lt * 2 + rt:
            q = trajPlaningDemo(q12, q0, t-(offset + mt * 4 + lt * 2), rt-wt, 2)
            state = False
    
    # 4th block
    offset = (mt * 4 + lt * 2 + rt) * 3
    if  offset <= t:
        if  t < offset + mt * 1 - st:
            q = trajPlaningDemo(q0, q13, t-offset, mt-wt-st, 2)
            state = False
        elif t < offset + mt * 1:
            q = q13
            state = True
        elif t < offset + mt * 1 + lt * 1:
            q = trajPlaningDemo(q13, q14, t-(offset + mt * 1), lt-wt, 2)
            state = True
        elif t < offset + mt * 2 + lt * 1:
            q = trajPlaningDemo(q14, left, t-(offset + mt * 1 + lt * 1), mt-wt, 1)
            state = True
        elif t < offset + mt * 3 + lt * 1:
            q = trajPlaning(l, r, t-(offset + mt * 2 + lt * 1), mt)
            state = True
        elif t < offset + mt * 4 + lt * 1:
            q = trajPlaningDemo(right, q15, t-(offset + mt * 3 + lt * 1), mt-wt, -1)
            state = True
        elif t < offset + mt * 4 + lt * 2 - st:
            q = trajPlaningDemo(q15, q16, t-(offset + mt * 4 + lt * 1), lt-wt-st, 2)
            state = True
        elif t < offset + mt * 4 + lt * 2:
            q = q16
            state = False
        elif t < offset + mt * 4 + lt * 2 + rt:
            q = trajPlaningDemo(q16, q0, t-(offset + mt * 4 + lt * 2), rt-wt, 2)
            state = False
    if t >= (mt * 4 + lt * 2 + rt) * 4:
        sim.pauseSimulation()    
    else:
        runState = move(q, state)
        
    """
    The following codes shows a procedure of trajectory planning using the 5th-order polynomial
    You may write your own code to replace this function, e.g. trapezoidal velocity planning
    """
def trajPlaning(start, end, t, time):
    if t < time:
        r = int(t / time * num_line_points)
        res = spline_q_lists[r] 
    else:
        res = spline_q_lists[num_line_points-1]

    if res.any() == np.nan:
        print("trajPlaning(): NAN")
        return False
    return res

def trajPlaningDemo(start, end, t, time, op):
    """ Quintic Polynomial: x = k5*t^5 + k4*t^4 + k3*t^3 + k2*t^2 + k1*t + k0
    :param start: Start point
    :param end: End point
    :param t: Current time
    :param time: Expected time spent
    :param op: Operation, 1 for picking, -1 for placing
    :return: The value of the current time in this trajectory planning
    """
    if t < time:
        tMatrix = np.matrix([
        [         0,           0,             0,          0,        0,   1],
        [   time**5,     time**4,       time**3,    time**2,     time,   1],
        [         0,           0,             0,          0,        1,   0],
        [ 5*time**4,   4*time**3,     3*time**2,     2*time,        1,   0],
        [         0,           0,             0,          2,        0,   0],
        [20*time**3,  12*time**2,        6*time,          2,        0,   0]])
        
        xArray = []
        for i in range(len(start)):
            xArray.append([start[i], end[i], 0 if op == 1 or op == 2 else  0.2/mt,
                                            0 if op == -1 or op == 2 else  0.2/mt,
                                            0, 0])
        xMatrix = np.matrix(xArray).T
        
        kMatrix = tMatrix.I * xMatrix
        
        timeVector = np.matrix([t**5, t**4, t**3, t**2, t, 1]).T
        x = (kMatrix.T * timeVector).T.A[0]
        
    else:
        x = end
    
    return x


####################################################
### You Don't Have to Change the following Codes ###
####################################################

def doSomeInit():
    global Joint_limits, Vel_limits, Acc_limits
    Joint_limits = np.array([[-200, -90, -120, -150, -150, -180],
                            [200, 90, 120, 150, 150, 180]]).transpose()/180*np.pi
    Vel_limits = np.array([100, 100, 100, 100, 100, 100])/180*np.pi
    Acc_limits = np.array([500, 500, 500, 500, 500, 500])/180*np.pi
    
    global lastPos, lastVel, sensorVel
    lastPos = np.zeros(6)
    lastVel = np.zeros(6)
    sensorVel = np.zeros(6)
    
    global robotHandle, suctionHandle, jointHandles
    robotHandle = sim.getObject('.')
    suctionHandle = sim.getObject('./SuctionCup')
    jointHandles = []
    for i in range(6):
        jointHandles.append(sim.getObject('./Joint' + str(i+1)))
    sim.writeCustomDataBlock(suctionHandle, 'activity', 'off')
    sim.writeCustomDataBlock(robotHandle, 'error', '0')
    
    global dataPos, dataVel, dataAcc, graphPos, graphVel, graphAcc
    dataPos = []
    dataVel = []
    dataAcc = []
    graphPos = sim.getObject('./DataPos')
    graphVel = sim.getObject('./DataVel')
    graphAcc = sim.getObject('./DataAcc')
    color = [[1, 0, 0], [0, 1, 0], [0, 0, 1], [1, 1, 0], [1, 0, 1], [0, 1, 1]]
    for i in range(6):
        dataPos.append(sim.addGraphStream(graphPos, 'Joint'+str(i+1), 'deg', 0, color[i]))
        dataVel.append(sim.addGraphStream(graphVel, 'Joint'+str(i+1), 'deg/s', 0, color[i]))
        dataAcc.append(sim.addGraphStream(graphAcc, 'Joint'+str(i+1), 'deg/s2', 0, color[i]))

def sysCall_sensing():
    # put your sensing code here
    if sim.readCustomDataBlock(robotHandle,'error') == '1':
        return
    global sensorVel
    for i in range(6):
        pos = sim.getJointPosition(jointHandles[i])
        if i == 0:
            if pos < -160/180*np.pi:
                pos += 2*np.pi
        vel = sim.getJointVelocity(jointHandles[i])
        acc = (vel - sensorVel[i])/sim.getSimulationTimeStep()
        if pos < Joint_limits[i, 0] or pos > Joint_limits[i, 1]:
            print("Error: Joint" + str(i+1) + " Position Out of Range!")
            sim.writeCustomDataBlock(robotHandle, 'error', '1')
            return
        
        if abs(vel) > Vel_limits[i]:
            print("Error: Joint" + str(i+1) + " Velocity Out of Range!")
            sim.writeCustomDataBlock(robotHandle, 'error', '1')
            return
        
        if abs(acc) > Acc_limits[i]:
            print("Error: Joint" + str(i+1) + " Acceleration Out of Range!")
            sim.writeCustomDataBlock(robotHandle, 'error', '1')
            return
        
        sim.setGraphStreamValue(graphPos,dataPos[i], pos*180/np.pi)
        sim.setGraphStreamValue(graphVel,dataVel[i], vel*180/np.pi)
        sim.setGraphStreamValue(graphAcc,dataAcc[i], acc*180/np.pi)
        sensorVel[i] = vel

def sysCall_cleanup():
    # do some clean-up here
    sim.writeCustomDataBlock(suctionHandle, 'activity', 'off')
    sim.writeCustomDataBlock(robotHandle, 'error', '0')


def move(q, state):
    if sim.readCustomDataBlock(robotHandle,'error') == '1':
        return
    global lastPos, lastVel
    # print("q")
    # print(q)
    # print("lastPos")
    # print(lastPos)
    # print("sim.getSimulationTimeStep()")
    # print(sim.getSimulationTimeStep())
    for i in range(6):
        if q[i] < Joint_limits[i, 0] or q[i] > Joint_limits[i, 1]:
            print("move(): Joint" + str(i+1) + " Position Out of Range!")
            return False
        if abs(q[i] - lastPos[i])/sim.getSimulationTimeStep() > Vel_limits[i]:
            
            print("q")
            print(q)
            print("lastPos")
            print(lastPos)
            print("sim.getSimulationTimeStep()")
            print(sim.getSimulationTimeStep())
            print(abs(q[i] - lastPos[i]))
            print(abs(q[i] - lastPos[i])/sim.getSimulationTimeStep())
            print(Vel_limits[i])
            
            print("move(): Joint" + str(i+1) + " Velocity Out of Range!")
            return False
        if abs(lastVel[i] - (q[i] - lastPos[i]))/sim.getSimulationTimeStep() > Acc_limits[i]:
            print("move(): Joint" + str(i+1) + " Acceleration Out of Range!")
            return False
            
    lastPos = q
    lastVel = q - lastPos
    
    for i in range(6):
        sim.setJointTargetPosition(jointHandles[i], q[i])
        
    if state:
        sim.writeCustomDataBlock(suctionHandle, 'activity', 'on')
    else:
        sim.writeCustomDataBlock(suctionHandle, 'activity', 'off')
    
    return True
    