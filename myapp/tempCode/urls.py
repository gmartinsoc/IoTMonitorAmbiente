from django.conf.urls import url

from . import views

urlpatterns = [
    url(r'^$', views.index, name='index'),
    url(r'^(?P<collection>[a-z]+)/$', views.colecao, name='colecao'),
]

