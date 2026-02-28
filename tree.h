#ifndef  __TREE_H__
#define __TREE_H__

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_WORDS 1024

typedef struct info
{
    char *name ;
    char *descript;
}info;

typedef struct tree
{
    info mot;
    struct tree *tleft;
    struct tree *tright;
    struct tree *parent;
}tree;


tree *new_tree(char *name,char *info);
void free_tree(tree *tr);
tree* insert_tree(info* tableau, int debut, int fin);
void print_tree(tree *tr);
int count_tree_element(tree* tr);
tree* search_tree(tree *tr,char *name);
void print_infixe(tree *tr);
info* lire_dico(char *path,int *nb_elemnts);
int comparer_info_name(const void *a, const void *b);
#endif