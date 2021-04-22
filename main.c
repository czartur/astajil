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
        printf("%d | %s | %s\n", p->codigo, p->nome, p->professor);
}
dis* encontraDisciplina(int codigo, dis* head){
    dis* p = head;
    while(p && p->codigo != codigo) p=p->next;
    return p;
}
void verDisciplina(dis* head){
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
    /*
    for(int i=1; i<=(aux->qtd); i++){
        dis* auxDis = encontraDisciplina((aux->disciplinas)[i-1], headDis);
        printf("(%d) %s\n", i, auxDis->nome); 
    } 
    */
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
    insereDisciplina(nova, &(auxAlu->disciplinas));
}


void removeDisciplina(int codigo, dis** head, alu** headAlu){
    dis *p = *head, *prev=NULL; 
    while(p && p->codigo != codigo){
        prev=p; 
        p=p->next; 
    }
    if(p == NULL) return;
    (prev == NULL) ? *head=p->next : prev->next=p->next;

    //passar em cada aluno para deslinkar

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
    ans[0]=eval%10 + '0'; eval/=10;
    ans[1]='.';
    for(int i=2; i<6; i++) {ans[i] = eval%10 + '0'; eval/=10;}
    ans[6]='\0';
    return ans; 
}
void loadData(FILE **ptr, float per, alu** headAlu, dis** headDis){
    *ptr = fopen(perString(per), "r");
    char tipo;
    while(fscanf(*ptr, " %c", &tipo) !=EOF){
        if(tipo == 'D'){
            dis* nova = (dis*) malloc(sizeof(dis));
            nova->next = NULL;
            fscanf(*ptr, "%d %s %s %d", &(nova->codigo), nova->nome, nova->professor, &(nova->creditos));
        }
    }
}


int menuPrincipal();
int menuCadastros(alu**, dis**);
int menuConsultas(alu**, dis**);

void wait(){
    printf("press anything to continue...");
    fflush(stdin);
    fgetc(stdin);
    getchar();
}

int main(){
    FILE *ptr;
    alu* headAlu = NULL;
    dis* headDis = NULL;
    while(true){
        int level=0;
        system("clear");
        printf("Carregar Período (ex 2021.1) // 0 para sair\n");
        float per;
        scanf("%f", &per);
        if(per==0) break;
        
        //loadData(&ptr, per, &headAlu, &headDis);

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
                //save data
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
            removeDisciplina(codigo, headDis, headAlu);
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
            verDisciplina(*headDis);
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

//período (data base archive)
//Disciplinas nos alunos
 
//Main MENU
//0. Escolha um período >>

//1. Cadastros
//1.1 Inserir Aluno
//1.2 Inserir Disciplina
//1.3 Linkar Aluno e Disciplina

//2. Consultas
//2.1 Ver disciplina
//2.2 Ver aluno
//2.3 List ALL  

//3. Wipe data

