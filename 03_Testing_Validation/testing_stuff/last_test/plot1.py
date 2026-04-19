from gmplot import gmplot

# List of coordinates
latitudes = [
    30.7668163, 30.7668122, 30.7668122, 30.7668122, 30.7668122, 30.7668122,
    30.7668038, 30.7668038, 30.7668038, 30.7668038, 30.7668038,
    30.7668037, 30.7668037, 30.7668037, 30.7668037, 30.7668037,
    30.7668045, 30.7668045, 30.7668045, 30.7668045
]

longitudes = [
    76.7889395, 76.7889355, 76.7889355, 76.7889355, 76.7889355, 76.7889355,
    76.7889292, 76.7889292, 76.7889292, 76.7889292, 76.7889292,
    76.7889288, 76.7889288, 76.7889288, 76.7889288, 76.7889288,
    76.7889280, 76.7889280, 76.7889280, 76.7889280
]

# Center of the map (first coordinate)
gmap = gmplot.GoogleMapPlotter(latitudes[0], longitudes[0], 20, apikey='YOUR_GOOGLE_MAPS_API_KEY')

# Plot path
gmap.plot(latitudes, longitudes, color='red', edge_width=4)

# Save to HTML
gmap.draw("simple_path_map.html")

print("Map has been saved to 'simple_path_map.html'")
