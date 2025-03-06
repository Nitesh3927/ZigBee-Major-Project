import re

def parse_log_file(filepath):
    with open(filepath, 'r') as file:
        log_data = file.readlines()
    return log_data

def compute_throughput(log_data):
    packet_count = 0
    start_time = None
    end_time = None

    for line in log_data:
        match = re.search(r'(\d{2}:\d{2}:\d{2}:\d{3}) -> Receive\((\d+)\)', line)
        if match:
            time_str = match.group(1)
            packet_size = int(match.group(2))
            packet_count += 1
            if start_time is None:
                start_time = time_str
            end_time = time_str

    if start_time and end_time:
        start_time_ms = convert_to_milliseconds(start_time)
        end_time_ms = convert_to_milliseconds(end_time)
        duration_ms = end_time_ms - start_time_ms
        throughput = (packet_count * 127 * 8) / (duration_ms / 2000)  # bits per second
        return throughput
    else:
        return 0

def convert_to_milliseconds(time_str):
    h, m, s, ms = map(int, time_str.split(':'))
    return ((h * 3600 + m * 60 + s) * 1000) + ms

if __name__ == "__main__":
    log_filepaths = [
        r'C:\Users\Nitesh\Desktop\exp\Log\ash_reciver\Fixed_Distance_90_End_Device.txt',
        r'C:\Users\Nitesh\Desktop\exp\Log\ash_reciver\Fixed_Distance_180_End_Device.txt',
        r'C:\Users\Nitesh\Desktop\exp\Log\ash_reciver\Fixed_Distance_270_End_Device.txt',
        r'C:\Users\Nitesh\Desktop\exp\Log\ash_reciver\Fixed_Distance_300_End_Device.txt'
    ]
    
    for log_filepath in log_filepaths:
        log_data = parse_log_file(log_filepath)
        throughput = compute_throughput(log_data)
        print(f"Throughput for {log_filepath}: {throughput} bits per second")
