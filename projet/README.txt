Le code présent utilise l'API OpenNI ansi que NITE. Il permet de détecter des personnes dans le champs de vision de la caméra de profondeur, et d'en extraire le squelette. Les squelettes sont stockés dans un conteneur, ce qui nous permet à chaque détection de posture de calculer la différence avec la posture précédente. Si la différence est trop élevée, on reprend la pose précédente. Un export du bvh aurai du être intégré cependant celui-ci n'est pas fonctionnel. 


Pour pouvoir compiler le projet, il faut avoir installé cmake, puis exécuter la commande `cmake ..` dans le dossier build. Il faut aussi avoir installé les librairies OpenNI et Nite.
