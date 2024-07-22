#include <stdio.h> // для функций ввода/вывода (printf, fopen, fclose и т.д.)
#include <stdlib.h> // для функций работы с памятью (malloc, free)
#include <string.h> // для функций работы со строками (strstr, strcpy, strcmp)
#include <unistd.h> // для функций работы с файлами (access, unlink)
#include <errno.h> // для функций работы с ошибками (errno)
#include "hosts.h" // для деклараций функций из hosts.h

// Функция для проверки корректности IP-адреса
int validate_ip(const char *ip) {
    int num_dots = 0;
    int num_digits = 0;
    int digit = 0;
    for (int i = 0; ip[i] != '\0'; i++) {
        if (ip[i] == '.') {
            num_dots++;
            if (num_digits == 0) {
                return 0; // Ошибка: цифра отсутствует перед точкой
            }
            num_digits = 0;
        } else if (isdigit(ip[i])) {
            digit = ip[i] - '0';
            if (digit < 0 || digit > 9) {
                return 0; // Ошибка: некорректный символ
            }
            num_digits++;
            if (num_digits > 3) {
                return 0; // Ошибка: более 3 цифр в октете
            }
        } else {
            return 0; // Ошибка: некорректный символ
        }
    }

    if (num_dots != 3) {
        return 0; // Ошибка: недостаточно точек
    }
    if (num_digits == 0) {
        return 0; // Ошибка: цифра отсутствует после последней точки
    }

    return 1; // IP-адрес корректен
}

// Функция для проверки корректности имени хоста
int validate_hostname(const char *hostname) {
    // Простая проверка:  имя хоста должно начинаться с буквы или цифры
    // и может содержать только буквы, цифры, тире (-) и точки (.)
    if (!isalpha(hostname[0]) && !isdigit(hostname[0])) {
        return 0;
    }
    for (int i = 1; hostname[i] != '\0'; i++) {
        if (!isalnum(hostname[i]) && hostname[i] != '-' && hostname[i] != '.') {
            return 0;
        }
    }
    return 1; // Имя хоста корректен
}

// Функция для проверки корректности записи в /etc/hosts
int validate_host(char *hostname, char *ip) {
    if (!validate_hostname(hostname)) {
        fprintf(stderr, "Ошибка: Некорректное имя хоста: %s\n", hostname);
        return 1;
    }
    if (!validate_ip(ip)) {
        fprintf(stderr, "Ошибка: Некорректный IP-адрес: %s\n", ip);
        return 1;
    }
    return 0; // Запись корректна
}

// Функция для добавления новой записи в /etc/hosts
int add_host(char *hostname, char *ip) {
    FILE *fp;
    char line[1024];
    int exists = 0;

    // Проверка корректности записи
    if (validate_host(hostname, ip)) {
        return 1;
    }

    // Проверка,  существует  ли  запись  с  данным  именем  хоста
    fp = fopen("/etc/hosts", "r");
    if (fp != NULL) {
        while (fgets(line, sizeof(line), fp) != NULL) {
            if (strstr(line, hostname) != NULL) {
                exists = 1;
                break;
            }
        }
