# -*- coding: utf-8 -*-
from cmath import inf
import numpy as np
import math as m



class RRT:

    def __init__(self,obstacles_point, start_point, end_point, planning_minx,planning_miny,planning_maxx,planning_maxy,grid,dist):
        self.node_set = []
        self.start_point = start_point
        self.end_point = end_point
        self.start_node = self.RRT_Tree(start_point,[],[],end_point,start_point)
        self.planning_minx = planning_minx
        self.planning_miny = planning_miny
        self.planning_maxx = planning_maxx
        self.planning_maxy = planning_maxy
        self.obstacles_point = obstacles_point
        self.grid = grid
        self.dist = dist
       
    class RRT_Tree:
        def __init__(self,point,father,child,endpoint,startpoint):
            self.point = point
            self.father = father
            self.child = child
            self.endpoint = endpoint  # 终点坐标
            self.startpoint = startpoint # 起点坐标


    def Process(self):

        new_node = self.start_node
        self.node_set.append(new_node)
        while self.if_nearend(new_node) == 0:
            new_node = self.search_next()
            self.node_set.append(new_node)
        end_node = self.RRT_Tree(self.end_point,new_node,[],self.end_point,self.start_point)
        best_path_X = []
        best_path_Y = []
        temp_node = end_node  # 拿到终点顶点
        while (temp_node):
            best_path_X.append(temp_node.point[0])
            best_path_Y.append(temp_node.point[1])
            temp_node = temp_node.father
        best_path_X.reverse()  # 逆转链表
        best_path_Y.reverse()  # 逆转链表
        return best_path_X,best_path_Y
    def search_next(self):

        flag =1
        while flag:
            flag = 0
            # 利用rand()函数在[0,1]区间内随机生成一个数
            if np.random.rand() < self.grid:
                # 如果小于0.5，则在图 img_binary 的范围内随机采样一个点
                x_temp = np.random.randint(self.planning_minx,self.planning_maxx, dtype=int)
                y_temp = np.random.randint(self.planning_miny,self.planning_maxy, dtype=int)
                temp_point = (x_temp,y_temp)
            else:
                # 否则用目标点作为采样点
                temp_point = self.end_point
            dist,nearest_node = self.min_distance_node(temp_point)
            d = ([temp_point[i]-nearest_node.point[i] for i in range(len(temp_point))])/np.linalg.norm([temp_point[i]-nearest_node.point[i] for i in range(len(temp_point))])
            near_node = RRT.RRT_Tree(nearest_node.point+d*self.grid,nearest_node,[],nearest_node.endpoint,nearest_node.startpoint)
            for obstacles_point in self.obstacles_point:
                if np.linalg.norm(obstacles_point-near_node.point)<self.dist:
                    flag = 1
                    break 
        nearest_node.child.append(near_node)     
        return near_node

    def min_distance_node(self,temp_point):

        dist = float("inf")
        for node in self.node_set:
            temp_dist = np.linalg.norm([node.point[i]-temp_point[i] for i in range(len(temp_point))])
            if temp_dist<dist:
                dist = temp_dist
                near_node  = node
        return dist,near_node

    def if_nearend(self,node):

        if np.linalg.norm(node.point-node.endpoint) < self.grid:
            return 1
        return 0

    