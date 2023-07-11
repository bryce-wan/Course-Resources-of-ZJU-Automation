#!/usr/bin/env python
import rospy
import tf
from nav_msgs.srv import GetMap
from nav_msgs.msg import Path
from geometry_msgs.msg import PoseStamped
from course_agv_nav.srv import Plan, PlanResponse
from nav_msgs.msg import OccupancyGrid
from std_msgs.msg import Bool
import numpy as np
import matplotlib.pyplot as plt
# import Astar1 as A1
# import Astar2 as A2
import RRT
# from RRTplanner import RRT
import sys

class GlobalPlanner:
    def __init__(self):
        self.plan_sx = 0.0
        self.plan_sy = 0.0
        self.plan_gx = 8.0
        self.plan_gy = -8.0
        self.plan_grid_size = 0.3
        self.plan_robot_radius = 0.01
        self.plan_ox = []
        self.plan_oy = []
        self.plan_rx = []
        self.plan_ry = []

        # count to update map
        self.map_count = 0

        self.tf = tf.TransformListener()
        self.goal_sub = rospy.Subscriber('/course_agv/goal',PoseStamped,self.goalCallback)
        self.plan_srv = rospy.Service('/course_agv/global_plan',Plan,self.replan)
        self.path_pub = rospy.Publisher('/course_agv/global_path',Path,queue_size = 1)
        self.map_sub = rospy.Subscriber('/map',OccupancyGrid,self.mapCallback)        
        self.collision_sub = rospy.Subscriber('/collision_checker_result',Bool,self.collisionCallback)

        self.updateMap()
        # self.updateGlobalPose()

        pass
    def goalCallback(self,msg):
        self.plan_goal = msg
        self.plan_gx = msg.pose.position.x
        self.plan_gy = msg.pose.position.y
        # print("get new goal!!! ",self.plan_goal)
        self.replan(0)
        pass

    def collisionCallback(self,msg):
        self.replan(0)
    def updateGlobalPose(self):
        try:
            self.tf.waitForTransform("/map", "/base_footprint", rospy.Time(), rospy.Duration(4.0))
            (self.trans,self.rot) = self.tf.lookupTransform('/map','/base_footprint',rospy.Time(0))
        except (tf.LookupException, tf.ConnectivityException, tf.ExtrapolationException):
            print("get tf error!")
        self.plan_sx = self.trans[0]
        self.plan_sy = self.trans[1]

    def replan(self,req):
        print('get request for replan!!!!!!!!')
        self.initAStar()
        self.updateGlobalPose()
        # self.plan_rx,self.plan_ry = self.planner.Process()
        print("!1",type(self.plan_ox))
        print("!2",type(self.plan_sx))
        print("!3",type(self.plan_gx))
        print("!4",type(np.array(self.plan_ox).min()))
        
        self.plan_rx,self.plan_ry = self.planner.planning(self.plan_ox,self.plan_oy,    
                                                          self.plan_sx,self.plan_sy,
                                                          self.plan_gx,self.plan_gy,
                                                          np.array(self.plan_ox).min(),
                                                          np.array(self.plan_oy).min(),
                                                          np.array(self.plan_ox).max(),
                                                          np.array(self.plan_oy).max())
        print("!!!")
        print(type(self.plan_rx))
        
        self.plan_rx.reverse();
        self.plan_ry.reverse()
        print(type(self.plan_rx))

        self.publishPath()
        res = True
        return PlanResponse(res)
    
    def initAStar(self):
        print('info' , self.map.info)
        map_data = np.array(self.map.data).reshape((-1,self.map.info.height)).transpose()
        print("map_data_size",len(map_data))
        print("!!!!!!!")
        print(map_data)
        ox,oy = np.nonzero(map_data != 0)
        self.plan_ox = (ox*self.map.info.resolution+self.map.info.origin.position.x).tolist()
        self.plan_oy = (oy*self.map.info.resolution+self.map.info.origin.position.y).tolist()
        self.planner=RRT.RRTPlanner(self.plan_grid_size,self.plan_robot_radius)
        
        # self.planner=rrt.planning(self.plan_ox,self.plan_oy,self.plan_sx,self.plan_sy,self.plan_gx,self.plan_gy,np.array(self.plan_ox).min(),np.array(self.plan_oy).min(),np.array(self.plan_ox).max(),np.array(self.plan_oy).max())

    def mapCallback(self,msg):
        self.map = msg
        pass
    def updateMap(self):
        rospy.wait_for_service('/static_map')
        try:
            getMap = rospy.ServiceProxy('/static_map',GetMap)
            msg = getMap().map
        except:
            e = sys.exc_info()[0]
            print('Service call failed: %s'%e)
        # Update for planning algorithm
        self.mapCallback(msg)

    def publishPath(self):
        path = Path()
        path.header.seq = 0
        path.header.stamp = rospy.Time(0)
        path.header.frame_id = 'map'
        for i in range(len(self.plan_rx)):
            pose = PoseStamped()
            pose.header.seq = i
            pose.header.stamp = rospy.Time(0)
            pose.header.frame_id = 'map'
            pose.pose.position.x = self.plan_rx[i]#reverse
            pose.pose.position.y = self.plan_ry[i]#reverse
            pose.pose.position.z = 0.01
            pose.pose.orientation.x = 0
            pose.pose.orientation.y = 0
            pose.pose.orientation.z = 0
            pose.pose.orientation.w = 1
            path.poses.append(pose)
        self.path_pub.publish(path)


def main():
    rospy.init_node('global_planner')
    gp = GlobalPlanner()
    rospy.spin()
    pass

if __name__ == '__main__':
    main()
