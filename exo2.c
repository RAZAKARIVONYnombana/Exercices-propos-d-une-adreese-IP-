#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "exo2.h"

#define IPV4_MAX_OCTETS 4
#define MAX_BITS 32

// Fonction pour vérifier si une adresse IP est valide
int is_valid_ip(const char *ip) {
    int octets[IPV4_MAX_OCTETS];
    int count = sscanf(ip, "%d.%d.%d.%d", &octets[0], &octets[1], &octets[2], &octets[3]);
    
    if (count != IPV4_MAX_OCTETS) {
        return 0;
    }
    
    for (int i = 0; i < IPV4_MAX_OCTETS; i++) {
        if (octets[i] < 0 || octets[i] > 255) {
            return 0;
        }
    }
    return 1;
}

// Fonction pour convertir une adresse IP en entier
unsigned int ip_to_int(const char *ip) {
    int octets[IPV4_MAX_OCTETS];
    sscanf(ip, "%d.%d.%d.%d", &octets[0], &octets[1], &octets[2], &octets[3]);
    return (octets[0] << 24) | (octets[1] << 16) | (octets[2] << 8) | octets[3];
}

// Fonction pour convertir un entier en adresse IP
void int_to_ip(unsigned int ip, char *ip_str) {
    sprintf(ip_str, "%d.%d.%d.%d",
            (ip >> 24) & 0xFF,
            (ip >> 16) & 0xFF,
            (ip >> 8) & 0xFF,
            ip & 0xFF);
}

// Fonction pour calculer le masque de sous-réseau à partir du nombre de bits
unsigned int get_subnet_mask(int bits) {
    return (0xFFFFFFFF << (MAX_BITS - bits)) & 0xFFFFFFFF;
}

// Fonction pour calculer l'adresse réseau
unsigned int get_network_address(unsigned int ip, unsigned int subnet_mask) {
    return ip & subnet_mask;
}

// Fonction pour calculer l'adresse de broadcast
unsigned int get_broadcast_address(unsigned int ip, unsigned int subnet_mask) {
    return (ip & subnet_mask) | ~subnet_mask;
}

// Fonction pour calculer le nombre d'hôtes
unsigned int get_number_of_hosts(int bits) {
    return (unsigned int) pow(2, MAX_BITS - bits) - 2;
}
