#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string.h>
#include <windows.h>

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 4096 //makro, kde definujeme velkost prijimacieho buffera

int is_prime(int a) {
    if (a < 2)
        return 0;
    if (a == 2 || a == 3)
        return 1;
    if (a % 2 == 0)
        return 0;
    for (int i = 3; i <= a/2; i += 2) {
        if (a % i == 0) {
            return 0;
        }
    }
    return 1;
}

void posunuty_vypis(const char *text, int lava_prava) {
    int medzera = (lava_prava == 1) ? 0 : 60;
    int sirka_riadku = 60 - 1;
    char kopia[DEFAULT_BUFLEN];
    strncpy(kopia, text, DEFAULT_BUFLEN);
    char *slovo = strtok(kopia, " ");
    int zostava = sirka_riadku;
    printf("%*s", medzera, "");

    while (slovo != NULL) {
        int dlzka_slova = strlen(slovo);
        if (dlzka_slova + 1 > zostava) {
            printf("\n");
            printf("%*s", medzera, "");
            zostava = sirka_riadku;
        }
        printf("%s ", slovo);
        zostava -= (dlzka_slova + 1);
        slovo = strtok(NULL, " ");
    }
    printf("\n");
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void vypis_milisekund(char meno[]) {
    for(int i = 0; i < strlen(meno); i++) {
        printf("%c", meno[i]);
        Sleep(500);
    }
    printf("\n");
}

int sum_of_id(const char *id) {
    int sum = 0;
    for(int i = 0; i < 5; i++) {
        sum += id[i] - '0';
    }
    int podiel = sum/ (id[4] - '0');
    return sum - podiel* (id[4] - '0');
}

int posielanie(SOCKET socket, const char *text, FILE *f) {
    int vysledok = send(socket, text, (int)strlen(text), 0);
    if (vysledok == SOCKET_ERROR) {
        printf("send failed: %d\n", WSAGetLastError());
        closesocket(socket);
        WSACleanup();
        return -1;
    }
    printf("Bytes Sent: %ld \n", vysledok);
    fprintf(f,"Ja: %s\n\n", text);
    setColor(9);
    posunuty_vypis(text,1);
    setColor(7);
    return vysledok;
}

int prijimanie(SOCKET socket, char *text, FILE *f) {
    int vysledok = recv(socket, text, DEFAULT_BUFLEN, 0);
    text[vysledok] = '\0';
    if ( vysledok > 0 )
        printf("Bytes received: %d\n", vysledok);     //prisli validne data, vypis poctu
    if ( vysledok == 0 ) {
        printf("Connection closed\n");
        return 0;
    }//v tomto pripade server ukoncil komunikaciu
    if (vysledok < 0) {
        printf("recv failed with error: %d\n", WSAGetLastError());     //ina chyba
        return -1;
    }
    fprintf(f,"Morpheus: %s\n", text);
    setColor(10);
    posunuty_vypis(text,2);
    setColor(7);
    return 1;
}

void sifrovanie(char *text) {
    for(int i = 0; i < 131; i++) {
        text[i] ^= 55;
    }
    for(int i = 0; i < 131; i++) {
        putchar(text[i]);
    }
    printf("\n");
}

const char *posun_znakov(char text[DEFAULT_BUFLEN]) {
    static char posunute_znaky[DEFAULT_BUFLEN];
    int dlzka_noveho = 0;
    for (int i = 0; i < strlen(text)-1; i++) {
        if (is_prime(i+1)) {
            posunute_znaky[dlzka_noveho] = text[i];
            dlzka_noveho++;
        }
    }
    return posunute_znaky;
}

int main(void) {

    //uvodne nastavovacky
    WSADATA wsaData;    //struktura WSADATA pre pracu s Winsock
    int iResult;
    SetConsoleOutputCP(CP_UTF8);
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);     //zakladna inicializacia
    if (iResult != 0)     //kontrola, ci nestala chyba
    {
        printf("SAStartup failed: %d\n", iResult);
        return 1;
    }

    struct addrinfo *result = NULL, *ptr = NULL;     //struktura pre pracu s adresami
    struct addrinfo hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;     //pracujeme s protokolom TCP/IP

    // Resolve the server address and port
    iResult = getaddrinfo("147.175.115.34", "777", &hints, &result);
    if (iResult != 0)     //kontrola, ci nenastala chyba
    {
        printf("getaddrinfo failed: %d\n", iResult);
        WSACleanup();
        return 1;
    }
    else
        printf("getaddrinfo didn't fail...\n");

    //vytvorenie socketu a pripojenie sa

    SOCKET ConnectSocket = INVALID_SOCKET;

    // Attempt to connect to the first address returned by
    // the call to getaddrinfo
    ptr = result;

    // Create a SOCKET for connecting to server => pokus o vytvorenie socketu
    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,ptr->ai_protocol);

    if (ConnectSocket == INVALID_SOCKET)     //kontrola, ci nenastala chyba
    {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }
    else
        printf("Error at socket DIDN'T occur...\n");

    // Connect to server. => pokus o pripojenie sa na server

    iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR)     //kontrola, ci nenastala chyba
        printf("Not connected to server…\n");
    else
        printf("Connected to server!\n");

    if (iResult == SOCKET_ERROR)    //osetrenie chyboveho stavu
    {
        closesocket(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
        WSACleanup();
        return 1;
    }

    Sleep(250);

    char sendbuf[4096]; //buffer (v zasade retazec), kam sa budu ukladat data, ktore chcete posielat
    char recvbuf[DEFAULT_BUFLEN];
    int pocet = 1;
    FILE *f;
    f = fopen("konverzacia.txt", "a");
    while (1) {
        if (pocet == 1) {
            strncpy(sendbuf, "1", DEFAULT_BUFLEN);
            if (posielanie(ConnectSocket, sendbuf, f) == -1)
                continue;
            if (prijimanie(ConnectSocket, recvbuf, f) <= 0)
                break;
        }
        else if (pocet == 2) {
            strncpy(sendbuf, "134117", DEFAULT_BUFLEN);
            if (posielanie(ConnectSocket, sendbuf, f) == -1)
                continue;
            if (prijimanie(ConnectSocket, recvbuf, f) <= 0)
                break;
        }
        if (pocet == 3) {
            strncpy(sendbuf, "1", DEFAULT_BUFLEN);
            if (posielanie(ConnectSocket, sendbuf, f) == -1)
                continue;
            if (prijimanie(ConnectSocket, recvbuf, f) <= 0)
                break;
        }
        else if (pocet == 4) {
            vypis_milisekund("Martin Slatárovič");
            strncpy(sendbuf,"845548", DEFAULT_BUFLEN);
            if (posielanie(ConnectSocket, sendbuf, f) == -1)
                continue;
            if (prijimanie(ConnectSocket, recvbuf, f) <= 0)
                break;
        }
        else if (pocet == 5) {
            strncpy(sendbuf,"753332", DEFAULT_BUFLEN);
            if (posielanie(ConnectSocket, sendbuf, f) == -1)
                continue;
            if (prijimanie(ConnectSocket, recvbuf, f) <= 0)
                break;
        }
        else if (pocet == 6) {
            int cislo = sum_of_id("134117");
            sprintf(sendbuf,"%d", cislo);
            if (posielanie(ConnectSocket, sendbuf, f) == -1)
                continue;
            if (prijimanie(ConnectSocket, recvbuf, f) <= 0)
                break;
        }
        else if (pocet == 7) {
            strncpy(sendbuf,"333222334", DEFAULT_BUFLEN);
            if (posielanie(ConnectSocket, sendbuf, f) == -1)
                continue;
            if (prijimanie(ConnectSocket, recvbuf, f) <= 0)
                break;
        }
        else if (pocet == 8) {
            strncpy(sendbuf,"123", DEFAULT_BUFLEN);
            if (posielanie(ConnectSocket, sendbuf, f) == -1)
                continue;
            if (prijimanie(ConnectSocket, recvbuf, f) <= 0)
                break;
        }
        else if (pocet == 9) {
            sifrovanie(recvbuf);
            if (posielanie(ConnectSocket, sendbuf, f) == -1)
                continue;
            if (prijimanie(ConnectSocket, recvbuf, f) <= 0)
                break;
        }
        else if (pocet == 10) {
            double suradnica1 = 51.500729;
            int integralova_cast1 = (int)(suradnica1);
            char poslana_suradnica1[1000];
            sprintf(poslana_suradnica1, "%d", integralova_cast1);
            strncpy(sendbuf, poslana_suradnica1, DEFAULT_BUFLEN);
            if (posielanie(ConnectSocket, sendbuf, f) == -1)
                continue;
            if (prijimanie(ConnectSocket, recvbuf, f) <= 0)
                break;
        }
        else if (pocet == 11) {
            double suradnica2 = -0.124625;
            int integralova_cast2 = (int)(suradnica2);
            char poslana_suradnica2[1000];
            sprintf(poslana_suradnica2, "%d", integralova_cast2);
            strncpy(sendbuf, poslana_suradnica2, DEFAULT_BUFLEN);
            if (posielanie(ConnectSocket, sendbuf, f) == -1)
                continue;
            if (prijimanie(ConnectSocket, recvbuf, f) <= 0)
                break;
        }
        else if (pocet == 12) {
            if (posielanie(ConnectSocket, "B.B.", f) == -1)
                continue;
            if (prijimanie(ConnectSocket, recvbuf, f) <= 0)
                break;
        }
        else if (pocet == 13) {
            if (posielanie(ConnectSocket, "PRIMENUMBER", f) == -1)
                continue;
            if (prijimanie(ConnectSocket, recvbuf, f) <= 0)
                break;
        }
        else if (pocet == 14) {
            char *novy_text = posun_znakov(recvbuf);
            strncpy(sendbuf, novy_text, DEFAULT_BUFLEN);
            if (posielanie(ConnectSocket, sendbuf, f) == -1)
                continue;
            if (prijimanie(ConnectSocket, recvbuf, f) <= 0)
                break;
        }
        else if (pocet == 15) {
            if (posielanie(ConnectSocket, "Trinity", f) == -1)
                continue;
            if (prijimanie(ConnectSocket, recvbuf, f) <= 0)
                break;
        }
        else if (pocet == 16) {
            if (posielanie(ConnectSocket, "nekonecno", f) == -1)
                continue;
            if (prijimanie(ConnectSocket, recvbuf, f) <= 0)
                break;

        }
        else if (pocet == 17) {
            if (posielanie(ConnectSocket, "cache", f) == -1)
                continue;
            if (prijimanie(ConnectSocket, recvbuf, f) <= 0)
                break;
        }
        else if (pocet == 18) {
            break;
        }
        pocet++;
    }
    fclose(f);
    //zavretie socketu
    closesocket(ConnectSocket);
    WSACleanup();
    return 0;
}