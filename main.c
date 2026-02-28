#include"tree.h"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr,"Usage: %s \"path_dico\" \"word\" \n",argv[0]);
        return 1;
    }
    int n_elements;
    // lire_dico va lire un fichier.cvs et mettre les information dans un tableau
    info *dico = lire_dico(argv[1],&n_elements);

    // trier les elemets du tableau par name alphabetiquement
    qsort(dico,n_elements,sizeof(info),comparer_info_name);

    // insert_tree est une fonction recursive vas insert le tableau a partir du milieu , puis divise le tableau et fais une recursion
    // L'arbre devient propriétaire des chaînes du tableau.
    tree *arbre = NULL;
    arbre = insert_tree(dico,0,n_elements-1);
    printf("Racine : %s\n\n",arbre->mot.name);

    printf("Les elements de dico : \n");
    print_infixe(arbre);
    printf("\n\n");

    // appelle recurcive 
    tree *result=search_tree(arbre,argv[2]);

    if (result == NULL)
    {
        printf("element absent");
    }
    else
    {
        printf("Description de %s --> %s \n",result->mot.name,result->mot.descript);
    }
    printf("\n");

    printf("le nombre totale de mots dans la base de donner: %d\n",count_tree_element(arbre));
    free_tree(arbre);

    // free independant de strdup
    for (int i = 0; i < n_elements; i++) {
        free(dico[i].name);
        free(dico[i].descript);
    }
    free(dico); // free_tree se charge deja de name et descript il ne reste plus que le tableau conteneur
}