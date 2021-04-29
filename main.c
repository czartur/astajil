#include <stdio.h>
#include <stdlib.h>


// Created by: César (19006) and Almeida (19047)
// Sinopse do código: 
//* Criamos uma lista de alunos e uma lista de disciplinas
//* Todos os dados são salvos e recuperados por período
//* Para tratar os links (matrículas) colocamos, em cada aluno, a lista de disciplinas que ele está matriculado
//* Para verificar quais alunos estão matriculados em uma disciplina passamos por cada aluno cadastrado
//  e verificamos se a disciplina em questão está na sua lista de disciplinas matriculadas

typedef struct Aluno alu;
typedef struct Disciplina dis;

struct Disciplina {
    int codigo;
    char nome[40], professor[30];
    int creditos;

    struct Disciplina* next;
};

struct Aluno {
    int codigo;
    char nome[30], cpf[15];
    
    struct Disciplina* disciplinas;  

    struct Aluno* next;
};

//wait for user input before cleaning terminal
void wait(){
    printf("press enter to continue...");
    fflush(stdin);
    fgetc(stdin);
    getchar();
}

//testing user inputint testaPer(char* per){
int testaPer(char* per){
    int cnt=0;
    while(per[cnt]!='\0'){
        //printf("per[%d] = %c\n", cnt, per[cnt]);
        if(per[cnt] == '\0') break;
        if((cnt != 4) && (per[cnt]<'0' | per[cnt]>'9')) return 0;
        if((cnt == 4) && per[cnt]!='.') return 0;
        cnt++; 
    }
    if(cnt == 1 && per[0] == '0') return -1;
    return cnt == 6;
}
int testaCodDis (int cod)
{
	if ((1000<=cod)&&(cod<=9999)) return 1;
	return 0;
}
int testaCredDis (int cred)
{
	if (cred>=0) return 0;
	return 1;
}
int testaCodAlu (int cod)
{
	if ((10000<=cod)&&(cod<=99999)) return 1;
	return 0;
}
int testaCPFAlu (char *cpf)
{
	int contador=0,i=0;
	for (i;cpf[i]!='\0';i++)
	{
		if (!((48<=cpf[i])&&(cpf[i]<=57))){
		//printf("\ncaractere invalido aqui\n");
		return 1;
		} 
		contador++;
		//printf("\ncontador %d\n",contador);
	}
	if (contador!=11) return 1;
	return 0;
}


// ##Disciplina##

// handle Disciplina input
dis* novaDisciplina(){
	int teste=0;
    dis* nova = (dis*) malloc(sizeof(dis));
    nova->next = NULL;
    while (!teste)
	{	
		printf("Codigo? (ex 1234): ");
    	scanf("%d", &(nova->codigo));
    	teste=testaCodDis (nova->codigo);
    	if(!teste) printf("Codigo de disciplina invalido.\n");
	}
	printf("Nome? (ex Laboratorio de Programaçao): ");
    scanf(" %39[^\n]", nova->nome);
    printf("Professor? (ex Julio Cesar): ");
    scanf(" %29[^\n]", nova->professor);
    while (teste)
    {
		printf("Créditos? (ex 90): ");
    	scanf("%d", &(nova->creditos));
    	teste=testaCredDis(nova->creditos);
    	if(teste) printf("Valor dos creditos invalido.\n");
	}
	return nova;
}
// add new Disciplina
void insereDisciplina(dis* nova, dis** head){
    nova->next=*head;
    *head = nova;
}
// show all Disciplinas
void printaDisciplinas(dis* head){
    printf("#Disciplinas\n");
    for(dis *p=head; p!=NULL; p=p->next)
        printf("%d | %s\n", p->codigo, p->nome);
}
// find Disciplina by code
dis* encontraDisciplina(int codigo, dis* head){
    dis* p = head;
    while(p && p->codigo != codigo) p=p->next;
    return p;
}
// show everything about a specific Disciplina
void verDisciplina(dis* head, alu* headAlu){
    int codigo;
    printf("Código?(ex 1234): ");
    scanf("%d", &codigo);
    dis* aux = encontraDisciplina(codigo, head);
    if(aux == NULL){
        printf("Disciplina não encontrada!\n");
        return;
    }
    printf("Nome: %s\n", aux->nome);
    printf("Professor: %s\n", aux->professor);
    printf("Créditos: %d\n", aux->creditos);
    printf("Alunos: \n");
    int cnt=0;
    for(alu* p = headAlu; p!=NULL; p=p->next){
        dis* aux=p->disciplinas;
        if(encontraDisciplina(codigo, aux))
            printf("(%d) %s\n", ++cnt, p->nome);
    }
}

// ##Aluno##

// handle Aluno input
alu* novoAluno(){
    alu* ans = (alu*) malloc(sizeof(alu));
    ans->next = NULL;
    ans->disciplinas = NULL;
    int teste = 0;
    while (!teste)
    {
	    printf("Código (ex 12345): ");
    	scanf("%d", &(ans->codigo));
		teste = testaCodAlu(ans->codigo);
		if(!teste) printf("Codigo do aluno invalido.\n");
	}
	printf("Nome (ex Fulano de Tal): ");
    scanf(" %29[^\n]", ans->nome);
    while (teste)
    {
    	printf("CPF (ex 09876543211): ");
    	scanf("%s", ans->cpf);
		teste = testaCPFAlu(ans->cpf);
		if (teste)printf("CPF invalido.\n");
	}
    return ans;
}
// add new Aluno
void insereAluno(alu* novo, alu** head){
    novo->next = *head;
    *head=novo; 
}
// show all Alunos
void printaAlunos(alu* head){
    printf("#Alunos\n");
    for(alu *p=head; p!=NULL; p=p->next)
        printf("%d | %s \n", p->codigo, p->nome);
}
// find Aluno by code
alu* encontraAluno(int codigo, alu* head){
    alu* p = head;
    while(p && p->codigo != codigo) p=p->next;
    return p;
}
// show everything about an Aluno
void verAluno(alu* head, dis* headDis){
    int codigo;
    printf("Código?(ex 12345): ");
    scanf("%d", &codigo);
    alu* aux = encontraAluno(codigo, head);
    if(aux == NULL) {
        printf("Aluno não encontrado!\n");
        return;
    }
    printf("Nome: %s\n", aux->nome);
    printf("CPF: %s\n", aux->cpf);
    printf("Disciplinas: \n");
    int cnt=0;
    for(dis* p = aux->disciplinas; p!=NULL; p=p->next)
        printf("(%d) %s\n", ++cnt, p->nome);
}

//link (add a Disciplina to an Aluno node)
void linkar(alu** headAlu, dis** headDis){
    int codigoAlu, codigoDis;
    printf("Codigo do Aluno? (ex 12345): ");
    scanf("%d", &codigoAlu);
    alu* auxAlu = encontraAluno(codigoAlu, *headAlu);
    if(auxAlu == NULL){
        printf("Aluno não encontrado!\n");
        return; 
    }
    
    printf("Codigo da Disciplina? (ex 1234): ");
    scanf("%d", &codigoDis);
    dis* auxDis = encontraDisciplina(codigoDis, *headDis);
    if(auxDis == NULL){ 
        printf("Disciplina não encontrada!\n");
        return; 
    }
    dis* nova = (dis*) malloc(sizeof(dis));
    *nova = *auxDis;
    nova->next = NULL;
    insereDisciplina(nova, &(auxAlu->disciplinas));
}

//remove&unlink functions 
void removeDisciplina(int codigo, dis** head){
    dis *p = *head, *prev=NULL; 
    while(p && p->codigo != codigo){
        prev=p; 
        p=p->next; 
    }
    if(p == NULL) return;
    (prev == NULL) ? *head=p->next : prev->next=p->next;
}
void removeAluno(int codigo, alu** head){
    alu *p = *head, *prev=NULL;
    while(p && p->codigo != codigo){
        prev=p; 
        p=p->next;
    }
    if(p == NULL) return;
    (prev == NULL) ? *head=p->next : prev->next=p->next;
}
void deslinkar(alu** headAlu, dis** headDis){
	int codigoAlu, codigoDis;
    printf("Codigo do Aluno? (ex 12345): ");
    scanf("%d", &codigoAlu);
    alu* auxAlu = encontraAluno(codigoAlu, *headAlu);
    if(auxAlu == NULL){
        printf("Aluno nao encontrado!\n");
        wait();
        return; 
    }
    printf("Codigo da Disciplina? (ex 1234): ");
    scanf("%d", &codigoDis);//falta testar a disciplina 
    if(!(encontraDisciplina(codigoDis, *headDis))){
        printf("Disciplina nao encontrada!\n");
        wait();
        return;
    }
    if (!(encontraDisciplina(codigoDis,auxAlu->disciplinas))) {
        printf("Disciplina nao relacionada ao aluno!\n");
        wait();
        return;
    }
 	removeDisciplina(codigoDis, &(auxAlu->disciplinas));
}


void readNomeComposto(FILE **ptr, char *nome, int lim){
    int cnt=0; 
    while(true){
        char c = fgetc(*ptr);
        if(c == '\n') break;
        nome[cnt++]=c;
        if(cnt == lim) {
            while(fgetc(*ptr)!='\n');
            break;
        }
    }
    nome[cnt] = '\0';
}
//load & save
void loadData(FILE **ptr, char* per, alu** headAlu, dis** headDis){
    *ptr = fopen(per, "r");
    if(*ptr == NULL) return;
    char tipo;
    while(fscanf(*ptr, " %c", &tipo) != EOF){
        if(tipo == 'D'){
            dis* nova = (dis*) malloc(sizeof(dis));
            nova->next = NULL;
            fscanf(*ptr, "%d", &(nova->codigo));
            fgetc(*ptr);
            readNomeComposto(ptr, nova->nome, 39);
            readNomeComposto(ptr, nova->professor, 29);
            fscanf(*ptr, "%d", &(nova->creditos));
            //printf("\n%d\n%s\n%s\n%d\n\n", nova->codigo, nova->nome, nova->professor, nova->creditos);
            insereDisciplina(nova, headDis);
        }
        if(tipo == 'A'){
            alu* novo = (alu*) malloc(sizeof(alu));
            novo->next = NULL;
            novo->disciplinas = NULL;
            fscanf(*ptr, "%d", &(novo->codigo));
            fgetc(*ptr);
            readNomeComposto(ptr, novo->nome, 29);
            fscanf(*ptr, "%s", novo->cpf);
            //printf("\n%d\n%s\n%s\n", novo->codigo, novo->nome, novo->cpf);
            int codigoDis; 
            while(fscanf(*ptr, "%d", &codigoDis)){
                if(codigoDis == 0) break;
                dis* nova = (dis*) malloc(sizeof(dis));
                *nova=*encontraDisciplina(codigoDis, *headDis);
                nova->next = NULL;
                insereDisciplina(nova, &(novo->disciplinas));
                //printf("%d ", codigoDis);
            }
            //printf("0\n\n");
            insereAluno(novo, headAlu);
        }
    }
    //wait();
    fclose(*ptr);
}
void saveData(FILE **ptr, char* per, alu** headAlu, dis** headDis){
    *ptr = fopen(per, "w+");
    for(dis* p = *headDis; p!=NULL; p=p->next){
        fprintf(*ptr, "D\n%d\n%s\n%s\n%d\n\n", p->codigo, p->nome, p->professor, p->creditos);
    }
    for(alu* p = *headAlu; p!=NULL; p=p->next){
        fprintf(*ptr, "A\n%d\n%s\n%s\n", p->codigo, p->nome, p->cpf);
        dis* aux = p->disciplinas;
        while(aux!=NULL){
            fprintf(*ptr, "%d ", aux->codigo);
            aux=aux->next;
        }
        fprintf(*ptr, "0\n\n");
    }
    fclose(*ptr);
}

// ##Menu##
int menuPrincipal();
int menuCadastros(alu**, dis**);
int menuConsultas(alu**, dis**);

int main(){
    while(true){
        FILE *ptr;
        alu* headAlu = NULL;
        dis* headDis = NULL;
        int level=0;
        system("clear");
        printf("Carregar Período (ex 2021.1)\n[0] para sair\n");
        char per[20];
        scanf("%s", per);
        if(testaPer(per) == -1) break;
        if(testaPer(per) == 0) {
            printf("Periodo invalido!\n");
            wait();
            continue;
        }
        loadData(&ptr, per, &headAlu, &headDis);

        level++;
        while(level>0){
            switch (menuPrincipal()){
            case 1:
                while(menuCadastros(&headAlu, &headDis));
                break;
            case 2:
                while(menuConsultas(&headAlu, &headDis));
                break;
            case 3:
                saveData(&ptr, per, &headAlu, &headDis);
                break;
            default:
                level--;
                break;
            }
        }
    }
}

int menuPrincipal(){
    int ans;
    system("clear");
    printf("1. Cadastros\n");
    printf("2. Consultas\n");
    printf("3. Salvar progresso\n");
    printf("0. Voltar\n\n");
    scanf("%d", &ans);
    return ans; 
}

int menuCadastros(alu **headAlu, dis **headDis){
    int ans, codigo;
    system("clear");
    printf("1. Inserir Aluno\n");
    printf("2. Inserir Disciplina\n");
    printf("3. Linkar Aluno e Disciplina\n");
    printf("4. Deslinkar Aluno e Disciplina\n");
    printf("5. Remover Aluno\n");
    printf("6. Remover Disciplina\n");
    printf("0. Voltar\n\n");
    scanf("%d", &ans);

    switch(ans){
        case 1: 
            insereAluno(novoAluno(), headAlu);
            break;
        case 2: 
            insereDisciplina(novaDisciplina(), headDis);
            break;
        case 3: 
            linkar(headAlu, headDis);
            break;
        case 4:
            deslinkar(headAlu, headDis);
        	break;
        case 5: 
            printf("Código?(ex 19051): ");
            scanf("%d", &codigo);
            removeAluno(codigo, headAlu);
            break;
        case 6:
            printf("Código?(ex 4123): ");
            scanf("%d", &codigo);
            removeDisciplina(codigo, headDis);
            for(alu* p=*headAlu; p!=NULL; p=p->next)
                removeDisciplina(codigo, &(p->disciplinas));
            break;
    }
    return ans;
}

int menuConsultas(alu **headAlu, dis **headDis){
    int ans;
    system("clear");
    printf("1. Ver Disciplina\n");
    printf("2. Ver Aluno\n");
    printf("3. list ALL\n");
    printf("0. Voltar\n\n");
    scanf("%d", &ans);
    switch(ans){
        case 1:
            verDisciplina(*headDis, *headAlu);
            printf("\n");
            break;
        case 2:
            verAluno(*headAlu, *headDis);
            printf("\n");
            break;
        case 3:
            printaAlunos(*headAlu);
            printf("\n");
            printaDisciplinas(*headDis);
            printf("\n");
            break; 
    }
    if(ans) wait();
    return ans;
}