import math
import pandas as pd

#calculate geographical distance between 2 coordinates
def calculate_distance(lat1, lon1, lat2, lon2):
    R = 6373.0
    lat1 = math.radians(lat1)
    lon1 = math.radians(lon1)
    lat2 = math.radians(lat2)
    lon2 = math.radians(lon2)
    dlon = lon2 - lon1
    dlat = lat2 - lat1
    a = math.sin(dlat / 2)**2 + math.cos(lat1) * math.cos(lat2) * math.sin(dlon / 2)**2
    c = 2 * math.atan2(math.sqrt(a), math.sqrt(1 - a))
    distance = R * c
    return distance
    

#read csv
df = pd.read_csv('data.csv')

#get link points column
link_points = df['link_points']

#get first 100 rows
# link_points = link_points[:1000]

coordinatesByRowIndex = {}
distanceByRowIndex = {}

for i in range(0, len(link_points)):
    #split link points
    coordinates = link_points[i].split(' ')
    (originStr , destinationStr) = (coordinates[0], coordinates[-2])
    if(originStr == "" or destinationStr == ""):
        continue
    #split origin and destination
    origin = originStr.split(',')
    destination = destinationStr.split(',')

    #check if any coordinate has length less than 3
    if(len(origin[0]) < 5 or len(origin[1]) < 5 or len(destination[0]) < 5 or len(destination[1]) < 5):
        continue

    distance = calculate_distance(float(origin[0]), float(origin[1]), float(destination[0]), float(destination[1]))

    if(distance < 1 or distance > 10):
        continue

    if(df['travel_time'][i] > 500):
        continue
    
    coordinatesByRowIndex[i] = (origin, destination)
    distanceByRowIndex[i] = distance

    

print(len(coordinatesByRowIndex))

# add coordinates to dataframe
for x in coordinatesByRowIndex:
        df.loc[x, 'originLat'] = coordinatesByRowIndex[x][0][0]
        df.loc[x, 'originLon'] = coordinatesByRowIndex[x][0][1]
        df.loc[x, 'destinationLat'] = coordinatesByRowIndex[x][1][0]
        df.loc[x, 'destinationLon'] = coordinatesByRowIndex[x][1][1]
        df.loc[x, 'distance'] = distanceByRowIndex[x]

#select travel time, speed, origin, destination and distance columns
df = df[['travel_time', 'speed', 'originLat', 'originLon', 'destinationLat', 'destinationLon','distance']]

#select all rows in coordinatesByRowIndex
df = df.loc[coordinatesByRowIndex.keys()]

df.to_csv('cleanNYData.csv', index=False)





#write to csv
df[:1500].to_csv('addedData.csv')

