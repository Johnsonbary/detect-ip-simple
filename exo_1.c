#include "exo_1.h"

char *affichage_classe()
{
    char *ip;
    int decimal[4];
    int open;
    try:
    ip = affichage_ip();
    open = sscanf(ip, "%d.%d.%d.%d", &decimal[0], &decimal[1], &decimal[2], &decimal[3]);
    if(open != 4)
    {
        goto try;
    }
    if ((decimal[0]>= 0 && decimal[0]<= 127) && (decimal[1]>= 0 && decimal[1]<= 255) && (decimal[2]>= 0 && decimal[2]<= 255) && (decimal[3]>= 0 && decimal[3]<= 255))
    {
		affichage_classe_type('A');
    }
    else if ((decimal[0]>= 128 && decimal[0]<= 191) && (decimal[1]>= 0 && decimal[1]<= 255) && (decimal[2]>= 0 && decimal[2]<= 255) && (decimal[3]>= 0 && decimal[3]<= 255))
    {
        affichage_classe_type('B');
    }
    else if ((decimal[0]>= 192 && decimal[0]<= 223) && (decimal[1]>= 0 && decimal[1]<= 255) && (decimal[2]>= 0 && decimal[2]<= 255) && (decimal[3]>= 0 && decimal[3]<= 255))
    {
        affichage_classe_type('C');
    }
    else
    {
        goto try; 
    }
    return (ip);
}
void affichage_subnet(char *mask_adress, char *ip)
{
    int bytemask[4];
    int byteip[4];
    int add[4];
    
    sscanf(mask_adress, "%d.%d.%d.%d", &bytemask[0], &bytemask[1], &bytemask[2], &bytemask[3]);
    sscanf(ip, "%d.%d.%d.%d", &byteip[0], &byteip[1], &byteip[2], &byteip[3]);
	
    add[0] = byteip[0] & bytemask[0];
    add[1] = byteip[1] & bytemask[1];
    add[2] = byteip[2] & bytemask[2];
    add[3] = byteip[3] & bytemask[3];
	
    printf("\nAdresse du Reseau          : \t\t\t%d.%d.%d.%d\n", add[0], add[1], add[2], add[3]);
}

void affichage_broadcast(char *adress_network, char *ip_mask)
{
    int bytes[4];
    int bytesMask[4];
    int bytesBrad[4];

    sscanf(adress_network, "%d.%d.%d.%d", &bytes[0], &bytes[1], &bytes[2], &bytes[3]);
    sscanf(ip_mask, "%d.%d.%d.%d", &bytesMask[0], &bytesMask[1], &bytesMask[2], &bytesMask[3]);

    bytesMask[0] = 255 - bytesMask[0];
    bytesMask[1] = 255 - bytesMask[1];
    bytesMask[2] = 255 - bytesMask[2];
    bytesMask[3] = 255 - bytesMask[3];

    bytesBrad[0] = bytes[0] | bytesMask[0];
    bytesBrad[1] = bytes[1] | bytesMask[1];
    bytesBrad[2] = bytes[2] | bytesMask[2];
    bytesBrad[3] = bytes[3] | bytesMask[3];

    printf("\nAdresse Broadcast          : \t\t\t%d.%d.%d.%d\n", bytesBrad[0], bytesBrad[1], bytesBrad[2], bytesBrad[3]);
	printf("-----------------------------------------------------------------\n");
}
char *affichage_ip()
{
    char *ip;
    ip = (char *)malloc(40 * sizeof(char));
    printf("Enter the IP Adress : ");
    scanf("%s", ip);
    return (ip);
}
char *affichage_mask()
{
    char *mask = (char*)malloc(40 * sizeof(char));
    printf("Enter the MASK Adress : ");
    scanf("%s", mask);
    return (mask);
}
char *determine_mask()
{
    char *mask;
    int open = 0;
    int decimal[4];
    int know;
    try:
    mask = affichage_mask();
    open = sscanf(mask, "%d.%d.%d.%d", &decimal[0], &decimal[1], &decimal[2], &decimal[3]);
    if(open != 4)
    {
        goto try;
    }
    know = savoir(mask);
    if(know == 0)
    {
        goto try;
    }
    printf("\n\n-----------------------------------------------------------------\n");
    printf("Number of user possible    : \t\t\t%d\n", (int)pow(2, know) - 2);
    return (mask);
}
int savoir(char *mask)
{
	int i,
		j;
	int know = 0;
    int tableau_mask[4] = {0};
    int *binary_mask;

    sscanf(mask, "%d.%d.%d.%d", &tableau_mask[0], &tableau_mask[1], &tableau_mask[2], &tableau_mask[3]);
    for(i = 0; i < 4; i++)
    {
		if(0 > tableau_mask[i] || tableau_mask[i] > 255)
			return 0;
		binary_mask = binary(tableau_mask[i]);
		for(j = 0; j < 8; j++)
		{
			if(binary_mask[j] == 0)
				know++;
			if(binary_mask[j] == 1 && know > 1)
				return 0;
		}

	}

	return (know);
}
void affichage_classe_type(char class)
{
	printf("\n\n-----------------------------------------------------------------\n");
    printf("Adresse Classe             :\t\t\t%c\n", class);
	printf("-----------------------------------------------------------------\n\n");
}
int *binary(int entier)
{
	int	j;
	int base;
	int *binary_mask = (int*)malloc(8 * sizeof(int));
	for(j = 7; j >= 0; j--)
	{
		base = entier % 2;
		entier = entier / 2;
		binary_mask[j] = base;
	}
	return (binary_mask);
}

