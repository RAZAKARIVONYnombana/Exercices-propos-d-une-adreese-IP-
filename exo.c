#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "exo.h"

int isValidIP(char *ip) {
    int num;          // Variable pour stocker chaque segment de l'adresse IP
    int dots = 0;     // Compteur pour le nombre de points (".") dans l'adresse IP
    char *ptr;        // Pointeur pour parcourir chaque segment de l'adresse IP

    if (ip == NULL)   // Vérifie si l'adresse IP est NULL (non initialisée)
        return 0;

    // Compte le nombre de points dans l'adresse IP
    for (int i = 0; ip[i]; i++) {
        if (ip[i] == '.')
            dots++;
    }
    
    // L'adresse IP doit avoir exactement 3 points pour être valide
    if (dots != 3)
        return 0;

    // Découpe l'adresse IP en segments séparés par des points
    ptr = strtok(ip, ".");
    
    while (ptr) {
        // Vérifie si chaque segment contient uniquement des chiffres
        if (!isdigit(*ptr))
            return 0;
        
        num = atoi(ptr);  // Convertit le segment en entier
        
        // Chaque segment de l'adresse IP doit être compris entre 0 et 255
        if (num < 0 || num > 255)
            return 0;
        
        ptr = strtok(NULL, ".");  // Passe au segment suivant
    }

    return 1;  // L'adresse IP est valide
}

// Fonction qui détermine la classe de l'adresse IP en fonction du premier octet
char getIPClass(int firstOctet) {
    if (firstOctet >= 0 && firstOctet <= 127)
        return 'A';  // Classe A
    else if (firstOctet >= 128 && firstOctet <= 191)
        return 'B';  // Classe B
    else if (firstOctet >= 192 && firstOctet <= 223)
        return 'C';  // Classe C
    else if (firstOctet >= 224 && firstOctet <= 239)
        return 'D';  // Classe D
    else
        return 'E';  // Classe E
}

// Fonction pour obtenir le masque de sous-réseau en fonction de la classe IP
char* getSubnetMask(char ipClass) {
    if (ipClass == 'A')
        return "255.0.0.0";
    else if (ipClass == 'B')
        return "255.255.0.0";
    else if (ipClass == 'C')
        return "255.255.255.0";
    else
        return "N/A";  // Classe D et E ne sont pas utilisées pour les réseaux classiques
}

// Fonction pour calculer l'adresse de diffusion (broadcast)
char* getBroadcastAddress(char *ip, char ipClass) {
    static char broadcast[16];
    char subnet[16];
    
    strcpy(subnet, getSubnetMask(ipClass));
    
    int ipParts[4], subnetParts[4];
    
    sscanf(ip, "%d.%d.%d.%d", &ipParts[0], &ipParts[1], &ipParts[2], &ipParts[3]);
    sscanf(subnet, "%d.%d.%d.%d", &subnetParts[0], &subnetParts[1], &subnetParts[2], &subnetParts[3]);
    
    for (int i = 0; i < 4; i++) {
        ipParts[i] = ( ipParts[i] | ~subnetParts[i] ) & 255;
    }
    
    sprintf(broadcast, "%d.%d.%d.%d", ipParts[0], ipParts[1], ipParts[2], ipParts[3]);
    
    return broadcast;
}

// Fonction pour calculer le nombre de machines pouvant se connecter dans chaque sous-réseau
int getMaxHosts(char ipClass) {
    if (ipClass == 'A')
        return 16777214;  // 2^24 - 2
    else if (ipClass == 'B')
        return 65534;     // 2^16 - 2
    else if (ipClass == 'C')
        return 254;       // 2^8 - 2
    else
        return 0;         // Classe D et E ne sont pas utilisées pour les réseaux classiques
}
