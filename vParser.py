objfile = open("chikipi.obj")

v = [] #list of sets of coordinates of shape vertices
vn = [] #list of sets of vertex normals
f = [] #list of faces
finalVertices = []
finalIndices = []


for line in objfile:
    if(line[0] == "v" and line[1] == " "):
        x = line.split()
        if("v" in x):
            x.remove("v")
        y = [float(vertices) for vertices in x]
        v.append(y)
    elif(line[0] == "v" and line[1] == "n"):
        x = line.split()
        if("vn" in x):
            x.remove("vn")
        y = [float(vertNormals) for vertNormals in x]
        vn.append(y)
    elif(line[0] == "f" and line[1] == " "):
        lineReplaced = line.replace('//',' ')
        x = lineReplaced.split()
        if("f" in x):
            x.remove("f")
        y = [int(faces) for faces in x]

        #creating indices

        finalIndices.append(y[0])
        finalIndices.append(y[2])
        finalIndices.append(y[4])
        finalIndices.append(y[1])
        finalIndices.append(y[3])
        finalIndices.append(y[5])
        f.append(y)


def appendColor():
    finalVertices.append(str(1) + '.0')
    finalVertices.append(str(1) + '.0')
    finalVertices.append(str(0) + '.0')

for faces in f:
    fv1_index = faces[0]
    fvn1_index = faces[1]
    fv2_index = faces[2]
    fvn2_index = faces[3]
    fv3_index = faces[4]
    fvn3_index = faces[5]

    # pair 1
    for coordinates in v[fv1_index-1]:
        finalVertices.append(coordinates)
    appendColor()
    for coordinates in vn[fvn1_index-1]:
        finalVertices.append(coordinates)

    # pair 2
    for coordinates in v[fv2_index-1]:
        finalVertices.append(coordinates)
    appendColor()
    for coordinates in vn[fvn2_index-1]:
        finalVertices.append(coordinates)

    # pair 3
    for coordinates in v[fv3_index-1]:
        finalVertices.append(coordinates)
    appendColor()
    for coordinates in vn[fvn3_index-1]:
        finalVertices.append(coordinates)
    
with open('chikipi.txt','w') as chikipi:
    count = 0
    for e in finalVertices:
        chikipi.write(str(e) + 'f')
        count+=1
        chikipi.write(', ')
        if(count == 9):
            chikipi.write('\n')
            count=0

with open('chikipi_Indices.txt', 'w') as cIndices:
    count = 0
    for ind in finalIndices:
        cIndices.write(str(ind-1) + ', ')
        count+=1
        if(count == 3):
            count = 0
            cIndices.write('\n')
