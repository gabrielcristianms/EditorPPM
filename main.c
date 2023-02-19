#include "img.h"
#include <stdio.h>
#include <string.h>

int main(){
	//"img" é uma variável do tipo imagem que recebe os valores do arquivo que vai ser lido
	//"img_temp" é a variável do tipo imagem que irá sofrer as transformações.
	//"acao' é um array de no máximo 4 char. É utilizado para os testes condicionais que definem qual ação será executada
	//"flag_exit" é um inteiro que é inicializado em zero, e que dependendendo de um comando do usuário, é setado em '1', finalizando o loop principal
	//'n' é um inteiro que será lido da entrada padrão. Será utilizado pelas funções recursivas.
	//'i' e 'c' são contadores, o primeiro para o for que irá percorrer o array "acao"
	//e o último para contar quantos desses caracteres são diferentes de \0.
	Imagem img, img_temp;
	char acao[4];
	int flag_exit = 0, n, i, c = 0;

	//Imprime as boas vindas
	//Executa a função de abrir imagens
	//Executa a função de copiar imagens. Isso garante que "img_temp" seja inicializada, evitando problemas de desalocamento de memória caso nenhuma
	//transformação seja feita.
	printf("Bem vindo ao editor de imagem ITP-PTP 2015.2\n");
	open_img(&img);
	copy_img(&img, &img_temp);

	//Loop principal do programa, permitindo que o usuário execute diversas ações de processamento de imagem
	do{
		//Imprime o menu, mostrando todas a ações permitidas e lê dá entrada padrão
		printf("Os seguintes comandos estao disponiveis:\n");
		printf("|--------------------------------------------|\n->blu(borra a imagem)\n->sha(aprimora as bordas)\n->bor(detecta as bordas)\n->thr(binariza a imagem)\n");
		printf("->amp(amplia a imagem)\n->red(reduz a imagem)\n->gry(transforma as cores em tons de cinza)\n->rot(rotaciona a imagem)\n->ext(encerra a aplicacao)\n->sav(salva uma imagem)\n->ope(abre uma imagem)\n");
		printf("|--------------------------------------------|\n");
		gets(acao);

		//Percorre o array de char para contar quantos caracteres são diferentes de \0.
		for(i = 0; i < 4; i++){
			if(acao[i] != '\0')
				c++;
		}
		
		//Teste para saber se o usuário digitou um comando de 3 caracteres, se sim executa as comparações com os comandos disponíveis, senão diz que
		//o comando é inválido e o usuário irá digitar novamente.
		if(c == 3){
			//Compara se "acao" é igual ao comando de Blurring. Se sim chama a função que aplica filtros
			//passando o endereço de img, o endereço de img_temp e BLUR como tipo de filtro.
			if(strcmp(acao, "blu") == 0 || strcmp(acao, "BLU") == 0 ){
				img_filter(&img, &img_temp, BLUR);
				printf("Filtro aplicado com sucesso!\n\n");
			}
			//Compara se "acao" é igual ao comando de Sharpening. Se sim chama a função que aplica filtros
			//passando o endereço de img, o endereço de img_temp e SHARP como tipo de filtro.
			if(strcmp(acao, "sha") == 0 || strcmp(acao, "SHA") == 0 ){
				img_filter(&img, &img_temp, SHARP);
				printf("Filtro aplicado com sucesso!\n\n");

			}
			//Compara se "acao' é igual ao comando de Detecção de Borda. Se sim chama a função que aplica filtros
			//passando o endereço de img, o endereço de img_temp e BORDA como tipo de filtro.
			if(strcmp(acao, "bor") == 0 || strcmp(acao, "BOR") == 0 ){
				img_filter(&img, &img_temp, BORDA);
				printf("Filtro aplicado com sucesso!\n\n");
			}
			//Compara se "acao" é igual ao comando de Binarização. Se sim chama a função que aplica a Binarização.
			if(strcmp(acao, "thr") == 0 || strcmp(acao, "THR") == 0 ){
				img_bin(&img, &img_temp);
				printf("Filtro aplicado com sucesso!\n\n");
			}
			//Compara se "acao" é igual ao comando de Ampliar. Se sim chama a função que aplica a Amplificação n vezes.
			if(strcmp(acao, "amp") == 0 || strcmp(acao, "AMP") == 0 ){
				printf("Digite o numero de vezes que a imagem sera ampliada:\n");
				scanf("%i", &n);
				getchar();
				if(n != 0){
					amp_rec(&img, &img_temp, n);
					printf("Filtro aplicado com sucesso!\n\n");
				}
			}
			//Compara se "acao" é igual ao comando de Reduzir. Se sim chama a função que aplica a Redução n vezes.
			if(strcmp(acao, "red") == 0 || strcmp(acao, "RED") == 0 ){
				printf("Digite o numero de vezes que a imagem sera reduzida:\n");
				scanf("%i", &n);
				getchar();
				if(n != 0){
					reduc_rec(&img, &img_temp, n);
					printf("Filtro aplicado com sucesso!\n\n");
				}
			}
			//Compara se "acao" é igual ao comando de Escala de Cinza. Se sim chama a função que aplica a Escala de Cinza na imagem.
			if(strcmp(acao, "gry") == 0 || strcmp(acao, "GRY") == 0 ){
				img_gray(&img, &img_temp);
				printf("Filtro aplicado com sucesso!\n\n");
			}
			//Compara se "acao" é igual ao comando de Rotacionar. Se sim chama a função que aplica a Rotação n vezes, sendo n sempre um valor entre 0 e 3.
			if(strcmp(acao, "rot") == 0 || strcmp(acao, "ROT") == 0 ){
				printf("Digite o angulo de rotacao (multiplos de 90):\n");
				scanf("%i", &n);
				getchar();
				n = n / 90;
				n = n % 4;
				if(n != 0)
					rotate_rec(&img, &img_temp, n);
				printf("Filtro aplicado com sucesso!\n\n");
			}
			//Compara se "acao" é igual ao comando de Abrir Arquivo. Se sim chama a função que abre arquivos.
			if(strcmp(acao, "ope") == 0 || strcmp(acao, "OPE") == 0 ){
				open_img(&img);
				copy_img(&img, &img_temp);
			}
			//Compara se "acao" é igual ao comando de Salvar Arquivo. Se sim chama a função que salva arquivos.
			if(strcmp(acao, "sav") == 0 || strcmp(acao, "SAV") == 0 ){
				save_img(&img);
			}
			//Compara se acao é igual ao comando de Sair. Se sim, "flag_exit" é atribuido o valor inteiro 1.
			if(strcmp(acao, "ext") == 0 || strcmp(acao, "EXT") == 0 ){
				flag_exit = 1;
				printf("O programa foi finalizado com sucesso!\n\n");
			}
		}
		else{
			printf("Comando invalido. Digite novamente\n\n");
		}
		c = 0;		
	}while(flag_exit == 0);
	//Função que desaloca a memória alocada dinamicamente em "img" e "img_temp".
	clear_img(&img);
	clear_img(&img_temp);
	return 0;
}