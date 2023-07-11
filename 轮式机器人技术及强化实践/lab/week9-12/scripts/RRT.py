# encoding utf-8

import random
import math
import numpy as np

class RRTPlanner:
    class Node:
        def __init__(self, x, y):
            self.x = x
            self.y = y
            self.parent = None

            def __str__(self):
                return str(self.x)+", "+str(self.y)
            
    def __init__(self, expand_distance, robot_radius):
        self.robot_radius = robot_radius  
        self.max_iter = 3000              
        self.goal_sample_rate = 0.1      
        self.expand_distance = expand_distance     
        self.nodes = []                
    def planning(self, obstacle_list_x, obstacle_list_y,
                  start_x, start_y,
                    goal_x, goal_y,
                    planning_minx, planning_miny,
                    planning_maxx, planning_maxy):
        # new_col = np.ones(len(obstacle_list_x)) * self.robot_radius
        # obstacle_list = np.column_stack((obstacle_list_x, obstacle_list_y, new_col))
        # start = (start_x, start_y)
        
        goal = (goal_x, goal_y)
        print(goal)
        start_node = self.Node(start_x, start_y)
        self.nodes.append(start_node)
        for i in range(self.max_iter):
            if i % 100 == 0:
                print(i)

            if random.random() > self.goal_sample_rate:
                x = (planning_maxx - planning_minx) * random.random() + planning_minx
                y = (planning_maxy - planning_miny) * random.random() + planning_miny
            else:
                x, y = goal

            nearest_node = self.nodes[0]
            for node in self.nodes:
                if self.distance((node.x, node.y), (x, y)) < self.distance((nearest_node.x,nearest_node.y), (x, y)):
                    nearest_node = node
            
            new_node_x = nearest_node.x + self.expand_distance * math.cos(self.angle((nearest_node.x,nearest_node.y), (x, y)))
            new_node_y = nearest_node.y + self.expand_distance * math.sin(self.angle((nearest_node.x,nearest_node.y), (x, y)))
            new_node = self.Node(new_node_x, new_node_y)
            # print("sb2")
            # print(new_node_x,new_node_y)
            if self.is_collision(new_node_x, new_node_y, obstacle_list_x, obstacle_list_y, self.robot_radius):
                
                continue
            else:
                # print("sb")
                new_node.parent = nearest_node
                # print(new_node.x, new_node.y)
                self.nodes.append(new_node)
                # print(self.distance((new_node_x, new_node_y), goal), self.expand_distance)
                if self.distance((new_node_x, new_node_y), goal) < self.expand_distance:
                    # print("dfghjkl")
                    return self.generate_path(self.nodes.index(new_node))
    
    def generate_path(self, end_node_index):
        path_x = []
        path_y = []
        current_node = self.nodes[end_node_index]
        while current_node.parent is not None:
            path_x.append(current_node.x)
            path_y.append(current_node.y)
            # print(path_x, path_y)
            current_node = current_node.parent
        path_x.append(current_node.x)
        path_y.append(current_node.y)
        return list(path_x), list(path_y)
    
    def distance(self, node1, node2):
        return math.sqrt((node1[0]- node2[0])**2 + (node1[1] - node2[1])**2)
    
    def angle(self, node1, node2):
        return math.atan2(node2[1] - node1[1], node2[0] - node1[0])

    def is_collision(self, new_node_x, new_node_y, obs_x, obs_y, robot_radius):
        sum = 0
        for i in range(len(obs_x)):
            if self.distance((new_node_x, new_node_y), (obs_x[i], obs_y[i])) < robot_radius:
                sum += 1
            # if sum > len(obs_x)*0.001:
                return True
                # print("______________________")
                # print("1",(new_node_x, new_node_y))
                # print("2",(obs_x[i], obs_y[i]))
                # return True
        return False