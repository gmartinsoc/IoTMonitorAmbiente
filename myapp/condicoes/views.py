# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.shortcuts import render
from django.http import HttpResponse
#from . import mongoDB

def index(request):
    pass

def dados():
    '''
        retorna dados de temperatura e umidade do dia
        media de leituras de cada "reads" cadastrado no banco
    '''
    pass
    
def temperatura():
    '''
        temperatura - retornar valor mais recente cadastrado no banco
    '''
    pass
    
def umidade():
    '''
        umidade - retorna valor mais recente cadastrado no banco
    ''' 
    pass
    
def picoTemperatura():
    pass
