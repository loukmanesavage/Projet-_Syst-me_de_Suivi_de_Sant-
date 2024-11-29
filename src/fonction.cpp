#include "fonction.h"

struct Enregistrement {
    string identifiant;
    string nomComplet;
    float poids;
    int pression;
    int pouls;
    string date;
};

void Menu::afficherMenu() {
    cout << "\n";
    cout << "   MENU PRINCIPAL\n";
    cout << "   ==============\n\n";
    cout << "     1. Enregistrer\n";
    cout << "     2. Rechercher\n";
    cout << "     3. G�n�rer un rapport\n";
    cout << "     4. Prendre un rendez-vous\n";
    cout << "     5. Importer les donn�es\n";
    cout << "     0. Quitter\n";
    cout << "\n";
    cout << "   Choix [1-6]: ";
}

void Menu::executerOption(int choix) {
    switch (choix) {
        case 1:
            enregistrer();
            break;
        case 2:
            rechercher();
            break;
        case 3:
            genererRapport();
            break;
        case 4:
            prendreRendezVous();
            break;
        case 5:
            importerDonnees();
            break;
        case 0:
            cout << "Au revoir ! Merci d'avoir utilis� ce programme.\n";
            break;
        default:
            cout << "   Option invalide.\n";
    }
}

void Menu::enregistrer() {
    system("cls");
    cout << "\n";
    cout << "   Enregistrement\n";
    cout << "   ==============\n\n";

    string identifiant, nomComplet;
    float poids;
    int pression, pouls;

    cout << "   Identifiant: ";
    cin >> identifiant;
    cin.ignore();
    cout << "   Nom complet: ";
    getline(cin, nomComplet);

    cout << "   Poids [en kg]: ";
    cin >> poids;

    cout << "   Pression sanguine: ";
    cin >> pression;

    cout << "   Pouls: ";
    cin >> pouls;

    time_t now = time(0);
    tm *ltm = localtime(&now);
    char date[11];
    strftime(date, sizeof(date), "%Y-%m-%d", ltm);

    ofstream fichier("save.data", ios::app);
    if (fichier.is_open()) {

        fichier << identifiant << "," << nomComplet << "," << poids << ","
                << pression << "," << pouls << "," << date << "\n";
        fichier.close();
        cout << "   Enregistrement ajout� avec succ�s!\n";
    } else {
        cout << "   Erreur: Impossible d'ouvrir le fichier 'save.data'.\n";
    }
}

void Menu::rechercher() {
    system("cls");
    cout << "\n";
    cout << "   Recherche\n";
    cout << "   =========\n\n";

    int jour, mois, annee;
    cout << "   Jour (JJ): ";
    cin >> jour;
    cout << "   Mois (MM): ";
    cin >> mois;
    cout << "   Ann�e (AAAA): ";
    cin >> annee;

    ostringstream dateRecherche;
    dateRecherche << setw(4) << setfill('0') << annee << "-"
                  << setw(2) << setfill('0') << mois << "-"
                  << setw(2) << setfill('0') << jour;

    string dateCherchee = dateRecherche.str();

    // Ouvrir le fichier
    ifstream fichier("save.data");
    if (!fichier.is_open()) {
        cout << "Erreur: Impossible d'ouvrir le fichier 'save.data'.\n";
        return;
    }

    // Lire et traiter le fichier
    string ligne;
    bool found = false;
    system("cls");
    cout << "\n";
    cout << "   R�sultats de la recherche\n";
    cout << "   ==========================\n\n   ";
    cout << left << setw(15) << "Identifiant" << setw(20) << "Nom complet"
         << setw(10) << "Poids" << setw(15) << "Pression" << setw(10)
         << "Pouls" << setw(12) << "Date" << endl;
    cout << "   --------------------------------------------------------------------------------\n";

    while (getline(fichier, ligne)) {
        stringstream ss(ligne);
        string identifiant, nomComplet, poids, pression, pouls, date;

        // D�couper la ligne
        getline(ss, identifiant, ',');
        getline(ss, nomComplet, ',');
        getline(ss, poids, ',');
        getline(ss, pression, ',');
        getline(ss, pouls, ',');
        getline(ss, date, ',');

        // Comparer la date avec celle recherch�e
        if (date == dateCherchee) {
            found = true;
            // Afficher les informations sous forme de tableau
            cout << "   ";
            cout << left << setw(15) << identifiant << setw(20) << nomComplet
                 << setw(10) << poids << setw(15) << pression << setw(10)
                 << pouls << setw(12) << date << endl;
        }
    }

    if (!found) {
        cout << "\n   Aucun enregistrement trouv� pour la date: " << dateCherchee << ".\n";
    }

    cout << "   ================================================================================\n";

    fichier.close();
}

void Menu::genererRapport() {
    system("cls");
    cout << "\n";
    cout << "   G�n�ration du Rapport\n";
    cout << "   =====================\n\n";

    ifstream fichier("save.data");
    if (!fichier.is_open()) {
        cout << "Erreur: Impossible d'ouvrir le fichier 'save.data'.\n";
        return;
    }

    vector<Enregistrement> enregistrements;
    string ligne;

    while (getline(fichier, ligne)) {
        stringstream ss(ligne);
        Enregistrement e;
        string poids, pression, pouls;

        getline(ss, e.identifiant, ',');
        getline(ss, e.nomComplet, ',');
        getline(ss, poids, ',');
        getline(ss, pression, ',');
        getline(ss, pouls, ',');
        getline(ss, e.date, ',');

        e.poids = stof(poids);
        e.pression = stoi(pression);
        e.pouls = stoi(pouls);

        enregistrements.push_back(e);
    }
    fichier.close();

    if (enregistrements.empty()) {
        cout << "Aucun enregistrement trouv� pour g�n�rer le rapport.\n";
        return;
    }

    int total = enregistrements.size();
    float totalPoids = 0.0f;
    int totalPression = 0, totalPouls = 0;

    for (const auto &e : enregistrements) {
        totalPoids += e.poids;
        totalPression += e.pression;
        totalPouls += e.pouls;
    }

    float poidsMoyen = totalPoids / total;
    float pressionMoyenne = static_cast<float>(totalPression) / total;
    float poulsMoyen = static_cast<float>(totalPouls) / total;

    sort(enregistrements.begin(), enregistrements.end(),
         [](const Enregistrement &a, const Enregistrement &b) {
             return a.date < b.date;
         });

    string nomFichier;
    cout << "   Nom du fichier: ";
    cin >> nomFichier;

    ofstream rapport(nomFichier);
    if (!rapport.is_open()) {
        cout << "Erreur: Impossible de cr�er le fichier '" << nomFichier << "'.\n";
        return;
    }

    rapport << "   Rapport des Enregistrements\n";
    rapport << "   ===========================\n\n";
    rapport << "   Total d'enregistrements: " << total << "\n";
    rapport << "   Poids moyen: " << fixed << setprecision(2) << poidsMoyen << " kg\n";
    rapport << "   Pression sanguine moyenne: " << fixed << setprecision(2)
            << pressionMoyenne << "\n";
    rapport << "   Pouls moyen : " << fixed << setprecision(2) << poulsMoyen << "\n";
    rapport << "\n\n   Liste des enregistrements\n\n";
    rapport << left << setw(15) << "   Identifiant" << setw(20) << "Nom complet"
            << setw(10) << "Poids" << setw(15) << "Pression" << setw(10)
            << "Pouls" << setw(12) << "Date" << "\n";
    rapport << "   --------------------------------------------------------------------------------\n";

    for (const auto &e : enregistrements) {
        rapport << "   ";
        rapport << left << setw(15) << e.identifiant << setw(20) << e.nomComplet
                << setw(10) << e.poids << setw(15) << e.pression << setw(10)
                << e.pouls << setw(12) << e.date << "\n";
    }

    rapport.close();
    cout << "Rapport g�n�r� avec succ�s dans le fichier '" << nomFichier << "' !\n";
}

void Menu::prendreRendezVous() {
    system("cls");
    cout << "\n";
    cout << "   Prise de Rendez-vous\n";
    cout << "   ====================\n";

    string identifiant, nomComplet, motif, date, heure;

    cout << "   Identifiant: ";
    cin >> identifiant;

    cout << "   Nom complet: ";
    cin.ignore();
    getline(cin, nomComplet);

    cout << "   Motif: ";
    getline(cin, motif);

    cout << "   Date (YYYY-MM-DD): ";
    cin >> date;

    cout << "   Heure (HH:MM): ";
    cin >> heure;

    if (date.length() != 10 || date[4] != '-' || date[7] != '-' ||
        heure.length() != 5 || heure[2] != ':') {
        cout << "   Erreur : Format de date ou d'heure invalide !\n";
        return;
    }

    stringstream nouvelleLigne;
    nouvelleLigne << "   ";
    nouvelleLigne << std::setw(15) << std::left << identifiant
                  << std::setw(25) << std::left << nomComplet
                  << std::setw(30) << std::left << motif
                  << std::setw(15) << std::left << date
                  << std::setw(10) << std::left << heure;

    bool fichierExiste = ifstream("rendezvous.data").good();

    ofstream fichier("rendezvous.data", ios::app);
    if (fichier.is_open()) {
        if (!fichierExiste) {
            fichier << std::setw(15) << std::left << "   Identifiant"
                    << std::setw(25) << std::left << "Nom complet"
                    << std::setw(30) << std::left << "Motif"
                    << std::setw(15) << std::left << "Date"
                    << std::setw(10) << std::left << "Heure\n";
            fichier << string(91, '-') << "\n";
        }

        fichier << nouvelleLigne.str() << "\n";
        fichier.close();
        cout << "\nRendez-vous enregistr� avec succ�s !\n";
    } else {
        cout << "Erreur: Impossible d'ouvrir le fichier 'rendezvous.data'.\n";
    }
}
