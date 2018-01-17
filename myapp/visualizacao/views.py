# -*- coding: utf-8 -*-
from django.shortcuts import render
from django.http import HttpResponse
# Create your views here.
from . import mongoDB

def getValores(request, db, collection):
    jsonResponse = consultarBD(collection, db)
    return HttpResponse(jsonResponse)
