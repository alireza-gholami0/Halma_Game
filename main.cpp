#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h> 
#include <ctime>
	int Size=16;
	int state[20][20]={0};
	char title[30];
	int Player_Num=2;
	char First_Color[10]="green";
	char Second_Color[10]="blue";
	int leave_camp_value=40;
	int turn=1; 
	int count=0 , sum=0; //shomareshgar tedad harkat
	int Beads_order[10]={1,2,3,4,3};
	char User[50];
	char User1[50];
	char UserP1[50];
	char UserP2[50]="PC";
void menu1();
int menu2();
int menu3();
// nahve chinesh mohre ha ra moshakhas mikonad		
int maxElement(int array[]){
	int max=0,j;
	for(j=0;array[j]!=0;j++){
		if(array[j]>max) max=array[j];
	}
	return max;
}
// ba tavajoh be Size va Beads_order jadval bazi ra meghdar midahad
void stateValue(){
	int max=0,i,j,k;
	max=maxElement(Beads_order);
	k=max;
	for(i=0,j=0;j<max;j++){
		state[i][j]=1;
	}
	for(i=1;i<max;i++,k--){
		for(j=0;j<k;j++){
			state[i][j]=1;
		}
	}
	k=Size-(max+1);
	for(i=Size-1,j=Size-1;j>k;j--){
		state[i][j]=2;
	}
	for(i=Size-2;i>Size-(max+1);i--,k++){
		for(j=Size-1;j>k;j--){
			state[i][j]=2;
		}
	}
}
// file setting.txt ra mikhanad
void scanSetting(){
		int i , j;
	FILE *inputfile ;
	inputfile=fopen("setting.txt","rt");
	fscanf(inputfile,"%s",title);
	while(!feof(inputfile)){
		if(strstr(title,"Size")){
			fscanf(inputfile,"%s",title);
			fscanf(inputfile,"%d",&Size);	
		}
		else if(strstr(title,"First_Color")){
			fscanf(inputfile,"%s",title);
			fscanf(inputfile,"%s",First_Color);
		}
		else if(strstr(title,"Second_Color")){
			fscanf(inputfile,"%s",title);
			fscanf(inputfile,"%s",Second_Color);
		}
		else if(strstr(title,"leave_camp_value")){
			fscanf(inputfile,"%s",title);
			fscanf(inputfile,"%d",&leave_camp_value);
		}
		else if(strstr(title,"Beads_order")){
			for(i=0;i<10;i++)
			Beads_order[i]=0;
			fscanf(inputfile,"%s",title);
			for(i=0;;i++){
				fscanf(inputfile,"%d",&Beads_order[i]);
				if(Beads_order[i]>9) break;
			}
		}
		else if(strstr(title,"Player_Num")){
			fscanf(inputfile,"%s",title);
			fscanf(inputfile,"%d",&Player_Num);
		}
		fscanf(inputfile,"%s",title);
	}
	fclose(inputfile);
	stateValue();
}	
void setTextColor(int textColor, int backColor = 0) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	int colorAttribute = backColor << 4 | textColor;
	SetConsoleTextAttribute(consoleHandle, colorAttribute);
}
// safhe bazi ra print mikonad
void printBorder(int state2[][20]){
	int row , column;
	int x=1 , y=1 ; // shomaresh gar radif v ston
	for( row=0 ; row<(Size*2)-1 ; row++){
		for( column=0 ; column<(Size*2)-1 ; column++){
				if(row%2==1){
					printf("-");
				}else if(column%2==1){
						printf("|");
				}else{
					if(state[row/2][column/2]==1){
						if(strcmp(First_Color,"green")==0){
							if(state2[row/2][column/2]==1) setTextColor(10,9);
							else setTextColor(10);
						}
						else{
							if(state2[row/2][column/2]==1) setTextColor(9,10);
							else setTextColor(9);
						}
						printf("O");
					}else if(state[row/2][column/2]==2){
						if(strcmp(Second_Color,"green")==0){
							if(state2[row/2][column/2]==2) setTextColor(10,9);
							else setTextColor(10);
						}
						else{
							if(state2[row/2][column/2]==2) setTextColor(9,10);
							else setTextColor(9);
						}
						printf("X");
					}else if(state[row/2][column/2]==0){
						if(state2[row/2][column/2]==1){
							if(strcmp(First_Color,"green")==0){
								if(state2[row/2][column/2]==1) setTextColor(10,9);
								else setTextColor(10);
							}
							else{
								if(state2[row/2][column/2]==1) setTextColor(9,10);
								else setTextColor(9);
							}
						}
						else if(state2[row/2][column/2]==2){
							if(strcmp(Second_Color,"green")==0){
								if(state2[row/2][column/2]==2) setTextColor(10,9);
								else setTextColor(10);
							}
							else{
								if(state2[row/2][column/2]==2) setTextColor(9,10);
								else setTextColor(9);
							}
						}
						printf(" ");
					}
					setTextColor(15);
				}
		//	}
		}
		printf("\n"); 
	}
}
// nobat player ha ra ava mikonad
void changeTurn(int &turn){
	if(turn==1) turn=2;
	else turn=1;
}
// moshakhas mikonad aya harkat Jump sade hast
int jump(int x1 , int y1 , int x2 , int y2){
	if(x1-2==x2 && y1-2==y2 && state[x1-2][y1-2]!=0) return 0;
	else if(x1-2==x2 && y1==y2 && state[x1-2][y1-1]!=0) return 0;
	else if(x1-2==x2 && y1+2==y2 && state[x1-2][y1]!=0) return 0;
	else if(x1==x2 && y1-2==y2 && state[x1-1][y1-2]!=0) return 0;
	else if(x1==x2 && y1+2==y2 && state[x1-1][y1]!=0) return 0;
	else if(x1+2==x2 && y1-2==y2 && state[x1][y1-2]!=0) return 0;
	else if(x1+2==x2 && y1==y2 && state[x1][y1-1]!=0) return 0;
	else if(x1+2==x2 && y1+2==y2 && state[x1][y1]!=0) return 0;
	return 1;
}
// moshakhas mikonad aya harkat SuperJump hast
int SuperJump(int x1 , int y1 , int x2 , int y2){
	if(x1-4==x2 && y1-4==y2 && state[x1-2][y1-2]!=0 && state[x1-1][y1-1]==0 && state[x1-3][y1-3]==0) return 0;
	else if(x1-4==x2 && y1==y2 && state[x1-2][y1]!=0 && state[x1-1][y1]==0 && state[x1-3][y1]==0) return 0;
	else if(x1-4==x2 && y1+4==y2 && state[x1-2][y1+2]!=0 && state[x1-1][y1+1]==0 && state[x1-3][y1+3]==0) return 0;
	else if(x1==x2 && y1-4==y2 && state[x1][y1-2]!=0 && state[x1][y1-1]==0 && state[x1][y1-3]==0) return 0;
	else if(x1==x2 && y1+4==y2 && state[x1][y1+2]!=0 && state[x1][y1+1]==0 && state[x1][y1+3]==0) return 0;
	else if(x1+4==x2 && y1-4==y2 && state[x1+2][y1-2]!=0 && state[x1+1][y1-1]==0 && state[x1+3][y1-3]==0) return 0;
	else if(x1+4==x2 && y1==y2 && state[x1+2][y1]!=0 && state[x1+1][y1]==0 && state[x1+3][y1]==0) return 0;
	else if(x1+4==x2 && y1+4==y2 && state[x1+2][y1+2]!=0 && state[x1+1][y1+1]==0 && state[x1+3][y1+3]==0) return 0;
	return 1;
}
// moshakhas mikonad aya harkat normal hast
int normal(int x1 , int y1 , int x2 , int y2){
		 if(x1-1==x2 && y1-1==y2) return 0;
	else if(x1-1==x2 && y1==y2) return 0;
	else if(x1-1==x2 && y1+1==y2) return 0;
	else if(x1==x2 && y1-1==y2) return 0;
	else if(x1==x2 && y1+1==y2) return 0;
	else if(x1+1==x2 && y1-1==y2) return 0;
	else if(x1+1==x2 && y1==y2) return 0;
	else if(x1+1==x2 && y1+1==y2) return 0;
	return 1;
}
// check mikonad aya in mohre mitavand harkat konand
int check(int posx , int posy){ 
 	int i,j,x,y,sw,sw2;
 	i=posx-1;
 	j=posy-1;
 				sw=1;
        			for(x=i-1 ; x<=i+1 && sw==1 ; x++){ 
        				sw2=1;
		        	 	for(y=j-1 ; y<=j+1 && sw2==1 ; y++){
		        	 		if(x>=0 && x<Size && y>=0 && y<Size){
		            	 		if( state[x][y]==2 || state[x][y]==1);
				            	else{
								
									sw2=0;        
					            }	
					        }
				        }
				     if(sw2==0) sw=0;
			        }
 				    if (sw==1){ 
 			        	sw=1;
		                	for(x=i-2 ; x<=i+2 && sw==1 ; x+=2){
		                		sw2=1;
		                	 	for(y=j-2 ; y<=j+2 && sw2==1 ; y+=2){
		                	 		if(x>=0 && x<Size && y>=0 && y<Size ){
			                     		if(state[x][y]==2 || state[x][y]==1);	
				                    	else{
				            	 	        sw2=0;
					                    }	
					                }
				                }
			            	 if(sw2==0) sw=0;
			                }							
				    }
			if (sw==0) return 0;
			else if(sw==1) return 1;	 			
			}
// mokhtasate mohre va mokhtasat maghsad ra migirad va mohre ra ja be ja mikonad
void move(int state[][20], int Size , int &turn , int state2[][20]){
    int pos_x1 , pos_y1 , pos_x2 , pos_y2; //x va y radif va sotoon hastand
    
       do{ //check mikonad mokhtasat mohre dorost ast ya na
          printf("player%d please select your piece:\n",turn);
          scanf("%d %d",&pos_x1 ,&pos_y1);
        }while(pos_x1<1 || pos_x1>Size || pos_y1<1 || pos_y1>Size || state[pos_x1 -1][pos_y1 -1]!=turn || check(pos_x1,pos_y1)!=0);
        
       do{ //check mikonad mokhtasat maghsad dorost ast ya na
          printf("player%d please select available position:\n",turn);
          scanf("%d %d",&pos_x2,&pos_y2);
        }while(pos_x2<1 || pos_x2>Size || pos_y2<1 || pos_y2>Size || state[pos_x2 -1][pos_y2 -1]!=0 || normal(pos_x1,pos_y1,pos_x2,pos_y2)+SuperJump(pos_x1-1,pos_y1-1,pos_x2-1,pos_y2-1)+jump(pos_x1,pos_y1,pos_x2,pos_y2)==3 );
       if(normal(pos_x1,pos_y1,pos_x2,pos_y2)==0 || SuperJump(pos_x1-1,pos_y1-1,pos_x2-1,pos_y2-1)==0){
            state[pos_x2 -1][pos_y2 -1]=turn;
            state[pos_x1 -1][pos_y1 -1]=0;       	
	   }
	   else if(jump(pos_x1,pos_y1,pos_x2,pos_y2)==0){
	   	char reply[4]="YES";
	   	do{
	   		state[pos_x2 -1][pos_y2 -1]=turn;
        	state[pos_x1 -1][pos_y1 -1]=0;
        	system("cls");
	   		printBorder(state2);
	   		if(jump(pos_x1,pos_y1,pos_x2,pos_y2)==0){
	   			printf("You want to continue(YES/NO)?");
	   			scanf("%s",reply);
	   		}
	   		pos_x1=pos_x2;
	   		pos_y1=pos_y2;
	   		if(strcmp(reply,"YES")==0){
	   		//	system("cls");
	   		//	printBorder(state);
 				do{
          			printf("player%d please select available position:\n",turn);
        		  scanf("%d %d",&pos_x2,&pos_y2);
        		}while(pos_x2<1 || pos_x2>Size || pos_y2<1 || pos_y2>Size || state[pos_x2 -1][pos_y2 -1]!=0 || SuperJump(pos_x1,pos_y1,pos_x2,pos_y2)+jump(pos_x1,pos_y1,pos_x2,pos_y2)==2 || normal(pos_x1,pos_y1,pos_x2,pos_y2)==0);
				state[pos_x2 -1][pos_y2 -1]=turn;
        		state[pos_x1 -1][pos_y1 -1]=0;	
			   }
		   }while(strcmp(reply,"YES")==0 && jump(pos_x1,pos_y1,pos_x2,pos_y2)==0);
	    }
}  
// check mikonad aya playeri ordoogahe harif ra taskhir karde va barande shode ya na
int CheckWinner(){
	int max=0,i,j,k;
	int sw1=1;
	max=maxElement(Beads_order);
	k=max;
	for(i=0,j=0;j<max;j++){
		if(state[i][j]!=2){
			sw1=0;
			break;
		}
	}
	for(i=1;i<max;i++,k--){
		for(j=0;j<k;j++){
			if(state[i][j]!=2){
			sw1=0;
			break;
			}
		}
	}
	if(sw1==1) return 2;
	int sw2=1;
	k=Size-(max+1);
	for(i=Size-1,j=Size-1;j>k;j--){
		if(state[i][j]!=1){
			sw2=0;
			break;
			}
	}
	for(i=Size-2;i>Size-(max+1);i--,k++){
		for(j=Size-1;j>k;j--){
			if(state[i][j]!=1){
			sw2=0;
			break;
			}
		}
	}
	if(sw2==1) return 1;
	return 0;
}
// check mikonad yek mohre mohasere shode va bazi ra bakhte ya na
 int CheckMohasere(){ 
 	int i,j,x,y,sw,sw2;
 	for(i=0 ; i<Size ; i++){
 		for(j=0 ; j<Size ; j++){ 
 			if(state[i][j]==1){
 				sw=1;
        			for(x=i-1 ; x<=i+1 && sw==1 ; x++){ 
        				sw2=1;
		        	 	for(y=j-1 ; y<=j+1 && sw2==1 ; y++){
		        	 		if(x>=0 && x<Size && y>=0 && y<Size){
		            	 		if( state[x][y]==2);
		            	 		else if(state[x][y]==1 && x==i && y==j);
				            	else{
					                sw2=0;           
					            }	
					        }
				        }
				     if(sw2==0) sw=0;
			        }
 				    if (sw==1){ 
 			        	sw=1;
		                	for(x=i-2 ; x<=i+2 && sw==1 ; x+=2){
		                		sw2=1;
		                	 	for(y=j-2 ; y<=j+2 && sw2==1 ; y+=2){
		                	 		if(x>=0 && x<Size && y>=0 && y<Size ){
			                     		if(state[x][y]==2);
			                     		else if(state[x][y]==1 && x==i && y==j);	
				                    	else{
				            	 	        sw2=0;
					                    }	
					                }
				                }
			            	 if(sw2==0) sw=0;
			                }							
				    }
			 if(sw==1) return 2;
			}
		else if(state[i][j]==2){
 				sw=1;
		        	for(x=i-1 ; x<=i+1 && sw==1 ; x++){
		        		sw2=1;
		        	 	for(y=j-1 ; y<=j+1 && sw2==1; y++){
			        		if(x>=0 && x<Size && y>=0 && y<Size){
			            		if( state[x][y]==1);
			            		else if(state[x][y]==2 && x==i && y==j);	
			            		else{
					        	    sw2=0;
					            }	
					        }
				        }
				     if(sw2==0) sw=0;
			        }
 			    	if (sw==1){
 		        		sw=1;
		                	for(x=i-2 ; x<=i+2 && sw==1 ; x+=2){
		                		sw2=1;
		                	 	for(y=j-2 ; y<=j+2 && sw2==1 ; y+=2){
		                	 		if(x>=0 && x<Size && y>=0 && y<Size ){
		                    	 		if(state[x][y]==1);
		                    	 		else if(state[x][y]==2 && x==i && y==j);	
			                    		else{
				                    	 	sw2=0;
					                    }	
					                } 
				                }
				             if(sw2==0) sw=0;
			                }						
				    }
			 if(sw==1) return 1;				
			}
		}
	}
	return 0;
 }
// check mikonad bad az leave camp value dar ordoogahi mohre nabashad
int LeaveCamp(){
	int max=0,i,j,k;
	int player1=1 , player2=1;
	int sw1=1;
	max=maxElement(Beads_order);
	k=max;
	for(i=0,j=0;j<max;j++){
		if(state[i][j]==1){
			sw1=0;
			break;
		}
	}
	for(i=1;i<max;i++,k--){
		for(j=0;j<k;j++){
			if(state[i][j]==1){
			sw1=0;
			break;
			}
		}
	}
	if(sw1==1) player1=0;
	int sw2=1;
	k=Size-(max+1);
	for(i=Size-1,j=Size-1;j>k;j--){
		if(state[i][j]==2){
			sw2=0;
			break;
			}
	}
	for(i=Size-2;i>Size-(max+1);i--,k++){
		for(j=Size-1;j>k;j--){
			if(state[i][j]==2){
			sw2=0;
			break;
			}
		}
	}
	if(sw2==1) player2=0;
    	if (player1==0 && player2==1) return 1;
    	else if (player1==1 && player2==0) return 2;
      	else if (player1==1 && player2==1) return 3;
       	else return 0;
}
// password vard shode ra check mikonad
int passCheck(char  pass[] , char user[]){
	FILE *account;
	account = fopen("accounts.bin","rb");
	char Use[50];
	char pas[50];
	while(!feof(account)){
		fread(Use,sizeof(char),50,account);
		fread(pas,sizeof(char),50,account);
		if(strcmp(Use,user)==0){
			if(strcmp(pas,pass)==0){
				return 1;
			}
			else 0;
		}
	}
	return 0;
}
// username vard shode ra check mikonad
int userCheck(char user[]){
	FILE *account;
	account = fopen("accounts.bin","rb");
	char Use[50];
	char pas[50];
	while(!feof(account)){
		fread(Use,sizeof(char),50,account);
		fread(pas,sizeof(char),50,account);
		if(strcmp(Use,user)==0){
			fclose(account);
			return 1;
		}
	}
	return 0;
}
// password ra ramzgozari mikonad
void Passcoding(char Pass[]){
	int i;
	for(i=0;Pass[i]!=NULL;i++){
		if(Pass[i]=='1') Pass[i]='9';
		else if(Pass[i]=='5') Pass[i]='6';
		else if(Pass[i]=='8') Pass[i]='4';
		else if(Pass[i]=='3') Pass[i]='2';
		else if(Pass[i]=='a') Pass[i]='*';
		else if(Pass[i]=='d') Pass[i]='\\';
		else if(Pass[i]=='k') Pass[i]='Y';
		else if(Pass[i]=='m') Pass[i]='@';
		else if(Pass[i]=='c') Pass[i]='e';
		else if(Pass[i]=='b') Pass[i]='B';
		else if(Pass[i]=='e') Pass[i]='T';
		else if(Pass[i]=='z') Pass[i]=')';
		else if(Pass[i]=='w') Pass[i]='(';
		else if(Pass[i]=='l') Pass[i]='=';
		else if(Pass[i]=='r') Pass[i]='7';
		else if(Pass[i]=='x') Pass[i]='^';
		else if(Pass[i]=='h') Pass[i]='G';
		else if(Pass[i]=='A') Pass[i]='r';
		else if(Pass[i]=='D') Pass[i]='+';
		else if(Pass[i]=='R') Pass[i]='O';
		else if(Pass[i]=='P') Pass[i]='Q';
		else if(Pass[i]=='V') Pass[i]='-';
		else if(Pass[i]=='S') Pass[i]='_';
	}
}
// tedad harkat bala va paein ra baray menu mifrstad
int Up_Down(int num){
	int get;
	int i=0;
	get=getch();
	if(get==224){
		do{
			get=getch();
			if(get==80){
				i++;
			}
			if(get==72){
				i--;
			}
			if(i<0) i=1;
			else if(i>num) i=num;
		}while(get!=13);
	}
	else return 0;
	return i;
}
int signIn(){
	char Pass[50];
	int i=0;
	printf("  <<SignIn>>\n");
	printf("Username:\n");
	scanf("%s",User);
	printf("Password:\n");
	scanf("%s",Pass);

	Passcoding(Pass);
	printf("1-> Submit\n");
	printf("2-> Back\n");
	i=Up_Down(2);
	if(i==1){
		if(passCheck(Pass,User)==1&&userCheck(User)==1){
			system("cls");
			return 1;
		}else if(userCheck(User)==0){
			system("cls");
			printf("Wrong Username!\a\n");
			signIn();
			return 0;
		}else if(passCheck(Pass,User)==0&&userCheck(User)==1){
			system("cls");
			printf("Wrong password!\a\n");
			signIn();
			return 0;
		}
	}
	else if(i==2){
		system("cls");
		menu1();
		return 0;
	}
	return 1;
}
int signUp(){
	char Pass[50];
	printf("  <<SignUp>>\n");
	printf("Username:\n");
	scanf("%s",User);
	printf("Password:\n");
	scanf("%s",Pass);
	Passcoding(Pass);
	printf("1-> Submit\n");
	printf("2-> Back\n");
	int i=0;
	i=Up_Down(2);
	if(i==1){
		if(userCheck(User)==0){
			FILE *account;
			account = fopen("accounts.bin","r+b");
			fseek(account,0,2);
			fwrite(User,sizeof(char),50,account);
			fwrite(Pass,sizeof(char),50,account);
			fclose(account);
			int num=0;
			FILE *statistics;
			statistics = fopen("statistics.bin","r+b");
			fseek(statistics,0,2);
			fwrite(User,sizeof(char),50,statistics);
			fwrite(&num,sizeof(int),1,statistics);
			fwrite(&num,sizeof(int),1,statistics);
			fwrite(&num,sizeof(int),1,statistics);
			fwrite(&num,sizeof(int),1,statistics);
			fclose(statistics);
			system("cls");
			return 1;
		}else if(userCheck(User)==1){
			system("cls");
			printf("Choose another Username!\a\n");
			signUp();
			return 0;
		}
	}
	else if(i==2){
		system("cls");
		menu1();
		return 0;
	}
	return 1;
}
// menu avalie baray vard shodan
void menu1(){
	int number;
	printf("1-> Sign-In\n");
	printf("2-> Sign-Up");
	number=Up_Down(2);
	if(number==1){
		system("cls");
		signIn();
	}
	else if(number==2){
		system("cls");
		signUp();
	}
}
// chap amalkard player
void PlayerStatistics(){
	FILE *player;
	player = fopen("statistics.bin","rb");
	char a[50];
	int num;
	int win;
	int draw;
	int lost;
	while(!feof(player)){
		fread(a,sizeof(char),50,player);
		fread(&num,sizeof(int),1,player);
		fread(&win,sizeof(int),1,player);
		fread(&draw,sizeof(int),1,player);
		fread(&lost,sizeof(int),1,player);
		if(strcmp(a,User1)==0){
			printf("Id:\t%s\n",a);
			printf("Match Played:\t%d\n",num);
			printf("Win:\t%d\n",win);
			printf("Draw:\t%d\n",draw);
			printf("Lost:\t%d\n",lost);
			break;
		}
	}
	getch();
	fclose(player);
	system("cls");
	menu2();
}
// chap username behtarin tarin player
void MostPlayer(){
	int a;
	char idmost[50];
	int winmost;
	int drawmost;
	int lostmost;
	char id[50];
	int win;
	int draw;
	int lost;
	FILE *mp;
	mp = fopen("statistics.bin","rb");
	fread(idmost,sizeof(char),50,mp);
	fread(&a,sizeof(int),1,mp);
	fread(&winmost,sizeof(int),1,mp);
	fread(&drawmost,sizeof(int),1,mp);
	fread(&lostmost,sizeof(int),1,mp);
	while(!feof(mp)){
		fread(id,sizeof(char),50,mp);
		if(!feof(mp)){
		fread(&a,sizeof(int),1,mp);
		fread(&win,sizeof(int),1,mp);
		fread(&draw,sizeof(int),1,mp);
		fread(&lost,sizeof(int),1,mp);
		if(win>winmost){
			strcpy(idmost,id);
			winmost=win;
			drawmost=draw;
			lostmost=lost;
		}
		else if(win==winmost && draw>drawmost){
			strcpy(idmost,id);
			winmost=win;
			drawmost=draw;
			lostmost=lost;
		}
		else if(win==winmost && draw==drawmost && lost<lostmost){
			strcpy(idmost,id);
			winmost=win;
			drawmost=draw;
			lostmost=lost;
		}
		}
	}
	printf("Most Player:\t%s\n",idmost);
	fclose(mp);
}
// chap username bad tarin player
void WorstPlayer(){
	int a;
	char idworst[50];
	int winworst;
	int drawworst;
	int lostworst;
	char id[50];
	int win;
	int draw;
	int lost;
	FILE *wp;
	wp = fopen("statistics.bin","rb");
	fread(idworst,sizeof(char),50,wp);
	fread(&a,sizeof(int),1,wp);
	fread(&winworst,sizeof(int),1,wp);
	fread(&drawworst,sizeof(int),1,wp);
	fread(&lostworst,sizeof(int),1,wp);
	while(!feof(wp)){
		fread(id,sizeof(char),50,wp);
		if(!feof(wp)){
		fread(&a,sizeof(int),1,wp);
		fread(&win,sizeof(int),1,wp);
		fread(&draw,sizeof(int),1,wp);
		fread(&lost,sizeof(int),1,wp);
		if(lost>lostworst){
			strcpy(idworst,id);
			winworst=win;
			drawworst=draw;
			lostworst=lost;
		}
		else if(lost==lostworst && draw<drawworst){
			strcpy(idworst,id);
			winworst=win;
			drawworst=draw;
			lostworst=lost;
		}
		else if(lost==lostworst && draw==drawworst && win<winworst){
			strcpy(idworst,id);
			winworst=win;
			drawworst=draw;
			lostworst=lost;
		}
	}
	}
	printf("Worst Player:\t%s",idworst);
	getch();
	fclose(wp);
	system("cls");
	menu2();	
}
// vard shodan player dovom dar soorat 2 nafare boodan
void selectPlayer(int Pnum){
	if(Pnum==1){
		int i;
		printf("%s Player(1 or 2)?\n",User1);
		scanf("%d",&i);
		if(i==1){
			strcpy(UserP1,User);
			strcpy(UserP2,"PC");
			system("cls");
			menu2();
		}
		else{
			strcpy(UserP2,User);
			strcpy(UserP1,"PC");
			system("cls");
			menu2();
		}
	}
	else{
		int i;
		printf("%s Player(1 or 2)?\n",User1);
		scanf("%d",&i);
		if(i==1){
			strcpy(UserP1,User);
			menu1();
			strcpy(UserP2,User);
			system("cls");
			menu2();
		}
		else{
			strcpy(UserP2,User);
			menu1();
			strcpy(UserP1,User);
			system("cls");
			menu2();
		}
	}
}
// amar ra baad payan har bazi update mikonad
void updateStatistics(int pl1,int pl2){
	int n;
	int w;
	int d;
	int l;
	char user[50];
		FILE *p1;
		p1 = fopen("statistics.bin","r+b");
		while(!feof(p1)){
			fread(user,sizeof(char),50,p1);
			fread(&n,sizeof(int),1,p1);
			fread(&w,sizeof(int),1,p1);
			fread(&d,sizeof(int),1,p1);
			fread(&l,sizeof(int),1,p1);
			if(strcmp(user,UserP1)==0){
				n++;
				fseek(p1,-4 * sizeof(int),1);
				fwrite(&n,sizeof(int),1,p1);
				if(pl1==1&&pl2==0){
					w++;
					fwrite(&w,sizeof(int),1,p1);					
				}
				else if(pl1==0&&pl2==1){
					l++;
					fseek(p1,+2 * sizeof(int),1);
					fwrite(&l,sizeof(int),1,p1);					
				}
				else if(pl1==0&&pl2==0){
					d++;
					fseek(p1,+1 * sizeof(int),1);
					fwrite(&d,sizeof(int),1,p1);					
				}
				fclose(p1);
				break;
			}
		}
		FILE *p2;
		p2 = fopen("statistics.bin","r+b");		
			while(!feof(p2)){
			fread(user,sizeof(char),50,p2);
			fread(&n,sizeof(int),1,p2);
			fread(&w,sizeof(int),1,p2);
			fread(&d,sizeof(int),1,p2);
			fread(&l,sizeof(int),1,p2);
			if(strcmp(user,UserP2)==0){
				n++;
				fseek(p2,-4 * sizeof(int),1);
				fwrite(&n,sizeof(int),1,p2);
				if(pl2==1&&pl1==0){
					w++;
					fwrite(&w,sizeof(int),1,p2);					
				}
				else if(pl2==0&&pl1==1){;
					l++;
					fseek(p2,+2 * sizeof(int),1);
					fwrite(&l,sizeof(int),1,p2);					
				}
				else if(pl1==0&&pl2==0){
					d++;
					fseek(p2,+1 * sizeof(int),1);
					fwrite(&d,sizeof(int),1,p2);					
				}
				fclose(p2);
				break;
			}
		}		
	FILE *num;
	num = fopen("num.bin","r+b");
	fread(&n,sizeof(int),1,num);
	n++;
	fseek(num,-1L*sizeof(int),1);
	fwrite(&n,sizeof(int),1,num);
	fclose(num);
	fclose(p2);
	fclose(p1);
}
// bazi gadid igad mikonad baraye bazi 2 nafare
int newGame(){
	int menu;
	int state2[20][20];//baraye rangi kardan posht
		for(int i=0;i<Size;i++){
			for(int j=0;j<Size;j++){
				state2[i][j]=state[i][j];
			}
	}
	stateValue();									
		while(1){
	printBorder(state2); 	  
    if (CheckWinner()==1){
    	printf("\nplayer1 is winner");
    	updateStatistics(1,0);
    	getch();
    	system("cls");
    	menu2();
    	return 0;
	} 
    else if (CheckWinner()==2){
        printf("\nplayer2 is winner");
        updateStatistics(0,1);
        getch();
        system("cls");
        menu2();
    	return 0;	
	} 
	if (CheckMohasere()==1){
		printf("\nplayer1 is winner");
		updateStatistics(1,0);
		getch();
		system("cls");
		menu2();
    	return 0;
	}
	else if (CheckMohasere()==2){
		printf("\nplayer2 is winner");
		updateStatistics(0,1);
		getch();
		system("cls");
		menu2();
    	return 0;
	} 
	if(count>=leave_camp_value){
		if(LeaveCamp()==1){
			printf("\nplayer1 is winner");
			updateStatistics(1,0);
			getch();
			system("cls");
			menu2(); 
			return 0;	
		}
		else if(LeaveCamp()==2){
			printf("\nplayer2 is winner");
			updateStatistics(0,1);
			getch();
			system("cls");
			menu2();
			return 0;
		}
		else if(LeaveCamp()==3){
			printf("\nIntense equals");
			updateStatistics(0,0);
			getch();
			system("cls");
			menu2();
			return 0; 
		}
	}  
	move(state,Size,turn,state2);
	sum++;
	if(sum%2==0&&sum!=0) count++;
	changeTurn(turn);
		menu=menu3();
	if(menu==0){
		system("cls");
			menu2();
			return 0;
	}
	else if(menu==-1){
		return 0;
	}
	system("cls"); 
	}
}
// in tabe harekat computer ra anjam midahad			
void ComputerMove(){
	int x,i,j,count,sw1,sw,pos_x2,pos_y2;
	 
	do{
    	sw=0;
    	for (i=0 ; i<Size && sw==0 ;i++){  
    		sw1=0; 
    		for (j=0 ; j<Size && sw1==0 ;j++){
    			if (state[i][j]==2 && check(i+1,j+1)==0) { 
    				sw1=1;
    				break;
				} 
    		}
    		if (sw1==1){
    			sw=1;
    			break;
			} 
    	} 
    }while(sw==0); 
    
 sw1=0;
        int pos_x1=i;
        int pos_y1=j;
    	for(pos_x2=i-2;pos_x2<=i+4 &&sw1==0 ; pos_x2++){
    		int sw=0;
    		for(pos_y2=j-2;pos_y2<=j+4 && sw==0; pos_y2++){
    			if(	pos_x2>=0 && pos_x2<Size && pos_y2>=0 && pos_y2<Size && state[pos_x2][pos_y2]==0 
    			&& normal(pos_x1+1,pos_y1+1,pos_x2+1,pos_y2+1)+SuperJump(pos_x1+1,pos_y1+1,pos_x2+1,pos_y2+1)+jump(pos_x1+1,pos_y1+1,pos_x2+1,pos_y2+1)!=3 ){
    				state[i][j]=0;
    				state[pos_x2][pos_y2]=2;
    				sw=1;
    				break;
	    		}			
	    	}
	    	if(sw==1) {
	    		sw1=1;
	    		break;
			}
		    	}

}
// in tabe mokhtasate mohre va mokhtasat maghsad ra migirad va mohre ra ja be ja mikonad
void movepc(int state[][20], int Size , int &turn , int state2[][20]){
    int pos_x1 , pos_y1 , pos_x2 , pos_y2; //x va y radif va sotoon hastand
    if(turn==1){
       do{ //check mikonad mokhtasat mohre dorost ast ya na
          printf("player%d please select your piece:\n",turn);
          scanf("%d %d",&pos_x1 ,&pos_y1);
        }while(pos_x1<1 || pos_x1>Size || pos_y1<1 || pos_y1>Size || state[pos_x1 -1][pos_y1 -1]!=turn || check(pos_x1,pos_y1)!=0);
        
       do{ //check mikonad mokhtasat maghsad dorost ast ya na
          printf("player%d please select available position:\n",turn);
          scanf("%d %d",&pos_x2,&pos_y2);
        }while(pos_x2<1 || pos_x2>Size || pos_y2<1 || pos_y2>Size || state[pos_x2 -1][pos_y2 -1]!=0 || normal(pos_x1,pos_y1,pos_x2,pos_y2)+SuperJump(pos_x1-1,pos_y1-1,pos_x2-1,pos_y2-1)+jump(pos_x1,pos_y1,pos_x2,pos_y2)==3 );
       if(normal(pos_x1,pos_y1,pos_x2,pos_y2)==0 || SuperJump(pos_x1-1,pos_y1-1,pos_x2-1,pos_y2-1)==0){
            state[pos_x2 -1][pos_y2 -1]=turn;
            state[pos_x1 -1][pos_y1 -1]=0;       	
	   }
	   else if(jump(pos_x1,pos_y1,pos_x2,pos_y2)==0){
	   	char reply[4]="YES";
	   	do{
	   		state[pos_x2 -1][pos_y2 -1]=turn;
        	state[pos_x1 -1][pos_y1 -1]=0;
        	system("cls");
	   		printBorder(state2);
	   		if(jump(pos_x1,pos_y1,pos_x2,pos_y2)==0){
	   			printf("You want to continue(YES/NO)?");
	   			scanf("%s",reply);
	   		}
	   		pos_x1=pos_x2;
	   		pos_y1=pos_y2;
	   		if(strcmp(reply,"YES")==0){
	   		//	system("cls");
	   		//	printBorder(state);
 				do{
          			printf("player%d please select available position:\n",turn);
        		  scanf("%d %d",&pos_x2,&pos_y2);
        		}while(pos_x2<1 || pos_x2>Size || pos_y2<1 || pos_y2>Size || state[pos_x2 -1][pos_y2 -1]!=0 || SuperJump(pos_x1,pos_y1,pos_x2,pos_y2)+jump(pos_x1,pos_y1,pos_x2,pos_y2)==2 || normal(pos_x1,pos_y1,pos_x2,pos_y2)==0);
				state[pos_x2 -1][pos_y2 -1]=turn;
        		state[pos_x1 -1][pos_y1 -1]=0;	
			   }
		   }while(strcmp(reply,"YES")==0 && jump(pos_x1,pos_y1,pos_x2,pos_y2)==0);
	    }
	}
	else if(turn==2){
		ComputerMove();
	}
}  
// bazi gadid igad mikonad baraye bazi 1 nafare
int newGamepc(){
	int menu;
	int state2[20][20];//baraye rangi kardan posht
		for(int i=0;i<Size;i++){
			for(int j=0;j<Size;j++){
				state2[i][j]=state[i][j];
			}
	}
	stateValue();									
		while(1){
	printBorder(state2); 	  
    if (CheckWinner()==1){
    	printf("\nplayer1 is winner");
    	updateStatistics(1,0);
    	getch();
    	system("cls");
    	menu2();
    	return 0;
	} 
    else if (CheckWinner()==2){
        printf("\nplayer2 is winner");
        updateStatistics(0,1);
        getch();
        system("cls");
        menu2();
    	return 0;	
	} 
	if (CheckMohasere()==1){
		printf("\nplayer1 is winner");
		updateStatistics(1,0);
		getch();
		system("cls");
		menu2();
    	return 0;
	}
	else if (CheckMohasere()==2){
		printf("\nplayer2 is winner");
		updateStatistics(0,1);
		getch();
		system("cls");
		menu2();
    	return 0;
	} 
	if(count>=leave_camp_value){
		if(LeaveCamp()==1){
			printf("\nplayer1 is winner");
			updateStatistics(1,0);
			getch();
			system("cls");
			menu2(); 
			return 0;	
		}
		else if(LeaveCamp()==2){
			printf("\nplayer2 is winner");
			updateStatistics(0,1);
			getch();
			system("cls");
			menu2();
			return 0;
		}
		else if(LeaveCamp()==3){
			printf("\nIntense equals");
			updateStatistics(0,0);
			getch();
			system("cls");
			menu2();
			return 0; 
		}
	}  
	movepc(state,Size,turn,state2);
	sum++;
	if(sum%2==0&&sum!=0) count++;
	changeTurn(turn);
	menu=menu3();
	if(menu==0){
		system("cls");
			menu2();
			return 0;
	}
	else if(menu==-1){
		return 0;
	}
	system("cls"); 
	}
}
// menu asli
int menu2(){
	int number;
	if(Player_Num==2){
	printf("1-> Game statistics\n");
	printf("2-> Player statistics\n");
	printf("3-> Select players\n");
	printf("4-> New game\n");
	printf("5-> Exit\n");
//	printf("4-> Continue playing\n");
	number=Up_Down(5);
	if(number==1){
		system("cls");
		FILE *game;
		game = fopen("num.bin","rb");
		int num;
		fread(&num,sizeof(int),1,game);
		printf("Total match played: %d\n",num);
		fclose(game); 
		MostPlayer();
		WorstPlayer();
	}
	else if(number==2){
		system("cls");
		PlayerStatistics();
	}
	else if(number==3){
		system("cls");
		selectPlayer(Player_Num);
	}
	else if(number==4){
		system("cls");
		newGame();
	}
	else if(number==5){
		return 0;
	}
	}
	else{
		printf("1-> Game statistics\n");
	printf("2-> Player statistics\n");
	printf("3-> New game\n");
	printf("4-> Exit\n");
//	printf("4-> Continue playing\n");
	number=Up_Down(4);
	if(number==1){
		system("cls");
		FILE *game;
		game = fopen("num.bin","rb");
		int num;
		fread(&num,sizeof(int),1,game);
		printf("Total match played: %d\n",num);
		fclose(game); 
		MostPlayer();
		WorstPlayer();
	}
	else if(number==2){
		system("cls");
		PlayerStatistics();
	}
	else if(number==3){
		system("cls");
		newGamepc();
	}
	else if(number==4){ 
		return 0;
	}	
	}
}
// menu dar hengam bazi kardan
int menu3(){
	int number;
	printf("1-> Submit\n");
	printf("2-> To menu\n");
	printf("3-> Exit\n");
//	printf("4-> Continue playing\n");
	number=Up_Down(3);
	if(number==1){
		return 1;
	}
	else if(number==2){
		system("cls");
		menu2();
		return 0;
	}
	else if(number==3){
		return -1;
	}
}
int main(){
	scanSetting();									
	menu1();
	strcpy(User1,User);
	menu2();	
	return 0;
}
