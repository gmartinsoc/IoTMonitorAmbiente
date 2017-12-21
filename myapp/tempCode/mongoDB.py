#!/usr/bin/env python
# -*- coding: utf-8 -*-
import pymongo
import json
from datetime import datetime

def inserirBD(jsonInsert, collection="", db=""):

    mongo = pymongo.MongoClient()

    jsonInsert = json.loads(jsonInsert)
    timestamp = datetime.now().strftime('%d-%m-%Y %H:%M:%S')
    jsonInsert['timestamp']=timestamp
    

    if (db==""):
        db = "moniT" #monitoração de temperatura das salas de servidor da UFRJ
    if (collection==""):
        collection = "temp" #colecao padrao
        
    db = mongo[db]    
    collection = db[collection]
    
    collection.insert(jsonInsert)


'''
tp - temperatura em Celcius.
timestamp - horário da leitura no nó.
id_no - identificação do nó (por exemplo, MAC de um ESP8266 que permita identificá-lo).
id_sensor - um nó pode ter vários sensores plugados e espalhados em uma sala. É preciso diferenciá-los.
place - identificação da localização do nó (por sala, neste caso).
'''        
ins ='{"reads":[{"tp":10,"timestamp":10,"id_no":"MAC","id_sensor":"UUID","place":"sala 6"}, {"tp":10,"timestamp":10,"id_no":"MAC","id_sensor":"UUID","place":"sala 6"}, {"tp":10,"timestamp":10,"id_no":"MAC","id_sensor":"UUID","place":"sala 6"}]}'
inserirBD(ins)
