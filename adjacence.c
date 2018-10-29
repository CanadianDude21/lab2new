/*
 *  Création : Francis Bourdeau
 *  Fichier  : adjacence.h
 *  Cours    : ELE440
 *
 *
 *  Ce module contient des fonctions utilitaires permettant d'obtenir et
 *  de sauvegarder la matrice d'adjacence d'un graphe.
 *
 *  Les services offerts sont les suivants:
 *
 *      - lire_adjacence    : Permet de lire la matrice d'adjence d'un graphe à
 *                            partir d'un fichier csv.
 *
 *      - ecrire_adjacence  : Permet de sauvegarder la matrice d'adjence d'un
 *                            graphe à l'intérieur d'un fichier csv.
 *
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/******************************************************************************/
/*                  DEFINITIONS DE TYPES ET DE CONSTANTES                     */
/******************************************************************************/

//La plus longue ligne accepte dans les fichier csv.
#define LONGUEUR_LIGNE_MAX      1024

/******************************************************************************/
/*                  DÉCLARATION DES FONCTIONS PRIVÉES                         */
/******************************************************************************/

/******************************************************************************/
/*          IMPLÉMENTATIONS DES FONCTIONS PUBLIQUES ET PRIVÉES                */
/******************************************************************************/

//
// Permet de lire une matrice d'adjacence dans le fichier reçu.
//
int ** lire_adjacence(char *nom_fichier, int* nb_noeud)
{

    FILE *fichier;                  //Le fichier dans lequel on lit la matrice d'adjacence.
    char ligne[LONGUEUR_LIGNE_MAX]; //Une ligne du fichier contenant la matrice d'adjacence.

    int ** adjacence;               //La matrice d'adjacence lue.

    int i, j;                       //Itérateur permettant de parser le fichier csv.

    //On tente d'ouvre le fichier en lecture.
    //On stop le programme lorsque le fichier ne peut être ouvert correctement.
    fichier = fopen(nom_fichier, "rt");
    if (fichier == NULL)
    {
        sprintf(ligne, "Le fichier <%s> ne peut etre ouvert.\n", nom_fichier);
        perror(ligne);
        exit(-1);
    }

    //On lit le nombre de noeud et l'on crée la matrice d'adjacence.
    //On se debarasse ensuite du reste de la premiere ligne.
    fscanf(fichier, "%i", nb_noeud);
    adjacence = (int**) malloc(sizeof(int*) * (*nb_noeud));
    fgets(ligne, LONGUEUR_LIGNE_MAX, fichier);

    //On crée chaque ligne de la matrice d'adjacence.
    for (i = 0; i < (*nb_noeud); i++)
    {
        adjacence[i] = (int *) malloc(sizeof(int) * (*nb_noeud));

        //On se débarasse de l'indice de la ligne.
        fscanf(fichier, "%i", &j);

        //On extrait chaque valeur de la matrice d'adjacence pour la ligne courante.
        for (j = 0; j < (*nb_noeud); j++)
        {
            fscanf(fichier, ",%i", &adjacence[i][j]);
        }

        //On se débarasse du saut de ligne
        fscanf(fichier, "\n");
    }

    fclose(fichier);
    return adjacence;
}

//
// Permet d'écrire la matriche d'adjacence reçu dans un fichier csv.
//
void ecrire_adjacence(char * nom_fichier, int ** adjacence, int nb_noeud)
{
    FILE *fichier;                  //Le fichier dans lequel on ecrit la matrice d'adjacence.
    int i, j;                       //Itérateur permettant parcourir la matrice à sauvegarder.

    //On tente d'ouvre le fichier en écriture.
    //Ca ne peut pas vraiment échouer....
    fichier = fopen(nom_fichier, "wt");

    //On crée la première ligne.
    fprintf(fichier, "%i", nb_noeud);
    for (i = 0; i < nb_noeud; i++)
    {
        fprintf(fichier, ",%i", i);
    }
    fprintf(fichier, "\n");

    //On écrit chaque ligne de la matrice d'adjacence.
    for (i = 0; i < nb_noeud; i++)
    {
        //On écrit l'indice de la ligne.
        fprintf(fichier, "%i", i);

        //On écrit chaque valeur de la matrice d'adjacence pour la ligne courante.
        for (j = 0; j < nb_noeud; j++)
        {
            fprintf(fichier, ",%i", adjacence[i][j]);
        }
        fprintf(fichier, "\n");
    }

    fclose(fichier);
}

//
// Permet de créer une nouvelle matrice d'adjance en combinant les coûts
// des deux matrices d'adjacences reçues.
//
int** combiner_adjacence(int** adjacence1, int** adjacence2, int nb_noeuds)
{
	int **tab = (int**)malloc(sizeof(int*) * nb_noeuds);
	for(int i= 0; i < nb_noeuds; i++){
		tab[i] = (int*)malloc(sizeof(int) * nb_noeuds);
	}
	for(int i = 0; i < nb_noeuds; i++){
		for(int j = 0; j < nb_noeuds; j++){
			if(adjacence1[i][j] <= 0){
				tab[i][j] = adjacence2[i][j];
			}
			else if(adjacence2[i][j] <= 0){
				tab[i][j] = adjacence1[i][j];
			}
			else{
				tab[i][j] = adjacence1[i][j] + adjacence2[i][j];
			}
		}
	}
	return tab;
}
