import open3d as o3d


def read_vis_model(model_path):
    '''
    Input:
    model_path: string, file path of a 3d model
    '''
    ########################
    # Write your code here
    pcd = o3d.io.read_point_cloud(model_path)
    o3d.visualization.draw_geometries([pcd])
    ########################


if __name__ == '__main__':
    read_vis_model('cat.ply')
