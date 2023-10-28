#!/usr/bin/env python

# -*- coding: utf-8 -*-

from mpmath import *
from matplotlib import pyplot as plt


def calc_couple(pressionMax_dixiemeDeBar):
    pressionMax = pressionMax_dixiemeDeBar / 10

    # # Seringue
    rayonSeringue = 3.9#cm
    hauteurSeringue = 19.5#cm
    volumeUtileSeringue = 500#cm2
    airePressionSeringue = rayonSeringue * rayonSeringue * 3.14

    # # Compartiment
    # # volumeCompartiment = 1500#cm3
    # volumePerdu = 1000#cm3
    # volumeCompartimentCompressible = volumeCompartiment - volumeUtileSeringue - volumePerdu#cm3

    # # Pressions
    # # 1bar = 10N/cm2
    # pressionExterieure = 1#bar

    # pressionMaxCompartiment = volumeCompartimentCompressible / (volumeCompartimentCompressible - volumeUtileSeringue)#bar

    forceSeringue = ((pressionMax) * 10) * airePressionSeringue#N


    # Conversion couple
    diametreMoyenVisDePuissance = 14/1000# mm en m
    coeffFrotementPasDeVis=0.15
    pasDeVis=2/1000# mm en m
    # angleHeliceVis=mp.atan(pasDeVis/(3.14*diametreMoyenVisDePuissance))
    angleHeliceVis=0.464

    # angleHeliceVis=mp.radians(4.5)  
    coupleLevage = 0.5*diametreMoyenVisDePuissance*forceSeringue*(((coeffFrotementPasDeVis*mp.sec((0.2618)))+mp.tan(angleHeliceVis))/(1-(coeffFrotementPasDeVis*mp.sec((0.2618))*mp.tan(angleHeliceVis))))
    return coupleLevage * 10.19716212978; #kg/cm


def calc_vitesse_compression(pasDeVisEnMMFois10):
    pasDeVis = pasDeVisEnMMFois10 / 10000#m
    rotationMoteur = 25/4#rpm
    longeurSeringue = 19#cm
    vitesse = rotationMoteur * pasDeVis
    tempsRemplissage = longeurSeringue / vitesse
    return tempsRemplissage / 60




xCouple = list(range(1, 50, 1))
yCouple = list(map(calc_couple, xCouple))

xVitesse = list(range(10, 50, 1))
yVitesse = list(map(calc_vitesse_compression, xVitesse))


# plt.plot(xCouple,yCouple)
# plt.plot(xVitesse,yVitesse)

# plt.show()

print(calc_vitesse_compression(20))