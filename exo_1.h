#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int savoir(char *mask);
int *binary(int entier);
char *affichage_ip();
char *affichage_mask();
char *determine_mask();
char *affichage_classe();
void affichage_subnet(char *mask_adress, char *ip);
void affichage_broadcast(char *adress_network,char *ip_mask);
void affichage_classe_type(char class);
