#include "liste.h"

#include <stdlib.h>

t_liste* creer_liste(void (*afficher_element)(void* contenu), int (*comparer_element)(void* contenu1, void* contenu2))
{
	t_liste *liste;
	liste = (t_liste*)malloc(sizeof(t_liste));
	liste->afficher_element =  afficher_element;
	liste->comparer_element = comparer_element;
	liste->nb_element = 0;
	liste->tete = NULL;

	return liste;


}

void supprimer_liste(t_liste* une_liste)
{
	while(une_liste->tete != NULL){
		t_element *supprime = une_liste->tete;
		une_liste->tete = une_liste->tete->suivant;
		free(supprime);
	}
	une_liste->afficher_element = NULL;
	une_liste->comparer_element = NULL;
	free(une_liste);

}

void afficher_liste(t_liste* une_liste)
{
	t_element *present = une_liste->tete;
	while(present != NULL){
		une_liste->afficher_element(present);
		present = present->suivant;
	}
}

void ajouter_element(t_liste* une_liste, void* element)
{
	t_element *new = malloc(sizeof(t_element));
	new->contenu = element;
	new->suivant = une_liste->tete;
	if(une_liste->tete != NULL){
		une_liste->tete->precedant = new;
	}
	une_liste->tete = new;
	new->precedant = NULL;
	une_liste->nb_element++;
}

void* supprimer_element_debut(t_liste* une_liste)
{
	t_element *supprimer = une_liste->tete;
	if(supprimer->precedant != NULL){
		supprimer->precedant->suivant = supprimer->suivant;
	}
	else{
		une_liste->tete = supprimer->suivant;
	}
	if(supprimer->suivant != NULL){
		supprimer->suivant->precedant = supprimer->precedant;
	}
    une_liste->nb_element--;
    return supprimer->contenu;

}

void* supprimer_element_position(t_liste* une_liste, int position)
{
	t_element *supprimer = une_liste->tete;
	int i = 0;
	while(supprimer != NULL && i < position){
		supprimer = supprimer->suivant;
		i++;
	}
	if(supprimer->precedant != NULL){
		supprimer->precedant->suivant = supprimer->suivant;
	}
	else{
		une_liste->tete = supprimer->suivant;
	}
	if(supprimer->suivant != NULL){
		supprimer->suivant->precedant = supprimer->precedant;
	}
    une_liste->nb_element--;
    return supprimer->contenu;

}

void* supprimer_element_contenu(t_liste* une_liste, void* contenu)
{
	t_element *supprimer = une_liste->tete;
	int i = 0;
	while(supprimer->contenu != contenu && i < une_liste->nb_element){
		supprimer = supprimer->suivant;
		i++;
	}
	if(supprimer->precedant != NULL){
		supprimer->precedant->suivant = supprimer->suivant;
	}
	else{
		une_liste->tete = supprimer->suivant;
	}
	if(supprimer->suivant != NULL){
		supprimer->suivant->precedant = supprimer->precedant;
	}
	une_liste->nb_element--;
	return supprimer->contenu;
}

int trouver_position_element(t_liste* une_liste, void* contenu)
{
	t_element *a_trouver = une_liste->tete;
	int i = 0;
	while(i < une_liste->nb_element){
		if(a_trouver->contenu == contenu){
				return i;
		}
		a_trouver = a_trouver->suivant;
		i++;
	}
	return -1;
}

void trier_liste(t_liste* une_liste)
{
	void *temp;
	t_element *debut = une_liste->tete;
	t_element *present = une_liste->tete;
	t_element *min = une_liste->tete;
	int i = 0;
	int j = 0;
	for(i = 0; i < une_liste->nb_element-1; i++){
		present = debut->suivant;
		for(j = i+1; j < une_liste->nb_element; j++){
			if(une_liste->comparer_element(present->contenu, min->contenu) < 0){
				min = present;
			}
			present = present->suivant;
		}
		temp = min->contenu;
		min->contenu = debut->contenu;
		debut->contenu = temp;
		debut = debut->suivant;
		min = debut;
	}
}

t_liste* fusionner_liste(t_liste* liste1, t_liste* liste2)
{
	t_liste *liste3 = creer_liste(liste1->afficher_element, liste1->comparer_element);

	t_element *present = liste2->tete;
	while(present->suivant != NULL){
		present = present->suivant;
	}
	while(present != NULL){
		ajouter_element(liste3, present->contenu);
		present = present->precedant;
	}

	present = liste1->tete;
	while(present->suivant != NULL){
			present = present->suivant;
	}
	while(present != NULL){
		ajouter_element(liste3, present->contenu);
		present = present->precedant;
	}

	return liste3;
}
