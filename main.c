#include <stdio.h>
#include <stdlib.h>

typedef struct Aluno alu;
typedef struct Disciplina dis;
typedef long long ll;

struct Disciplina {
    int codigo;
    char nome[30], professor[30];
    int creditos;

    struct Disciplina* next;
};

struct Aluno {
    int codigo;
    char nome[30], cpf[15];
    
    struct Disciplina* disciplinas;  

    struct Aluno* next;
};

void wait(){
    printf("press enter to continue...");
    fflush(stdin);
    fgetc(stdin);
    getchar();
}
//testes dos valores inseridos na disciplina
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


//Disciplina
dis* novaDisciplina(){
	int teste=0;
    dis* nova = (dis*) malloc(sizeof(dis));
    nova->next = NULL;
    while (!teste)
	{	
		printf("Codigo? (ex: 1234): ");
    	scanf("%d", &(nova->codigo));
    	teste=testaCodDis (nova->codigo);
    	if(!teste) printf("Código de disciplina inválido.\n");
	}
	printf("Nome? (ex Matematica): ");
    scanf(" %29[^\n]", nova->nome);
    printf("Professor? (ex Luiz): ");
    scanf(" %29[^\n]", nova->professor);
    while (teste)
    {
		printf("CrÃ©ditos? (ex 90): ");
    	scanf("%d", &(nova->creditos));
    	teste=testaCredDis(nova->creditos);
    	if(teste) printf("Valor dos Créditos inválido.\n");
	}
	return nova;
}
void insereDisciplina(dis* nova, dis** head){
    nova->next=*head;
    *head = nova;
}
void printaDisciplinas(dis* head){
    printf("#Disciplinas\n");
    for(dis *p=head; p!=NULL; p=p->next)
        printf("%d | %s\n", p->codigo, p->nome);
}
dis* encontraDisciplina(int codigo, dis* head){
    dis* p = head;
    while(p && p->codigo != codigo) p=p->next;
    return p;
}
void verDisciplina(dis* head, alu* headAlu){
    int codigo;
    printf("CÃ³digo?(ex 1432): ");
    scanf("%d", &codigo);
    dis* aux = encontraDisciplina(codigo, head);
    if(aux == NULL){
        printf("Disciplina nÃ£o encontrada!\n");
        return;
    }
    printf("Nome: %s\n", aux->nome);
    printf("Professor: %s\n", aux->professor);
    printf("CrÃ©ditos: %d\n", aux->creditos);
    printf("Alunos: \n");
    int cnt=0;
    for(alu* p = headAlu; p!=NULL; p=p->next){
        dis* aux=p->disciplinas;
        if(encontraDisciplina(codigo, aux))
            printf("(%d) %s\n", ++cnt, p->nome);
    }
}

//teste dos valores inseridos nos alunos
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


//Aluno
alu* novoAluno(){
    alu* ans = (alu*) malloc(sizeof(alu));
    ans->next = NULL;
    ans->disciplinas = NULL;
    int teste = 0;
    while (!teste)
    {
	    printf("CÃ³digo (ex 19401): ");
    	scanf("%d", &(ans->codigo));
		teste = testaCodAlu(ans->codigo);
		if(!teste) printf("Código do aluno inválido.\n");
	}
	printf("Nome (ex Almeida): ");
    scanf(" %29[^\n]", ans->nome);
    while (teste)
    {
    	printf("CPF (ex 09876543211): ");
    	scanf("%s", ans->cpf);
		teste = testaCPFAlu(ans->cpf);
		if (teste)printf("CPF inválido.\n");
	}
    return ans;
}
void insereAluno(alu* novo, alu** head){
    novo->next = *head;
    *head=novo; 
}
void printaAlunos(alu* head){
    printf("#Alunos\n");
    for(alu *p=head; p!=NULL; p=p->next)
        printf("%d | %s \n", p->codigo, p->nome);
}
alu* encontraAluno(int codigo, alu* head){
    alu* p = head;
    while(p && p->codigo != codigo) p=p->next;
    return p;
}
void verAluno(alu* head, dis* headDis){
    int codigo;
    printf("CÃ³digo?(ex 19004): ");
    scanf("%d", &codigo);
    alu* aux = encontraAluno(codigo, head);
    if(aux == NULL) {
        printf("Aluno nÃ£o encontrado!\n");
        return;
    }
    printf("Nome: %s\n", aux->nome);
    printf("CPF: %s\n", aux->cpf);
    printf("Disciplinas: \n");
    int cnt=0;
    for(dis* p = aux->disciplinas; p!=NULL; p=p->next)
        printf("(%d) %s\n", ++cnt, p->nome);
}

//link
void linkar(alu** headAlu, dis** headDis){
    int codigoAlu, codigoDis;
    printf("Codigo do Aluno? (ex 19006): ");
    scanf("%d", &codigoAlu);
    alu* auxAlu = encontraAluno(codigoAlu, *headAlu);
    if(auxAlu == NULL){
        printf("Aluno nÃ£o encontrado!\n");
        return; 
    }
    
    printf("Codigo da Disciplina? (ex 4321): ");
    scanf("%d", &codigoDis);
    dis* auxDis = encontraDisciplina(codigoDis, *headDis);
    if(auxDis == NULL){ 
        printf("Disciplina nÃ£o encontrada!\n");
        return; 
    }
    dis* nova = (dis*) malloc(sizeof(dis));
    *nova = *auxDis;
    nova->next = NULL;
    insereDisciplina(nova, &(auxAlu->disciplinas));
}

//remove#
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
void deslinkar(alu** headAlu){
	int codigoAlu, codigoDis;
    printf("Codigo do Aluno? (ex 19086): ");
    scanf("%d", &codigoAlu);
    alu* auxAlu = encontraAluno(codigoAlu, *headAlu);
    if(auxAlu == NULL){
        printf("Aluno nÃ£o encontrado!\n");
        return; 
    }
    printf("Codigo da Disciplina? (ex 4321): ");
    scanf("%d", &codigoDis);//falta testar a disciplina
    if (!(encontraDisciplina(codigoDis,auxAlu->disciplinas))) {
        printf("Disciplina nao relacionada ao aluno!\n");
        return;
    }
 	removeDisciplina(codigoDis, &(auxAlu->disciplinas));
}

int testaPer(char* per){
    int cnt=0;
    while(per[cnt]!='\0'){
        //printf("per[%d] = %c\n", cnt, per[cnt]);
        if(per[cnt] == '\0') break;
        if((cnt != 4) && (per[cnt]<'0' | per[cnt]>'9')) return 0;
        if((cnt == 4) && per[cnt]!='.') return 0;
        cnt++; 
    }
    if(cnt == 0 && per[0] == '0') return -1;
    return cnt == 6;
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
            fscanf(*ptr, "%d %s %s %d", &(nova->codigo), nova->nome, nova->professor, &(nova->creditos));
            //printf("\n%d\n%s\n%s\n%d\n\n", nova->codigo, nova->nome, nova->professor, nova->creditos);
            insereDisciplina(nova, headDis);
        }
        if(tipo == 'A'){
            alu* novo = (alu*) malloc(sizeof(alu));
            novo->next = NULL;
            novo->disciplinas = NULL;
            fscanf(*ptr, "%d %s %s", &(novo->codigo), novo->nome, novo->cpf);
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
        printf("Carregar PerÃ­odo (ex 2021.1)\n[0] para sair\n");
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
            deslinkar(headAlu);
        	break;
        case 5: 
            printf("CÃ³digo?(ex 19051): ");
            scanf("%d", &codigo);
            removeAluno(codigo, headAlu);
            break;
        case 6:
            printf("CÃ³digo?(ex 4123): ");
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
