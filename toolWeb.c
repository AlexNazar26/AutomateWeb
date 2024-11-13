#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define RED   "\x1B[31m"
#define RESET "\x1B[0m"

char* ip(void)
{
    static char ip[15];
    printf("Entrez l'adresse IP de la cible : ");
    scanf("%s", ip);
    return ip;
}


void nmap(void)
{
    char* ip_cible = ip();
    char commande[100];
    FILE *fp;
    char buffer[1024];

    if (system("which nmap > /dev/null 2>&1") == 0) {
        sprintf(commande, "nmap -p- -sV -sC -T4 %s", ip_cible);
        printf("Commande : %s\n", commande);

        fp = popen(commande, "r");
        if (fp == NULL) {
            perror("popen");
            return;
        }

        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            printf("%s", buffer);
        }

        pclose(fp);
    } 
    else {
        printf("nmap n'est pas installé.\nPour l'installer : https://nmap.org/download \n");
    }
}

void nikto(void)
{
    char* ip_cible = ip();
    char commande[100];
    FILE *fp;
    char buffer[1024];

    if (system("which nikto > /dev/null 2>&1") == 0) {
        sprintf(commande, "nikto -h %s", ip_cible);
        printf("Commande : %s\n", commande);

        fp = popen(commande, "r");
        if (fp == NULL) {
            perror("popen");
            return;
        }

        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            printf("%s", buffer);
        }

        pclose(fp);
    } 
    else {
        printf("nikto n'est pas installé.\nPour l'installer : https://cirt.net/Nikto2 \n");
    }
}

void gobuster(void)
{
    char* ip_cible = ip();
    char commande[100];
    FILE *fp;
    char buffer[1024];

    if (system("which gobuster > /dev/null 2>&1") == 0) {
        sprintf(commande, "gobuster dir -u http://%s -w /usr/share/wordlists/dirbuster/directory-list-2.3-medium.txt -t 50", ip_cible);
        printf("Commande : %s\n", commande);

        fp = popen(commande, "r");
        if (fp == NULL) {
            perror("popen");
            return;
        }

        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            printf("%s", buffer);
        }

        pclose(fp);
    } 
    else {
        printf("gobuster n'est pas installé.\nPour l'installer :https://github.com/OJ/gobuster \n");
    }
}

void wpscan(void)
{
    char* ip_cible = ip();
    char commande[100];
    FILE *fp;
    char buffer[1024];

    if (system("which wpscan > /dev/null 2>&1") == 0) {
        sprintf(commande, "wpscan --url http://%s -e ap, at, u", ip_cible);
        printf("Commande : %s\n", commande);

        fp = popen(commande, "r");
        if (fp == NULL) {
            perror("popen");
            return;
        }

        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            printf("%s", buffer);
        }

        pclose(fp);
    } 
    else {
        printf("wpscan n'est pas installé.\nPour l'installer :https://wpscan.com/ \n");
    }
}

int main(void) {
    int choix;
    


    printf(RED "  ___          _                             _           _    _        _                                   \n"
           " / _ \\        | |                           | |         | |  | |      | |                                  \n"
           "/ /_\\ \\ _   _ | |_   ___   _ __ ___    __ _ | |_   ___  | |  | |  ___ | |__                                \n"
           "|  _  || | | || __| / _ \\ | '_ ` _ \\  / _` || __| / _ \\ | |/\\| | / _ \\| '_ \\                               \n"
           "| | | || |_| || |_ | (_) || | | | | || (_| || |_ |  __/ \\  /\\  /|  __/| |_) |                              \n"
           "\\_| |_/ \\__,_| \\__| \\___/ |_| |_| |_| \\__,_| \\__| \\___|  \\/  \\/  \\___||_.__/                              \n"
           "                                                                                                           \n"
           "          ______           ___   _              _               _____                                  _   \n"
           "          | ___ \\         / _ \\ | |            (_)             /  ___|                                | |  \n"
           "          | |_/ / _   _  / /_\\ \\| |  ___ __  __ _  ___         \\ `--.   ___  _ __   __ _   ___  _ __  | |_ \n"
           "          | ___ \\| | | | |  _  || | / _ \\\\ \\/ /| |/ __|         `--. \\ / _ \\| '__| / _` | / _ \\| '_ \\ | __|\n"
           "          | |_/ /| |_| | | | | || ||  __/ >  < | |\\__ \\        /\\__/ /|  __/| |   | (_| ||  __/| | | || |_ \n"
           "          \\____/  \\__, | \\_| |_/|_| \\___|/_/\\_\\|_||___/        \\____/  \\___||_|    \\__, | \\___||_| |_| \\__|\n"
           "                   __/ |                                ______                      __/ |                   \n"
           "                  |___/                                |______|                    |___/                    \n"RESET);

    printf("\n\n");
    system("echo 'Welcome to ToolKaliWeb'");
    printf("Quel outil voulez-vous utiliser ?\
            \n          1. Nmap\
            \n          2. Nikto\
            \n          3. GoBuster\
            \n          4. Wpscan\
            \n          5. Exit\
            \n=> ");
    scanf("%d", &choix);
    switch (choix)
    {
    case 1 :
        nmap();
        break;
    case 2 :
        nikto();
        break;
    case 3 :
        gobuster();
        break;
    case 4 :
        wpscan();
        break;
    default:
        break;
    }
    
    return 0;
}



