import math

predictedTimeDictionaryBus = {}

predictedTimeDictionaryRailway = {}

def fillDictionary():
    file = open("./predictions/busNNPredictions.csv")
    for i in file:
        i = i.split(",")
        setOfCoords = i[2] + " " + i[3] + "," + i[4] + " " + i[5]
        predictedTimeDictionaryBus[setOfCoords] = i[7]
        

    file.close()

    file = open("./predictions/railwayNNPredictions.csv")
    for i in file:
        i = i.split(",")
        setOfCoords = i[2] + " " + i[3] + "," + i[4] + " " + i[5]
        predictedTimeDictionaryRailway[setOfCoords] = i[7]

    file.close()

    # print(predictedTimeDictionaryBus)


def calculateRealWorldDistanceinKm(edge1, edge2):

    coords1 = edge1.split(" ") 

    lat1 = float(coords1[0])
    lon1 = float(coords1[1])

    coords2 = edge2.split(" ")
    lat2 = float(coords2[0])
    lon2 = float(coords2[1])

    R = 6371
    dLat = math.radians(lat2-lat1)
    dLon = math.radians(lon2-lon1)
    a = math.sin(dLat/2) * math.sin(dLat/2) + math.cos(math.radians(lat1)) * math.cos(math.radians(lat2)) * math.sin(dLon/2) * math.sin(dLon/2)
    c = 2 * math.atan2(math.sqrt(a), math.sqrt(1-a))
    d = R * c
    return d

def replaceSpaceWithComma(line):
    line = line.split(" ")
    return line[1]+","+line[0]

def switchLatLon(line):
    line = line.split(",")
    coord1 = line[0].split(" ")
    coord2 = line[1].split(" ")
    return coord1[1] + " " + coord1[0] + "," + coord2[1] + " " + coord2[0]


def cleanCsv(filename):
    file = open(filename+".csv")

    speed = 0

    if filename == "bus":
        speed = 20
    elif filename == "railway":
        speed = 35

    nodes = []

    edges = []

    for i in file:
        node = {}
        edge = ()
        if i[1] == "P":
            i = i.split(",")
            coordData = i[0]
            node["coords"] = coordData[coordData.find("(")+1:coordData.find(")")]
            node["name"] = i[1]
            nodes.append(node)
        elif i[1] == "L":
            lineCoordinates = i[i.find("(")+1:i.find(")")]
            lineCoordinates = lineCoordinates.split(",")

            print(lineCoordinates)

            correctedLineCoordinates = []

            for singleCoord in lineCoordinates:
                singleCoord = singleCoord.strip()
                singleCoordDivision = singleCoord.split(" ")
                correctedLineCoordinates.append(singleCoordDivision[1]+" "+singleCoordDivision[0])

            for j in range(len(correctedLineCoordinates)-1):
                edge = (correctedLineCoordinates[j].strip(), correctedLineCoordinates[j+1].strip())
                edges.append(edge)
                edge = (correctedLineCoordinates[j+1].strip(), correctedLineCoordinates[j].strip())
                edges.append(edge)

    file.close()

    file = open(filename+".txt", "w")

    neuralNetworkFile = open(filename+"NN.csv", "w")

    neuralNetworkFile.write("speed,origin_lat,origin_lon,destination_lat,destination_lon,distance\n")
    
    file.write(str(len(nodes))+"\n")

    for i in nodes:
        splittedCoords = i["coords"].split(" ")
        i["coords"] = splittedCoords[1] + " " + splittedCoords[0]
        file.write(i["name"] + "|" + i["coords"] + "\n")

    for i in edges:
        if filename == "bus":
            travelTime = predictedTimeDictionaryBus[switchLatLon(i[0]+","+i[1])]
        elif filename == "railway":
            travelTime = predictedTimeDictionaryRailway[switchLatLon(i[0]+","+i[1])]
        file.write(i[0] + "|" + i[1] + "|" + travelTime)
        distance = calculateRealWorldDistanceinKm(i[0], i[1])
        neuralNetworkFile.write(str(speed) + "," + replaceSpaceWithComma(i[0]) + "," + replaceSpaceWithComma(i[1]) + "," + str(distance) + "\n")


    file.close()
    neuralNetworkFile.close()

fillDictionary()
cleanCsv("bus")
cleanCsv("railway")