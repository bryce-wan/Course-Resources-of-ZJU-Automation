#!/usr/bin/env python

import rospy
import numpy as np
import math
from scipy.spatial import cKDTree as KDTree
# structure of the nearest neighbor


class NeighBor:
    def __init__(self):
        self.distances = []
        self.src_indices = []
        self.tar_indices = []


class ICP:
    def __init__(self):
        # max iterations
        self.max_iter = rospy.get_param('/icp/max_iter', 10)
        # distance threshold for filter the matching points
        self.dis_th = rospy.get_param('/icp/dis_th', 3)
        # tolerance to stop icp
        self.tolerance = rospy.get_param('/icp/tolerance', 0)
        # min match
        self.min_match = rospy.get_param('/icp/min_match', 2)

    # ICP process function
    # Waiting for Implementation
    # return: T = (R, t), where T is 2*3, R is 2*2 and t is 2*1
    def process(self, tar_pc, src_pc):
        tar_pc = tar_pc[:, ~np.isnan(tar_pc).any(axis=0)]
        src_pc = src_pc[:, ~np.isnan(src_pc).any(axis=0)]

        Transform_acc = np.identity(3)
        iter_cnt = 0
        prev_error = 0.0
        for i in range(self.max_iter):
            neigh = self.findNearest(src_pc.T, tar_pc.T)

            paired_src = src_pc[0:2, neigh.src_indices].copy()
            paired_tar = tar_pc[0:2, neigh.tar_indices].copy()

            Transform = self.getTransform(paired_src.T, paired_tar.T)
            Transform_acc = np.dot(Transform, Transform_acc)

            src_pc = np.dot(Transform, src_pc)
            mean_error = np.mean(neigh.distances)
            if np.abs(prev_error - mean_error) < self.tolerance:
                break

            prev_error = mean_error
            iter_cnt += 1

        print("total_iter:", iter_cnt)
        return Transform_acc

    # find the nearest points & filter
    # return: neighbors of src and tar

    def findNearest(self, src, tar):
        vec_src = src[:, :2]
        vec_tar = tar[:, :2]

        tree = KDTree(vec_tar)
        neigh = NeighBor()
        dist,ind = tree.query(vec_src, k=1)
        valid_ind = np.where(dist < self.dis_th)[0]
        neigh.distances = dist[valid_ind]
        neigh.src_indices = valid_ind
        neigh.tar_indices = ind[valid_ind]

        return neigh

    # Waiting for Implementation
    # return: T = (R, t), where T is 2*3, R is 2*2 and t is 2*1
    def getTransform(self, src, tar):
        T = np.identity(3)

        centroid_src = np.mean(src, axis=0)
        centroid_tar = np.mean(tar, axis=0)
        src_demean = src - centroid_src
        tar_demean = tar - centroid_tar

        H = np.dot(src_demean.T, tar_demean)
        U, S, Vt = np.linalg.svd(H)
        R = np.dot(Vt.T, U.T)
        t = centroid_tar - np.dot(R, centroid_src)
        T[:2, :2] = R
        T[:2, 2] = t

        return T

    def calcDist(self, a, b):
        dx = a[0] - b[0]
        dy = a[1] - b[1]
        return math.hypot(dx, dy)
