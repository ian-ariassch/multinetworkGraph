


def cleanCsv(filename):
    file = open(filename+".csv")

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
            for j in range(len(lineCoordinates)-1):
                edge = (lineCoordinates[j].strip(), lineCoordinates[j+1].strip())
                edges.append(edge)
                edge = (lineCoordinates[j+1].strip(), lineCoordinates[j].strip())
                edges.append(edge)

    file.close()

    file = open(filename+".txt", "w")

    file.write(str(len(nodes))+"\n")
    # file.write(str(len(edges))+"\n")

    for i in nodes:
        file.write(i["name"] + "|" + i["coords"] + "\n")

    for i in edges:
        file.write(i[0] + "|" + i[1] + "\n")

    file.close()

cleanCsv("bus")
cleanCsv("railway")