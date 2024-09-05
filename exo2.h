int is_valid_ip(const char *ip) ;
unsigned int ip_to_int(const char *ip) ;
void int_to_ip(unsigned int ip, char *ip_str) ; 
unsigned int get_subnet_mask(int bits) ;
unsigned int get_network_address(unsigned int ip, unsigned int subnet_mask) ;
unsigned int get_broadcast_address(unsigned int ip, unsigned int subnet_mask) ;
unsigned int get_number_of_hosts(int bits) ;
