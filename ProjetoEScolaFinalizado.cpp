#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#define tamAlunos 3
#define tamProfessores 3
#define tamDisciplinas 3
#define maxAlunosPorDisciplina 3

// --- STRUCTS ---

struct Aluno {
    int matricula;
    char nome[50];
    char sexo;
    char dataNascimento[11];
    char cpf[15];
};

struct Professor {
    int matricula;
    char nome[50];
    char sexo;
    char dataNascimento[11];
    char cpf[15];
};

struct Disciplina {
    int codigo;
    char nome[50];
    int semestre;
    int matriculaProfessor; 
    int matriculasAlunos[maxAlunosPorDisciplina]; 
    int qtdAlunosMatriculados; 
};

// --- FUNÇÕES ---

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int validarSexo(char sexo) {
    if (sexo == 'M' || sexo == 'm' || sexo == 'F' || sexo == 'f') return 1;
    return 0;
}

int validarData(char data[]) {
    if (strlen(data) == 10) return 1;
    return 0;
}

int validarCPF(char cpf[]) {
    if (strlen(cpf) >= 11 && strlen(cpf) <= 14) return 1;
    return 0;
}

int compararDatas(char d1[], char d2[]) {
    int dia1, mes1, ano1;
    int dia2, mes2, ano2;
    sscanf(d1, "%2d/%2d/%4d", &dia1, &mes1, &ano1);
    sscanf(d2, "%2d/%2d/%4d", &dia2, &mes2, &ano2);

    if (ano1 != ano2) return ano1 - ano2;
    if (mes1 != mes2) return mes1 - mes2;
    return dia1 - dia2;
}

// Buscas
int buscarAlunoPorMatricula(struct Aluno lista[], int qtdAtual, int mat) {
    for (int i = 0; i < qtdAtual; i++) if (lista[i].matricula == mat) return i;
    return -1;
}

int buscarProfessorPorMatricula(struct Professor lista[], int qtdAtual, int mat) {
    for (int i = 0; i < qtdAtual; i++) if (lista[i].matricula == mat) return i;
    return -1;
}

int buscarDisciplinaPorCodigo(struct Disciplina lista[], int qtdAtual, int cod) {
    for (int i = 0; i < qtdAtual; i++) if (lista[i].codigo == cod) return i;
    return -1;
}


// --- MÓDULOS ALUNO, PROFESSOR E DISCIPLINA ---


int cadastrarAluno(struct Aluno lista[], int qtdAtual) {
    if (qtdAtual >= tamAlunos) { printf("\n[ERRO] Lista de Alunos Cheia!\n"); return qtdAtual; }
    printf("\n--- Incluir Novo Aluno ---\nMatricula: ");
    scanf("%d", &lista[qtdAtual].matricula); limparBuffer();
    if (lista[qtdAtual].matricula <= 0) return qtdAtual;
    if (buscarAlunoPorMatricula(lista, qtdAtual, lista[qtdAtual].matricula) != -1) { printf("[ERRO] Matricula ja existe!\n"); return qtdAtual; }
    printf("Nome: "); fgets(lista[qtdAtual].nome, 50, stdin); lista[qtdAtual].nome[strcspn(lista[qtdAtual].nome, "\n")] = 0;
    printf("Sexo (M/F): "); scanf("%c", &lista[qtdAtual].sexo); limparBuffer();
    printf("Nascimento (DD/MM/AAAA): "); fgets(lista[qtdAtual].dataNascimento, 11, stdin); limparBuffer(); lista[qtdAtual].dataNascimento[strcspn(lista[qtdAtual].dataNascimento, "\n")] = 0;
    printf("CPF: "); fgets(lista[qtdAtual].cpf, 15, stdin); lista[qtdAtual].cpf[strcspn(lista[qtdAtual].cpf, "\n")] = 0;
    printf("\n[SUCESSO] Aluno cadastrado!\n"); return qtdAtual + 1; 
}

void listarAlunos(struct Aluno lista[], int qtdAtual) {
    if (qtdAtual == 0) { printf("\nNenhum aluno cadastrado.\n"); return; }
    for (int i = 0; i < qtdAtual; i++) printf("Mat: %d | Nome: %s\n", lista[i].matricula, lista[i].nome);
}

void atualizarAluno(struct Aluno lista[], int qtdAtual) {
    if (qtdAtual == 0) return;
    int mat; printf("\nAtualizar - Digite a matricula: "); scanf("%d", &mat); limparBuffer();
    int idx = buscarAlunoPorMatricula(lista, qtdAtual, mat);
    if (idx == -1) { printf("[ERRO] Nao encontrado!\n"); return; }
    printf("Novo nome: "); fgets(lista[idx].nome, 50, stdin); lista[idx].nome[strcspn(lista[idx].nome, "\n")] = 0;
    printf("Novo sexo: "); scanf("%c", &lista[idx].sexo); limparBuffer();
    printf("Nova data: "); fgets(lista[idx].dataNascimento, 11, stdin); limparBuffer(); lista[idx].dataNascimento[strcspn(lista[idx].dataNascimento, "\n")] = 0;
    printf("Novo CPF: "); fgets(lista[idx].cpf, 15, stdin); lista[idx].cpf[strcspn(lista[idx].cpf, "\n")] = 0;
    printf("\n[SUCESSO] Atualizado!\n");
}

int excluirAluno(struct Aluno lista[], int qtdAtual) {
    if (qtdAtual == 0) return qtdAtual;
    int mat; printf("\nExcluir - Digite a matricula: "); scanf("%d", &mat); limparBuffer();
    int idx = buscarAlunoPorMatricula(lista, qtdAtual, mat);
    if (idx == -1) { printf("[ERRO] Nao encontrado!\n"); return qtdAtual; }
    for (int i = idx; i < qtdAtual - 1; i++) lista[i] = lista[i + 1];
    printf("\n[SUCESSO] Excluido!\n"); return qtdAtual - 1;
}

int cadastrarProfessor(struct Professor lista[], int qtdAtual) {
    if (qtdAtual >= tamProfessores) return qtdAtual;
    printf("\n--- Incluir Professor ---\nMatricula: "); scanf("%d", &lista[qtdAtual].matricula); limparBuffer();
    if (lista[qtdAtual].matricula <= 0 || buscarProfessorPorMatricula(lista, qtdAtual, lista[qtdAtual].matricula) != -1) return qtdAtual;
    printf("Nome: "); fgets(lista[qtdAtual].nome, 50, stdin); lista[qtdAtual].nome[strcspn(lista[qtdAtual].nome, "\n")] = 0;
    printf("Sexo (M/F): "); scanf("%c", &lista[qtdAtual].sexo); limparBuffer();
    printf("Nascimento (DD/MM/AAAA): "); fgets(lista[qtdAtual].dataNascimento, 11, stdin); limparBuffer(); lista[qtdAtual].dataNascimento[strcspn(lista[qtdAtual].dataNascimento, "\n")] = 0;
    printf("CPF: "); fgets(lista[qtdAtual].cpf, 15, stdin); lista[qtdAtual].cpf[strcspn(lista[qtdAtual].cpf, "\n")] = 0;
    printf("\n[SUCESSO] Professor cadastrado!\n"); return qtdAtual + 1; 
}

void listarProfessores(struct Professor lista[], int qtdAtual) {
    if (qtdAtual == 0) { printf("\nNenhum professor cadastrado.\n"); return; }
    for (int i = 0; i < qtdAtual; i++) printf("Mat: %d | Nome: %s\n", lista[i].matricula, lista[i].nome);
}

void atualizarProfessor(struct Professor lista[], int qtdAtual) {
    if (qtdAtual == 0) return;
    int mat; printf("\nAtualizar - Digite a matricula: "); scanf("%d", &mat); limparBuffer();
    int idx = buscarProfessorPorMatricula(lista, qtdAtual, mat);
    if (idx == -1) { printf("[ERRO] Nao encontrado!\n"); return; }
    printf("Novo nome: "); fgets(lista[idx].nome, 50, stdin); lista[idx].nome[strcspn(lista[idx].nome, "\n")] = 0;
    printf("Novo sexo: "); scanf("%c", &lista[idx].sexo); limparBuffer();
    printf("Nova data: "); fgets(lista[idx].dataNascimento, 11, stdin); limparBuffer(); lista[idx].dataNascimento[strcspn(lista[idx].dataNascimento, "\n")] = 0;
    printf("Novo CPF: "); fgets(lista[idx].cpf, 15, stdin); lista[idx].cpf[strcspn(lista[idx].cpf, "\n")] = 0;
    printf("\n[SUCESSO] Atualizado!\n");
}

int excluirProfessor(struct Professor lista[], int qtdAtual) {
    if (qtdAtual == 0) return qtdAtual;
    int mat; printf("\nExcluir - Digite a matricula: "); scanf("%d", &mat); limparBuffer();
    int idx = buscarProfessorPorMatricula(lista, qtdAtual, mat);
    if (idx == -1) { printf("[ERRO] Nao encontrado!\n"); return qtdAtual; }
    for (int i = idx; i < qtdAtual - 1; i++) lista[i] = lista[i + 1];
    printf("\n[SUCESSO] Excluido!\n"); return qtdAtual - 1;
}

int cadastrarDisciplina(struct Disciplina listaDisc[], int qtdDisc, struct Professor listaProf[], int qtdProf) {
    if (qtdDisc >= tamDisciplinas || qtdProf == 0) return qtdDisc;
    printf("\n--- Incluir Nova Disciplina ---\nCodigo: "); scanf("%d", &listaDisc[qtdDisc].codigo); limparBuffer();
    if (buscarDisciplinaPorCodigo(listaDisc, qtdDisc, listaDisc[qtdDisc].codigo) != -1) return qtdDisc;
    printf("Nome: "); fgets(listaDisc[qtdDisc].nome, 50, stdin); listaDisc[qtdDisc].nome[strcspn(listaDisc[qtdDisc].nome, "\n")] = 0;
    printf("Semestre: "); scanf("%d", &listaDisc[qtdDisc].semestre); limparBuffer();
    printf("Matricula do Professor: "); scanf("%d", &listaDisc[qtdDisc].matriculaProfessor); limparBuffer();
    if (buscarProfessorPorMatricula(listaProf, qtdProf, listaDisc[qtdDisc].matriculaProfessor) == -1) return qtdDisc;
    listaDisc[qtdDisc].qtdAlunosMatriculados = 0; 
    printf("\n[SUCESSO] Disciplina criada!\n"); return qtdDisc + 1;
}

void inserirAlunoNaDisciplina(struct Disciplina listaDisc[], int qtdDisc, struct Aluno listaAlun[], int qtdAlun) {
    if (qtdDisc == 0 || qtdAlun == 0) return;
    int codDisc, matAlun;
    printf("\nMatricular - Codigo Disciplina: "); scanf("%d", &codDisc); limparBuffer();
    int idxDisc = buscarDisciplinaPorCodigo(listaDisc, qtdDisc, codDisc);
    if (idxDisc == -1 || listaDisc[idxDisc].qtdAlunosMatriculados >= maxAlunosPorDisciplina) return;
    printf("Matricula Aluno: "); scanf("%d", &matAlun); limparBuffer();
    if (buscarAlunoPorMatricula(listaAlun, qtdAlun, matAlun) == -1) return;
    for (int i = 0; i < listaDisc[idxDisc].qtdAlunosMatriculados; i++) if (listaDisc[idxDisc].matriculasAlunos[i] == matAlun) return;
    listaDisc[idxDisc].matriculasAlunos[listaDisc[idxDisc].qtdAlunosMatriculados++] = matAlun;
    printf("\n[SUCESSO] Aluno matriculado!\n");
}

void removerAlunoDaDisciplina(struct Disciplina listaDisc[], int qtdDisc) {
    if (qtdDisc == 0) return;
    int codDisc, matAlun;
    printf("\nRemover - Codigo Disciplina: "); scanf("%d", &codDisc); limparBuffer();
    int idxDisc = buscarDisciplinaPorCodigo(listaDisc, qtdDisc, codDisc);
    if (idxDisc == -1 || listaDisc[idxDisc].qtdAlunosMatriculados == 0) return;
    printf("Matricula Aluno: "); scanf("%d", &matAlun); limparBuffer();
    int pos = -1;
    for (int i = 0; i < listaDisc[idxDisc].qtdAlunosMatriculados; i++) {
        if (listaDisc[idxDisc].matriculasAlunos[i] == matAlun) { pos = i; break; }
    }
    if (pos == -1) return;
    for (int i = pos; i < listaDisc[idxDisc].qtdAlunosMatriculados - 1; i++) listaDisc[idxDisc].matriculasAlunos[i] = listaDisc[idxDisc].matriculasAlunos[i + 1];
    listaDisc[idxDisc].qtdAlunosMatriculados--;
    printf("\n[SUCESSO] Aluno removido!\n");
}


// --- MÓDULO RELATÓRIOS ---


void relatorioDisciplinasSimples(struct Disciplina listaDisc[], int qtdDisc, struct Professor listaProf[], int qtdProf) {
    if (qtdDisc == 0) { printf("\nNenhuma disciplina.\n"); return; }
    printf("\n=== DISCIPLINAS ===\n");
    for (int i = 0; i < qtdDisc; i++) {
        int idxProf = buscarProfessorPorMatricula(listaProf, qtdProf, listaDisc[i].matriculaProfessor);
        char* nomeProf = (idxProf != -1) ? listaProf[idxProf].nome : "Desconhecido";
        printf("Cod: %d | Nome: %s | Semestre: %d | Professor: %s\n", listaDisc[i].codigo, listaDisc[i].nome, listaDisc[i].semestre, nomeProf);
    }
}

void relatorioUmaDisciplina(struct Disciplina listaDisc[], int qtdDisc, struct Professor listaProf[], int qtdProf, struct Aluno listaAlun[], int qtdAlun) {
    if (qtdDisc == 0) { printf("\nNenhuma disciplina.\n"); return; }
    int cod; printf("\nConsultar Disciplina - Codigo: "); scanf("%d", &cod); limparBuffer();
    int idxDisc = buscarDisciplinaPorCodigo(listaDisc, qtdDisc, cod);
    if (idxDisc == -1) { printf("[ERRO] Nao encontrada!\n"); return; }
    
    int idxProf = buscarProfessorPorMatricula(listaProf, qtdProf, listaDisc[idxDisc].matriculaProfessor);
    printf("\n--- DADOS ---\nNome: %s | Prof: %s\n", listaDisc[idxDisc].nome, (idxProf != -1) ? listaProf[idxProf].nome : "Desc");
    printf("\n--- ALUNOS ---\n");
    for (int i = 0; i < listaDisc[idxDisc].qtdAlunosMatriculados; i++) {
        int idxAlun = buscarAlunoPorMatricula(listaAlun, qtdAlun, listaDisc[idxDisc].matriculasAlunos[i]);
        if (idxAlun != -1) printf("%d. Mat: %d | Nome: %s\n", i + 1, listaAlun[idxAlun].matricula, listaAlun[idxAlun].nome);
    }
}

void relatorioAlunosPorSexo(struct Aluno lista[], int qtdAtual) {
    if (qtdAtual == 0) return;
    printf("\n=== ALUNOS POR SEXO ===\n--- Masculino ---\n");
    for (int i = 0; i < qtdAtual; i++) if (lista[i].sexo == 'M' || lista[i].sexo == 'm') printf("Mat: %d | Nome: %s\n", lista[i].matricula, lista[i].nome);
    printf("--- Feminino ---\n");
    for (int i = 0; i < qtdAtual; i++) if (lista[i].sexo == 'F' || lista[i].sexo == 'f') printf("Mat: %d | Nome: %s\n", lista[i].matricula, lista[i].nome);
}

void relatorioAlunosOrdenadosPorNome(struct Aluno lista[], int qtdAtual) {
    if (qtdAtual == 0) { printf("\nNenhum aluno cadastrado.\n"); return; }
    struct Aluno copia[tamAlunos];
    for (int i = 0; i < qtdAtual; i++) copia[i] = lista[i];

    for (int i = 0; i < qtdAtual - 1; i++) {
        for (int j = 0; j < qtdAtual - i - 1; j++) {
            if (strcmp(copia[j].nome, copia[j+1].nome) > 0) {
                struct Aluno temp = copia[j];
                copia[j] = copia[j+1];
                copia[j+1] = temp;
            }
        }
    }
    printf("\n=== ALUNOS ORDENADOS POR NOME ===\n");
    for (int i = 0; i < qtdAtual; i++) printf("Nome: %s | Mat: %d | CPF: %s\n", copia[i].nome, copia[i].matricula, copia[i].cpf);
}

void relatorioAlunosOrdenadosPorNascimento(struct Aluno lista[], int qtdAtual) {
    if (qtdAtual == 0) { printf("\nNenhum aluno cadastrado.\n"); return; }
    struct Aluno copia[tamAlunos];
    for (int i = 0; i < qtdAtual; i++) copia[i] = lista[i];

    for (int i = 0; i < qtdAtual - 1; i++) {
        for (int j = 0; j < qtdAtual - i - 1; j++) {
            if (compararDatas(copia[j].dataNascimento, copia[j+1].dataNascimento) > 0) {
                struct Aluno temp = copia[j];
                copia[j] = copia[j+1];
                copia[j+1] = temp;
            }
        }
    }
    printf("\n=== ALUNOS ORDENADOS POR DATA DE NASCIMENTO ===\n");
    for (int i = 0; i < qtdAtual; i++) printf("Nasc: %s | Nome: %s | Mat: %d\n", copia[i].dataNascimento, copia[i].nome, copia[i].matricula);
}

void relatorioProfessoresPorSexo(struct Professor lista[], int qtdAtual) {
    if (qtdAtual == 0) { printf("\nNenhum professor cadastrado.\n"); return; }
    printf("\n=== PROFESSORES POR SEXO ===\n--- Masculino ---\n");
    int contM = 0;
    for (int i = 0; i < qtdAtual; i++) {
        if (lista[i].sexo == 'M' || lista[i].sexo == 'm') {
            printf("Mat: %d | Nome: %s\n", lista[i].matricula, lista[i].nome); contM++;
        }
    }
    if (contM == 0) printf("Nenhum professor do sexo masculino.\n");

    printf("\n--- Feminino ---\n");
    int contF = 0;
    for (int i = 0; i < qtdAtual; i++) {
        if (lista[i].sexo == 'F' || lista[i].sexo == 'f') {
            printf("Mat: %d | Nome: %s\n", lista[i].matricula, lista[i].nome); contF++;
        }
    }
    if (contF == 0) printf("Nenhuma professora do sexo feminino.\n");
}

// -----------
// RELATÓRIOS FINAIS
// -----------

// 7. Alunos matriculados em menos de 3 disciplinas
void relatorioMenosDeTresDisciplinas(struct Aluno listaAlun[], int qtdAlun, struct Disciplina listaDisc[], int qtdDisc) {
    if (qtdAlun == 0) { printf("\nNenhum aluno cadastrado no sistema.\n"); return; }

    printf("\n=== ALUNOS EM MENOS DE 3 DISCIPLINAS ===\n");
    int encontrou = 0;

    // Contagem de disciplinas
    for (int i = 0; i < qtdAlun; i++) {
        int contDisciplinas = 0;
        
        for (int j = 0; j < qtdDisc; j++) {
            for (int k = 0; k < listaDisc[j].qtdAlunosMatriculados; k++) {
                if (listaDisc[j].matriculasAlunos[k] == listaAlun[i].matricula) {
                    contDisciplinas++;
                    break; 
                }
            }
        }

        if (contDisciplinas < 3) {
            printf("Mat: %d | Nome: %s | Total de Disciplinas: %d\n", 
                   listaAlun[i].matricula, listaAlun[i].nome, contDisciplinas);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Todos os alunos estao matriculados em 3 ou mais disciplinas.\n");
    }
}

// 8. Aniversariantes do Mês
void relatorioAniversariantesDoMes(struct Aluno listaAlun[], int qtdAlun, struct Professor listaProf[], int qtdProf) {
    int mesBusca;
    
    printf("\n--- Aniversariantes do Mes ---\n");
    printf("Digite o numero do mes atual (1 a 12): ");
    scanf("%d", &mesBusca); limparBuffer();

    if (mesBusca < 1 || mesBusca > 12) {
        printf("[ERRO] Mes invalido!\n");
        return;
    }

    printf("\n=== ANIVERSARIANTES DO MES %02d ===\n", mesBusca);
    int encontrou = 0;

    // Busca nos Alunos
    for (int i = 0; i < qtdAlun; i++) {
        int dia, mes, ano;
        sscanf(listaAlun[i].dataNascimento, "%2d/%2d/%4d", &dia, &mes, &ano); // Extrair os dados da string
        
        if (mes == mesBusca) {
            printf("[ALUNO] Mat: %d | Nome: %s | Data: %s\n", 
                   listaAlun[i].matricula, listaAlun[i].nome, listaAlun[i].dataNascimento);
            encontrou = 1;
        }
    }

    // Busca nos Professores
    for (int i = 0; i < qtdProf; i++) {
        int dia, mes, ano;
        sscanf(listaProf[i].dataNascimento, "%2d/%2d/%4d", &dia, &mes, &ano);
        
        if (mes == mesBusca) {
            printf("[PROFESSOR] Mat: %d | Nome: %s | Data: %s\n", 
                   listaProf[i].matricula, listaProf[i].nome, listaProf[i].dataNascimento);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhum aniversariante encontrado neste mes.\n");
    }
}

// ---------------

int main() {
    int escolha = 0;
    
    struct Aluno alunos[tamAlunos]; int qtdalunos = 0;
    struct Professor professores[tamProfessores]; int qtdprofessores = 0;
    struct Disciplina disciplinas[tamDisciplinas]; int qtddisciplinas = 0;
    
    while (escolha != 5) {
        printf("\n=== SISTEMA ESCOLA TOTVS ===\n");
        printf("1 - Modulo Aluno\n");
        printf("2 - Modulo Professor\n");
        printf("3 - Modulo Disciplina\n");
        printf("4 - Modulo Relatorios\n"); 
        printf("5 - Sair\n");              
        printf("Escolha: ");
        scanf("%d", &escolha); limparBuffer();
        
        switch (escolha) {
            case 1: {
                int opA = 0;
                while (opA != 5) { 
                    printf("\n-- ALUNO --\n1-Cadastrar\n2-Listar\n3-Atualizar\n4-Excluir\n5-Voltar\nEscolha: "); 
                    scanf("%d", &opA); limparBuffer();
                    
                    if(opA==1) qtdalunos = cadastrarAluno(alunos, qtdalunos);
                    else if(opA==2) listarAlunos(alunos, qtdalunos);
                    else if(opA==3) atualizarAluno(alunos, qtdalunos); 
                    else if(opA==4) qtdalunos = excluirAluno(alunos, qtdalunos); 
                }
                break;
            }
            case 2: {
                int opP = 0;
                while (opP != 5) { 
                    printf("\n-- PROFESSOR --\n1-Cadastrar\n2-Listar\n3-Atualizar\n4-Excluir\n5-Voltar\nEscolha: "); 
                    scanf("%d", &opP); limparBuffer();
                    
                    if(opP==1) qtdprofessores = cadastrarProfessor(professores, qtdprofessores);
                    else if(opP==2) listarProfessores(professores, qtdprofessores);
                    else if(opP==3) atualizarProfessor(professores, qtdprofessores); 
                    else if(opP==4) qtdprofessores = excluirProfessor(professores, qtdprofessores); 
                }
                break;
            }
            case 3: {
                int opD = 0;
                while (opD != 4) {
                    printf("\n--- Modulo Disciplina ---\n");
                    printf("1 - Cadastrar Disciplina\n");
                    printf("2 - Inserir Aluno na Disciplina\n");
                    printf("3 - Excluir Aluno da Disciplina\n"); 
                    printf("4 - Voltar\nEscolha: ");
                    scanf("%d", &opD); limparBuffer();

                    if (opD == 1) qtddisciplinas = cadastrarDisciplina(disciplinas, qtddisciplinas, professores, qtdprofessores);
                    else if (opD == 2) inserirAlunoNaDisciplina(disciplinas, qtddisciplinas, alunos, qtdalunos);
                    else if (opD == 3) removerAlunoDaDisciplina(disciplinas, qtddisciplinas); 
                }
                break;
            }
            case 4: { 
                int opR = 0;
                while (opR != 9) { 
                    printf("\n--- Modulo Relatorios ---\n");
                    printf("1 - Listar Todas as Disciplinas (Sem Alunos)\n");
                    printf("2 - Consultar Uma Disciplina (Com Alunos)\n");
                    printf("3 - Listar Alunos por Sexo\n");
                    printf("4 - Listar Alunos ordenados por Nome\n");             
                    printf("5 - Listar Alunos ordenados por Data Nascimento\n");  
                    printf("6 - Listar Professores por Sexo\n");                  
                    printf("7 - Listar Alunos em menos de 3 disciplinas\n"); // NOVO
                    printf("8 - Listar Aniversariantes do Mes\n");           // NOVO
                    printf("9 - Voltar\nEscolha: ");
                    scanf("%d", &opR); limparBuffer();

                    if (opR == 1) relatorioDisciplinasSimples(disciplinas, qtddisciplinas, professores, qtdprofessores);
                    else if (opR == 2) relatorioUmaDisciplina(disciplinas, qtddisciplinas, professores, qtdprofessores, alunos, qtdalunos);
                    else if (opR == 3) relatorioAlunosPorSexo(alunos, qtdalunos);
                    else if (opR == 4) relatorioAlunosOrdenadosPorNome(alunos, qtdalunos);
                    else if (opR == 5) relatorioAlunosOrdenadosPorNascimento(alunos, qtdalunos);
                    else if (opR == 6) relatorioProfessoresPorSexo(professores, qtdprofessores);
                    else if (opR == 7) relatorioMenosDeTresDisciplinas(alunos, qtdalunos, disciplinas, qtddisciplinas);
                    else if (opR == 8) relatorioAniversariantesDoMes(alunos, qtdalunos, professores, qtdprofessores);
                }
                break;
            }
            case 5: printf("Saindo do sistema...\n"); break;
            default: printf("Invalido!\n");
        }
    }
    return 0;
}
