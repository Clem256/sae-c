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


void print_info_vol_et_passagers(struct Vol vol) {
    int num=1;
    printf("|  %-10d|  %-18s|  %-18s|  %-20dH |  %-18dH |  %-19d|  %-18dH |  %-16dH |  %-15d|  %-18d|%20s|\n", vol.num_vol, vol.comp_vol, vol.dest, vol.hdber,vol.hfiner,vol.num_cpt,vol.hdfebem,vol.hfinem,vol.s_emb,vol.h_dec,vol.etat_vol);

    struct Personne *Passager = vol.passagers;
    while (Passager != NULL) {
        printf("Passager n°%d: %s %s,né le %s, Siege: %d, Prix du tiquet: %d\n",num,
               Passager->prenom, Passager->nom,Passager->date_n ,Passager->num_siege, Passager->prix_billet);
        Passager = Passager->next;
        num++;
    }

    printf("\n");
}

void print_info_vol(struct Vol vol) {
    printf("|  %-10d|  %-18s|  %-18s|  %-20dH |  %-18dH |  %-19d|  %-18dH |  %-16dH |  %-15d|  %-18d|%-20s|\n", vol.num_vol, vol.comp_vol, vol.dest, vol.hdber,vol.hfiner,vol.num_cpt,vol.hdfebem,vol.hfinem,vol.s_emb,vol.h_dec,vol.etat_vol);
}

void print_info_passagers(struct Vol vol) {
    int num=1;
    struct Personne *Passager = vol.passagers;
    while (Passager != NULL) {
        printf("Passager n°%d: %s %s, Siege: %d, Prix du tiquet: %d\n",num,
               Passager->prenom, Passager->nom, Passager->num_siege, Passager->prix_billet);
        Passager = Passager->next;
        num++;
    }
    printf("\n");
}

struct Vol lecture_insertion_ligne(char *line) {
    struct Vol vol;
    char *token = strtok(line, ",");


    vol.num_vol = atoi(token);
    strcpy(vol.comp_vol, strtok(NULL, ","));
    strcpy(vol.dest, strtok(NULL, ","));
    vol.num_cpt = atoi(strtok(NULL, ","));
    vol.hdber = atoi(strtok(NULL, ","));
    vol.hfiner = atoi(strtok(NULL, ","));
    vol.s_emb = atoi(strtok(NULL, ","));
    vol.hdfebem = atoi(strtok(NULL, ","));
    vol.hfinem = atoi(strtok(NULL, ","));
    vol.h_dec = atoi(strtok(NULL, ","));
    strcpy(vol.etat_vol, strtok(NULL, ","));


    vol.passagers = NULL;
    char *Passager_data = strtok(NULL, "");
    char *Passager_token = strtok(Passager_data, ";");
    while (Passager_token != NULL) {
        struct Personne *Passager = (struct Personne*)malloc(sizeof(struct Personne));
        sscanf(Passager_token, "%[^,],%[^,],%[^,],%d,%d",
               Passager->nom,
               Passager->prenom,
               Passager->date_n,
               &Passager->num_siege,
               &Passager->prix_billet);
        Passager->next = vol.passagers;
        vol.passagers = Passager;
        Passager_token = strtok(NULL, ";");
    }

    return vol;
}

void lecture_csv(const char *nomf, struct Vol *vols, int *num_vols) {
    FILE *file = fopen(nomf, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[1024];
    *num_vols = 0;


    while (fgets(line, sizeof(line), file) != NULL) {
        vols[*num_vols] = lecture_insertion_ligne(line);
        (*num_vols)++;
    }

    fclose(file);
}

int compteurLignes(const char *nomFichier) {
    FILE *fichier = fopen(nomFichier, "r");

    if (fichier == NULL) {
        perror("Erreur fichier");
        return -1;
    }

    int nombreLignes = 0;
    char caractere;

    while ((caractere = fgetc(fichier)) != EOF) {
        if (caractere == '\n') {
            nombreLignes++;
        }
    }

    fclose(fichier);

    return nombreLignes;
}
