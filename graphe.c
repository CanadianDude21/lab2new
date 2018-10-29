#include "graphe.h"

#include <stdlib.h>
#include <string.h>

/******************************************************************************/
/*                  DEFINITIONS DE TYPES ET DE CONSTANTES                     */
/******************************************************************************/

/******************************************************************************/
/*                  DÉCLARATION DES FONCTIONS PRIVÉES                         */
/******************************************************************************/

//
// Permet de comparer deux arêtes en fonction de leur poids.
//
static int comparer_arete(void* arete1, void* arete2);

//
// Permet de comparer deux voisins en fonction de leur id.
//
static int comparer_voisin(void* arete1, void* arete2);

/******************************************************************************/
/*          IMPLÉMENTATIONS DES FONCTIONS PUBLIQUES ET PRIVÉES                */
/******************************************************************************/
t_graphe* creer_graphe(int** adjacence, int nb_noeuds)
{
	t_graphe *graphe = (t_graphe*)malloc(sizeof(t_graphe));
	graphe->noeuds = (t_noeud*)malloc(nb_noeuds * sizeof(t_noeud));
	graphe->nb_noeuds = nb_noeuds;
	for(int i = 0; i < nb_noeuds; i++){
		graphe->noeuds[i].id = i;
		graphe->noeuds[i].voisins = creer_liste(NULL, NULL);
		for(int j = 0; j < nb_noeuds; j++){
			if(adjacence[i][j] != -1 && adjacence[i][j] != 0){
				t_voisin *voisin = (t_voisin*)malloc(sizeof(t_voisin));
				voisin->id = j;
				voisin->poids_arrete = adjacence[i][j];
				ajouter_element(graphe->noeuds[i].voisins, (void*)voisin);
			}
		}
		graphe->noeuds[i].nb_voisins = graphe->noeuds[i].voisins->nb_element;
	}



	return graphe;
}

t_graphe* creer_graphe_vide(int nb_noeuds)
{
	t_graphe *graphe = (t_graphe*)malloc(sizeof(t_graphe));
	graphe->noeuds = (t_noeud*)malloc(nb_noeuds * sizeof(t_noeud));
	graphe->nb_noeuds = nb_noeuds;

	for(int i = 0; i < nb_noeuds; i++){
		graphe->noeuds[i].id = i;
		graphe->noeuds[i].voisins = creer_liste(NULL, NULL);
	}

	return graphe;
}

int** creer_adjacence(t_graphe* un_graphe)
{
    int **tab = (int**)malloc(sizeof(int*) * un_graphe->nb_noeuds);
    for(int i= 0; i < un_graphe->nb_noeuds; i++){
    	tab[i] = (int*)malloc(sizeof(int) * un_graphe->nb_noeuds);
    }
    t_element *voisin_present;
    t_voisin *contenu_voisin_present;
    for(int i = 0; i < un_graphe->nb_noeuds; i++){
    	voisin_present = un_graphe->noeuds[i].voisins->tete;
    	contenu_voisin_present = voisin_present->contenu;
    	for(int j = un_graphe->nb_noeuds-1; j >= 0; j--){
    		if(i == j){
    			tab[i][j] = 0;
    		}
    		else if(j == contenu_voisin_present->id){
    			tab[i][j] = contenu_voisin_present->poids_arrete;
    			if(voisin_present->suivant != NULL){
    				voisin_present = voisin_present->suivant;
    				contenu_voisin_present = voisin_present->contenu;
    			}
    		}
    		else{
    			tab[i][j] = -1;
    		}
    	}
    }
    return tab;
}

void ajouter_arete(t_graphe* un_graphe, t_arete* une_arete)
{
	t_liste *liste_present = un_graphe->noeuds[une_arete->id_noeud1].voisins;
	t_voisin *voisin_ajouter1 = (t_voisin*)malloc(sizeof(t_voisin));
	voisin_ajouter1->id = une_arete->id_noeud2;
	voisin_ajouter1->poids_arrete = une_arete->poids;
	ajouter_element(liste_present,voisin_ajouter1);
	un_graphe->noeuds[une_arete->id_noeud1].nb_voisins++;

	liste_present = un_graphe->noeuds[une_arete->id_noeud2].voisins;
	t_voisin *voisin_ajouter2 = (t_voisin*)malloc(sizeof(t_voisin));
	voisin_ajouter2->id = une_arete->id_noeud1;
	voisin_ajouter2->poids_arrete = une_arete->poids;
	ajouter_element(liste_present,voisin_ajouter2);
	un_graphe->noeuds[une_arete->id_noeud2].nb_voisins++;

}

t_liste* obtenir_aretes(t_graphe* un_graphe)
{
	t_liste *new_liste = creer_liste(NULL, comparer_arete);

	t_element *voisin_present;
	t_voisin *contenu_voisin_present;
	for(int i = 0; i < un_graphe->nb_noeuds; i++){
	    voisin_present = un_graphe->noeuds[i].voisins->tete;
	    contenu_voisin_present = voisin_present->contenu;
	    for(int j = 0; j < un_graphe->noeuds[i].voisins->nb_element; j++){
	    	if(contenu_voisin_present->id > i){
	    		t_arete *arete = (t_arete*)malloc(sizeof(t_arete));
	    		arete->id_noeud1 = i;
	    		arete->id_noeud2 = contenu_voisin_present->id;
	    		arete->poids = contenu_voisin_present->poids_arrete;
	    		ajouter_element(new_liste, arete);
	    	}
	    	if(voisin_present->suivant != NULL){
	    		voisin_present = voisin_present->suivant;
	    		contenu_voisin_present = voisin_present->contenu;
	    	}

	    }
	}
	//trier_liste(new_liste);
	return new_liste;
}

//
// Compare deux arêtes en fonction de leur poids.
// Servira à trier des arêtes en ordre croissant.
//
static int comparer_arete(void* arete1, void* arete2)
{
    int resultat;

    //On convertit les deux addresses dans le bon type.
    t_arete* a1 = (t_arete*) arete1;
    t_arete* a2 = (t_arete*) arete2;

    // On retourne -1 lorsque l'on considère arête1 < arête2.
    // On retourne  0 lorsque l'on considère arête1 = arête2.
    // On retourne  1 lorsque l'on considère arête1 > arête2.
    if ((a1->poids) < (a2->poids))
        resultat = -1;

    else if ((a1->poids) > (a2->poids))
        resultat = 1;

    else if (a1->id_noeud1 == a2->id_noeud1 && a1->id_noeud2 == a2->id_noeud2)
        resultat = 0;

    else if (a1->id_noeud1 == a2->id_noeud2 && a1->id_noeud2 == a2->id_noeud1)
        resultat = 0;

    else if (a1->id_noeud1 <= a2->id_noeud2)
        resultat = -1;

    else
        resultat = -1;

    return resultat;
}

//
// Compare deux voisins afin de vérifier s'il sont identiques.
// La fonction appelante sait déjà que le noued courant est le même.
//
static int comparer_voisin(void* voisin1, void* voisin2)
{
    //On convertit les deux addresses dans le bon type.
    t_voisin* v1 = (t_voisin*) voisin1;
    t_voisin* v2 = (t_voisin*) voisin2;

    //On vérifie si l'es deux addresses sont pareils en suivant.
    return (v1->id - v2->id);
}

