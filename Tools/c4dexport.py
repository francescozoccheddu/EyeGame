import c4d
from c4d import gui
from c4d import documents

def GetPolyTriIndices(obj):
    polys = []
    rpolys = obj.GetAllPolygons()
    for rpoly in rpolys:
        if rpoly.IsTriangle():
            polys.append(rpoly.a - 1)
            polys.append(rpoly.b - 1)
            polys.append(rpoly.c - 1)
        else:
            raise ValueError(str(obj) + ' has non-triangle polygons')
    return polys

def GetPolyVertPositions(obj):
    poss = []
    rposs = obj.GetAllPoints()
    for rpos in rposs:
        poss.append(rpos.x)
        poss.append(rpos.y)
        poss.append(rpos.z)
    return poss

def SerializePolyObj(obj):
    txt = ''
    polys = obj.GetAllPolygons()
    for poly in polys:
        

    return txt

def main():
    doc = documents.GetActiveDocument()
    objs = doc.GetActiveObjects(c4d.GETACTIVEOBJECTFLAGS_0)
    for obj in objs:
        if obj.GetType() == c4d.Opolygon:
            SerializePolyObj(obj)


if __name__=='__main__':
    try:
        main()
        gui.MessageDialog('Done')
    except Exception as e:
        gui.MessageDialog(str(e))
