#include"tree.h"

tree *new_tree(char *name,char *info)
{
    tree *tr = malloc(sizeof(*tr)); // place pour tleft/tright/paren/value
    if (tr == NULL)
    {
        fprintf(stderr,"Erreur allocartion\n");
        exit(EXIT_FAILURE);
    }
    tr->mot.name = strdup(name); // copy + malloc
    tr->mot.descript = strdup(info);
    if (tr->mot.name == NULL || tr->mot.descript == NULL) 
    {
        fprintf(stderr, "Erreur allocation chaines\n");
        exit(EXIT_FAILURE);
    }

    tr->tleft = NULL; //il n'y a rien pour l'instant
    tr->tright = NULL;
    tr->parent = NULL;

    return tr;
}


void free_tree(tree *tr)
{
    if (tr == NULL)
    {
        return;
    } 
    free_tree(tr->tleft);
    free_tree(tr->tright);

    free(tr);
}


tree* insert_tree(info* tableau, int debut, int fin) 
{
    if (debut > fin) 
    {
        return NULL;
    }

    int milieu = (debut + fin) / 2;
    if (tableau[milieu].name == NULL) 
    {
        fprintf(stderr,"Erreur allocartion\n");
        exit(EXIT_FAILURE);
    }

    //Créer le nœud avec ce milieu
    tree* tr = new_tree(tableau[milieu].name, tableau[milieu].descript);
    if (tr == NULL)
    {
        fprintf(stderr,"Erreur allocartion\n");
        exit(EXIT_FAILURE);
    }
    //Construire les sous-arbres de la même manière
    tr->tleft = insert_tree(tableau, debut, milieu - 1); // ne plus prendre le milieu
    if (tr->tleft) tr->tleft->parent = tr;

    tr->tright = insert_tree(tableau, milieu + 1, fin);// ne plus prendre le mileu aussi
    if (tr->tright) tr->tright->parent = tr;

    return tr;
}


tree* search_tree(tree *tr,char *name)
{
    if (tr == NULL || strcmp(name,(tr->mot.name)) == 0)
    {
        return tr;
    }

    // on cherche a gauche si c'est petit
    if (strcmp(name,(tr->mot.name)) < 0)
    {
        return search_tree(tr->tleft, name);
    }

    // La valeur cherchée est plus grande -> on ne cherche qu'à droite
    return search_tree(tr->tright, name);
}


void print_tree(tree *tr)
{
    if (tr == NULL)
    {
        printf("fin\n");
        return;
    }
    printf("%s -> %s\n",tr->mot.name,tr->mot.descript);    

    if (tr->tleft != NULL)
    {
        print_tree(tr->tleft);
    }
    if (tr->tright != NULL)
    {
        print_tree(tr->tright);
    }
}

void print_infixe(tree *tr) 
{
    if (tr == NULL) return;
    
    print_infixe(tr->tleft);   // On vas a la gauche
    printf("[%s] ", tr->mot.name);  // On affiche tout a gauche
    print_infixe(tr->tright);  // On vas la droite
}

int count_tree_element(tree* tr)
{
    if (tr == NULL)
    {
        return 0;
    }
    return (count_tree_element(tr->tleft)+count_tree_element(tr->tright)+1);
}

info* lire_dico(char *path,int *nb_elemnts)
{
    *nb_elemnts = 0;
    FILE *file = fopen(path,"r");
    if (file == NULL) {
        perror("Erreur ouverture fichier");
        exit(EXIT_FAILURE);
    }
    info* temp = malloc(sizeof(*temp)*1024);
    if (temp == NULL)
    {
        fprintf(stderr,"Erreur allocation\n");
        exit(EXIT_FAILURE);
    }
    char ligne[1124];
    int i = 0;
    while (i < 1024 && fgets(ligne, sizeof(ligne), file))
    {
        char n[100];
        char d[MAX_WORDS];
        // name et descript ne sont pas encore alouer
        //on peut pas encore utiliser strcpy Solution stdup

        // %99[^,] : "ignore les sauts de ligne Lis jusqu'à 99 caractères tant que ce n'est pas une virgule".
        //, : "Saute la virgule et les espaces qui servent de séparation".
        //%1023[^/] : "Lis tout (y compris les virgules et les espaces) jusqu'à ce que tu tombes sur le slash /"
        if (sscanf(ligne," %99[^,] , %1023[^/]", n, d) == 2)  
        {
            temp[i].name = strdup(n);
            temp[i].descript = strdup(d);
            i++;
            *nb_elemnts = *nb_elemnts +1;
        } else {
            printf("Ligne ignorée (format incorrect) : %s", ligne);
        }
    } 

    fclose(file);
    return temp;
}

int comparer_info_name(const void *a, const void *b) // obliger de faire void , argument pour qsort
{
    const info *infoA = (const info*)a;
    const info *infoB = (const info*)b;
    return strcmp(infoA->name, infoB->name);
}
