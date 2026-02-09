#include <iostream>
#include <fstream>
#include "teams.h"

const int BUFFER = 1000;
const char *FILE_NAME = "data.txt";


int strLen(const char *str) {
    int index = 0;
    while (str[index] != '\0') {
        index++;
    }
    return index;
}

char *strCopy(const char *sor, char *dest) {
    int index = 0;
    while (sor[index] != '\0') {
        dest[index] = sor[index];
        index++;
    }
    dest[index] = '\0';
    return dest;
}

bool strCmp(const char *str1, const char *str2) {
    int index = 0;
    if (strLen(str1) != strLen(str2)) {
        return false;
    }
    while (str1[index] != '\0' && str2[index] != '\0') {
        if (str1[index] != str2[index]) {
            return false;
        }
        index++;
    }
    return true;
}

void printNSpaces(int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << " ";
    }
}

std::ofstream createFile() {
    std::ofstream out(FILE_NAME);
    return out;
}

void readFile(team *&teams, int &teamsCount, int &capacity) {
    std::ifstream in(FILE_NAME);
    if (!in.is_open()) {
        std::cout << ">> Data file could not be opened. New one will be created." << std::endl;
        return;
    }
    int fileCount, fileCapacity;
    in >> fileCount >> fileCapacity;
    in.ignore();
    if (fileCapacity >= capacity) {
        delete []teams;
        capacity = fileCapacity;
        teams = new team[capacity];
    }
    teamsCount = fileCount;
    for (int i = 0; i < teamsCount; ++i) {
        char buffer[1000];
        in.getline(buffer, 1000, '|');
        teams[i].name = new char[strLen(buffer) + 1];
        strCopy(buffer, teams[i].name);
        in >> teams[i].gamesPlayed >> teams[i].wins >> teams[i].draws >> teams[i].loses >> teams[i].goalsFor >> teams[i]
                .goalsAgainst >> teams[i].goalDiff >> teams[i].points;
        in.ignore();
    }
    in.close();
}

void freeTeamsMemory(team *&teams, const int &teamsCount) {
    for (int i = 0; i < teamsCount; ++i) {
        delete [] teams[i].name;
    }
    delete [] teams;
}

void printGDSign(const int n) {
    if (n > 0) {
        std::cout << '+';
    } else if (n == 0) {
        std::cout << " ";
    }
}

void printSpaceForSmallNums(const int n) {
    if (n < 10) {
        std::cout << " ";
    }
}

void printMenu() {
    std::cout << "Menu:" << std::endl;
    std::cout << "1. Add team" << std::endl;
    std::cout << "2. Record match result" << std::endl;
    std::cout << "3. View standings" << std::endl;
    std::cout << "4. Team stats" << std::endl;
    std::cout << "5. Edit team name" << std::endl;
    std::cout << "6. Delete team" << std::endl;
    std::cout << "7. Save & exit" << std::endl;
    std::cout << std::endl;
    std::cout << "Choice: ";
}

void setStatsNull(team *&teams, const int &teamCount) {
    for (int i = 0; i < teamCount; ++i) {
        teams[i].name = new char [1];
        teams[i].name[0] = '\0';
        teams[i].gamesPlayed = 0;
        teams[i].wins = 0;
        teams[i].draws = 0;
        teams[i].loses = 0;
        teams[i].goalsFor = 0;
        teams[i].goalsAgainst = 0;
        teams[i].goalDiff = 0;
        teams[i].points = 0;
    }
}

void addTeam(team *&teams, int &teamCount, int &capacity) {
    if (teamCount >= capacity) {
        capacity *= 2;
        team *newTeams = new team[capacity];
        for (int i = 0; i < teamCount; ++i) {
            newTeams[i] = teams[i];
        }
        delete []teams;
        teams = newTeams;
    }
    std::cout << ">> Enter team name:";
    char buffer[BUFFER];
    std::cin.ignore();
    std::cin.getline(buffer, BUFFER);
    teams[teamCount].name = new char[strLen((buffer)) + 1];
    strCopy(buffer, teams[teamCount].name);
    std::cout << ">> Success: Team \"" << teams[teamCount].name << "\" added!" << std::endl;
    teamCount++;
}

void recordMatchResult(team *&teams, const int &teamCount) {
    if (teamCount < 2) {
        std::cout << ">> Not enough teams!" << std::endl;
        return;
    }
    std::cout << ">> Enter home team:";
    char team1[BUFFER];
    char team2[BUFFER];
    std::cin.ignore();
    std::cin.getline(team1, BUFFER);
    std::cout << ">> Enter away team:";
    std::cin.getline(team2, BUFFER);
    std::cout << ">> Enter home goals:";
    int hG = 0;
    int aG = 0;
    std::cin >> hG;
    std::cout << ">> Enter away goals:";
    std::cin >> aG;
    int indexHome = -1;
    int indexAway = -1;
    for (int i = 0; i < teamCount; ++i) {
        if (strCmp(teams[i].name, team1)) {
            indexHome = i;
        }
        if (strCmp(teams[i].name, team2)) {
            indexAway = i;
        }
    }
    if (indexHome == -1 || indexAway == -1) {
        std::cout << ">> Error: One or both teams not found!" << std::endl;
        return;
    }
    teams[indexHome].goalsFor += hG;
    teams[indexAway].goalsAgainst += hG;
    teams[indexAway].goalsFor += aG;
    teams[indexHome].goalsAgainst += aG;
    teams[indexHome].gamesPlayed++;
    teams[indexAway].gamesPlayed++;
    std::cout << ">> Match recorded!" << std::endl;
    if (hG > aG) {
        teams[indexHome].wins++;
        teams[indexAway].loses++;
        teams[indexHome].points += 3;
        std::cout << ">> " << teams[indexHome].name << " receives 3 points." << std::endl;
        std::cout << ">> " << teams[indexAway].name << " receives 0 points." << std::endl;
    } else if (aG > hG) {
        teams[indexHome].loses++;
        teams[indexAway].wins++;
        teams[indexAway].points += 3;
        std::cout << ">> " << teams[indexHome].name << " receives 0 points." << std::endl;
        std::cout << ">> " << teams[indexAway].name << " receives 3 points." << std::endl;
    } else {
        teams[indexHome].draws++;
        teams[indexAway].draws++;
        teams[indexHome].points++;
        teams[indexAway].points++;
        std::cout << ">> " << teams[indexHome].name << " receives 1 points." << std::endl;
        std::cout << ">> " << teams[indexAway].name << " receives 1 points." << std::endl;
    }
    teams[indexHome].goalDiff = teams[indexHome].goalsFor - teams[indexHome].goalsAgainst;
    teams[indexAway].goalDiff = teams[indexAway].goalsFor - teams[indexAway].goalsAgainst;
}

void viewStandings(team *&teams, const int &teamCount) {
    std::cout << "#  | Team ";
    printNSpaces(18);
    std::cout << "| MP | W | D | L | GF | GA | GD  | Pts" << std::endl;
    std::cout << "------------------------------------------------------------------" << std::endl;
    for (int i = 0; i < teamCount; ++i) {
        int currMaxPoints = teams[i].points;
        for (int j = i + 1; j < teamCount; ++j) {
            if (teams[j].points > currMaxPoints) {
                team tempTeam1 = teams[i];
                teams[i] = teams[j];
                teams[j] = tempTeam1;
                if (teams[j].points == currMaxPoints) {
                    if (teams[j].goalDiff > teams[i].goalDiff) {
                        team tempTeam2 = teams[i];
                        teams[i] = teams[j];
                        teams[j] = tempTeam2;
                    }
                    if (teams[j].goalDiff == teams[i].goalDiff) {
                        if (teams[j].goalsFor > teams[i].goalsFor) {
                            team tempTeam3 = teams[i];
                            teams[i] = teams[j];
                            teams[j] = tempTeam3;
                        }
                    }
                }
            }
        }
        std::cout << i + 1 << ". | " << teams[i].name;
        printNSpaces(21 - strLen(teams[i].name));
        std::cout << "  | " << teams[i].gamesPlayed;printSpaceForSmallNums(teams[i].gamesPlayed);std::cout << " | " << teams[i].wins <<
                " | " <<
                teams[i].draws << " | " << teams[i].loses << " | " << teams[i].goalsFor << "  | " << teams[i].
                goalsAgainst << "  | ";
        printGDSign(teams[i].goalDiff);
        std::cout << teams[i].goalDiff << "  | " << teams[i].points << std::endl;
    }
}

void teamStats(team *&teams, const int &teamsCount) {
    std::cout << ">> Enter team name:";
    char buffer[BUFFER];
    std::cin.ignore();
    std::cin.getline(buffer, BUFFER);
    int index = -1;
    for (int i = 0; i < teamsCount; ++i) {
        if (strCmp(teams[i].name, buffer)) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        std::cout << ">> Team is not existing!" << std::endl;
        return;
    }
    std::cout << std::endl;
    std::cout << "--- Stats for " << teams[index].name << "  ---" << std::endl;
    std::cout << "Matches played: " << teams[index].gamesPlayed << std::endl;
    std::cout << "Wins: " << teams[index].wins << " | Draws: " << teams[index].draws << " | Losses: " << teams[index].
            loses << std::endl;
    std::cout << "Goals: " << teams[index].goalsFor << " : " << teams[index].goalsAgainst << std::endl;
    std::cout << "Points: " << teams[index].points << std::endl;
    std::cout << "Position in league: " << index + 1 << std::endl;
}

void editTeamName(team *&teams, const int &teamsCount) {
    std::cout << ">> Enter current team name: ";
    char buffer[BUFFER];
    std::cin.ignore();
    std::cin.getline(buffer, BUFFER);
    int searchedIndex = -1;
    for (int i = 0; i < teamsCount; ++i) {
        if (strCmp(teams[i].name, buffer)) {
            searchedIndex = i;
            break;
        }
    }
    if (searchedIndex == -1) {
        std::cout << ">> Error: Team \"" << buffer << "\" not found." << std::endl;
        return;
    }
    std::cout << ">> Enter NEW name:";
    char newName[BUFFER];
    std::cin.getline(newName, BUFFER);
    teams[searchedIndex].name = new char[strLen(newName) + 1];
    strCopy(newName, teams[searchedIndex].name);
    std::cout << ">> Success: Team renamed to \"" << teams[searchedIndex].name << "\"." << std::endl;
}

void deleteTeam(team *&teams, int &teamsCount) {
    std::cout << ">> Enter team name: ";
    char buffer[BUFFER];
    std::cin.ignore();
    std::cin.getline(buffer, BUFFER);
    int searchedIndex = -1;
    for (int i = 0; i < teamsCount; ++i) {
        if (strCmp(teams[i].name, buffer)) {
            searchedIndex = i;
            break;
        }
    }
    if (searchedIndex == -1) {
        std::cout << ">> Error: Team \"" << buffer << "\" not found." << std::endl;
        return;
    }
    std::cout << "Are you sure (Y/N): ";
    char sure;
    std::cin >> sure;
    if (sure == 'Y' || sure == 'y') {
        delete[] teams[searchedIndex].name;
        for (int i = searchedIndex; i < teamsCount - 1; ++i) {
            teams[i] = teams[i + 1];
        }
        teams[teamsCount - 1].name = nullptr;
        teamsCount--;
    } else {
        std::cout << ">> Canceled!" << std::endl;
        return;
    }
    std::cout << ">> Team \"" << buffer << "\" deleted." << std::endl;
}


void exit(team *&teams, const int &teamsCount, const int &capacity) {
    std::ofstream out = createFile();
    if (!out.is_open()) {
        std::cout << ">> Error saving to file!" << std::endl;
        return;
    }
    out << teamsCount << " " << capacity << std::endl;
    for (int i = 0; i < teamsCount; ++i) {
        out << teams[i].name << '|' << teams[i].gamesPlayed << " " << teams[i].wins << " " << teams[i].draws << " " <<
                teams[i].loses << " " << teams[i].goalsFor << " " << teams[i].goalsAgainst << " " << teams[i].goalDiff
                << " " << teams[i].points << std::endl;
    }
    out.close();
    std::cout << ">> Data saved to \"" << FILE_NAME << "\"" << std::endl;
    std::cout << ">> Goodbye!" << std::endl;
}

void mainLoop() {
    int teamCount = 0;
    int capacity = 1;
    team *teams = new team[capacity];
    setStatsNull(teams, teamCount);
    readFile(teams, teamCount, capacity);
    int menuOption;
    do {
        printMenu();
        std::cin >> menuOption;
        switch (menuOption) {
            case 1: addTeam(teams, teamCount, capacity);
                break;
            case 2: recordMatchResult(teams, teamCount);
                break;
            case 3: viewStandings(teams, teamCount);
                break;
            case 4: teamStats(teams, teamCount);
                break;
            case 5: editTeamName(teams, teamCount);
                break;
            case 6: deleteTeam(teams, teamCount);
                break;
            case 7: exit(teams, teamCount, capacity);
                break;
            default: std::cout << ">> Invalid Option!" << std::endl;
                break;
        }
    } while (menuOption != 7);
    freeTeamsMemory(teams, teamCount);
}
