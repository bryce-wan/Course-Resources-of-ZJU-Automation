import math
import numpy as np

def plan(cur,dwaconfig,midpos,planning_obs):
    min_obs_cost=0
    min_heading_cost=0
    min_speed_cost=0
    if(math.sqrt((cur[0]-midpos[0])**2+(cur[1]-midpos[1])**2)<dwaconfig.arrive_dist):
        return [0,0],0
    # vxup,vxdo,vwup,vwdo=Vsd(cur[3],cur[4],dwaconfig)
    vx=cur[3]
    vw=cur[4]
    Vs = [[dwaconfig.min_speed, dwaconfig.max_speed],
            [-dwaconfig.max_yawrate, dwaconfig.max_yawrate]]
    
    Vd = [[vx - dwaconfig.max_accel * dwaconfig.dt, vx + dwaconfig.max_accel * dwaconfig.dt],
            [vw - dwaconfig.max_dyawrate * dwaconfig.dt, vw + dwaconfig.max_dyawrate * dwaconfig.dt]]

    min_score=np.inf
    # print("midpos: ",midpos)
    # print("curpos ",cur[0],cur[1])
    window = [[max(Vs[0][0], Vd[0][0]), min(Vs[0][1], Vd[0][1])],
                [max(Vs[1][0], Vd[1][0]), min(Vs[1][1], Vd[1][1])]]
    min_vx=0
    min_vw=0
    for vx in np.arange(window[0][0],window[0][1],dwaconfig.v_reso):
        for vw in np.arange(window[1][0],window[1][1],dwaconfig.yawrate_reso):
            Tra=cal_tra(cur,vx,vw,dwaconfig)
            cost1=dwaconfig.to_goal_cost_gain*goal_cost(Tra,midpos)
            cost2=dwaconfig.obstacle_cost_gain*obs_cost(Tra,planning_obs,dwaconfig)
            cost3=dwaconfig.speed_cost_gain*(dwaconfig.max_speed-Tra[-1,3])
            score=cost1+cost2+cost3
            # print(min_score)
            if score<min_score:
                min_score=score
                # print("-----------------")
                min_vx=vx
                min_vw=vw
                min_obs_cost=cost2
                min_heading_cost=cost1
                min_speed_cost=cost3
    # print(min_vx,min_vw)
    print("-----------------------")
    print("obs:", min_obs_cost)
    print("heading:",min_heading_cost)
    print("speed:",min_speed_cost)
    return np.array([min_vx,min_vw])

def goal_cost(Tra,goal):
    goal_dis=math.sqrt((Tra[-1,0]-goal[0])**2+(Tra[-1,1]-goal[1])**2)
    return goal_dis

def obs_cost(Tra,planning_obs,dwaconfig):
    obs_dis=0
    min_dist=0x7fffffff
    # for j in range (len(Tra)):
    min_i=0
    for i in range(len(planning_obs)):
        obs_dis=math.sqrt((Tra[-1,0]-planning_obs[i][0])**2+(Tra[-1,1]-planning_obs[i][1])**2)
        if(obs_dis<dwaconfig.robot_radius):
            return 0x7fffffff
        if(obs_dis<min_dist):
            min_dist=obs_dis
            min_i=i
    # print("cur:",Tra[-1,0],Tra[-1,1])
    # print("min_obs",planning_obs[i][0],planning_obs[i][1])
    # print("min dist to obs:",min_dist)
    # print("--------------------------------")
    return 1/min_dist

def motion(X,vx,vw,dt):
    X[0]+=dt*vx*math.cos(X[2]+dt*vw)
    X[1]+=dt*vx*math.sin(X[2]+dt*vw)
    X[2]+=dt*vw
    X[3]=vx
    X[4]=vw
    return X

def cal_tra(tra,vx,vw,dwaconfig):
    Tra=np.array(tra)
    X=np.array(tra)
    times=0
    while times<=dwaconfig.predict_time:
        X=motion(X,vx,vw,dwaconfig.dt)
        Tra=np.vstack((Tra,X))
        times+=dwaconfig.dt
    return Tra

def Vsd(vx,vw,dwaconfig):
    vxup=min(vx+dwaconfig.v_reso*10,dwaconfig.max_speed)
    vxdo=max(vx-dwaconfig.v_reso*10,dwaconfig.min_speed)
    vwup=min(vw+dwaconfig.yawrate_reso*10,dwaconfig.max_yawrate)
    vwdo=max(vw-dwaconfig.yawrate_reso*10,-dwaconfig.max_yawrate)
    return vxup,vxdo,vwup,vwdo

def Va(x,y,dwaconfig,planning_obs):
    i=0
    min_dist=0x7fffffff
    min_arc=math.pi
    min_id=-1
    while i<planning_obs.shape[0]:
        dist=math.sqrt((x-planning_obs[i][0])**2+(y-planning_obs[i][1])**2)
        if dist<min_dist:
            min_dist=dist
            min_id=i
            min_arc=math.atan2(planning_obs[i][1]-y,planning_obs[i][0]-x)
        i+=1
    min_dist=min_dist-dwaconfig.robot_radius-dwaconfig.obs_radius
    if min_dist*2*dwaconfig.max_accel>=0:
        vxup=math.sqrt(min_dist*2*dwaconfig.max_accel)
    else:
        vxup=0
    wup=math.sqrt(abs(min_arc)*2*dwaconfig.max_dyawrate)
    return vxup,wup,min_id

def evaluation(x,y,theta,vx,vw,dwaconfig,midpos,planning_obs,min_id):
    heading=math.sqrt((x-midpos[0])**2+(y-midpos[1])**2)
    # heading=math.atan2(midpos[1]-y,midpos[0]-x)-theta
    dist=0
    if min_id!=-1:
        dist=math.sqrt((x-planning_obs[min_id][0])**2+(y-planning_obs[min_id][1])**2)
        dist=1/dist
    velocity=(dwaconfig.max_speed-abs(vx))#/dwaconfig.max_speed#+(dwaconfig.max_yawrate-abs(vw))/dwaconfig.max_yawrate))/2
    return dwaconfig.to_goal_cost_gain*heading+dwaconfig.obstacle_cost_gain*dist+velocity*dwaconfig.speed_cost_gain

class Config:
    robot_radius = 0.3
    def __init__(self,obs_radius=0.05):
        self.obs_radius = obs_radius
        self.dt = 0.05  # [s] Time tick for motion prediction

        self.max_speed = 0.1  # [m/s]
        self.min_speed = -0.1  # [m/s]
        self.max_accel = 1  # [m/ss]
        self.v_reso = self.max_accel*self.dt/10.0  # [m/s]

        self.max_yawrate = 100.0 * math.pi / 180.0  # [rad/s]
        self.max_dyawrate = 100.0 * math.pi / 180.0  # [rad/ss]
        self.yawrate_reso = self.max_dyawrate*self.dt/10.0  # [rad/s]

        
        self.predict_time = 2  # [s]

        self.to_goal_cost_gain = 1
        self.speed_cost_gain = 0.5
        self.obstacle_cost_gain = 1

        self.tracking_dist = self.predict_time*self.max_speed
        self.arrive_dist = 0.1
    