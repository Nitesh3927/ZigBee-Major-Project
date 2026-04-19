import pandas as pd
import matplotlib.pyplot as plt
import os
from typing import Tuple

def read_data(acc_file: str, info_file: str) -> Tuple[pd.DataFrame, pd.DataFrame]:
    acc_data = pd.read_excel(acc_file)
    info_data = pd.read_csv(info_file)
    return acc_data, info_data

def filter_data(acc_data: pd.DataFrame, start_time: float, stop_time: float) -> pd.DataFrame:
    filtered_data = acc_data[(acc_data['time'] >= start_time) & (acc_data['time'] <= stop_time)].copy()
    filtered_data.loc[:, 'Y'] = filtered_data['Y'] - 0.18
    return filtered_data

def smooth_data(data: pd.DataFrame, window_size: int = 5) -> pd.DataFrame:
    return data.rolling(window=window_size, min_periods=1).mean()

def plot_graph(filtered_data: pd.DataFrame, graph_name: str) -> None:
    smoothed_data = smooth_data(filtered_data)
    
    plt.rcParams['font.family'] = 'Arial'
    fig, ax = plt.subplots(figsize=(10, 5))
    
    ax.plot(smoothed_data['time'], smoothed_data['Y'], label='Accleration vs time', color='#1f77b4')
    ax.axhline(y=0, color='black', linestyle='--', linewidth=2)
    ax.set_ylabel('Acceleration of the car (in multiples of g)', fontsize=12, fontweight='bold', labelpad=15)
    ax.set_xlabel('Time (s)', fontsize=12, fontweight='bold', labelpad=15)
    ax.legend(loc='upper right', fontsize=10)
    ax.grid(True, linestyle='--', linewidth=0.5)
    
    fig.suptitle(f'{graph_name}', fontsize=14, fontweight='bold')
    fig.tight_layout(rect=[0, 0.03, 1, 0.95])
    
    plt.savefig(f'ashutosh_results/{graph_name}.png')
    plt.close()

def plot_graphs(acc_file: str, info_file: str) -> None:
    acc_data, info_data = read_data(acc_file, info_file)
    
    if not os.path.exists('ashutosh_results'):
        os.makedirs('ashutosh_results')
    
    for index, row in info_data.iterrows():
        graph_name = row['Graph Name']
        start_time = row['Start Time']
        stop_time = row['Stop Time']
        
        filtered_data = filter_data(acc_data, start_time, stop_time)
        plot_graph(filtered_data, graph_name)

if __name__ == "__main__":
    acc_file = 'Acc_testing_ash.xlsx'
    info_file = 'ash_info.csv'
    plot_graphs(acc_file, info_file)