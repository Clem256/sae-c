#pragma once
#define charlen 50

struct Personne;
struct Vol;

int compteurLignes(const char *nomFichier);
struct Vol lecture_insertion_ligne(char *line);
void lecture_csv(const char *fichier, struct Vol *vols, int *num_vols);
void print_info_vol(struct Vol vol);
void print_info_passagers(struct Vol vol);
void print_info_vol_et_passagers(struct Vol vol);


