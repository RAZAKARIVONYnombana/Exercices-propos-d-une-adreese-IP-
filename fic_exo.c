#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "exo.h"

int main() {
    char ip[16];        // Tableau pour stocker l'adresse IP entrée par l'utilisateur
    char ipCopy[16];    // Copie de l'adresse IP pour éviter de modifier l'originale
    int firstOctet;     // Variable pour stocker le premier octet de l'adresse IP

    while (1) {
        // Demande à l'utilisateur d'entrer une adresse IP
        printf("Entrez une adresse IP:  ");
        scanf("%15s", ip);

        // Créer une copie de l'IP pour éviter la modification par strtok
        strncpy(ipCopy, ip, sizeof(ipCopy));

        // Vérifie si l'adresse IP est valide
        if (!isValidIP(ipCopy)) {
            printf("Adresse IP invalide. Veuillez réessayer.\n\n");
            continue;  // Redemande l'entrée en cas d'adresse IP invalide
        }

        // Réinitialiser ipCopy pour extraire le premier octet
        strncpy(ipCopy, ip, sizeof(ipCopy));
        firstOctet = atoi(strtok(ipCopy, "."));  // Convertit le premier segment en entier

        // Détermine la classe de l'adresse IP
        char ipClass = getIPClass(firstOctet);
        printf("La classe de l'adresse IP %s est : de classe %c\n", ip, ipClass);

        // Affiche le masque de sous-réseau
        char *subnetMask = getSubnetMask(ipClass);
        printf("Masque de sous-réseau: %s\n\n", subnetMask);

        // Affiche l'adresse de diffusion (broadcast)
        char *broadcast = getBroadcastAddress(ip, ipClass);
        printf("Adresse de diffusion: %s\n\n", broadcast);

        // Affiche le nombre de machines pouvant se connecter dans le sous-réseau
        int maxHosts = getMaxHosts(ipClass);
        printf("Nombre maximum de machines dans ce sous-réseau: %d machines\n\n", maxHosts);

        break;  // Termine la boucle après l'affichage des informations
    }

    return 0;  
}
