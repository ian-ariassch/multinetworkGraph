import math

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

            print("==================================================================")
            print(correctedLineCoordinates)
            print("´++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++")
            for j in range(len(correctedLineCoordinates)-1):
                edge = (correctedLineCoordinates[j].strip(), correctedLineCoordinates[j+1].strip())
                edges.append(edge)
                edge = (correctedLineCoordinates[j+1].strip(), correctedLineCoordinates[j].strip())
                edges.append(edge)

    file.close()

    file = open(filename+".txt", "w")

    neuralNetworkFile = open(filename+"NN.csv", "w")

    #write headers for neural network file
    neuralNetworkFile.write("speed,origin_lat,origin_lon,destination_lat,destination_lon,distance\n")
    

    file.write(str(len(nodes))+"\n")
    # file.write(str(len(edges))+"\n")

    for i in nodes:
        file.write(i["name"] + "|" + i["coords"] + "\n")

    for i in edges:
        file.write(i[0] + "|" + i[1] + "\n")
        distance = calculateRealWorldDistanceinKm(i[0], i[1])
        neuralNetworkFile.write(str(speed) + "," + replaceSpaceWithComma(i[0]) + "," + replaceSpaceWithComma(i[1]) + "," + str(distance) + "\n")


    file.close()
    neuralNetworkFile.close()

cleanCsv("bus")
cleanCsv("railway")