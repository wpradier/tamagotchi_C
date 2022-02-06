#include "tamagotchi.h"

void printActionsSave();
void printActionsGame();
void clean_stdin(void);

void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}

void printActionsSave(){
  printf("1 : \tNouvelle partie\n");
  printf("2 : \tContinuer la partie\n");
  printf("3 : \tChanger de partie\n");
}

void printActionsGame(){
  printf("1 : \tModifier le nom\n");
  printf("2 : \tAfficher le pourcentage de vie\n");
  printf("3 : \tAfficher le pourcentage de faim\n");
  printf("4 : \tAfficher le pourcentage de santé\n");
  printf("5 : \tAfficher le pourcentage d'hygiène\n");
  printf("7 : \tAfficher le pourcentage d'ennuie\n");
  printf("8 : \tNourrir\n");
  printf("9 : \tSoigner\n");
  printf("10 : \tLaver\n");
  printf("11 : \tJouer\n");
  printf("12 : \tBoutique\n");
  printf("13 : \tQuitter le jeu\n");
}

void game_consol(){
  printActionsSave();

  printf("\n________________________________________\n\n");
  // a mettre dans une condition si une partie est lancé
  printActionsGame();

  //remplace fflush(stind);
  clean_stdin();

  char tamagotchi_name[100];
  printf("Choisissez le nom de votre tamagotchi : ");
  fgets(tamagotchi_name, 255, stdin);

  if (tamagotchi_name[strlen(tamagotchi_name) - 1] == '\n')
    tamagotchi_name[strlen(tamagotchi_name) - 1] = '\0';

  fputs(tamagotchi_name, stdout);
}
