# 🌳 Dictionnaire C - Arbre Binaire de Recherche Équilibré

![Language](https://img.shields.io/badge/Language-C-blue.svg)
![OS](https://img.shields.io/badge/OS-Linux%20Ubuntu-orange.svg)
![Memory](https://img.shields.io/badge/Valgrind-0%20Leaks-success.svg)

                  [Milieu du tableau]
                 /                   \
        [Milieu Gauche]         [Milieu Droit]
         /           \           /          \
      [M-G-G]     [M-G-D]     [M-D-G]    [M-D-D]

Un moteur de dictionnaire ultra-rapide écrit en C. Ce projet charge un lexique depuis un fichier CSV et le structure en mémoire sous forme d'**Arbre Binaire de Recherche (ABR) parfaitement équilibré**, garantissant des temps de recherche optimaux.

## 🚀 Utilisation
./dico_tree <chemin_vers_csv> "<mot_a_chercher>"
Exemple :
./dico_tree dico.csv "Linux"

📂 Format du fichier CSV attendu
Le parseur s'attend à un format strict pour garantir l'intégrité des données :
Mot , Description complète du mot./

## Fonctionnement interne
Le probleme resolue : des donnees deja triees degenere un abre en une simple liste chaînée . 
Ce projet résout ce problème avec un algorithme récursif qui extrait systématiquement l'élément médian du segment courant pour en faire une racine, garantissant l'equilibre gauche et droite

Tri rapide : Utilisation de qsort de la libc pour trier le tableau alphabétiquement en complexité O(n*log(n)).

## 📈 Avantages et Performances
Complexité de recherche optimisée : Grâce à l'équilibrage parfait à la construction, la recherche s'effectue strictement en O(log n). 
Chercher un mot parmi 1 000 000 d'entrées prendra au maximum ~20 opérations.

Sécurité de la mémoire (Zero Leaks) : L'architecture sépare la structure de l'arbre (les nœuds) des données réelles (le texte). Allocation et libération sont gérées de manière déterministe. Testé sous Valgrind avec 0 bytes definitely lost.