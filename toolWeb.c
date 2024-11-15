#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


#define RED   "\x1B[31m"
#define RESET "\x1B[0m"

void display_help() {
    printf("Usage: ./ToolWeb [OPTIONS]\n");
    printf("Options:\n");
    printf("  -h        Displays this help\n");
    printf("  -ip <IP>  Specifies the target IP address\n");
    printf("  -nmap     To use nmap\n");
    printf("  -nikto    To use nikto\n");
    printf("  -gobuster To use gobuster\n");
    printf("  -wpscan   To use wpscan\n");
    printf("\nExample: ./ToolWeb -ip 127.0.0.1 -nmap (IP must be specified first)\n");
}


void get_linux_distribution(char *dist, size_t size) {
    FILE *file = fopen("/etc/os-release", "r");
    if (!file) {
        perror("Error while opening /etc/os-release");
        exit(EXIT_FAILURE);
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "ID=", 3) == 0) {
            strncpy(dist, line + 3, size - 1);
            dist[strcspn(dist, "\n")] = 0;  
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
        printf("Unrecognized distribution, manual installation required.\n");
    }
}

void nmap(const char *ip_cible) {
    char commande[100];
    FILE *fp;
    char buffer[1024];

    if (is_nmap_installed()) {
        sprintf(commande, "nmap -p- -sV -sC -T4 %s", ip_cible);
        printf("Command : %s\n", commande);

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
        printf("Nmap is not installed. Do you want to install it? (y/n): ");
        char choix;
        scanf(" %c", &choix);
        if (choix == 'y' || choix == 'Y') {
            char dist[50];
            get_linux_distribution(dist, sizeof(dist));
            printf("Installing Nmap for the distribution : %s\n", dist);
            install_nmap(dist);
            nmap(ip_cible); 
        } else {
            printf("Installation canceled.\n");
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
        printf("Unrecognized distribution, manual installation required.\n");
    }
}

void nikto(const char *ip_cible)
{
    char commande[100];
    FILE *fp;
    char buffer[1024];


    if (is_nikto_installed()) {
        sprintf(commande, "nikto -h %s", ip_cible);
        printf("Command : %s\n", commande);

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
        printf("Nikto is not installed. Do you want to install it? (y/n): ");
        char choix;
        scanf(" %c", &choix);
        if (choix == 'y' || choix == 'Y') {
            char dist[50];
            get_linux_distribution(dist, sizeof(dist));
            printf("Installing Nikto for the distribution : %s\n", dist);
            install_nikto(dist);
            nikto(ip_cible);
        } 
        else {
            printf("Installation canceled.\n");
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
        printf("Unrecognized distribution, manual installation required.\n");
    }
}



void gobuster(const char *ip_cible)
{
    char commande[100];
    FILE *fp;
    char buffer[1024];

    if (is_gobuster_installed()) {
        if (access("/usr/share/wordlists/dirbuster/directory-list-2.3-medium.txt", F_OK) != 0) {
        printf("Wordlist is not installed. Do you want to install it? (y/n): ");
        char choix;
        scanf(" %c", &choix);
        if (choix == 'y' || choix == 'Y') {
            system("sudo mkdir -p /usr/share/wordlists/dirbuster");
            system("sudo wget https://raw.githubusercontent.com/daviddias/node-dirbuster/refs/heads/master/lists/directory-list-2.3-medium.txt -P /usr/share/wordlists/dirbuster/");
        } 
        else {
            printf("Installation canceled.\n");
        }
    }
        sprintf(commande, "gobuster dir -u http://%s -w /usr/share/wordlists/dirbuster/directory-list-2.3-medium.txt", ip_cible);
        printf("Command : %s\n", commande);

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
        printf("GoBuster is not installed. Do you want to install it? (y/n): ");
        char choix;
        scanf(" %c", &choix);
        if (choix == 'y' || choix == 'Y') {
            char dist[50];
            get_linux_distribution(dist, sizeof(dist));
            printf("Installing Gobuster for the distribution : %s\n", dist);
            install_gobuster(dist);
            gobuster(ip_cible);
        } 
        else {
            printf("Installation canceled\n");
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
        printf("Unrecognized distribution, manual installation required\n");
    }
}


void wpscan(const char *ip_cible)
{
    char commande[200];
    FILE *fp;
    char buffer[1024];

   
    if (is_wpscan_installed()) {
        sprintf(commande, "wpscan --url http://%s -e ap,at,u", ip_cible);
        printf("Command : %s\n", commande);

        
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
        printf("Wpscan is not installed. Do you want to install it? (y/n): ");
        char choix;
        scanf(" %c", &choix);
        if (choix == 'y' || choix == 'Y') {
            char dist[50];
            get_linux_distribution(dist, sizeof(dist));
            printf("Installing Wpscan for the distribution : %s\n", dist);
            install_wpscan(dist);
            wpscan(ip_cible);  
        } else {
            printf("Installation canceled.\n");
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
    printf("Welcome to ToolWeb\n\n");
    printf("\n\n");

    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            display_help();
            return 0; 
        } else if (strcmp(argv[i], "-ip") == 0) {
            if (i + 1 < argc) { 
                ip_cible = argv[i + 1];
                i++; 
            } else {
                printf("Error: The -ip option requires an IP address.\n");
                return 1;
            }
        } else if (strcmp(argv[i], "-nmap") == 0) {
            if (ip_cible == NULL) {
                printf("Error: The -nmap option requires an IP address with -ip.\n");
                return 1;
            }
            nmap(ip_cible); 
            return 0;
        } 
        else if (strcmp(argv[i], "-nikto") == 0) {
            if (ip_cible == NULL) {
                printf("Error: The -nikto option requires an IP address with -ip.\n");
                return 1;
            }
            nikto(ip_cible); 
            return 0;
        } 
        else if (strcmp(argv[i], "-gobuster") == 0) {
            if (ip_cible == NULL) {
                printf("Error: The -gobuster option requires an IP address with -ip.\n");
                return 1;
            }
            gobuster(ip_cible); 
            return 0;
        } 
        else if (strcmp(argv[i], "-wpscan") == 0) {
            if (ip_cible == NULL) {
                printf("Error: The -wpscan option requires an IP address with -ip.\n");
                return 1;
            }
            wpscan(ip_cible); 
            return 0;
        } else {
            printf("Unknown option: %s\n", argv[i]);
            display_help();
            return 1;
        }
    }

    if (ip_cible) {
        printf("Target IP specified: %s\n", ip_cible);
    } else {
        printf("No IP specified. Use -h to see the options.\n");
    }

    

    return 0;
}
