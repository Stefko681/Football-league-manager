//
// Created by stefko on 2/8/26.
//

#ifndef FOOTBALL_LEAGUE_MANAGER_TEAMS_H
#define FOOTBALL_LEAGUE_MANAGER_TEAMS_H

struct team {
    char *name;
    int gamesPlayed;
    int wins;
    int draws;
    int loses;
    int goalsFor;
    int goalsAgainst;
    int goalDiff;
    int points;
};

int strLen(const char *str);

char *strCopy(const char *sor, char *dest);

bool strCmp(const char *str1, const char *str2);

void printNSpaces(int n);

std::ofstream createFile();

void readFile(team *&teams, int &teamsCount, int &capacity);

void freeTeamsMemory(team *&teams, const int &teamsCount);

void printMenu();

void setStatsNull(team *&teams, const int &teamCount);

int readInt();

void addTeam(team *&teams, int &teamCount, int &capacity);

void recordMatchResult(team *&teams, const int &teamCount);

void viewStandings(team *&teams, const int &teamCount);

void teamStats(team *&teams, const int &teamsCount);

void editTeamName(team *&teams, const int &teamsCount);

void deleteTeam(team *&teams, int &teamsCount);

void saveAndExit(team *&teams, const int &teamsCount, const int &capacity);

void mainLoop();
#endif //FOOTBALL_LEAGUE_MANAGER_TEAMS_H
