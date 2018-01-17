from django.conf.urls import url

from . import views

urlpatterns = [
    url(r'^$', views.index, name='index'),
    url(r'^(?P<collection>[a-zA-Z0-9]+)/$', views.colecao, name='colecao'),
    url(r'^(?P<bd>[a-zA-Z0-9]+)/(?P<collection>[a-zA-Z0-9]+)/$', views.banco, name='banco'), 
]

