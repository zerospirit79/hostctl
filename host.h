#ifndef HOSTS_H
#define HOSTS_H

// Прототипы функций для работы с /etc/hosts
int add_host(char *hostname, char *ip);
int delete_host(char *hostname);
int edit_host(char *hostname, char *ip);
void list_hosts();

// Прототип функции для проверки корректности ввода
int validate_host(char *hostname, char *ip);

#endif
