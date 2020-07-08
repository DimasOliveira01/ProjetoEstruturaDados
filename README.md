
============PROJETO DA DISCIPLINA DE ESTRUTURA DE DADOS================

Para que o executável do programa funcione é necessário baixar os seguintes arquivos:
- USUARIOS.DAT
- ProjetoEstruturaDados.exe 
Após baixar este 2 arquivos é necessário deixá-los na mesma pasta ou diretório para executar o programa.

=> Caso deseje visualizar o código na Linguagem C é necessário baixar somente o arquivo ProjetoEstruturaDados.c


=> Objetivo do projeto
Realizar um programa na Linguagem C, no qual existam as seguintes estruturas de dados:
 - Arquivos
 - Struct
 - Ordenação
 - Busca binária
 - Estrutura de pilha
 - Estrutura de fila

-> Etapa1: Login de acesso:

1. Ao iniciar a execução, exibir uma tela de login para que o usuário informe seu nome e prontuário.
1.1 De modo a garantir o controle de acesso ao sistema, os usuários e respectivos prontuários deverão estar
cadastrados no arquivo USUARIOS.DAT, mantidos SEMPRE EM ORDEM CRESCENTE DE NOMES.
1.2 Para tanto, seu projeto deve possuir um programa que cadastre estes dados (nome e prontuário) em
USUARIOS.DAT.
1.3 Assim, o programa de cadastro deverá assegurar que, pelo menos, os usuários abaixo listados estejam em
USUARIOS.DAT (cadastro padrão).
ALINE FIRMINO BRITO 				SP230285
DOMINGOS LUCAS LATORRE DE OLIVEIRA 		CJ146456
RODRIGO RIBEIRO DE OLIVEIRA 			RG134168
ANDRE LUIZ DA SILVA 				SP030028
CLAUDIA MIYUKI WERHMULLER 			SP030041
CLAUDETE DE OLIVEIRA ALVES 			SP03020X
FRANCISCO VERÍSSIMO LUCIANO 			SP030247
LUK CHO MAN 					SP060380
IVAN FRANCOLIN MARTINEZ 			SP060835
JOAO VIANEI TAMANINI 				SP060914
JOSE OSCAR MACHADO ALEXANDRE 			SP070038
JOSE BRAZ DE ARAUJO 				SP070385
PAULO ROBERTO DE ABREU 				SP070816
EURIDES BALBINO 				SP07102X
DOMINGOS BERNARDO GOMES SANTOS 			SP090888
ANDRE EVANDRO LOURENCO 				SP100092
MIGUEL ANGELO TANCREDI MOLINA 			SP102763
ANTONIO AIRTON PALADINO 			SP112197
JOSCELI MARIA TENORIO 				SP124382
LUIS FERNANDO AIRES BRANCO MENEGUETI 		SP141008
LEANDRO PINTO SANTANA 				SP144381
ANTONIO FERREIRA VIANA 				SP200827
LEONARDO BERTHOLDO 				SP204973
MARCELO TAVARES DE SANTANA 			SP20500X
DANIEL MARQUES GOMES DE MORAIS 			SP220097
ALEXANDRE BELETTI FERREIRA 			SP226117
ANSELMO DE ARAUJO COUTO 			SP232956
WILLIAM TAKAHIRO MARUYAMA 			SP233250
GUSTAVO MOLINA FIGUEIREDO 			SP23378X
PAULO ANDRE ZAPPAROLI 				SP236020
THIAGO DE NOVAES FRANCA 			SP236172
JOSE RONALDO DA SILVA JUNIOR 			SP3013197
MATHEUS CASAGRANDE 				SP3013944
CAIO ALENCAR MARCELLI SANTOS 			SP3017052
FERNANDO DE SOUSA SILVA 			SP3017061
GAWAN AUGUSTO GOMES FERREIRA 			SP302170X
RAFAEL DOS SANTOS FERREIRA 			SP3021734
CEZAR AUGUSTO DE NORONHA NAJJARIAN BATISTA 	SP3022552
LUIS FERNANDO ROCA KILZER 			SP3023109
PEDRO HENRIQUE SILVA DOS SANTOS 		SP3023176
FABIO MENDES TORRES 				SP3023184
ADRIANO RASPANTE SUARES 			SP3023231
BRUNNO PAPIS GUSMAO 				SP3024148
RENAN COELHO SANTOS 				SP3024156
LARISSA GUILGER DE PROENCA 			SP3024202
LINEKER EVANGELISTA DA SILVA 			SP3024253
CAMILA LOPEZ FRANQUEIRA DE FRANCA 		SP302427X
GUSTAVO DA COSTA SOUZA SILVA 			SP3024296
MARIVALDO TORRES JUNIOR 			SP3024792
LETICIA BRITO DOS SANTOS 			SP3026582
LEANDRO SAMPAIO PEREIRA 			SP3026591
GABRIELA VIANA BILINSKI 			SP3026868
CAROLINA DE MORAES JOSEPHIK 			SP3030571
DIMAS DE OLIVEIRA 				SP3030598
JOAO VICTOR TEIXEIRA DE OLIVEIRA 		SP3030644
LUCAS AMBROZIN GALLO 				SP3030661
MARIANA DA SILVA ZANGROSSI 			SP3030679
MATHEUS AUGUSTO DO NASCIMENTO DIAS 		SP3030687
BRUNA RODRIGUES DE OLIVEIRA 			SP3031853
JULIANA MACEDO SANTIAGO 			SP3032337
EDUARDO VIVI DE ARAUJO 				SP303240X
CESAR LOPES FERNANDES 				SP890534

1.4 Adicionalmente, seu programa de cadastro de usuários deverá permitir opcionalmente que seja cadastrado um
novo usuário, sempre garantindo que, após a inclusão, o arquivo USUARIOS.DAT permaneça em ordem
crescente de nomes.
1.5 OBSERVAÇÕES:
1.5.1 Você(s) deve(m) definir o layout do registro do usuário;
1.5.2 É IMPRESCINDÍVEL que seja usada uma função para ordenação dos usuários em ordem crescente de
nomes (para que os mesmos sejam gravados nesta ordem em USUARIOS.DAT);
1.5.3 É IMPRESCINDÍVEL que a validação do acesso ao sistema ocorra utilizando uma função de busca binária
baseada nos dados do arquivo USUARIOS.DAT.
1.5.4 Usar alocação dinâmica para efetuar a busca binária. Caso ocorra erro nesta alocação, o sistema deverá
apresentar a seguinte tela com a respectiva mensagem de erro e finalizar a execução.

2. Caso o nome e/ou prontuário do usuário não estejam cadastrados em USUARIOS.DAT, o sistema deverá
apresentar a seguinte tela com a respectiva mensagem de erro e finalizar a execução.
3. Caso o arquivo USUARIOS.DAT não seja localizado no momento do login, o sistema deverá apresentar a seguinte
tela com a respectiva mensagem de erro e finalizar a execução
4. Caso o login seja validado, o sistema deverá apresentar a seguinte tela com o menu de opções, que deverá
permanecer em looping até que seja selecionada a opção [0 = SAIR], com os seguintes itens:
 - Abastecer Gôndolas
 - Caixa/PDV
 - Realizar uma compra
 - Gerenciar usuários
 - Listar gôndolas e compras realizadas
 - Listar usuários cadastrados
 - Sair



-> Etapa2: Abastecimento de Gôndolas:

1. Para implementar esta etapa você deverá utilizar obrigatoriamente a estrutura de dados denominada
PILHA. A sua implementação poderá ser estática (vetor) ou dinâmica (lista encadeada)
2. Todas as manhãs, os repositores abastecem as gôndolas do supermercado com produtos respeitando um
estrutura similar a uma Pilha de Dados. Lembrando que em uma PILHA, o último produto inserido será o
primeiro a ser retirado (Last In – First Out).
3. Você deverá criar pelo menos 10 pilhas, onde cada pilha representa uma prateleira de uma gôndola do
supermercado. Cada prateleira tem capacidade para 5 itens. Cada item possui um nome, uma descrição,
seu peso e preço.
4. Somente o repositor (usuário master) poderá inserir itens nas prateleiras. O sistema deverá emitir um
alerta se a prateleira estiver cheia ou se a mesma estiver vazia.
5. A retirada de produtos da prateleira será sempre feita pelo usuário comum que irá retirar o produto e
colocar em um carrinho de compras. Este carrinho de compras também é implementado como uma pilha.
6. Sempre que precisar, o repositor, poderá visualizar quais produtos estão em cada gôndola, assim como a
quantidade de itens.



-> Etapa3: Caixa/PDV:

1. Uma vez que o cliente já escolheu os seus produtos, o mesmo deverá se dirigir até um PDV (Ponto de venda
- do inglês Point of Sale – POS).
2. Para o PDV, você deverá utilizar uma estrutura de dados denominada FILA, onde o primeiro produto
inserido, será o primeiro produto a ser processado (Fist In – First Out).
3. A esteira do PDV é uma estrutura do tipo FILA, onde cada produto retirado do carrinho (lembrando que o
carrinho está implementado como uma PILHA) entra na esteira para que o mesmo seja contabilizado para
gerar o valor a pagar.
4. A esteira é automática e conforme os produtos são colocados sobre ela, a mesma vai lendo os dados dos
itens, uma a um, respeitando o processamento por FILA e gerando o cupom fiscal com o valor final a pagar.
7. O cupom fiscal gerado deverá ser apresentado na tela ao final do processamento. Deverá mostrar a ordem
de processamento com nome, uma descrição, seu peso e preço.





