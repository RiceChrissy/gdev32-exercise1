# f {vertex index}/{vertex texture coordinate index}/{vertex normal index}
v = [] #list of sets of coordinates of shape vertices
vn = [] #list of sets of vertex normals
vt = [] #list of sets of texture coordinates
f = [] #list of faces
finalVertices = []
finalIndices = [] # was actually not needed in the end, but left it here anyway

def appendColor():
    finalVertices.append(str(1) + '.0')
    finalVertices.append(str(1) + '.0')
    finalVertices.append(str(1) + '.0')

def parseVertices(vertices):
    objfile = open(vertices)
    


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
        elif(line[0] == "v" and line[1] == "t"): # texture coordinates
            x = line.split()
            if("vt" in x):
                x.remove("vt")
            y = [float(texCoords) for texCoords in x]
            vt.append(y)
        elif(line[0] == "f" and line[1] == " "): # change to support the faces which include the textures
            lineReplaced = line.replace('/',' ')
            x = lineReplaced.split()
            if("f" in x):
                x.remove("f")
            y = [int(faces) for faces in x]
            f.append(y)

    for faces in f:
        # vertex / texture / normal
        fv1_index = faces[0]
        fvn1_index = faces[2]
        fvt1_index = faces[1]

        fv2_index = faces[3]
        fvn2_index = faces[5]
        fvt2_index = faces[4]

        fv3_index = faces[6]
        fvn3_index = faces[8]
        fvt3_index = faces[7]

        # pair 1
        for coordinates in v[fv1_index-1]:
            finalVertices.append(coordinates)
        appendColor()
        for coordinates in vn[fvn1_index-1]:
            finalVertices.append(coordinates)
        for coordinates in vt[fvt1_index-1]:
            finalVertices.append(coordinates)

        # pair 2
        for coordinates in v[fv2_index-1]:
            finalVertices.append(coordinates)
        appendColor()
        for coordinates in vn[fvn2_index-1]:
            finalVertices.append(coordinates)
        for coordinates in vt[fvt2_index-1]:
            finalVertices.append(coordinates)

        # pair 3
        for coordinates in v[fv3_index-1]:
            finalVertices.append(coordinates)
        appendColor()
        for coordinates in vn[fvn3_index-1]:
            finalVertices.append(coordinates)
        for coordinates in vt[fvt3_index-1]:
            finalVertices.append(coordinates)
    
    
    with open('newVertices.txt','w') as newVerts:
        count = 0
        for e in finalVertices:
            newVerts.write(str(e) + 'f')
            count+=1
            newVerts.write(', ')
            if(count == 11):
                newVerts.write('\n')
                count=0
    print(finalVertices)
parseVertices("basic_cube_triangulated.obj")