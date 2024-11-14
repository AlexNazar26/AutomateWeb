#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Couleurs pour l'affichage du logo
#define RED   "\x1B[31m"
#define RESET "\x1B[0m"

char* ip(void)
{
    static char ip[15];
    printf("Entrez l'adresse IP de la cible : ");
    scanf("%s", ip);
    return ip;
}

void get_linux_distribution(char *dist, size_t size) {
    FILE *file = fopen("/etc/os-release", "r");
    if (!file) {
        perror("Erreur lors de l'ouverture de /etc/os-release");
        exit(EXIT_FAILURE);
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "ID=", 3) == 0) {
            strncpy(dist, line + 3, size - 1);
            dist[strcspn(dist, "\n")] = 0;  // Enlever le caractère de fin de ligne
            break;
        }
    }
    fclose(file);
}

// Nmap

int is_nmap_installed() {
    return system("which nmap > /dev/null 2>&1") == 0;
}


void install_nmap(const char *dist) {
    if (strcmp(dist, "ubuntu") == 0 || strcmp(dist, "debian") == 0) {
        system("sudo apt update && sudo apt install -y nmap");
    } else if (strcmp(dist, "fedora") == 0) {
        system("sudo dnf install -y nmap");
    } else if (strcmp(dist, "arch") == 0) {
        system("sudo pacman -Syu nmap");
    } else {
        printf("Distribution non reconnue, installation manuelle requise.\n");
    }
}

void nmap() {
    char commande[100];
    FILE *fp;
    char buffer[1024];


    if (is_nmap_installed()) {
        char* ip_cible = ip();
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
        printf("Nmap n'est pas installé. Voulez-vous l'installer ? (y/n): ");
        char choix;
        scanf(" %c", &choix);
        if (choix == 'y' || choix == 'Y') {
            char dist[50];
            get_linux_distribution(dist, sizeof(dist));
            printf("Installation de Nmap pour la distribution : %s\n", dist);
            install_nmap(dist);
            nmap();
        } 
        else {
            printf("Installation annulée.\n");
        }
        
    }
   
}


// ---------------------------------------------------------------------------------
// Nikto

int is_nikto_installed() {
    return system("which nikto > /dev/null 2>&1") == 0;
}

void install_nikto(const char *dist) {
    if (strcmp(dist, "ubuntu") == 0 || strcmp(dist, "debian") == 0) {
        system("sudo apt update && sudo apt install -y nikto");
    } else if (strcmp(dist, "fedora") == 0) {
        system("sudo dnf install -y nikto");
    } else if (strcmp(dist, "arch") == 0) {
        system("sudo pacman -Syu nikto");
    } else {
        printf("Distribution non reconnue, installation manuelle requise.\n");
    }
}

void nikto(void)
{
    char commande[100];
    FILE *fp;
    char buffer[1024];


    if (is_nikto_installed()) {
        char* ip_cible = ip();
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
        printf("Nikto n'est pas installé. Voulez-vous l'installer ? (y/n): ");
        char choix;
        scanf(" %c", &choix);
        if (choix == 'y' || choix == 'Y') {
            char dist[50];
            get_linux_distribution(dist, sizeof(dist));
            printf("Installation de Nikto pour la distribution : %s\n", dist);
            install_nikto(dist);
            nikto();
        } 
        else {
            printf("Installation annulée.\n");
        }
        
    }
}

// ---------------------------------------------------------------------------------
// GoBuster
int is_gobuster_installed() {
    return system("which gobuster > /dev/null 2>&1") == 0;
}



void install_gobuster(const char *dist) {
    if (strcmp(dist, "ubuntu") == 0 || strcmp(dist, "debian") == 0) {
        system("sudo apt update && sudo apt install -y gobuster");
    } else if (strcmp(dist, "fedora") == 0) {
        system("sudo dnf install -y gobuster");
    } else if (strcmp(dist, "arch") == 0) {
        system("sudo pacman -Syu gobuster");
    } else {
        printf("Distribution non reconnue, installation manuelle requise.\n");
    }
}



void gobuster(void)
{
    char commande[100];
    FILE *fp;
    char buffer[1024];

    if (is_gobuster_installed()) {
        if (access("/usr/share/wordlists/dirbuster/directory-list-2.3-medium.txt", F_OK) != 0) {
        printf("Wordlist n'est pas installé. Voulez-vous l'installer ? (y/n): ");
        char choix;
        scanf(" %c", &choix);
        if (choix == 'y' || choix == 'Y') {
            system("sudo mkdir -p /usr/share/wordlists/dirbuster");
            system("sudo wget https://raw.githubusercontent.com/daviddias/node-dirbuster/refs/heads/master/lists/directory-list-2.3-medium.txt -P /usr/share/wordlists/dirbuster/");
        } 
        else {
            printf("Installation annulée.\n");
        }
    }
        char* ip_cible = ip();
        sprintf(commande, "gobuster dir -u http://%s -w /usr/share/wordlists/dirbuster/directory-list-2.3-medium.txt", ip_cible);
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
        printf("GoBuster n'est pas installé. Voulez-vous l'installer ? (y/n): ");
        char choix;
        scanf(" %c", &choix);
        if (choix == 'y' || choix == 'Y') {
            char dist[50];
            get_linux_distribution(dist, sizeof(dist));
            printf("Installation de GoBuster pour la distribution : %s\n", dist);
            install_gobuster(dist);
            gobuster();
        } 
        else {
            printf("Installation annulée.\n");
        }
        
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

    

    printf("\n\n");
    system("echo 'Welcome to ToolKaliWeb'");

    while (1) {  // Boucle infinie pour garder le menu actif jusqu'à ce que l'utilisateur choisisse de quitter
        system("clear");
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
           "                  |___/                                |______|                    |___/                    \n" RESET);
        
        printf("Quel outil voulez-vous utiliser ?\
                \n          1. Nmap\
                \n          2. Nikto\
                \n          3. GoBuster\
                \n          4. Wpscan\
                \n          5. Exit\
                \n=> ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                nmap();
                break;
            case 2:
                nikto();
                break;
            case 3:
                gobuster();
                break;
            case 4:
                wpscan();
                break;
            case 5:
                printf("Exiting...\n");
                return 0;  // Quitte le programme
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
                break;
        }
    }

    return 0;
}

