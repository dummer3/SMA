<div align="center">
    <img src = "./Photos/logo.jpg">
</div>

![Catch](https://img.shields.io/badge/Catch-2-brightgreen)
![CMake](https://img.shields.io/badge/CMake-3-brightgreen)
![Gprof](https://img.shields.io/badge/GNU-gprof-brightgreen)
![Doxygen](https://img.shields.io/badge/Doxygen-Comments-brightgreen)

# Simulation multi-agents

## Question

  * [ ] 2 Actions pour banane, l'une lorsque posé, l'autre lorsque le joueur l'utilise 
  * [ ] mettre à jour la position du soleil sur la map si un joueur la possède ?
  * [ ] Action nécessitant différent paramètre et type de retour ?
  * [ ] Comment faire lorsque collision entre les joueurs.

## Implémentation

### Map

*Pour tester la map*
g++ -Wall -Wextra -g -o exec Object.cpp Iplaceable.cpp Box.cpp Sun.cpp Map.cpp test.cpp 

- [x] Map présentation (entier)
- [x] Ajout Map soleil
- [x] Ajout Map Box
- [x] Width et Height valide
- [x] S'assurer que le nbr de boxs et de suns soit cohérent avec la génération choisie (2 ou 4)
- [ ] S'assurer qu'il y a assez d'espace pour poser les boxs et suns
- [ ] Ajout Map objet
- [ ] Ajout joueur sur Map
- [ ] Déplacement Joueur sur Map

### Objet et Joueur

- [ ] Contrôle soleil par les joueurs
- [ ] Bouger tous les objets dans diff fichier

- [ ] GameManager
- [ ] Champignon
- [ ] Banane
- [ ] CarapaceRouge
- [ ] Action Box
- [ ] Action Soleil 
- [ ] Equipe

## Documentation
  
- [ ] Map (75%)

## Optimisation

- [ ] Simplifier GénérerBox/Sun en renvoyant la position pour Half et Quarter (au lieu de tout parcourir)
- [ ] Tiles en tableau dynamique (! penser au destructeur)

## Allocation et free

- [x] Destructeur de Map 
- [ ] Autre ...


# START README
## Background
The project is to simulate the Mario Kart game in order to implement a multi-agent simulation program.
### Class diagram
___THIS IS A DIAGRAM OF CLASSES___
### Use case diagram
___THIS IS A DIAGRAM OF USE CASE___
## Usage
___USAGE___
## Maintainers
@MatthiasBenquet
@dummer3
@CestMerNeil
## Contributing
## License
___Est-ce que nous avons besoin d'un license?___