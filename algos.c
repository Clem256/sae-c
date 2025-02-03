#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
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

void recheche_nom_compagnie(struct Vol *vols, char *nom,int num,int voup) {
    printf("| Vol numero |      Compagnie     |     Destination    | Début d'enregistrement | Fin d'enregistrement | Numéro de comptoire | Début d'embarquement | Fin d'embarquement | Numéro de salle | Heure de décollage |     Etat du vol    |\n");
    for (int i = 0; i < num; i++) {
        if ((strcmp(vols[i].comp_vol, nom) == 0) && (vols[i].h_dec<=heure_actu()+300)&&(vols[i].h_dec>=heure_actu()-10)) {
            if (voup==1)
                print_info_vol(vols[i]);
            if(voup == 2)
                print_info_passagers(vols[i]);
            if(voup == 3) {
                print_info_vol_et_passagers(vols[i]);
            }
        }
    }
}

void recheche_destination(struct Vol *vols, char *destination,int num,int voup) {
    printf("| Vol numero |      Compagnie     |     Destination    | Début d'enregistrement | Fin d'enregistrement | Numéro de comptoire | Début d'embarquement | Fin d'embarquement | Numéro de salle | Heure de décollage |     Etat du vol    |\n");
    for (int i = 0; i < num; i++) {
        if ((strcmp(vols[i].dest, destination) == 0) && (vols[i].h_dec<=heure_actu()+300)&&(vols[i].h_dec>=heure_actu()-10)) {
            if (voup==1)
                print_info_vol(vols[i]);
            if(voup == 2)
                print_info_passagers(vols[i]);
            if(voup == 3) {
                print_info_vol_et_passagers(vols[i]);
            }
        }
    }
}

void recherche_heure(struct Vol *vols, int heure,int num,int voup) {
    printf("| Vol numero |      Compagnie     |     Destination    | Début d'enregistrement | Fin d'enregistrement | Numéro de comptoire | Début d'embarquement | Fin d'embarquement | Numéro de salle | Heure de décollage |     Etat du vol    |\n");
    for (int i = 0; i < num; i++) {
        if ((vols[i].h_dec == heure) && (vols[i].h_dec<=heure_actu()+300)&&(vols[i].h_dec>=heure_actu()-10)) {
            if (voup==1)
                print_info_vol(vols[i]);
            if(voup == 2)
                print_info_passagers(vols[i]);
            if(voup == 3) {
                print_info_vol_et_passagers(vols[i]);
            }
        }
    }
}

void recherche_vol(struct Vol *vols,int num) {
    int ch=0;

    printf(" 1. Recherche par compagnie\n 2. Recherche par destination\n 3. Recherche par heure\n\n Choisisez une colone : ");
    scanf("%d",&ch);
    printf("\n");

    switch (ch) {
        case 1: {
            char nom[charlen];
            int voup;
            printf("Entrer le nom de la compagnie: ");
            scanf("%s", &nom);
            printf("\n");
            printf("1.Afficher juste le vol\n2.Afficher juste les passagers\n3.Afficher le vol et les passagers\n\nChoisisez une option: ");
            scanf("%d", &voup);

            recheche_nom_compagnie(vols, nom,num,voup);
            break;
        }
        case 2: {
            char destination[charlen];
            int voup;
            printf(" Entrer la destination: ");
            scanf("%s", &destination);
            printf("\n");
            printf("1.Afficher juste le vol\n2.Afficher juste les passagers\n3.Afficher le vol et les passagers\n\nChoisisez une option: ");
            scanf("%d", &voup);
            recheche_destination(vols, destination,num,voup);
            break;
        }
        case 3: {
            int heure;
            int voup;
            printf(" Entrer l'heure de décollage: ");
            scanf("%d", &heure);
            printf("\n");
            printf("1.Afficher juste le vol\n2.Afficher juste les passagers\n3.Afficher le vol et les passagers\n\nChoisisez une option: ");
            scanf("%d", &voup);
            recherche_heure(vols, heure,num,voup);
            break;
        }
        default:
            printf(" Choix invalide\n");
            break;
    }
}

void echange(struct Vol *vols,int i,int j){
    struct Vol p=vols[i];
    vols[i]=vols[j];
    vols[j]=p;
}

int repartition(struct Vol *vols, int i_deb, int i_fin) {
    struct Vol p = vols[i_deb];
    int i = i_deb + 1;
    int j = i_fin;

    while (i <= j) {
        while (i <= j && vols[i].h_dec <= p.h_dec) {
            i = i + 1;
        }

        while (i <= j && vols[j].h_dec > p.h_dec) {
            j = j - 1;
        }

        if (i < j) {
            echange(vols, i, j);
        }
    }

    echange(vols, i_deb, j);
    return j;
}

void tri_rapide(struct Vol *vols,int i_deb,int i_fin){
    if (i_fin == i_deb+1){
        if (vols[i_fin].h_dec<vols[i_deb].h_dec){
            echange(vols,i_deb,i_fin);
        }
    }
    else {
        if (i_deb<i_fin){
            int i_pivot = repartition(vols,i_deb,i_fin);
            tri_rapide(vols,i_deb,i_pivot-1);
            tri_rapide(vols,i_pivot+1,i_fin);
        }
    }
}


int date_en_secondes(char *date) {
    char *date_copy = strdup(date);

    int date_epoch = 1970 * 365 * 24 * 60 * 60;
    int annee = atoi(strtok(date_copy, "/"));
    int mois = atoi(strtok(NULL, "/"));
    int jour = atoi(strtok(NULL, "/"));

    free(date_copy);

    return (annee * 365 * 24 * 60 * 60 + mois * 30 * 24 * 60 * 60 + jour * 24 * 60 * 60) - date_epoch;
}

int moins_de_12_ans(char *date) {
    int douze_ans_en_secondes = 12 * 365 * 24 * 60 * 60;
    int date_n = date_en_secondes(date);
    int date_actuelle = time(NULL);
    return date_actuelle - date_n <= douze_ans_en_secondes;
}

int heure_actu() {
    // Get the current time in seconds since epoch
    time_t currentTime = time(NULL)-(2024*31556926);

    // Calculate current hour and minutes
    int totalMinutes = currentTime / 60; // Convert seconds to minutes
    int currentHour = (totalMinutes / 60) % 24; // Extract hours and take modulo 24
    int currentMinute = totalMinutes % 60;

    int currenttime=currentHour*100+currentMinute;

    return currenttime;
}

void init_piste(struct Vol *vols,int num,int *piste) {
    for(int i=1;i<num;i++) {
        int m=(vols[i].h_dec%100)+(60*((vols[i].h_dec/100)-6));
        piste[m/5]=vols[i].num_vol;
    }
}

void replanification_de_vol(struct Vol vol,int *piste) {
    int h = vol.h_dec;
    int lim = 2200;
    int i = (vol.h_dec%100)+(60*((vol.h_dec/100)-6))/5;
    int t = 0;
    while (h!=lim && i<192){
        if(!(piste[i]==0)) {
            vol.h_dec=((((i*5)+(6*60))/60)*100)+(((i*5)+(6*60))%60);
            t = 1;
            break;
        }
        h=h+5;
        i++;
    }
    if(t!=1) {
        strcpy(vol.etat_vol,"Annule");
    }
}

void ordo(struct Vol *vols,int num,int *piste) {
    for(int i=1;i<num;i++) {
        if(strcmp(vols[i].etat_vol,"%[Retarde^]")) {
            replanification_de_vol(vols[i],piste);
        }
    }
}


void echange_p(struct Vol vol, int i, int j) {
    struct Personne temp = vol.passagers[i];
    vol.passagers[i] = vol.passagers[j];
    vol.passagers[j] = temp;
}

int repartition_p(struct Vol vol, int i_deb, int i_fin) {
    struct Personne pivot = vol.passagers[i_deb];
    int i = i_deb + 1;
    int j = i_fin;

    while (i <= j) {
        while (i <= j && vol.passagers[i].prix_billet <= pivot.prix_billet) {
            i++;
        }

        while (i <= j && vol.passagers[j].prix_billet > pivot.prix_billet) {
            j--;
        }

        if (i < j) {
            echange_p(vol, i, j);
        }
    }

    echange_p(vol, i_deb, j);
    return j;
}

void tri_rapide_p(struct Vol vol, int i_deb, int i_fin) {
    if (i_deb < i_fin) {
        int i_pivot = repartition_p(vol, i_deb, i_fin);
        tri_rapide_p(vol, i_deb, i_pivot - 1);
        tri_rapide_p(vol, i_pivot + 1, i_fin);
    }
}