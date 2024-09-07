#include "exo_1.h"

int main()
{
    char *ip;
    char *mask;
    ip = affichage_classe();
    mask = determine_mask();
    affichage_subnet(mask, ip);
    affichage_broadcast(ip, mask);
    return (0);
}
