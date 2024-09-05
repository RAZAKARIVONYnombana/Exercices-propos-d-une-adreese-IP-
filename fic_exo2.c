#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "exo2.h"

#define IPV4_MAX_OCTETS 4
#define MAX_BITS 32

int main() {
    char ip_str[16];
    int subnet_bits;
    unsigned int ip, subnet_mask, network_address, broadcast_address;
    char subnet_mask_str[16], network_ip[16], broadcast_ip[16];

    // Demander l'adresse IP
    while (1) {
        printf("Entrez une adresse IP (format x.x.x.x) : ");
        scanf("%15s", ip_str);
        
        if (is_valid_ip(ip_str)) {
            break;
        } else {
            printf("Adresse IP invalide. Veuillez réessayer.\n");
        }
    }

    // Convertir l'adresse IP en entier
    ip = ip_to_int(ip_str);

    // Demander le nombre de bits du sous-réseau
    while (1) {
        printf("Entrez le nombre de bits du sous-réseau (1-32) : ");
        if (scanf("%d", &subnet_bits) != 1 || subnet_bits < 1 || subnet_bits > MAX_BITS) {
            printf("Nombre de bits invalide. Veuillez entrer un nombre entre 1 et 32.\n");
            while (getchar() != '\n'); // Vider le buffer d'entrée
        } else {
            break;
        }
    }

    // Calculer le masque de sous-réseau
    subnet_mask = get_subnet_mask(subnet_bits);

    // Calculer l'adresse réseau et l'adresse de broadcast
    network_address = get_network_address(ip, subnet_mask);
    broadcast_address = get_broadcast_address(ip, subnet_mask);

    // Convertir les adresses en format IP
    int_to_ip(subnet_mask, subnet_mask_str);
    int_to_ip(network_address, network_ip);
    int_to_ip(broadcast_address, broadcast_ip);

    // Afficher les résultats
    printf("Masque de sous-réseau : %s\n", subnet_mask_str);
    printf("Adresse du réseau : %s\n", network_ip);
    printf("Adresse de broadcast : %s\n", broadcast_ip);
    printf("Nombre d'hôtes possibles : %u\n", get_number_of_hosts(subnet_bits));

    return 0;
}
