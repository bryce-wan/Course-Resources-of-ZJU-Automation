import pandas as pd
import numpy as np

if __name__ == '__main__':
    # 读取数据
    src_data = pd.read_excel('./a.xlsx', sheet_name='Sheet1')
    tgt_data = pd.read_excel('./b.xlsx', sheet_name='Sheet1')
