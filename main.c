#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "csv.h"
#include "algos.h"

#define charlen 50

struct Personne {
    char nom[charlen];
    char prenom[charlen];
    char date_n[11];
    int num_siege;
    int prix_billet;
    struct Personne* next;
};
struct Vol {
    int num_vol;
    char comp_vol[charlen];
    char dest[charlen];
    int num_cpt;
    int hdber;
    int hfiner;
    int s_emb;
    int hdfebem;
    int hfinem;
    int h_dec;
    char etat_vol[20];
    struct Personne* passagers;
};


int main() {
    const char *nomf = "../data_vols.csv";
    int num_vols=compteurLignes(nomf);
    int t=num_vols;
    int piste[192];
    struct Vol vols[t];

    lecture_csv(nomf, vols, &num_vols); // lecture du fichier csv et insertion des données dans un tableau de structures de type Vol
    tri_rapide(vols,0,t-1); // tri par ordre croissant des vols par rapport à leur heure de décollage
    init_piste(vols,t,piste); // initialisation d'une array d'entiers piste qui represente toutes les opportunités de décollage et leur disponibilité
    ordo(vols,t,piste); // Gestion de retards

    recherche_vol(vols,num_vols);

    return 0;
}
