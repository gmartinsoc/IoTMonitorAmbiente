from django.conf.urls import url

from . import views

urlpatterns = [
    url(r'^$', views.index, name='index'),
    url(r'^(?P<collection>[a-zA-Z]+)/$', views.dados, name='dados'),
    url(r'^(?P<collection>[a-zA-Z]+)/$', views.temperatura, name='temperatura'),
    url(r'^(?P<collection>[a-zA-Z]+)/$', views.umidade, name='umidade'),
]

