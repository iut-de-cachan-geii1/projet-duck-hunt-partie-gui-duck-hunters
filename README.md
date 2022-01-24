# Projet Pinchzoom

Sujet du projet Pinchzoom à l'IUT de Cachan

## Préface
L'objectif de cette semaine de projet GL est de développer un programme
(en binôme) en __langage C++__ dans l'environnement Qt. Il s'agira dans 
ce programme de faire évoluer un programme existant capable de détecter le
mouvement _pincer/zoomer_ capturé sur écran tactile.

## Cahier des charges
* Le programme initial fait bouger de manière aléatoire des objets
(des souris) sur une scène 2D. A l'approche d'une ou plusieurs objets souris 
voisins, chaque objet souris change de direction pour ne pas entrer en 
collision.

* L'évolution demandé est d'intégrer votre propre objet souris qui obéira à vos 
ordres : 
    - Si un double-toucher/double-clic (avec un seul doigt) sur le plan 2D 
    a été détecté, votre objet souris doit avancer dans cette direction
        - Une bulle avec point d'exclamation doit apparaître sur votre objet
         souris pendant 1s pour indiquer que celui-ci a bien reçu l'ordre
    - En avançant dans cette direction, votre objet souris doit éviter les 
    autres objets souris
    - Une fois arrivé à destination, votre objet souris repart de manière 
    aléatoire

## Etapes du travail 
### Phase 1 : Installation
Suivre le tutoriel video que vous fournira votre professeur pour installer les 
logiciels requis.

### Phase 2 : Exploration
Testez d'abord le programme dans la branche __`master`__
(_Pinchzoom_ avec juste la fonctionnalité _pincer/zoomer_)

### Phase 3 : Développement
Une fois compris, basculer dans une branche __`essai`__ dans lequel vous 
travaillerez.
