/*Syst�me de Suivi de Sant� Personnelle
 Ajouter des enregistrements quotidiens de poids, pression sanguine, et pouls pour chaque
 patient.
 Rechercher des enregistrements par date
 G�n�rer un rapport de sant� des informations du patient.
 G�rer les rendez des patients
 Enregistrer les donn�es dans un fichier pour suivi continu.
 Importer des donn�es pr�c�dentes � partir d'un fichier.*/


#include "fonction.h"

int main() {
    Menu menu;
    int choix;

    do {
        system("cls");
        menu.afficherMenu();
        cin >> choix;

        menu.executerOption(choix);

        if (choix != 6) {
            cout << "\nAppuyez sur Entr�e pour revenir au menu...";
            cin.ignore();
            cin.get();
        }
    } while (choix != 6);

    return 0;
}


