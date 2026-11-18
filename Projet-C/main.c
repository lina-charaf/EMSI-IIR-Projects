#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    char nom[50];
    float notes[3];
    float moyenne;
} Etudiant;

Etudiant etudiants[MAX];
int nb = 0;

void ajouter() {
    if (nb >= MAX) {
        printf("Liste pleine.\n");
        return;
    }

    Etudiant e;

    printf("Nom : ");
    scanf("%49s", e.nom);

   for (int i = 0; i < 3; i++) {
        do {
            printf("Note %d (0-20) : ", i + 1);
            scanf("%f", &e.notes[i]);

            if (e.notes[i] < 0 || e.notes[i] > 20) {
                printf("Note invalide !\n");
            }

        } while (e.notes[i] < 0 || e.notes[i] > 20);
    }

    e.moyenne = (e.notes[0] + e.notes[1] +
                 e.notes[2]) / 3.0;

    etudiants[nb] = e;
    nb++;

    printf("Etudiant ajoute avec succes.\n");
}

void afficher() {
    if (nb == 0) {
        printf("Aucun etudiant.\n");
        return;
    }

    for (int i = 0; i < nb; i++) {
        printf("%d. %s | Notes : %.1f %.1f %.1f | Moyenne : %.2f\n",
               i + 1,
               etudiants[i].nom,
               etudiants[i].notes[0],
               etudiants[i].notes[1],
               etudiants[i].notes[2],
               etudiants[i].moyenne);
    }
}

void classer() {
    Etudiant temp;

    if (nb == 0) {
        printf("Aucun etudiant a classer.\n");
        return;
    }

    for (int i = 0; i < nb - 1; i++) {
        for (int j = 0; j < nb - i - 1; j++) {

            if (etudiants[j].moyenne <
                etudiants[j + 1].moyenne) {

                temp = etudiants[j];
                etudiants[j] = etudiants[j + 1];
                etudiants[j + 1] = temp;
            }
        }
    }

    printf("Classement effectue avec succes !\n");
    afficher();
}

void rechercher() {
    char nomRecherche[50];
    int trouve = 0;

    printf("Donner le nom a rechercher : ");
    scanf("%49s", nomRecherche);

    for (int i = 0; i < nb; i++) {

        if (strcmp(etudiants[i].nom, nomRecherche) == 0) {

            printf("Etudiant trouve !\n");
            printf("Nom : %s\n", etudiants[i].nom);
            printf("Moyenne : %.2f\n", etudiants[i].moyenne);

            trouve = 1;
            break;
        }
    }

    if (trouve == 0) {
        printf("Etudiant introuvable.\n");
    }
}

void sauvegarder() {
    FILE *fichier;

    fichier = fopen("etudiants.txt", "w");

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    for (int i = 0; i < nb; i++) {
        fprintf(fichier, "%s %.2f %.2f %.2f %.2f\n",
                etudiants[i].nom,
                etudiants[i].notes[0],
                etudiants[i].notes[1],
                etudiants[i].notes[2],
                etudiants[i].moyenne);
    }

    fclose(fichier);

    printf("Donnees sauvegardees avec succes !\n");
}

void charger() {
    FILE *fichier;

    fichier = fopen("etudiants.txt", "r");

    if (fichier == NULL) {
        printf("Fichier introuvable.\n");
        return;
    }

    nb = 0;

    while (nb < MAX &&
           fscanf(fichier, "%49s %f %f %f %f",
                  etudiants[nb].nom,
                  &etudiants[nb].notes[0],
                  &etudiants[nb].notes[1],
                  &etudiants[nb].notes[2],
                  &etudiants[nb].moyenne) == 5) {

        nb++;
    }

    fclose(fichier);

    printf("%d etudiant(s) charge(s) avec succes !\n", nb);
}

int main() {
    int choix;

    do {
        printf("\n===== GESTION DES NOTES =====\n");
        printf("1. Ajouter un etudiant\n");
        printf("2. Afficher la liste\n");
        printf("3. Classer par moyenne\n");
        printf("4. Rechercher un etudiant\n");
        printf("5. Sauvegarder\n");
        printf("6. Charger\n");
        printf("0. Quitter\n");

        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {

            case 1:
                ajouter();
                break;

            case 2:
                afficher();
                break;

            case 3:
                classer();
                break;

            case 4:
                rechercher();
                break;

            case 5:
                sauvegarder();
                break;

            case 6:
                charger();
                break;

            case 0:
                printf("Au revoir !\n");
                break;

            default:
                printf("Choix invalide.\n");
        }

    } while (choix != 0);

    return 0;
}
