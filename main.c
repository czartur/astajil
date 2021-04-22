#include <stdio.h>
#include <stdlib.h>

typedef struct Aluno alu;
typedef struct Disciplina dis;
typedef long long ll;

struct Disciplina {
    int codigo;
    char nome[20], professor[20];
    int creditos;

    struct Disciplina* next;
};
struct Aluno {
    int codigo;
    char nome[20], cpf[20];
    
    struct Disciplina* disciplinas;  

    struct Aluno* next;
};

void wait(){
    printf("press anything to continue...");
    fflush(stdin);
    fgetc(stdin);
    getchar();
}


dis* novaDisciplina(){
    dis* nova = (dis*) malloc(sizeof(dis));
    nova->next = NULL;
    printf("Codigo? (ex: 1234): ");
    scanf("%d", &(nova->codigo));
    printf("Nome? (ex Matematica): ");
    scanf("%s", nova->nome);
    printf("Professor? (ex Luiz): ");
    scanf("%s", nova->professor);
    printf("Créditos? (ex 90): ");
    scanf("%d", &(nova->creditos));
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
    printf("Código?(ex 1432): ");
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

alu* novoAluno(){
    alu* ans = (alu*) malloc(sizeof(alu));
    ans->next = NULL;
    ans->disciplinas = NULL;
    
    printf("Código (ex 19401): ");
    scanf("%d", &(ans->codigo));
    printf("Nome (ex Almeida): ");
    scanf("%s", ans->nome);
    printf("CPF (ex 09876543211): ");
    scanf("%s", ans->cpf);
    
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
    printf("Código?(ex 19004): ");
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


void linkar(alu** headAlu, dis** headDis){
    int codigoAlu, codigoDis;
    printf("Codigo do Aluno? (ex 19006): ");
    scanf("%d", &codigoAlu);
    alu* auxAlu = encontraAluno(codigoAlu, *headAlu);
    if(auxAlu == NULL){
        printf("Aluno não encontrado!\n");
        return; 
    }
    
    printf("Codigo da Disciplina? (ex 4321): ");
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

char* perString(float per){
    char *ans = (char*) malloc(7*sizeof(char));
    int eval = (int)10*per;
    ans[5]=eval%10 + '0'; eval/=10;
    ans[4]='.';
    for(int i=3; i>=0; i--) {ans[i] = eval%10 + '0'; eval/=10;}
    ans[6]='\0';
    return ans;
}

void loadData(FILE **ptr, float per, alu** headAlu, dis** headDis){
    *ptr = fopen(perString(per), "r");
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
void saveData(FILE **ptr, float per, alu** headAlu, dis** headDis){
    *ptr = fopen(perString(per), "w+");
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
        printf("Carregar Período (ex 2021.1)\n[0] para sair\n");
        float per;
        scanf("%f", &per);
        if(per==0) break;
        
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
    printf("4. Remover Aluno\n");
    printf("5. Remover Disciplina\n");
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
            printf("Código?(ex 19051): ");
            scanf("%d", &codigo);
            removeAluno(codigo, headAlu);
            break;
        case 5:
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