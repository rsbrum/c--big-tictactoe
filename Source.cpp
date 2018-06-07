#include <iostream>
#include <vector>
#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

typedef vector< vector<char> > matriz;  //serve pra nao precisar ficando escrever vector< vector<char> > toda hora, toda vez que escrevo matriz ela tem aquele valor

/* Atualiza o placar e reinicia o jogo*/
void atualizarPlacar(char jogador);
/**************************************/

/* Inicializa o jogo sem pedir pra definir o tamanho do tabuleiro*/
void game(matriz &tabuleiro);
/**************************************/

/* Inicializa o tabuleiro */
void setTabuleiro(matriz &tabuleiro, int linha, int coluna);
/**************************************/

/* Printa o tabuleiro na tela*/
void getTabuleiro(matriz &tabuleiro);
/**************************************/

/* Coloca a posicao no tabuleiro */
void setPosicao(matriz &tabuleiro, int posicao, int jogador);
/**************************************/

/* Utilizado em todas as funcoes de logica do jogo, serve pra verificar se os valores coletados pelas funcoes sao iguais*/
bool testarIgualdade(vector<char> &temp);
/**************************************/

/* Logica do jogo - testa cada angulo respectivamente */

void testeDiagonal(matriz &tabuleiro);
void testeDiagonal2(matriz &tabuleiro);
void testeVertical(matriz &tabuleiro);
void testeHorizontal(matriz &tabuleiro);

/**************************************/

void testeEmpate(matriz &tabuleiro);
void testeVitoria(matriz &tabuleiro);
void vencedor();

/**************************************/

int placar[2] = { 0,0 }; // placar ta como global pra nao precisar ficar passando ele como parametro toda hora
bool start = false; // testa se o jogo ta sendo aberto pela primeira vez
int linha, coluna; //linha e coluna do tabuleiro

/*
	Funcao principal, se o jogo ja foi iniado uma vez ela passa a opcao de escolher linhas e colunas // 
	e continua com o tamanho escolhido anteriormente 
*/
int main() {

	matriz tabuleiro;
						
	if (start == false)
	{	
		start = true;

		cout << "Numero de colunas: "; cin >> coluna;
		cout << "Numero de linhas: "; cin >> linha;

		setTabuleiro(tabuleiro, linha, coluna);
		getTabuleiro(tabuleiro);
		game(tabuleiro);

	}
	else {

		setTabuleiro(tabuleiro, linha, coluna);
		getTabuleiro(tabuleiro);
		game(tabuleiro);

	}
	
}

/*
	Funcao onde chama todas as funcoes necessarias pro jogo funcionar e permite reiniciar o jogo apos toda vitoria
*/
void game(matriz &tabuleiro) {

	int posicao = 0;
	int jogador = 0;

	
	while (posicao != 666) 
	{
		jogador++;

		if (jogador % 2 == 0)
		{
			cout << "Posicao X: ";
		}
		else if (jogador % 2 != 0)
		{
			cout << "Posicao O: ";
		}


		cin >> posicao;

		if (posicao == 666) {
			vencedor();
			break;
		}
		setPosicao(tabuleiro, posicao, jogador);
		getTabuleiro(tabuleiro);
		testeEmpate(tabuleiro);
		testeVitoria(tabuleiro);


	}
	
}

/*
	Adiciona um vetor de vetores a cada iteracao, push_back apenas adiciona cada elemento no fim de cada vetor
*/
void setTabuleiro(matriz &tabuleiro, int linha, int coluna) {
	
	vector<char> temp;
	
	for (int x = 0; x < coluna; x++) {
		
		for (int y = 0; y < linha; y++) {
			temp.push_back('*');
		}
		tabuleiro.push_back(temp);
	}

}

/*
	Printa  o tabuleiro e o placar 
*/
void getTabuleiro(matriz &tabuleiro) {

	system("cls");
	
	int c = tabuleiro.size();
	int l = tabuleiro[0].size();

	cout << "						*** PLACAR *** " << endl;
	cout << "						X: " << placar[0] << " |   O:  " << placar[1] << endl;
	cout << "\n\n"; cout << "                                            Digite 666 para parar\n\n" << endl;

	for (int x = 0; x < c; x++) {
		cout << "   ";
		for (int y = 0; y < l; y++) {
			cout << "  |  " << tabuleiro[x][y];
		}
		cout << " | ";
		cout << endl;

		cout << endl;
	}

}

void setPosicao(matriz &tabuleiro, int posicao, int jogador) {
	
	int i = 0; 
	int c = tabuleiro.size();
	int l = tabuleiro[0].size();
	int novaPosicao;

	for (int x = 0; x < c; x++) {
		
		for (int y = 0; y < l; y++) {
			
			i++;
			if (i == posicao) 
			{	
				/*
					Testa por posicoes invalidas, se a posicao for invalida ele pede uma nova posicao e rechama a propria funcao setposicao, passando os novos valores
				*/
				if (tabuleiro[x][y] == 'X' or tabuleiro[x][y] == 'O') {
					cout << "################ Posicao invalida! ##################" << endl;
					Sleep(2000);
					getTabuleiro(tabuleiro);

					cout << "Nova posicao: ";
					cin >> novaPosicao;

					setPosicao(tabuleiro, novaPosicao, jogador);

					break;
				}
				/*
				 se jogador for par ele 'e X se for impar ele 'e O 
				*/
				if (jogador % 2 == 0)
				{
					tabuleiro[x][y] = 'X';
				}
				else if (jogador % 2 != 0)
				{
					tabuleiro[x][y] = 'O';
				}

				break;

			}

		}
	}

}

/*
	Essa funcao Sleep faz o console dormir por 2 segundos, system CLS limpa a tela 
*/
void atualizarPlacar(char jogador) {

	
	if (jogador == 'X') 
	{
		system("cls");
		cout << "Vitoria de X!!!" << endl;
		Sleep(2000);
		placar[0]++;
		main();
	}else if ( jogador == 'O')
	{
		system("cls");
		cout << "Vitoria de O!!!" << endl;
		Sleep(2000);
		placar[1]++;
		main();
	}
													
}


void testeVitoria(matriz &tabuleiro) {
	 
	testeDiagonal(tabuleiro);
	testeDiagonal2(tabuleiro);
	testeVertical(tabuleiro);
	testeHorizontal(tabuleiro);

}

/*
	Se nao tiver nenhum elemento no tabuleiro com valor de asterisco significa que foi um empate
*/
void testeEmpate(matriz &tabuleiro) {

	int count = 0;

	for (int x = 0; x < tabuleiro.size(); x++) {
		for (int y = 0; y < tabuleiro[0].size(); y++) {

			if (tabuleiro[x][y] == '*') 
			{

				count++;

				if (count >= 1) 
				{
					break;
				}

			}
		}
	}

	/*
		Isso aqui tem em toda funcao de teste, ele so substitui a carreira que venceu por @ 
	*/
	if (count == 0) 
	{

		for (int x = 0; x < tabuleiro.size(); x++) {
			for (int y = 0; y < tabuleiro[0].size(); y++) {

				tabuleiro[x][y] = '@';

			}
		}

		getTabuleiro(tabuleiro);
		cout << "EMPATE!" << endl;
		Sleep(3000);
		main();

	}

}

/*
	Desenha uma matriz em um papel pra entender a logica dessas funcoes
*/
void testeDiagonal(matriz &tabuleiro) {
		
	int c = tabuleiro.size();
	int l = tabuleiro[0].size();
	bool flag = false; 
	vector<char> temp;
	

	for (int x = 0; x < c; x++) {
		
		temp.push_back(tabuleiro[x][x]);
			
	}

	flag = testarIgualdade(temp);

	if (flag == true) 
	{
		for (int x = 0; x < c; x++) {

			tabuleiro[x][x] = '@';

		}

		getTabuleiro(tabuleiro);
		cout << "VITORIA!" << endl;
		Sleep(3000);
		atualizarPlacar(temp[0]);

	}


}

void testeDiagonal2(matriz &tabuleiro) {

	int c = tabuleiro.size();
	int count = 0;
	vector<char> temp;
	bool flag = false;

	for (int x = c -1; x >= 0; x--) {

		temp.push_back(tabuleiro[x][count]);
		count++;
	}

	flag = testarIgualdade(temp);

	if (flag == true)
	{
		count = 0;

		for (int x = c - 1; x >= 0; x--) {

			tabuleiro[x][count] = '@';
			count++;
		}

		getTabuleiro(tabuleiro);
		cout << "VITORIA!" << endl;
		Sleep(3000);
		atualizarPlacar(temp[0]);
	}


}

void testeHorizontal(matriz &tabuleiro) {

	int c = tabuleiro.size();
	int l = tabuleiro[0].size();
	bool flag = false;
	

	for (int x = 0; x < c; x++) {
	
		vector<char> temp;
		for (int y = c -1; y >= 0; y--) {

	 		temp.push_back(tabuleiro[x][y]);

		}

		flag = testarIgualdade(temp);
		
		if (flag == true)
		{

			for (int y = c - 1; y >= 0; y--) {

				tabuleiro[x][y] = '@';

			}

			getTabuleiro(tabuleiro);
			cout << "VITORIA!" << endl;
			Sleep(3000);
			atualizarPlacar(temp[0]);
		}

	}

}

void testeVertical(matriz &tabuleiro) {

	int c = tabuleiro.size();
	int l = tabuleiro[0].size();
	bool flag = false;


	for (int x = 0; x < c; x++) {

		vector<char> temp;
		for (int y = c - 1; y >= 0; y--) {

			temp.push_back(tabuleiro[y][x]);

		}

		flag = testarIgualdade(temp);

		if (flag == true)
		{

			for (int y = c - 1; y >= 0; y--) {

				tabuleiro[y][x] = '@';

			}

			getTabuleiro(tabuleiro);
			cout << "VITORIA!" << endl;
			Sleep(3000);
			atualizarPlacar(temp[0]);
		}

	}
}

bool testarIgualdade(vector<char> &temp) {

	for (int x = 0; x < temp.size(); x++) {

		for (int y = 0; y < temp.size(); y++) {

			if (temp[x] == 'X' or temp[x] == 'O')
			{
				if (temp[x] != temp[y])
				{
					return false;
					break;
				}
			}

		}
	}

	if (temp[0] == 'X' or temp[0] == 'O')
	{
		return true;
	}

}
/*
	Testa pelo vencedor
*/
void vencedor() {

	if (placar[0] > placar[1]) {

		system("cls");
		cout << "\n                                    X VENCEU!!!!!!!!!!!" << endl;
	}
	else {
		system("cls");
		cout << "\n                                    O VENCEU!!!!!!!!!!!" << endl;
	}

	system("pause");

}
