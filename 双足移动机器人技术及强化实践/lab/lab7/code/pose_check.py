from Robot import Robot
import numpy as np
import until
import time
import pandas as pd
import math
from myIK import IKSolver


def test():
    r = Robot(com='COM6', baud=250000)
    r.connect()
    # r.go_home()
    while (1):
        pose = r.syncFeedback()
        print(pose)


if __name__ == '__main__':
    test()
