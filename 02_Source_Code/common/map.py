import pandas as pd
import folium

# Configuration
FILE_PATH = 'pec_to_mohali.xlsx'
# FILE_PATH = 'dry_run_dhakouli.xlsx'
FILE_PATH = 'pec_to_hills.xlsx'
# FILE_PATH = 'hills_to_pec.xlsx'

SHEET_NAME = 'unique'
OUTPUT_FILE = 'route_map_custom_colors.html'

# Load and preprocess data
df = pd.read_excel(FILE_PATH, sheet_name=SHEET_NAME)
df['time'] = pd.to_datetime(df['time'], format='%H:%M:%S:%f')
df_sorted = df.sort_values('time').reset_index(drop=True)

# Define colors
normal_color = "#3fd831"  # bright green
highlight_colors = {
    'LANE_CHANGE_LEFT': 'cyan',
    'LANE_CHANGE_RIGHT': 'purple'
}

# Style function
def get_style(speed, status):
    if speed <= 1:
        return ('black', 8)
    elif speed <= 10:
        return ('orange', 8)
    elif status in highlight_colors:
        return (highlight_colors[status], 10)
    else:
        return (normal_color, 3)

# Center map
avg_lat, avg_lng = df_sorted['lat'].mean(), df_sorted['lng'].mean()

# Initialize map (no base tiles)
m = folium.Map(location=[avg_lat, avg_lng], zoom_start=14, tiles=None)

# Add custom CartoDB tile layer with retina support
folium.TileLayer(
    tiles='https://{s}.basemaps.cartocdn.com/rastertiles/voyager/{z}/{x}/{y}{r}.png',
    attr='&copy; <a href="http://www.openstreetmap.org/copyright">OpenStreetMap</a>, &copy; <a href="https://carto.com/attributions">CARTO</a>',
    name='CartoDB Voyager',
    subdomains='abcd',
    max_zoom=20,
    min_zoom=0,
    detect_retina=True,
).add_to(m)

# Draw route
for i in range(1, len(df_sorted)):
    start = (df_sorted.loc[i - 1, 'lat'], df_sorted.loc[i - 1, 'lng'])
    end = (df_sorted.loc[i, 'lat'], df_sorted.loc[i, 'lng'])
    speed = df_sorted.loc[i, 'speed']
    status = df_sorted.loc[i, 'status']
    color, weight = get_style(speed, status)
    folium.PolyLine([start, end], color=color, weight=weight, opacity=0.9).add_to(m)

# Markers for start and end
start = df_sorted.iloc[0]
end = df_sorted.iloc[-1]
folium.Marker([start['lat'], start['lng']], popup='Start', icon=folium.Icon(color='green')).add_to(m)
folium.Marker([end['lat'], end['lng']], popup='End', icon=folium.Icon(color='red')).add_to(m)

# Legend
legend_html = '''
<div style="
 position: fixed; 
 bottom: 50px; left: 50px; width: 250px; height: 160px; 
 background-color: white; border:2px solid grey; z-index:9999; font-size:14px;
 padding: 10px;
">
 <b>Legend</b><br>
 <i style="background: #3fd831; width: 12px; height: 12px; display: inline-block;"></i>&nbsp;Normal<br>
 <i style="background: orange; width: 12px; height: 12px; display: inline-block;"></i>&nbsp;Slowed (<10 km/h)<br>
 <i style="background: black; width: 12px; height: 12px; display: inline-block;"></i>&nbsp;Stopped (≤1 km/h)<br>
 <i style="background: cyan; width: 12px; height: 12px; display: inline-block;"></i>&nbsp;Lane Change Left<br>
 <i style="background: purple; width: 12px; height: 12px; display: inline-block;"></i>&nbsp;Lane Change Right
</div>
'''
m.get_root().html.add_child(folium.Element(legend_html))

# Save to HTML
m.save(OUTPUT_FILE)
print(f"Map saved to {OUTPUT_FILE}")
