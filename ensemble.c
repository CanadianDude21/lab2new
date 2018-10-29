#include "ensemble.h"

#include <stdlib.h>

void creer_ensemble(t_ensemble_disjoint* les_ensembles, void* membre)
{
	t_ensemble *ensemble = (t_ensemble*)malloc(sizeof(t_ensemble));
	ensemble->membres = creer_liste(NULL, NULL);
	ensemble->representant = membre;
	ajouter_element(ensemble->membres, membre);

	if(les_ensembles->collection == NULL){
		les_ensembles->collection = creer_liste(NULL, NULL);
	}

    ajouter_element(les_ensembles->collection, ensemble);
}

void* trouver_ensemble(t_ensemble_disjoint* les_ensembles, void* membre)
{
	t_element *ensemble_present = les_ensembles->collection->tete;
	t_ensemble *contenu_present = ensemble_present->contenu;
	void *representant_present;
	int trouver = -1;

	while(trouver == -1 && ensemble_present != NULL){
		representant_present = contenu_present->representant;
		trouver = trouver_position_element(contenu_present->membres, membre);
		if(ensemble_present->suivant != NULL){
			ensemble_present = ensemble_present->suivant;
			contenu_present = ensemble_present->contenu;
		}

	}
	return representant_present;
}

void unir_ensemble(t_ensemble_disjoint* les_ensembles, void* membre1, void* membre2)
{
	t_element *ensemble_present = les_ensembles->collection->tete;
	t_ensemble *liste1_present = ensemble_present->contenu;
	t_ensemble *liste2_present = ensemble_present->contenu;
	t_liste *nouvelle_liste;
	void *representant1 = trouver_ensemble(les_ensembles, membre1);
	void *representant2 = trouver_ensemble(les_ensembles, membre2);

	for(int i = 0; i < les_ensembles->collection->nb_element && liste1_present->representant != representant1; i++){
		ensemble_present = ensemble_present->suivant;
		liste1_present = ensemble_present->contenu;
	}

	ensemble_present = les_ensembles->collection->tete;
	for(int i = 0; i < les_ensembles->collection->nb_element && liste2_present->representant != representant2; i++){
		ensemble_present = ensemble_present->suivant;
		liste2_present = ensemble_present->contenu;
	}

	nouvelle_liste = fusionner_liste(liste1_present->membres, liste2_present->membres);
	liste1_present->membres = nouvelle_liste;
	supprimer_element_contenu(les_ensembles->collection, ensemble_present->contenu);
}

