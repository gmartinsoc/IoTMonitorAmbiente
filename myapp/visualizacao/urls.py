from django.conf.urls import url

from . import views

urlpatterns = [
    url(r'^(?P<db>[a-zA-Z0-9]+)/(?P<collection>[a-zA-Z0-9]+)/$', views.getValores, name='getValores'), 
]

