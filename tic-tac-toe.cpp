#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <windows.h>
#include <ctime>
using namespace std;

int cor[2]{11,12};
int turno = 0;
int vez = 1;
int step = 0;
int dif = 1;
string resp;
int iresp;
int color[3][3]{{15,15,15},{15,15,15},{15,15,15}};
string p[3][3]{{"1","2","3"},{"4","5","6"},{"7","8","9"}};
void setColor(int cor){
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cor);
}

string convert(int num){
	string converted;
	stringstream stream;
    stream << num;
    stream >> converted;
    return converted;
}

int startMenu(){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			p[i][j] = convert(3*i+j+1);
			color[i][j] = 15;
		}
	}
	turno = 0;
	vez = 1;
	
	cout << " Jogo da Velha\n";
	cout << " 1. Jogador Vs Jogador\n";
	cout << " 2. Jogador Vs Máquina\n";
	cout << " 3. Configurar Dificuldade\n ";
	getline(cin, resp);
	istringstream(resp) >> iresp;
	step = iresp*(iresp>0 and iresp<4);
}

int difMenu(){
	cout << " Configurar Dificuldade\n";
	cout << " 1. Fácil ";
	if(dif==1) cout << "X";
	cout << "\n 2. Médio ";
	if(dif==2) cout << "X";
	cout << "\n 3. Difícil ";
	if(dif==3) cout << "X";
	cout << "\n 0. Sair\n ";
	getline(cin, resp);
	istringstream(resp) >> iresp;
	step *= iresp>0 and iresp<4;
	if(step==3){
		dif = iresp;
	}
}

void showBoard(){
	cout << "     |     |\n  ";
	for(int j=0;j<3;j++){
		for(int i=0;i<3;i++){
			setColor(color[j][i]);cout << p[j][i];
			setColor(15);
			if(i!=2) cout << "  |  ";
		}
		if(j!=2){
			cout << "\n     |     |\n";
			cout << "-----+-----+-----\n";
			cout << "     |     |\n  ";
		}
	}
	cout << "\n     |     |\n";
}

void catchResp(){
	bool valid = false;
	cout << " Vez do jogador " << vez << ":\n ";
	getline(cin, resp);
	istringstream(resp) >> iresp;
	if(iresp>0 and iresp<10){
		for(int i=0;i<3 and not valid;i++){
			for(int j=0;j<3 and not valid;j++){
				if(p[i][j]==resp){
					if(vez==1){
						p[i][j] = "X";
						color[i][j] = cor[0];
					}else{
						p[i][j] = "O";
						color[i][j] = cor[1];
					}
					vez = 3-vez;
					turno++;
					valid = true;
				}
			}
		}
	}
}

bool botBrain(){
	if(turno==1){
		int y = p[1][1]=="5";
		p[y][y] = "O";
		color[y][y] = cor[1];
		return true;
	}
	bool valid = false;
	string x[2]{"O","X"};
	for(int k=0;k<2 and not valid;k++){
		for(int i=0;i<3 and not valid;i++){
			for(int j=0;j<3 and not valid;j++){
				if(p[i][j==2]==p[i][1+(j!=0)] and p[i][2-j]!="X" and p[i][2-j]!="O" and p[i][j==2]==x[k]){
					p[i][2-j] = "O";
					color[i][2-j] = cor[1];
					return true;
				}else if(p[j==2][i]==p[1+(j!=0)][i] and p[2-j][i]!="X" and p[2-j][i]!="O" and p[j==2][i]==x[k]){
					p[2-j][i] = "O";
					color[2-j][i] = cor[1];
					return true;
				}else if(i==0){
					if(p[j==2][j==2]==p[1+(j!=0)][1+(j!=0)] and p[2-j][2-j]!="X" and p[2-j][2-j]!="O" and p[j==2][j==2]==x[k]){
						p[2-j][2-j] = "O";
						color[2-j][2-j] = cor[1];
						return true;
					}else if(p[j==2][1+(j!=2)]==p[1+(j!=0)][j==0] and p[2-j][j]!="X" and p[2-j][j]!="O" and p[j==2][1+(j!=2)]==x[k]){
						p[2-j][j] = "O";
						color[2-j][j] = cor[1];
						return true;
					}
				}
			}
		}
	}
	if(dif==3){
		if(turno==3){
			if(p[1][1]==p[2][2] or p[0][0]==p[1][2] or p[2][2]==p[0][1]){
				p[0][2] = "O";
				color[0][2] = cor[1];
				return true;
			}else if(p[0][0]==p[2][1] or p[2][2]==p[1][0]){
				p[2][0] = "O";
				color[2][0] = cor[1];
				return true;
			}else if(p[2][0]==p[0][1] or p[0][2]==p[1][0]){
				p[0][0] = "O";
				color[0][0] = cor[1];
				return true;
			}else if(p[2][0]==p[1][2] or p[0][2]==p[2][1]){
				p[2][2] = "O";
				color[2][2] = cor[1];
				return true;
			}else if(p[0][1]==p[1][0]){
				p[0][0] = "O";
				color[0][0] = cor[1];
				return true;
			}else if(p[0][1]==p[1][2]){
				p[0][2] = "O";
				color[0][2] = cor[1];
				return true;
			}else if(p[2][1]==p[1][0]){
				p[2][0] = "O";
				color[2][0] = cor[1];
				return true;
			}else if(p[2][1]==p[1][2]){
				p[2][2] = "O";
				color[2][2] = cor[1];
				return true;
			}else if(p[0][1]=="2"){
				p[0][1] = "O";
				color[0][1] = cor[1];
				return true;
			}
		}
		int r[2];
		while(true){
			r[0] = rand()%3;r[1] = rand()%3;
			if(p[r[0]][r[1]]!="X" and p[r[0]][r[1]]!="O"){
				p[r[0]][r[1]] = "O";
				color[r[0]][r[1]] = cor[1];
				return true;
			}
		}
	}else{
		int r[2];
		while(true){
			r[0] = rand()%3;r[1] = rand()%3;
			if(p[r[0]][r[1]]!="X" and p[r[0]][r[1]]!="O"){
				p[r[0]][r[1]] = "O";
				color[r[0]][r[1]] = cor[1];
				return true;
			}
		}
	}
}

void botResp(){
	if(vez==2 and step!=0){
		bool valid = false;
		if(dif==1){
			int r[2];
			while(not valid){
				r[0] = rand()%3;r[1] = rand()%3;
				if(p[r[0]][r[1]]!="X" and p[r[0]][r[1]]!="O"){
					p[r[0]][r[1]] = "O";
					color[r[0]][r[1]] = cor[1];
					valid = true;
				}
			}
		}else{
			valid = botBrain();
		}
		if(valid){
			vez = 3-vez;
			turno++;
		}
	}
}

bool checkWin(){
	if(step!=0){
		for(int i=0;i<3;i++){
			if(p[i][0]==p[i][1] and p[i][1]==p[i][2] or p[0][i]==p[1][i] and p[1][i]==p[2][i] or p[0][0]==p[1][1] and p[1][1]==p[2][2] or p[2][0]==p[1][1] and p[1][1]==p[0][2]){
				turno = -1;
				break;
			}
		}
		if(turno==9 or turno==-1){
			system("clear||cls");
			showBoard();
			if(turno==-1){
				cout << " Vitória do jogador " << 3-vez << "\n ";
			}else{
				cout << " Empate\n ";
			}
			getline(cin,resp);
			step = 0;
		}
	}
}

int main(){
setlocale(LC_ALL, "PORTUGUESE");

	srand(time(0));
	
	while(true){
		system("clear||cls");
		if(step==0){
			startMenu();
		}else if(step==1){
			showBoard();
			catchResp();
			checkWin();
		}else if(step==2){
			showBoard();
			catchResp();
			checkWin();
			botResp();
			checkWin();
		}else{
			difMenu();
		}
	}
	
}
