Le code pr�sent utilise l'API OpenNI ansi que NITE. Il permet de d�tecter des personnes dans le champs de vision de la cam�ra de profondeur, et d'en extraire le squelette. Les squelettes sont stock�s dans un conteneur, ce qui nous permet � chaque d�tection de posture de calculer la diff�rence avec la posture pr�c�dente. Si la diff�rence est trop �lev�e, on reprend la pose pr�c�dente. Un export du bvh aurai du �tre int�gr� cependant celui-ci n'est pas fonctionnel. 


Pour pouvoir compiler le projet, il faut avoir install� cmake, puis ex�cuter la commande `cmake ..` dans le dossier build. Il faut aussi avoir install� les librairies OpenNI et Nite.
