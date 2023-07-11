from cmath import inf
import numpy as np
import math as m

class RRTplanning:
    def __init__(self,obstacles_point, start_point, end_point, planning_minx,planning_miny,planning_maxx,planning_maxy):
        self.node_set = []
        self.start_point = start_point
        self.end_point = end_point
        self.start_node = self.RRT_Tree(start_point,[],[],end_point,start_point)
        self.planning_minx = planning_minx
        self.planning_miny = planning_miny
        self.planning_maxx = planning_maxx
        self.planning_maxy = planning_maxy
        self.obstacles_point = obstacles_point
        pass
    
    class RRT_Tree:
        def __init__(self,point,father,child,endpoint,startpoint):
            self.point = point
            self.father = father
            self.child = child
            self.endpoint = endpoint
            self.startpoint = startpoint
            pass
    
    def Process(self):
        new_node = self.start_node
        self.node_set.append(new_node)
        while self.if_nearend(new_node) == 0:
            new_node = self.search_next()
            self.node_set.append(new_node)
        end_node = self.RRT_Tree(self.end_point,new_node,[],self.end_point,self.start_point)
        path_X = []
        path_Y = []
        temp_node = end_node
        while (temp_node):
            path_X.append(temp_node.point[0])
            path_Y.append(temp_node.point[1])
            temp_node = temp_node.father
        path_X.reverse() 
        path_Y.reverse()  
        return path_X,path_Y
    
    # search next node 
    def search_next(self):
        dt=.5
        flag =1
        while flag:
            flag = 0
            
            if np.random.rand() < 0.5:
                x_temp = np.random.randint(self.planning_minx,self.planning_maxx, dtype=int)
                y_temp = np.random.randint(self.planning_miny,self.planning_maxy, dtype=int)
                temp_point = (x_temp,y_temp)
            else:
                temp_point = self.end_point
            
            dist,nearest_node = self.min_distance_node(temp_point)
            d = (temp_point-nearest_node.point)/np.linalg.norm(temp_point-nearest_node.point)
            near_node = RRTplanning.RRT_Tree(nearest_node.point+d*dt,nearest_node,[],nearest_node.endpoint,nearest_node.startpoint)
            for obstacles_point in self.obstacles_point:
                if np.linalg.norm(obstacles_point-near_node.point)<1.5:
                    flag = 1
                    break 
        nearest_node.child.append(near_node)     
        return near_node
    
    # find the nearest node
    def min_distance_node(self,temp_point):
        dist = m.inf
        for node in self.node_set:
            temp_dist = np.linalg.norm(node.point-temp_point)
            if temp_dist<dist:
                dist = temp_dist
                near_node = node
        return dist,near_node
    
    # check if the end point is reached
    def if_nearend(self,node):
        
        if np.linalg.norm(node.endpoint-node.point) < 0.5:
            return 1
        else:
            return 0