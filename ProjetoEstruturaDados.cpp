#include<stdio.h>
#include<string.h>
#include<locale.h>
#include<stdlib.h> 
#include<conio.h>  
#include <windows.h>
#include<iostream>

#define MAX 2

using namespace std;

struct cadastro
{
	char nome[50];
	char prontuario[15];
}; typedef struct cadastro Cadastro;

typedef struct   								//defini��o do cadastro de produto
{         
   char nome[50];
	char descricao[50];
	float peso;
	float preco;
} 
REGISTRO;

typedef struct aux
{  
	REGISTRO 	reg;
	struct 		aux	* PROX; // prox APONTA para o endere�o de mem�ria
}                           // de um elemento com essa mesma estrutura
ELEMENTO;

typedef ELEMENTO * PONT;  

typedef struct 
{
	PONT topo; // topo APONTA para o endere�o do ELEMENTO do TOPO da PILHA
} 
PILHA;

typedef struct		
{
	PONT inicio;		//O inicio aponta para o endere�o de inicio de uma LISTA
}LISTA;

//-------------------------------------------------Chamado dos prot�tipos da fun��o--------------------------------------------------------
void tela_menu();
void ler_arquivo(Cadastro *leitura, int *numero_linhas);
void imprimir_arquivo(Cadastro *leitura, int *numero_linhas);
void salvar_escrever_arquivo();
void login(Cadastro *leitura, int *numero_linhas, Cadastro *usuario, int *logado);
int espaco_memoria();
long tamanho_arquivo();
void ordenar_arquivo(Cadastro *leitura, int *numero_linhas);
int busca_binaria(Cadastro *leitura, int *numero_linhas, Cadastro *usuario);
void cadastrar_produto_gondola(int *gondola, PILHA* pil);		
void escolha_gondola(int *gondola);		
//------------------------fun��es da PILHA de produtos gondola
void inicializarPilha 	(PILHA* p);
int  tamanho 			(PILHA* p);
void exibirPilha 		(PILHA* p);
bool inserirElemPilha	(PILHA* p, REGISTRO reg);
bool excluirElemPilha	(PILHA* p, REGISTRO* reg); 
void reinicializarPilha (PILHA* p);
bool estaVazia(PILHA* p);
void excluiDaPilha (PILHA* p);
void insereNaPilha (PILHA* p);
REGISTRO realizarCompra(PILHA* p);
void insereNaPilha_Compra (PILHA* p, PILHA* c);
//---------------------fun��es de fila do caixa PDV
void inicializarLista (LISTA* l);
void exibirLista (LISTA* l);
void reinicializarLista (LISTA* l);
void insereNaLista (LISTA* l);
void inserirElemLista( LISTA* l, PILHA* p);
void ValorCompra (LISTA* l);

int main()
{
	setlocale(LC_ALL, "Portuguese");
	Cadastro usuario;
	Cadastro *leitura;
	int i, numero_linhas, logado, gondola, opcao;
	PILHA pil[MAX];
	PILHA compra;
	char resposta;
	LISTA pdv;
	
	for(gondola=0;gondola<MAX;gondola++){					//Inicializa a Pilha de produtos
		inicializarPilha 	(&pil[gondola]);
	}
	inicializarPilha 	(&compra);							//Inicializa a Pilha de compra
	leitura=(Cadastro *)calloc(1, tamanho_arquivo());		//Esta fun��o aloca a mem�ria do tamanha do arquivio USUARIO.dat
	if(leitura==NULL)
	return (espaco_memoria());							//Caso n�o tenha espa�o suficiente na mem�ria o programa � encerrado											
	ler_arquivo(leitura, &numero_linhas);					//esta fun��o l� o arquivo USUARIO.dat
	ordenar_arquivo(leitura, &numero_linhas);				//esta fun��o ordena o arquivo na mem�ria alocada em leitura
	login(leitura, &numero_linhas, &usuario, &logado);		//esta fun��o realiza o login de um usu�rio
		
	do
	{
		//system("color 07");
		//system("mode 85, 75");
		tela_menu();										//EXIBE O MENU NA TELA
		fflush(stdin);
		scanf("%d", &opcao);	
		
		switch(opcao){								//ESCOLHE AS OP��ES DO MENU
			case 0:									//-----------------------------------------------------CASE 1
				system("cls");
				printf("\n\n-----Voc� est� saindo do sistema------\n\n");
				getch();
				break;
			
			case 1:									//-----------------------------------------------------CASE 1
				system ("cls");
				printf("\n----------Acesso somente a pessoas autorizadas------------");
				login(leitura, &numero_linhas, &usuario, &logado);						//esta fun��o realiza o login para cadastrar os produtos
				//system("color 07");
				//system("mode 85, 75");
				for(gondola=0;gondola<MAX;gondola++)									//ESTA FUN��O INICIALIZA A GONDOLA
				inicializarPilha(&pil[gondola]);
				cadastrar_produto_gondola(&gondola, pil);								//ESTA FUN��O CADASTRA OS PRODUTOS NA GONDULA
				for(gondola=0;gondola<MAX;gondola++){
					printf("\n------------------A gondola %d est� cheia!---------------------", gondola);
					exibirPilha (&(pil[gondola]));	
				}
				getch();
				system("cls");
				break;
			
			case 2:								//--------------------------------------------------------------------------------------------CASE 2
				inicializarLista (&pdv);																//Inicia a vari�vel LISTA pdv
				printf("\n-------------Estamos colocando os itens no caixa PDV---------------\n");
				inserirElemLista(&pdv, &compra);
				exibirLista (&pdv);																		//Exibe a Lista pdv na tela
				ValorCompra (&pdv);																		//mostra o valor da compra realizado
				getch();
				break;
			
			case 3:							//--------------------------------------------------------------CASE 3
				do{	
					system("cls");
					printf("\n------------------------Realizando uma compra--------------------------------\n");
					printf("\n--------Segue os produtos e os respectivos n�meros das gondolas:--------------\n");
					for(gondola=0;gondola<MAX;gondola++){
						printf("\n------------------Gondola %d---------------------\n", gondola);
						if(pil[gondola].topo==NULL)
							printf("\nA gondola %d est� vazia!\n", gondola);
						else{
							printf("\nGondola:  %d", gondola);
							exibirPilha (&(pil[gondola]));
						}	
					}
					escolha_gondola(&gondola);
					if(pil[gondola].topo==NULL)
					printf("\nN�o � poss�vel comprar um produto de uma gondola vazia!");
					else{
						system("cls");
						insereNaPilha_Compra (&(pil[gondola]), &compra);	
						printf("\n--------------LISTA DE COMPRAS------------------\n");
						exibirPilha (&compra);		
						excluiDaPilha (&pil[gondola]);
					}
					printf("\n---------Deseja continuar comprando?------------\nDigite S para continuar ou N para encerrar: ");
					fflush(stdin);
					scanf("%c", &resposta);
				}while(resposta=='s' || resposta=='S');
				break;
			
			case 4:									//--------------------------------------------------------------------CASE 4
				salvar_escrever_arquivo();									//esta fun��o insere um novo usu�rio
				free(leitura);
				leitura=(Cadastro *)calloc(1, tamanho_arquivo());		//Esta fun��o aloca a mem�ria do tamanha do arquivio USUARIO.dat
				ler_arquivo(leitura, &numero_linhas);					//esta fun��o l� o arquivo USUARIO.dat
				ordenar_arquivo(leitura, &numero_linhas);				//esta fun��o ordena o arquivo na mem�ria alocada em leitura
				break;
				
			case 5:									//--------------------------------------------------------------------CASE5
				system("cls");
				printf("\n-------------LISTA DE COMPRAS REALIZADAS------------\n");
				if(compra.topo==NULL){
					printf("\nA lista de compras est� vazia\n");
				}else
					exibirPilha (&compra);
				
				printf("\n-----------------LISTA DE GONDOLAS-----------------------\n");
				
				for(gondola=0;gondola<MAX;gondola++){
					if(pil[gondola].topo==NULL)
					printf("\nA gondola %d est� vazia!\n", gondola);
					else{
						printf("\nGondola:  %d", gondola);
						exibirPilha (&(pil[gondola]));
					}
				}
				getch();
				break;
			
			case 6:										//-----------------------------------------------------CASE 6
				system("cls");
				printf("\n-------------LISTA DE USU�RIOS CADASTRADOS------------\n\n");
				imprimir_arquivo(leitura, &numero_linhas);				//ler_arquivo(Cadastro *leitura, int *numero_linhas)					
				getch();
				break;
				
			default:
				system("cls");
				printf("-----Op��o inv�lida, escolha a op��o correta!----\n");
				getch();
				system("cls");	
		}
	}while(opcao!=0);

//-----------------------EXCLUINDO PILHAS, LISTAS E ARQUIVO DA MEM�RIA---------------------------------------
	
	for(gondola=0;gondola<MAX;gondola++)					
		{
			reinicializarPilha(&pil[gondola]);
		}
	
	reinicializarPilha(&compra);
	reinicializarPilha(pil);
	
	reinicializarLista (&pdv);
	
	free(leitura);
	
	
	system("Pause");
	return(0);
}







//---------------------------------------------LISTA DE FUN��ES--------------------------------------------------------------------------------

void tela_menu()
{
	system("cls");
		printf("-------SISTEMA GERENCIADOR DE SUPERMERCADO-------\n");
		printf("\n\tMenu de op��es\n");
		printf("\n\t\t1. Abastecer G�ndolas");
		printf("\n\t\t2. Caixa/PDV");
		printf("\n\t\t3. Realizar uma compra");
		printf("\n\t\t4. Gerenciar usu�rios");
		printf("\n\t\t5. Listar gondulas e compras realizadas");
		printf("\n\t\t6. Listar usu�rios cadastrados");
		printf("\n\t\t0. Sair");
		printf("\n\nEscolha a op��o: ");
}


int busca_binaria(Cadastro *leitura, int *numero_linhas, Cadastro *usuario)			//FUN��O BUSCA BIN�RIA
{
	int posicao_inicial=0, tamanho_vetor=*numero_linhas-1, media;
	
	while(tamanho_vetor>=posicao_inicial)
	{
		media=(posicao_inicial+tamanho_vetor)/2;						
		if(strcmp(leitura[media].nome, usuario[0].nome)==0)
		{
			if(strcmp(leitura[media].prontuario, usuario[0].prontuario)==0)
			{
				return media;
			}
		}
		if(strcmp(leitura[media].nome, usuario[0].nome)>0)
		{
			tamanho_vetor=media-1;
		}else
		{
			posicao_inicial=media+1;
		}
	}
	return -1;
}

void ordenar_arquivo(Cadastro *leitura, int *numero_linhas)				//FUN��O ORDENAR ARQUIVOS
{
	int i, j;
	Cadastro tmp;
	
	for(i = 0; i < *numero_linhas-1; i++)
  	{
		for(j = i+1; j < *numero_linhas; j++)
   		{
   			if(strcmp(leitura[j].nome, leitura[i].nome)<0)
		    {
		    	
				strcpy(tmp.nome, leitura[i].nome);
				strcpy(tmp.prontuario, leitura[i].prontuario);
			     
				strcpy(leitura[i].nome, leitura[j].nome);
				strcpy(leitura[i].prontuario, leitura[j].prontuario);
			     
				strcpy(leitura[j].nome, tmp.nome);
				strcpy(leitura[j].prontuario, tmp.prontuario);
		    }
		}
 	}
}

long tamanho_arquivo()												//FUN��O TAMANHO ARQUIVO
{
	FILE *file;
	long tamanho;
	
	file=fopen("USUARIOS.DAT", "rb");
	
	if(file==NULL)
	{
		printf("ARQUIVO USUARIOS.DAT INEXISTENTE!");
		system("Pause");
		exit(0);
	}else
	{
		fseek(file, 0, SEEK_END);
		tamanho=ftell(file);
	}
	fclose(file);
	return tamanho;
}

void ler_arquivo(Cadastro *leitura, int *numero_linhas)									//esta fun��o l� o arquivo e escreve todos os usu�rios cadastrados
{
	FILE *file;
	Cadastro cadastro;
	int i=0;
	file=fopen("USUARIOS.DAT", "rb");
	
	if(file==NULL)
	{
		printf("ARQUIVO USUARIOS.DAT INEXISTENTE!");
		system("Pause");
		exit(0);
	}
	

	while(fread(&cadastro, sizeof(Cadastro), 1, file)==1)					
	{		
		strcpy(leitura[i].nome, cadastro.nome);
		strcpy(leitura[i].prontuario, cadastro.prontuario);
		i++;
	}
	*numero_linhas=i;
	
	fclose(file);
}

void imprimir_arquivo(Cadastro *leitura, int *numero_linhas)				//FUN��O ORDENAR ARQUIVOS
{
	int i;
	
	for(i = 0; i < *numero_linhas-1; i++)
  	{
  		printf("\nNome: %s	- 	Prontu�rio: %s", leitura[i].nome, leitura[i].prontuario);
 	}
}

void login(Cadastro *leitura, int *numero_linhas, Cadastro *usuario, int *logado)				//FUN��O REALIZA LOGIN
{
	int n=2;
	
	do
	{
		//system("color 10");
		//system("mode 75, 10");
		
		printf("\n\n\tNOME DO USU�RIO: ");
		fflush(stdin);
		gets(usuario[0].nome);
		printf("\n\n\tPRONTU�RIO DO USU�RIO: ");
		fflush(stdin);
		gets(usuario[0].prontuario);
		system("cls");
	
		if(busca_binaria(leitura, numero_linhas, usuario)==-1)
		{
			//system("color C0");
			//system("mode 50, 10");
			printf("\n\n\tUsu�rio e/ou prontu�rio inv�lido!\n");
			printf("\n\tVoc� possui somente %d tentativa(s)", n);
			if(n==0){
				printf("\n\n\tO sistema ser� fechado!\n\n");
				getch();
				exit(0);
			}
		}else
		{
			printf("\n\n\tParab�ns! Login efetuado com sucesso!\n");
			*logado=1;
			n=-1;
		}
		n--;
		getch();
	}while(n>=0);
	system("cls");
}

int espaco_memoria()		//malloc como deve ficar a tela
{
	//system("mode 55, 10");
	//system("color 04");
	printf("\n\n\n\t\tCalloc devolveu NULL!\n");
	getch();
	return 0;
}

void salvar_escrever_arquivo()
{
	system("cls");
	FILE *file;
	Cadastro cadastro;
	int sair=5;
	file=fopen("USUARIOS.DAT", "a");
	if(file==NULL)
	{
		//system ("color 40");
		//system ("mode 55, 10");
		system ("cls");
		printf("ARQUIVO USUARIOS.DAT INEXISTENTE!\n");
		system("Pause");
		exit(0);
	}
	
	printf("Deseja cadastrar um novo usu�rio?\n");
	printf("- Digite 1 para o cadastro:\n");
	printf("- Digite 0 para sair:\n");
	fflush(stdin);
	scanf("%d", &sair);
	
	while(sair!=0)											// escreve a struct func no arquivo
	{	
		system("cls");
		printf("Digite o nome: ");
		fflush(stdin);
		gets(cadastro.nome);
		printf("Digite o prontu�rio: ");
		fflush(stdin);
		gets(cadastro.prontuario);
		system("cls");
		printf("Deseja cadastrar um novo usu�rio?\n");
		printf("- Digite 1 para o cadastro:\n");
		printf("- Digite 0 para sair:\n");
		fflush(stdin);
		scanf("%d", &sair);
		fwrite(&cadastro, sizeof(Cadastro), 1, file);
	}
	fclose(file);
	system("cls");
}

void cadastrar_produto_gondola(int *gondola, PILHA *pil)				
{
		
	for(*gondola=0;*gondola<MAX;*gondola++)
	{
		while(tamanho(&pil[*gondola])<5)
		{
			system ("cls");
			printf("\n----------CADASTRO DE PRODUTOS------------");
			printf ("\n-------------GONDOLA %d------------------", *gondola);
			printf("\nItem n�mero: %d\n", tamanho(&pil[*gondola])+1);
			insereNaPilha (&pil[*gondola]);
			getch();
			system ("cls");
		}
	}
}

void escolha_gondola(int *gondola)
{
	do
	{
		printf("\n\nEscolha o produto desejado(Digite o n�mero da gondola):");
		fflush(stdin);
		scanf("%d", &(*gondola));
		if(*gondola<0 || *gondola>MAX)
		{
			printf("\nVoc� digitou uma gondola que n�o existe, tente mais uma vez!");
			printf("\nPressione ENTER para continuar...");
			getch();
		}
	}while(*gondola<0 || *gondola>MAX);
}

/* 
Para inicializar uma pilha j� criada pelo usu�rio,  precisamos apenas acertar o valor do 
campo topo.
J� que o topo conter� o endere�o do elemento que est� no topo da pilha e apilha est� vazia,  
iniciaremos esse campo com valor NULL. 
*/
void inicializarPilha (PILHA* p)
{
  p->topo = NULL;
}

/* J� que n�o temos um campo com o n�mero de elementos na pilha, 
   precisaremos percorrer todos os elementos para contar quantos s�o.
*/
int tamanho (PILHA* p) 
{  
   PONT end = p->topo;  
   int tam = 0;
   while (end != NULL) 
   {  
      tam++;
      end = end->PROX;
   }  
   return tam;
}

/* Se topo est�  armazenando o endere�o NULL, significa que a pilha est� vazia. */
bool estaVazia(PILHA* p) 
{
	if (p->topo == NULL) 
      return true;
	else  
   return false;
}

/* Para exibir os elementos da estrutura precisaremos  percorrer os elementos
(iniciando pelo elemento do topo da pilha) e, por exemplo, imprimir suas chaves. */
void exibirPilha (PILHA* p) 
{  
   PONT end = p->topo;  
   printf("\nPilha de produtos: ");  
   while (end != NULL) 
   {
		printf("\nNome: %s - Descri��o: %s - Peso(gramas): %.2f - Pre�o(R$): %.2f", end->reg.nome, end->reg.descricao, end->reg.peso, end->reg.preco);  
		end = end->PROX;
   }
   printf("\n");
}
/* 
Inser��o de um elemento (push)
O usu�rio passa como par�metro um registro a ser inserido na pilha
O elemento ser� inserido no topo da pilha, ou  melhor, 
�acima� do elemento que est� no topo da  pilha.
O novo elemento ir� apontar para o elemento que estava no topo da pilha
*/
bool inserirElemPilha(PILHA* p, REGISTRO reg) 
{  
   PONT novo  = (PONT) malloc(sizeof(ELEMENTO));  
   novo->reg  = reg;
   novo->PROX = p->topo;  
   p->topo    = novo;  
   return true;
}

/*
Exclus�o de um elemento (pop)
O usu�rio solicita a exclus�o do elemento do topo da pilha:
Se a pilha n�o estiver vazia, al�m de excluir esse elemento da pilha 
iremos copi�-lo para um local indicado pelo usu�rio.
0*/
bool excluirElemPilha(PILHA* p, REGISTRO* reg) 
{  
   if ( p->topo == NULL) 
      return false;
   *reg        = p->topo->reg;  
   PONT apagar = p->topo;
   p->topo     = apagar->PROX; 
   free(apagar);
   return true;
}
/* 
S� tem sentido, se a pilha foi inicializada alguma vez.
Para reinicializar a pilha, precisamos excluir todos os seus elementos 
e colocar NULL no campo topo 
*/
void reinicializarPilha (PILHA* p) 
{  
   PONT apagar;
   PONT posicao = p->topo;  
   while (posicao != NULL) 
   {
      apagar  = posicao;  
      posicao = posicao->PROX;  
      free(apagar);
   }
}

/*------------------*/
/* Fun��es de apoio */
/*------------------*/
REGISTRO oqueInserir ()
{	REGISTRO r;
	printf ("\nNome: "); fflush (stdin); gets(r.nome);
	printf ("\nDescri��o: "); fflush (stdin); gets(r.descricao);
	printf ("\nPeso(gramas): "); fflush (stdin); scanf("%f", &r.peso);
	printf ("\nPre�o(R$): "); fflush (stdin); scanf("%f", &r.preco);
	return r;
}

void insereNaPilha (PILHA* p)
{
	REGISTRO	elem;
	elem  = oqueInserir();						//esta fun�ao retorna o registro dos dados
	if ( inserirElemPilha(p, elem) == true )
	   printf ("\nItem inserido com sucesso.");
	else
	   printf ("\nItem NAO inserido!");
}

void excluiDaPilha (PILHA* p) 
{	REGISTRO regExcluido;
 	if ( excluirElemPilha(p, &regExcluido) == true )
 	printf("");
	else
	   printf ("\nNao foi possivel excluir o item.");
}
//-------------------------------------------------
REGISTRO realizarCompra(PILHA* p)				//fun��o para utilizar na realiza��o da compra e passagem para a lista
{
	PONT end = p->topo;
	REGISTRO r;
	
	strcpy(r.nome, end->reg.nome);
	strcpy(r.descricao, end->reg.descricao);
	r.peso=end->reg.peso;
	r.preco=end->reg.preco;
	return r;
}																	//insereNaPilha_Compra (&(pil[gondola]), &compra);	

void insereNaPilha_Compra (PILHA* p, PILHA* c)
{
	REGISTRO	elem;
	elem  = realizarCompra(p);						//esta fun�ao retorna o registro dos dados
	if ( inserirElemPilha(c, elem) == true )
	   printf ("\nItem inserido com sucesso.");
	else
	   printf ("\nItem NAO inserido!");
}

/* ----------------------- Rotinas de gerenciamento da lista -------------------------------- */

/* A lista apontar� para NULL (n�o h� elementos na lista) */
void inicializarLista (LISTA* l)
{
  l->inicio = NULL;
}

/* Iremos percorrer todos os elementos da lista e mostra-los na tela */
void exibirLista (LISTA* l)
{  
   PONT end = l->inicio;  
   system ("cls");
   printf("\nLista de produtos:  ");  
   while (end != NULL) 
   {
		printf("\nNome: %s - Descri��o: %s - Peso(gramas): %.2f - Pre�o(R$): %.2f", end->reg.nome, end->reg.descricao, end->reg.peso, end->reg.preco);  
		end = end->PROX;
   }
   printf("\"\n");
}

void reinicializarLista (LISTA* l) 
{  
    PONT apagar;
	PONT end = l->inicio;    /* end aponta para o in�cio da lista   */
	while (end != NULL)      /* enquanto n�o for o final da lista...*/
	{  
		apagar 	= end;       /* ...o ponteiro apagar aponta para o end... */
		end 	= end->PROX; /* ...end aponta para o pr�ximo da lista...  */ 
		free(apagar);        /* ...e libera e mem�ria ocupada pelo apagar */
	}                        /* Ap�s liberar toda a mem�ria ocupada pela lista...*/
	l->inicio = NULL;        /*...faz o inicio apontar para NULL (lista vazia)*/
}

void inserirElemLista( LISTA* l, PILHA* p) 
{
	REGISTRO r;
	PONT end = p->topo;  
	
	while (end != NULL) 
	{  
		strcpy(r.nome, end->reg.nome);
		strcpy(r.descricao, end->reg.descricao);
		r.peso=end->reg.peso;
		r.preco=end->reg.preco;
	
		PONT i = (PONT) malloc(sizeof(ELEMENTO));
		i->reg = r;
		i->PROX=l->inicio;
		l->inicio=i;
	
		end = end->PROX;
	}
}

void ValorCompra (LISTA* l)
{
	
	float total=0;
	PONT end = l->inicio;  
	
	while (end != NULL) 
	{
		total=total+end->reg.preco;
		
		end = end->PROX;
	}
	printf("\n\n\nValor total da compra:  %.2f", total);  
	printf("\"\n");
}
