#include "tamagotchi.h"

void printActionsSave();
void printActionsGame();
void clean_stdin(void);
void actionsGame();

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
  printf("3 : \tChanger de partie\n\n");
}

void printActionsGame(){
  printf("1 : \tAfficher le pourcentage de vie\n");
  printf("2 : \tAfficher le pourcentage de faim\n");
  printf("3 : \tAfficher le pourcentage de santé\n");
  printf("4 : \tAfficher le pourcentage d'hygiène\n");
  printf("5 : \tAfficher le pourcentage d'ennuie\n");
  printf("6 : \tNourrir\n");
  printf("7 : \tSoigner\n");
  printf("8 : \tLaver\n");
  printf("9 : \tJouer\n");
  printf("10 : \tTravailler\n");
  printf("11 : \tBoutique\n");
  printf("12 : \tQuitter le jeu\n");
}

void actionsGame(){
  int   option;

  do{
    printActionsGame();

    printf("Choisissez une option : ");
    scanf("%d", &option);
  }while(option < 1 || option > 12);

  switch (option){
    case 9:
      printf("Le jeu est en cours de développement, revener plus tard\n");
      break;
    default:
      break;
  }
}

void    game_consol(s_parameters *parameters){
  int   option;
  char  tamagotchi_name[100];

  do{
    printActionsSave();

    printf("Choisissez une option : ");
    scanf("%d", &option);
    //fgets(option, 255, stdin);
  }while(option < 1 || option > 3);

  switch (option) {
    case 1:
      //remplace fflush(stind);
      clean_stdin();

      printf("Choisissez le nom de votre tamagotchi : ");
      fgets(tamagotchi_name, 255, stdin);

      if (tamagotchi_name[strlen(tamagotchi_name) - 1] == '\n')
        tamagotchi_name[strlen(tamagotchi_name) - 1] = '\0';

      parameters->tamagotchi->name = tamagotchi_name;

      printf("\n");
      actionsGame();
      break;
    case 2:
      actionsGame();
      break;
    default:
      actionsGame();
      break;
  }
  //fputs(tamagotchi_name, stdout);
}
