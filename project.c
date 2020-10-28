//	Name: Andrew Garcia
//  Group: 
//	Section:	Lab 504/Lecture 004
//	Problem:	Project
//  Date:	4/8/2020

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


struct player{
	
	char fname[100];
	int balance,winLoss;
	
};

//declare global variable player
struct player players[10];

// save content of file
void save_file(){
	FILE *fpr; 
	int i;
	fpr = fopen("players.txt","w");
	
	if (fpr == NULL){
		printf("File does not open");
		return NULL;
		}
	
	for(i = 0;players[i].fname[0] != '\0';i++){
		                        
		fprintf(fpr, "%s\t%d\t%d\n",players[i].fname,players[i].balance,players[i].winLoss);
	}
	fclose(fpr);
	
	
}

void load_file(){
	
	FILE *fpr;
	
	fpr = fopen("players.txt","r");
	
	if (fpr == NULL){
		printf("File does not open");
		return NULL;
		}
	for( int i = 0;!feof(fpr);i++){
		
		fscanf(fpr, "%s\t%d\t%d",players[i].fname,&players[i].balance,&players[i].winLoss);
		}
	fclose(fpr);
	
}

void topUp_bal(){
	
	char first_name[100];
	int addBal,i;
	int found = 0;
	printf("Please enter your name:");
	scanf("%s",first_name);
	printf("Enter the amount you want added to your balance: ");
	scanf("%d",&addBal);
	
	for( i = 0;players[i].fname[0] != '\0';i++){
		
		if (strcmp(players[i].fname,first_name) == 0){
			
			players[i].balance += addBal ;
			found = 1;
			}
	}
	if (found != 1){
		printf("\nPlayer is not registered.\n");
		//strcpy(players[i].fname,first_name);
		//players[i].balance = addBal;
		//players[i].winLoss = 0;
		}

}

void playgame(){
	
	//declare variables
	char tfname[100],pa[10];
	int i,dice1,dice2,sumdice,pointval;
	
	//ask user for name
	printf("Please enter your name:\n");
	scanf("%s",tfname);
	for (i = 0;players[i].fname[0] != '\0';i++){
		
		// check for names to match to playgame with correct player
		if (strcmp(players[i].fname,tfname) == 0){
			break;
			}
		}
	// continue until sentinel
	while (1){
		pointval = 0;
		getchar();
		while (1){
			printf("Hit enter to roll dice\n");
			getchar();
			
			// Initialized random number generator
			srand((unsigned) time(NULL));
			
			dice1= rand() % 6+1;
			dice2= rand() % 6+1;
			sumdice= dice1+dice2;
			
			printf("The values of the dices are %d and %d whose sum is %d and point value is %d\n",dice1,dice2,sumdice,pointval);
			
			//player wins on roll
			if(((sumdice == 7 || sumdice == 11 )&& pointval == 0)|| sumdice == pointval){
				players[i].balance += 10;
				players[i].winLoss += 10;
					
				printf("You win the game. Your current balance is %d\n",players[i].balance);
				break;
			}
			
			// player rolls a loss
			if(((sumdice == 2 || sumdice == 3 || sumdice == 12)&& pointval == 0) || ( sumdice== 7 && pointval != 0)){
				players[i].balance --;
				players[i].winLoss --;
				printf("You lost. Your current balance is %d\n",players[i].balance);
				break;
			}
			
			if(sumdice == 4 || sumdice == 5 || sumdice == 6 || sumdice == 8 || sumdice ==9 || sumdice == 10){
				pointval = sumdice;
				continue;
				
				
			}
			
		
		}
		printf("Do you want to play again hit yes\\no:");
		scanf("%s",pa);
			
		//turn input into lowercase
		for(int i = 0; pa[i];i++){
			pa[i] = tolower(pa[i]);
		}
		// check for play game again
		if(strcmp(pa,"yes") == 0){
			continue;
		}
		else break;

	}
	
	
	
	
}

void player_bal(){
	
	int pArr[10];
	int maxI;
	printf("The top players are:\n");
	//fill pArr w 0
	for(int i=0;i < 10;i++){
		pArr[i] = 0;
		}
		
	for(int j = 0; j< 5;j++){
		//reset
		maxI = -1;
		for(int i = 0;i< 10;i++){
				
			if(maxI == -1){
				if(pArr[i]== 0){
					maxI = i;
				}
				continue;
			}	
			if(players[i].balance >players[maxI].balance){
				if (pArr[i] == 0){
					maxI=i;
				}
				
			}
			
		}
		printf("%d:%s\t%d\n",j+1,players[maxI].fname,players[maxI].balance);
		pArr[maxI] = 1;
	
	}
	
}

void top_winners(){
	
	int playerArr[10];
	int maxgain;
	
	printf("the top players by gain are:\n");
	for(int i=0;i<10;i++){
		playerArr[i] = 0;
	}
	
	for(int j = 0; j < 5; j++){
		maxgain = -100;
		
		for(int i = 0; i < 10;i++){
			if(maxgain == -100){
				if(playerArr[i]== 0){
					maxgain = i;
				}
				continue;
			}	
			if(players[i].winLoss >players[maxgain].winLoss){
				if (playerArr[i] == 0){
					maxgain = i;
				}
				
			}
			
		}
		printf("%d:%s\t%d\n",j+1,players[maxgain].fname,players[maxgain].winLoss);
		playerArr[maxgain] = 1;
			
		
	}
	
	
	
	
}

int main(){

	int menu_num;
	load_file();

	do{
		printf("0) top up your balance\n1) play game\n2) top 5 players by balance\n3) top 5 winners by what they have won\n4) exit the game\nEnter number corresponding to menu: ");
		scanf("%d", &menu_num);
		switch(menu_num){
		
			case 0: topUp_bal();
					save_file();
				break;
			case 1: playgame();
					save_file();
				break;
			case 2: player_bal();
				break;
			case 3: top_winners();
				break;
			case 4:
				break;
				}
		}while(menu_num != 4);
	
	
		
	
	return 0;
	
}
