import pymongo
#import json


def consultarBD(collection="", db=""):
    
    mongo = pymongo.MongoClient()
    
    if (db==""):
        db = "moniT" #monitoração de temperatura das salas de servidor da UFRJ
    if (collection==""):
        collection = "temp" #colecao padrao
    
    db = mongo[db]    
    collection = db[collection]
    #collection.insert(jsonInsert)
    jsonResposta = collection.find().sort("_id",-1).limit(1)
    jsonResposta = jsonResposta[0]
    return jsonResposta['reads'][-1] 
    
#print (consultarBD("sala6","monServ"))
