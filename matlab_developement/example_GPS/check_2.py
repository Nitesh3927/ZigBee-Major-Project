import pandas as pd

# Load the Excel file
file_path = "gps.xlsx"
df = pd.read_excel(file_path, header=None)  # Read the file

# Round the first column (timestamps) to 3 decimal places
df.iloc[:, 0] = df.iloc[:, 0].apply(lambda x: round(x, 3) if isinstance(x, (int, float)) else x)

# Separate timestamp and ASCII columns
time_col = df.iloc[:, 0]  # First column (timestamps)
ascii_cols = df.iloc[:, 1:]  # Remaining columns (ASCII values)

# Function to convert ASCII values to text
def ascii_to_sentence(row):
    try:
        return ''.join(chr(int(round(float(val)))) for val in row.dropna() if str(val).replace('.', '', 1).isdigit() and 32 <= int(float(val)) <= 126)
    except ValueError:
        return None  # Skip rows with invalid values

# Convert each row to a readable sentence
sentences = ascii_cols.apply(ascii_to_sentence, axis=1)

# Combine timestamps and sentences
output_data = pd.DataFrame({"Timestamp": time_col, "Sentence": sentences})

# Drop rows where sentence extraction failed
output_data = output_data.dropna()

# Save to text file
output_file = "gps_sentences.txt"
with open(output_file, "w", encoding="utf-8") as f:
    for _, row in output_data.iterrows():
        f.write(f"{row['Timestamp']}: {row['Sentence']}\n")

print(f"GPS sentences saved to {output_file}")
