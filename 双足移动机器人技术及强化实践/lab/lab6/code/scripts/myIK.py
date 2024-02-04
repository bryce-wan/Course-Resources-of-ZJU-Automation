import numpy as np


class IKSolver:
    def __init__(self):
        pass

    def solve(self, end):
        result = []
        sgn_lists = [[-1, 1], [-1, -1], [1, 1], [1, -1]]

        X, Y, Z, r, p, y = end
        # r, p, y, X, Y, Z = end

        for sgn1, sgn2 in sgn_lists:
            T_ = np.array([[X], [Y], [Z]])
            red = np.array([0, 0, 0, 1])

            R = np.array([[1, 0, 0],
                          [0, np.cos(r), -np.sin(r)],
                          [0, np.sin(r), np.cos(r)]]) @ np.array([[np.cos(p), 0, np.sin(p)],
                                                                  [0, 1, 0],
                                                                  [-np.sin(p), 0, np.cos(p)]]) @ np.array([[np.cos(y), -np.sin(y), 0],
                                                                                                           [np.sin(y), np.cos(
                                                                                                               y), 0],
                                                                                                           [0, 0, 1]])

            T = np.column_stack([R, T_])
            T = np.row_stack([T, red])

            nx, ox, ax, dx = T[0, :]
            ny, oy, ay, dy = T[1, :]
            nz, oz, az, dz = T[2, :]

            a = [0, 0.185, 0.170, 0, 0, 0]
            d = [0.230, -0.054, 0, 0.077, 0.077, 0.0855]
            A = dy - d[5] * ay
            B = dx - d[5] * ax
            C = d[1] + d[3]

            theta_1 = np.arctan2(A, B) - np.arctan2(C,
                                                    sgn1 * np.sqrt(B**2 + A**2 - C**2))

            theta_5 = sgn1 * \
                np.arccos(ax * np.sin(theta_1) - ay * np.cos(theta_1))

            A = ny * np.cos(theta_1) - nx * np.sin(theta_1)
            B = oy * np.cos(theta_1) - ox * np.sin(theta_1)
            C = -np.sin(theta_5)

            theta_6 = np.arctan2(A, B) + np.arctan2(C, 0)

            M = dx * np.cos(theta_1) + dy * np.sin(theta_1) - ay * d[5] * np.sin(theta_1) - ax * d[5] * np.cos(theta_1) - d[4] * ny * np.sin(theta_1) * np.sin(
                theta_6) - d[4] * ox * np.cos(theta_1) * np.cos(theta_6) - d[4] * nx * np.cos(theta_1) * np.sin(theta_6) - d[4] * oy * np.cos(theta_6) * np.sin(theta_1)
            N = d[0] - dz + az * d[5] + d[4] * oz * \
                np.cos(theta_6) + d[4] * nz * np.sin(theta_6)

            theta_3 = sgn2 * np.arccos((M**2 + N**2 - a[1]**2 -
                                        a[2]**2) / (2 * a[1] * a[2]))

            s2 = ((a[2] * np.cos(theta_3) + a[1]) * N - a[2] * np.sin(theta_3) *
                  M) / (a[1]**2 + a[2]**2 + 2 * a[1] * a[2] * np.cos(theta_3))
            c2 = (M + a[2] * np.sin(theta_3) * s2) / \
                (a[2] * np.cos(theta_3) + a[1])

            theta_2 = np.arctan2(s2, c2)

            # if abs(theta_5 - np.pi / 2) < 1e-3:
            #     theta_4 = np.arcsin(ox * np.cos(theta_1) * np.cos(theta_6) + nx * np.cos(theta_1)
            #                         * np.sin(theta_6) + oy * np.sin(theta_1) * np.cos(theta_6) + ny * np.sin(theta_1) * np.sin(theta_6)) - theta_2 - theta_3
            # else:
            #     theta_4 = np.arcsin(
            #         (oz * np.sin(theta_6) - nz * np.cos(theta_6)) / np.cos(theta_5)) - theta_2 - theta_3

            theta_4 = -np.arctan2(-np.sin(theta_6)*(nx*np.cos(theta_1)+ny*np.sin(theta_1))-np.cos(
                theta_6)*(ox*np.cos(theta_1)+oy*np.sin(theta_1)), oz*np.cos(theta_6)+nz*np.sin(theta_6)) - theta_2 - theta_3

            th = np.array([theta_1, theta_2, theta_3,
                           theta_4, theta_5, theta_6])

            th = (
                th - np.array([0, -np.pi/2, 0, np.pi/2, np.pi/2, 0]))

            th_ = th < -np.pi
            th[th_] += np.pi * 2
            th_ = th > np.pi
            th[th_] -= np.pi * 2
            th_ = abs(th) < 1e-10
            th[th_] = 1e-16

            result.append(th)
            res = np.array(result).T

        return res


if __name__ == "__main__":

    # np.set_printoptions(suppress=True)
    end_lists = [[-2.019, -0.058, -2.19, 0.117, 0.334, 0.499],
                 [-2.618, -0.524, -3.141, -0.066, 0.339, 0.444],
                 [-2.64, 0.59, -2.35, 0.3, 0.25, 0.26],
                 [3.14, 1, -1.57, 0.42, 0, 0.36],
                 [3, 0.265, -0.84, 0.32, -0.25, 0.16]]

    iks = IKSolver()

    # solver.solve(np.array([-0.35, 0.05, 0.3, 0.75 * np.pi, 0, -np.pi]))
    res = iks.solve(np.array([-0.35, -0.05, 0.3, -0.75 * np.pi, 0, np.pi]))
    # print(res)