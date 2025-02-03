#pragma once
#define charlen 50

struct Personne;
struct Vol;

void recherche_vol(struct Vol *vols,int num);
void recheche_nom_compagnie(struct Vol *vols, char *nom,int num,int voup);
void recheche_destination(struct Vol *vols, char *destination,int num,int voup);
void recherche_heure(struct Vol *vols, int heure,int num,int voup);
void echange(struct Vol *vols,int i,int j);
int repartition(struct Vol *vols,int i_deb,int i_fin);
void tri_rapide(struct Vol *vols,int i_deb,int i_fin);
int date_en_secondes(char *date);
int moins_de_12_ans(char *date);
int heure_actu();
void init_piste(struct Vol *vols,int num,int *piste);
void replanification_de_vol(struct Vol vol,int *piste);
void ordo(struct Vol *vols,int num,int *piste);
void echange_p(struct Vol vol,int i,int j);
int repartition_p(struct Vol vol, int i_deb, int i_fin);
void tri_rapide_p(struct Vol vol,int i_deb,int i_fin);