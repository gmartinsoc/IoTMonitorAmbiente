# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.shortcuts import render
from django.http import HttpResponse
from . import mongoDB 


# Create your views here.
def index(request):
    leitura = request.GET['leitura']
    mongoDB.inserirBD(leitura)
    return HttpResponse("Leitura salva. Especifique uma collection com um identificado para o ambiente</br>Ex: sala6, ou labweb-ufrrj")


def colecao(request, collection):   
    leitura = request.GET['leitura'] 
    mongoDB.inserirBD(leitura,collection)
    response = "Leitura salva na coleção %s."
    return HttpResponse(response % collection)
