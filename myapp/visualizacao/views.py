# -*- coding: utf-8 -*-
from django.shortcuts import render
from django.http import HttpResponse
# Create your views here.
from . import mongoDB
import json

def getValores(request, db, collection):
    jsonResponse = mongoDB.consultarBD(collection, db)
    #print (jsonResponse)
    return HttpResponse(json.dumps(jsonResponse),content_type="application/json")
