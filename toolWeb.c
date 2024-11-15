#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


// Couleurs pour l'affichage du logo
#define RED   "\x1B[31m"
#define RESET "\x1B[0m"

void afficher_aide() {
    printf("Usage : ./ToolWeb [OPTIONS]\n");
    printf("Options :\n");
    printf("  -h        Affiche cette aide\n");
    printf("  -ip <IP>  Spécifie l'adresse IP de la cible\n");
    printf("  -nmap     Pour utiliser nmap\n");
    printf("  -nikto    Pour utiliser nikto\n");
    printf("  -gobuster Pour utiliser gobuster\n");
    printf("  -wpscan   Pour utiliser wpscan\n");
    printf("\nExemple : ./ToolWeb -ip 127.0.0.1 -namp (Ip à spécifier en premier)\n");
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

// ------------------------------------------------------------
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

void nmap(const char *ip_cible) {
    char commande[100];
    FILE *fp;
    char buffer[1024];

    if (is_nmap_installed()) {
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
    } else {
        printf("Nmap n'est pas installé. Voulez-vous l'installer ? (y/n): ");
        char choix;
        scanf(" %c", &choix);
        if (choix == 'y' || choix == 'Y') {
            char dist[50];
            get_linux_distribution(dist, sizeof(dist));
            printf("Installation de Nmap pour la distribution : %s\n", dist);
            install_nmap(dist);
            nmap(ip_cible); // Rappel de la fonction après installation
        } else {
            printf("Installation annulée.\n");
        }
    }
}
// --------------------------------------------------------------
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

void nikto(const char *ip_cible)
{
    char commande[100];
    FILE *fp;
    char buffer[1024];


    if (is_nikto_installed()) {
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
            nikto(ip_cible);
        } 
        else {
            printf("Installation annulée.\n");
        }
        
    }
}

// --------------------------------------------------------------
// Gobuster

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



void gobuster(const char *ip_cible)
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
            gobuster(ip_cible);
        } 
        else {
            printf("Installation annulée.\n");
        }
        
    }
    
    
}

// --------------------------------------------------------------
// Wpscan


int is_wpscan_installed() {
    return system("which wpscan > /dev/null 2>&1") == 0;
}

void install_wpscan(const char *dist) {
    if (strcmp(dist, "ubuntu") == 0 || strcmp(dist, "debian") == 0) {
        system("sudo apt update && sudo apt install -y ruby-full build-essential libcurl4-openssl-dev libxml2 libxml2-dev libxslt1-dev");
        system("sudo gem install wpscan");
    } else if (strcmp(dist, "fedora") == 0) {
        system("sudo dnf install -y ruby ruby-devel libcurl-devel libxml2 libxml2-devel libxslt libxslt-devel");
        system("sudo gem install wpscan");
    } else if (strcmp(dist, "arch") == 0) {
        system("sudo pacman -S ruby libxml2 libxslt");
        system("sudo gem install wpscan");
    } else {
        printf("Distribution non reconnue, installation manuelle requise.\n");
    }
}


void wpscan(const char *ip_cible)
{
    char commande[200];
    FILE *fp;
    char buffer[1024];

   
    if (is_wpscan_installed()) {
        sprintf(commande, "wpscan --url http://%s -e ap,at,u", ip_cible);
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
    } else {
        printf("wpscan n'est pas installé. Voulez-vous l'installer ? (y/n): ");
        char choix;
        scanf(" %c", &choix);
        if (choix == 'y' || choix == 'Y') {
            char dist[50];
            get_linux_distribution(dist, sizeof(dist));
            printf("Installation de wpscan pour la distribution : %s\n", dist);
            install_wpscan(dist);
            wpscan(ip_cible);  
        } else {
            printf("Installation annulée.\n");
        }
    }
}


int main(int argc, char *argv[]) {
    char *ip_cible = NULL;

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

    printf("\n\n");
    printf("Bienvenue dans ToolWeb\n\n");
    printf("\n\n");

    // Parcourir les arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            afficher_aide();
            return 0; // Quitte après l'affichage de l'aide
        } else if (strcmp(argv[i], "-ip") == 0) {
            if (i + 1 < argc) { // Vérifie si une IP suit l'argument
                ip_cible = argv[i + 1];
                i++; // Saute à l'argument suivant
            } else {
                printf("Erreur : L'option -ip nécessite une adresse IP.\n");
                return 1;
            }
        } else if (strcmp(argv[i], "-nmap") == 0) {
            if (ip_cible == NULL) {
                printf("Erreur : L'option -nmap nécessite une adresse IP avec -ip.\n");
                return 1;
            }
            nmap(ip_cible); // Appel de la fonction avec l'IP cible
            return 0;
        } 
        else if (strcmp(argv[i], "-nikto") == 0) {
            if (ip_cible == NULL) {
                printf("Erreur : L'option -nikto nécessite une adresse IP avec -ip.\n");
                return 1;
            }
            nikto(ip_cible); // Appel de la fonction avec l'IP cible
            return 0;
        } 
        else if (strcmp(argv[i], "-gobuster") == 0) {
            if (ip_cible == NULL) {
                printf("Erreur : L'option -gobuster nécessite une adresse IP avec -ip.\n");
                return 1;
            }
            gobuster(ip_cible); // Appel de la fonction avec l'IP cible
            return 0;
        } 
        else if (strcmp(argv[i], "-wpscan") == 0) {
            if (ip_cible == NULL) {
                printf("Erreur : L'option -wpscan nécessite une adresse IP avec -ip.\n");
                return 1;
            }
            wpscan(ip_cible); // Appel de la fonction avec l'IP cible
            return 0;
        } else {
            printf("Option inconnue : %s\n", argv[i]);
            afficher_aide();
            return 1;
        }
    }

    if (ip_cible) {
        printf("IP cible spécifiée : %s\n", ip_cible);
    } else {
        printf("Aucune IP spécifiée. Utilisez -h pour voir les options.\n");
    }

    

    return 0;
}
