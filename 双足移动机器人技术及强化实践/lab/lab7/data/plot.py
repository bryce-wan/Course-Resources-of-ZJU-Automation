import pandas as pd
import matplotlib.pyplot as plt

# # 读取Excel文件
# file_path = './output_theta.xlsx'  # 将文件路径替换为你的实际路径
# df = pd.read_excel(file_path)

# # 提取时间和角度数据
# time_column = df.iloc[:, 6]  # 第七列为时间
# angle_columns = df.iloc[:, :6]  # 从第二列开始为角度

# # 绘图
# plt.figure(figsize=(10, 6))  # 设置图形大小

# for column in angle_columns.columns:
#     plt.plot(time_column, angle_columns[column], label=column)

# # 添加标签和标题
# plt.xlabel('Time / s')
# plt.ylabel('Joint Position / deg')
# plt.title('Joint Position - Time')
# legend_labels = [f'Joint {i}' for i in range(1, 7)]
# plt.legend(legend_labels)  # 显示图例
# plt.grid(True)  # 添加网格

# plt.savefig('./output_theta.png')  # 保存图形
# # 显示图形
# plt.show()

# 读取Excel文件
file_path = './output_w.xlsx'  # 将文件路径替换为你的实际路径
df = pd.read_excel(file_path)

# 提取时间和角度数据
time_column = df.iloc[:, 6]  # 第七列为时间
angle_columns = df.iloc[:, :6]  # 从第二列开始为角度
window_size = 20

# 对每列进行滑动平均
angle_columns = angle_columns.rolling(window=window_size).mean()

# 绘图
plt.figure(figsize=(10, 6))  # 设置图形大小

for column in angle_columns.columns:
    plt.plot(time_column, angle_columns[column], label=column)

# 添加标签和标题
plt.xlabel('Time / s')
plt.ylabel('Joint Velocity')
plt.title('Joint Velocity - Time')
legend_labels = [f'Joint {i}' for i in range(1, 7)]
plt.legend(legend_labels)  # 显示图例
plt.grid(True)  # 添加网格

plt.savefig('./output_w.png')  # 保存图形
# 显示图形
plt.show()
