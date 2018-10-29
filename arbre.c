#include "arbre.h"
#include "ensemble.h"
#include <stdlib.h>

t_graphe* creer_mst_multicriteres(int*** tab_adjacence, int nb_matrice, int nb_noeuds)
{
    return NULL;
}

t_graphe* kruskal(t_graphe* un_graphe)
{
	 t_ensemble_disjoint les_ensembles = { NULL };
    int n = un_graphe->nb_noeuds;
    t_liste *e = obtenir_aretes(un_graphe);
    trier_liste(e);

    t_graphe *mst = creer_graphe_vide(n);

    for(int i = 0; i < n; i++){
    	creer_ensemble(&les_ensembles, (void*)(size_t)un_graphe->noeuds[i].id);
    }

    t_element *arete_present = e->tete;
    t_arete *contenu_arete_present = arete_present->contenu;
    for(int i = 0; i < e->nb_element; i++){
    	if(trouver_ensemble(&les_ensembles, (void*)(size_t)contenu_arete_present->id_noeud1) != trouver_ensemble(&les_ensembles, (void*)(size_t)contenu_arete_present->id_noeud2)){
    		unir_ensemble(&les_ensembles,(void*)(size_t)contenu_arete_present->id_noeud1,(void*)(size_t)contenu_arete_present->id_noeud2);
    		ajouter_arete(mst,contenu_arete_present);
    	}
    	if(arete_present->suivant != NULL){
    		arete_present = arete_present->suivant;
    		contenu_arete_present = arete_present->contenu;
    	}
    }
    return mst;
}
