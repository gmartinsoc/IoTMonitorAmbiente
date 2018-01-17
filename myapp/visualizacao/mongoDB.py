import pymongo


def consultarBD(collection="", db=""):
    
    mongo = pymongo.MongoClient()
    
    if (db==""):
        db = "moniT" #monitoração de temperatura das salas de servidor da UFRJ
    if (collection==""):
        collection = "temp" #colecao padrao
    
    db = mongo[db]    
    collection = db[collection]
    #collection.insert(jsonInsert)
    return collection.find({}).sort({_id:-1}).limit(1)
    #db.market.find({}).sort({_id:-1}).limit(1) #consulta origial
