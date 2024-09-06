#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int savoir(int);
char *affichage_ip();
char *affichage_mask();
char *determine_mask();
char *affichage_classe();
void affichage_subnet(char *mask_adress, char *ip);
void affichage_broadcast(char *adress_network,char *ip_mask);

//ip
//msr 
//classe, @reseau, @broadcast

int main()
{
    char *ip;
    char *mask;
    ip = affichage_classe();
    mask = determine_mask();
    affichage_subnet(mask, ip);
    affichage_broadcast(ip, mask);
    return 0;
}

char *affichage_classe()
{
    char *ip;
    int decimal[4];
    int count = 0;
    int open;
    try:
    ip = affichage_ip();
    open = sscanf(ip, "%d.%d.%d.%d", &decimal[0], &decimal[1], &decimal[2], &decimal[3]);
    if(open != 4)
    {
        goto try;
    }
    printf("\n###############################################################################################\n\n");
    if ((decimal[0]>= 0 && decimal[0]<= 127) && (decimal[1]>= 0 && decimal[1]<= 255) && (decimal[2]>= 0 && decimal[2]<= 255) && (decimal[3]>= 0 && decimal[3]<= 255))
    {
        printf("Adresse Classe             :\t\t\tA\n");
    }
    else if ((decimal[0]>= 128 && decimal[0]<= 191) && (decimal[1]>= 0 && decimal[1]<= 255) && (decimal[2]>= 0 && decimal[2]<= 255) && (decimal[3]>= 0 && decimal[3]<= 255))
    {
        printf("Adresse Classe             :\t\t\tB\n");
    }
    else if ((decimal[0]>= 192 && decimal[0]<= 223) && (decimal[1]>= 0 && decimal[1]<= 255) && (decimal[2]>= 0 && decimal[2]<= 255) && (decimal[3]>= 0 && decimal[3]<= 255))
    {
        printf("Adresse Classe             :\t\t\tC\n");
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
    char *address_net;

    sscanf(mask_adress, "%d.%d.%d.%d", &bytemask[0], &bytemask[1], &bytemask[2], &bytemask[3]);
    sscanf(ip, "%d.%d.%d.%d", &byteip[0], &byteip[1], &byteip[2], &byteip[3]);

    add[0] = byteip[0] & bytemask[0];
    add[1] = byteip[1] & bytemask[1];
    add[2] = byteip[2] & bytemask[2];
    add[3] = byteip[3] & bytemask[3];

    sprintf(address_net, "%d.%d.%d.%d", add[0], add[1], add[2], add[3]);
    printf("\nAdresse du Reseau          : \t\t\t%s\n", address_net);
}

void affichage_broadcast(char *adress_network, char *ip_mask)
{
    int bytes[4];
    int bytesMask[4];
    int bytesBrad[4];
    char *add_broad;

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

    sprintf(add_broad, "%d.%d.%d.%d", bytesBrad[0], bytesBrad[1], bytesBrad[2], bytesBrad[3]);
    printf("\nAdresse Broadcast          : \t\t\t%s\n", add_broad);
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
    int sum = 0;
    int i;
    int know;
    try:
    mask = affichage_mask();
    open = sscanf(mask, "%d.%d.%d.%d", &decimal[0], &decimal[1], &decimal[2], &decimal[3]);
    if(open != 4)
    {
        goto try;
    }
    for(i = 0; i < 4; i++)
    {
        sum =  sum + decimal[i];
    }
    know = savoir(sum);
    if(know = 0)
    {
        goto try;
    }
    return (mask);
}
int savoir(int n)
{
    int i;
    int know = 0;
    int base;
    int tmp = 0;
    for(i = 31; i >= 0; i--)
    {
        base = (int)pow(2,i % 8);
        tmp = know;
        know = n / base;
        n = n % base;
        if(know == 0 && tmp == 1)
            return 1;
    }
    return 0;
}

