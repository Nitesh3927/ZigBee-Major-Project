import csv

class DataLogger:
    def __init__(self, file_name='log.txt'):
        self.file_name = file_name

    def log(self, data):
        with open(self.file_name, mode='a', newline='') as file:
            file.write(data)
        # with open(self.file_name, mode='a', newline='') as file:
        #     writer = csv.writer(file)
        #     writer.writerow([data])
