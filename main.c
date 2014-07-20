#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct data
{
    int _dia;
    int _mes;
    int _ano;

} data;

typedef struct doador
{
    char _ID[30]; //identificação
    char _nome[30]; //nome
    char _local[30]; //localização
    char _intencao[30]; //intenção

} doador;

typedef struct doacao
{
    char _ID[30]; //identificação
    char _doadorID[30]; //ID do doador associado
    char _projetoID[30]; //ID do projeto
    char _funcionarioID[30]; //ID do funcionario
    int _quantia; //quantia do donativo
    data _data; //data

} doacao;

typedef struct posicao
{
    char _voluntarioID[30]; //ID do voluntario
    char _funcionarioID[30]; //ID do funcionario responsavel/supervisor
    char _desgn[30]; //designação
    char _dept[30]; //departamento
    data _dataentrada; //data de entrada
    data _datasaida; //data de saida

} posicao;

typedef struct funcionario
{
    char _ID[30]; //identificação
    char _nome[30]; //nome
    char _morada[30]; //morada
    char _funcao[30]; //funcão
    char _dept[30]; //departamento
    char _educ[30]; //nivel de educação
    char _experiencia[30]; //experiência
    char _descricao[30]; //descricao
    int _salario; //salario
    int _ISvoluntario; // 0 - false; 1 - true
    char _posicao[30];
    //posicao _posicao; //posição no projeto

} funcionario;

typedef struct doadores
{
    doador _dados[5];
    int _last;
    int _quantidade;

} doadores;

typedef struct doacoes
{
    doacao _dados[5];
    int _last;
    int _quantidade;

} doacoes;

typedef struct funcionarios
{
    funcionario _dados[5];
    int _last;
    int _quantidade;

} funcionarios;

typedef struct administradores
{
    funcionario _dados[5];
    int _last;
    int _quantidade;

} administradores;

typedef struct voluntarios
{
    funcionario _dados[5];
    int _last;
    int _quantidade;

} voluntarios;

typedef struct projeto
{
    char _ID[30]; //identificação
    char _desgn[30]; //designação
    char _local[30]; //localização
    char _liderID[30]; //identificação do lider
    char _tipo[15]; //tipo de projeto
    char _cond[30]; //condição
    char _obs[30]; //observações
    data _data; //data
    doadores _doadores;
    doacoes _doacoes;
    funcionarios _funcionarios;
    voluntarios _voluntarios;

} projeto;

typedef struct empresa
{
    projeto _projetos[5];
    funcionarios _funcionarios;
    administradores _administradores;

    int _last;
    int _quantidade;

    /**
    * a empresa mantem um registo de todos os projetos
    * bem como uma ficha de doadores, doações e funcionarios
    */

} empresa;

int argumentIsInteger(char arg[]);

int mostrarMenuInicial(int escolha);
int mostrarMenuFuncionarios(int escolha);
int mostrarMenuAdministradores(int escolha);
int mostrarMenuProjetos(int escolha);

empresa gerirFuncionarios(empresa _empresa);
empresa gerirAdministradores(empresa _empresa);
empresa gerirProjetos(empresa _empresa);

empresa inserirFuncionario(empresa _empresa);
void listarFuncionarios(empresa _empresa);
void listarFuncionario(funcionario f);
empresa apagarFuncionario(empresa _empresa);
void procurarFuncionario(empresa _empresa);
void questionaListarFuncionario(funcionario f);

empresa inserirAdministrador(empresa _empresa);
void listarAdministradores(empresa _empresa);
void listarAdministrador(funcionario f);
empresa apagarAdministrador(empresa _empresa);
void procurarAdministrador(empresa _empresa);
void questionaListarAdministrador(funcionario f);

empresa inserirProjeto(empresa _empresa);
void listarProjetos(empresa _empresa);
void listarProjeto(projeto f);
empresa apagarProjeto(empresa _empresa);

empresa abrirMenuProjeto(empresa _empresa, int pos);
int mostrarMenuUMProjeto(int escolha);
empresa procurarProjeto(empresa _empresa);
empresa questionaAbrirProjeto(empresa _empresa, projeto p, int pos);

empresa questionaAtribuirLider(empresa _empresa, projeto p);
empresa atribuirLider(empresa _empresa, projeto p);

empresa inserirDoacao(empresa _empresa, int pos);
void listarDoacoes(empresa _empresa, int pos);
void listarDoacao(doacao f);
empresa apagarDoacao(empresa _empresa, int pos);
void procurarDoacao(empresa _empresa, int pos);
void questionaListarDoacao(doacao f);

empresa questionaAtribuirDoador(int pos, empresa _empresa, doacao p);
empresa atribuirDoador(int pos, empresa _empresa, doacao p);
empresa questionaAtribuirResponsavel(int pos, empresa _empresa, doacao p);
empresa atribuirResponsavel(int pos, empresa _empresa, doacao p);

empresa inserirDoador(empresa _empresa, int pos);
void listarDoadores(empresa _empresa, int pos);
void listarDoador(doador f);
empresa apagarDoador(empresa _empresa, int pos);
void procurarDoador(empresa _empresa, int pos);
void questionaListarDoador(doador f);

empresa inserirVoluntario(empresa _empresa, int pos);
void listarVoluntarios(empresa _empresa, int pos);
void listarVoluntario(funcionario f);
empresa apagarVoluntario(empresa _empresa, int pos);
void procurarVoluntario(empresa _empresa, int pos);
void questionaListarVoluntario(funcionario f);

empresa afiliarFuncionario(empresa _empresa, int pos);
void procurarFuncionarioNumProjeto(empresa _empresa, int pos);
void questionaListarFuncionarioNumProjeto(funcionario f);
void listarFuncionariosNumProjeto(empresa _empresa, int pos);
void listarFuncionarioNumProjeto(funcionario f);
empresa alterarFuncao(empresa _empresa, int pos);

empresa acrescentarFuncionarioaProjeto(empresa _empresa, int pos, funcionario f);

empresa pagarSalarios(empresa _empresa);
void estatisticasEmpresa(empresa _empresa);

void displayData(data d);

int main()
{
    empresa _empresa;
    int i, j;

    for (i=0; i<5; i++) //para garantir que todos os voluntarios são inicializados como tal
    {
        for (j=0; j<5; j++)
        {
            _empresa._projetos[i]._voluntarios._dados[j]._ISvoluntario = 1;
        }
    }

    _empresa._last = 0;
    _empresa._funcionarios._last = 0;
    _empresa._administradores._last = 0;
    _empresa._quantidade = 0;
    _empresa._funcionarios._quantidade = 0;
    _empresa._administradores._quantidade = 0;


    int escolha = 10;

    printf("--------- Bem-Vindo a Aplicacao de Gestao de Instituicoes ---------\n");

    while (escolha != 0)
    {
        escolha = mostrarMenuInicial(escolha);
        switch(escolha)
        {
        case 1 :
        {
            _empresa = gerirFuncionarios(_empresa);
            escolha = 10;
            break;
        }

        case 2 :
        {
            _empresa = gerirAdministradores(_empresa);
            escolha = 10;
            break;
        }

        case 3 :
        {
            _empresa = gerirProjetos(_empresa);
            escolha = 10;
            break;
        }

        case 4 :
        {
            _empresa = pagarSalarios(_empresa);
            escolha = 10;
            break;
        }

        case 5 :
        {
            estatisticasEmpresa(_empresa);
            escolha = 10;
            break;
        }
        }
    }

    return 0;
}

/**********************************************************************/
/**********************************************************************/
/**********************************************************************/

int mostrarMenuInicial(int escolha)
{
    char s[30];
    int valid = 0;
    int i;

    while ((escolha < 0) || (escolha > 5))
    {
        printf("\n1) Gerir Funcionarios\n");
        printf("2) Gerir Administradores\n");
        printf("3) Gerir Projetos\n");
        printf("4) Pagar Salarios\n");
        printf("5) Ver Estatisticas\n");

        printf("\n0) SAIR\n");


        while ((valid == 0) || ((escolha < 0) || (escolha > 5)))
        {
            printf("\nSeleccione a opcao pretendida (0-5): ");
            scanf("%s", s);
            valid = argumentIsInteger(s);

            if (valid == 1)
            {
                escolha = atoi(s);
            }

            if (valid == 0)
            {
                printf("\nOpcao Invalida. Formato Invalido. Introduza um valor NUMERICO entre 0 e 5.\n\n");
                for (i=0; i<strlen(s); i++)
                {
                    s[i] = "";
                }
            }

            else
            {
                if ((escolha < 0) || (escolha > 5))
                {
                    printf("Opcao Invalida. Formato Invalido. Introduza um valor entre 0 e 5.\n\n");
                    for (i=0; i<strlen(s); i++)
                    {
                        s[i] = "";
                    }

                    valid = 0;
                }
            }
        }
    }
    return escolha;
}

empresa pagarSalarios(empresa _empresa)
{
    int totalSalariosFuncionarios = 0;
    int totalSalariosAdministradores = 0;
    int totalSalarios = 0;
    int i,j;

    if((_empresa._funcionarios._quantidade > 0) || (_empresa._administradores._quantidade > 0))
    {

    for (i=0; i<_empresa._funcionarios._last; i++)
    {
        if (strcmp(_empresa._funcionarios._dados[i]._nome, "DELETED") != 0)
        {
            totalSalariosFuncionarios += _empresa._funcionarios._dados[i]._salario;
            totalSalarios += _empresa._funcionarios._dados[i]._salario;
        }
    }

    for (j=0; j<_empresa._administradores._last; j++)
    {
        if (strcmp(_empresa._administradores._dados[j]._nome, "DELETED") != 0)
        {
            totalSalariosAdministradores += _empresa._administradores._dados[j]._salario;
            totalSalarios+=_empresa._administradores._dados[j]._salario;
        }
    }

    printf("\n%d$ pagos a Funcionarios.\n", totalSalariosFuncionarios);
    printf("%d$ pagos a Administradores.\n\n", totalSalariosAdministradores);
    printf("Total de %d$ pagos em salarios.\n\n", totalSalarios);

    }

    else
        printf("\n!!!ERRO: Nao ha funcionarios nem administradores registados na Empresa.\n\n");

    return _empresa;
}

void estatisticasEmpresa(empresa _empresa)
{
    int totalSalariosFuncionarios = 0;
    int totalSalariosAdministradores = 0;
    int totalSalarios = 0;
    int i,j;

    for (i=0; i<_empresa._funcionarios._last; i++)
    {
        if (strcmp(_empresa._funcionarios._dados[i]._nome, "DELETED") != 0)
        {
            totalSalariosFuncionarios += _empresa._funcionarios._dados[i]._salario;
            totalSalarios += _empresa._funcionarios._dados[i]._salario;
        }
    }

    for (j=0; j<_empresa._administradores._last; j++)
    {
        if (strcmp(_empresa._administradores._dados[j]._nome, "DELETED") != 0)
        {
            totalSalariosAdministradores += _empresa._administradores._dados[j]._salario;
            totalSalarios+=_empresa._administradores._dados[j]._salario;
        }
    }

    printf("\nHa actualmente %d Administrador(es) a trabalhar na empresa.\n", _empresa._administradores._quantidade);
    printf("Ha actualmente %d Funcionario(s) a trabalhar na empresa.\n", _empresa._funcionarios._quantidade);
    printf("Ha actualmente %d Projeto(s) registado(s) na empresa.\n", _empresa._quantidade);
    printf("\nA empresa gasta actualmente  %d$ em salarios,\n", totalSalarios);
    printf("dos quais %d$ sao salarios de Funcionarios e %d$ sao salarios de administradores.\n\n", totalSalariosFuncionarios, totalSalariosAdministradores);

    return _empresa;
}

empresa gerirFuncionarios(empresa _empresa)
{
    int escolha = 5;
    while (escolha != 0)
    {
        escolha = mostrarMenuFuncionarios(escolha);
        switch(escolha)
        {
        case 1 :
        {
            _empresa = inserirFuncionario(_empresa);
            escolha = 0;
            break;
        }

        case 2 :
        {
            listarFuncionarios(_empresa);
            escolha = 0;
            break;
        }

        case 3 :
        {
            _empresa = apagarFuncionario(_empresa);
            escolha = 0;
            break;
        }

        case 4 :
        {
            procurarFuncionario(_empresa);
            escolha = 0;
            break;
        }
        }
    }
    return _empresa;
}

int mostrarMenuFuncionarios(int escolha)
{
    char s[30];
    int valid = 0;
    int i;

    while ((escolha < 0) || (escolha > 4))
    {
        printf("\n1) Inserir Funcionario\n");
        printf("2) Listar Funcionarios\n");
        printf("3) Apagar Funcionario\n");
        printf("4) Procurar Funcionario\n");

        printf("\n0) VOLTAR AO MENU INICIAL\n");


        while ((valid == 0) || ((escolha < 0) || (escolha > 4)))
        {
            printf("\nSeleccione a opcao pretendida (0-4): ");
            scanf("%s", s);
            valid = argumentIsInteger(s);

            if (valid == 1)
            {
                escolha = atoi(s);
            }

            if (valid == 0)
            {
                printf("\nOpcao Invalida. Formato Invalido. Introduza um valor NUMERICO entre 0 e 4.\n\n");
                for (i=0; i<strlen(s); i++)
                {
                    s[i] = "";
                }
            }

            else
            {
                if ((escolha < 0) || (escolha > 4))
                {
                    printf("\nOpcao Invalida. Formato Invalido. Introduza um valor entre 0 e 4.\n\n");
                    for (i=0; i<strlen(s); i++)
                    {
                        s[i] = "";
                    }

                    valid = 0;
                }
            }
        }
    }
    return escolha;
}

empresa inserirFuncionario(empresa _empresa)
{
    printf("\nID: ");
    scanf(" %[^\n]s", _empresa._funcionarios._dados[_empresa._funcionarios._last]._ID);
    printf("\n");
    printf("Nome: ");
    scanf(" %[^\n]s", _empresa._funcionarios._dados[_empresa._funcionarios._last]._nome);
    printf("\n");
    printf("Morada: ");
    scanf(" %[^\n]s", _empresa._funcionarios._dados[_empresa._funcionarios._last]._morada);
    printf("\n");
    printf("Funcao: ");
    scanf(" %[^\n]s", _empresa._funcionarios._dados[_empresa._funcionarios._last]._funcao);
    printf("\n");
    printf("Departamento: ");
    scanf(" %[^\n]s", _empresa._funcionarios._dados[_empresa._funcionarios._last]._dept);
    printf("\n");
    printf("Educacao: ");
    scanf(" %[^\n]s", _empresa._funcionarios._dados[_empresa._funcionarios._last]._educ);
    printf("\n");
    printf("Experiencia: ");
    scanf(" %[^\n]s", _empresa._funcionarios._dados[_empresa._funcionarios._last]._experiencia);
    printf("\n");
    printf("Descricao: ");
    scanf(" %[^\n]s", _empresa._funcionarios._dados[_empresa._funcionarios._last]._descricao);
    printf("\n");
    printf("Salario: ");
    scanf("%d", &_empresa._funcionarios._dados[_empresa._funcionarios._last]._salario);
    printf("\n");

    printf("\nFuncionario %s inserido com sucesso.\n\n", _empresa._funcionarios._dados[_empresa._funcionarios._last]._nome);

    _empresa._funcionarios._last ++;
    _empresa._funcionarios._quantidade ++;
    return _empresa;
}

void listarFuncionarios(empresa _empresa)
{
    int i;

    if (_empresa._funcionarios._quantidade > 0)
    {
        for (i=0; i<_empresa._funcionarios._last; i++)
        {
            if (strcmp(_empresa._funcionarios._dados[i]._nome, "DELETED") != 0)
            {
                listarFuncionario(_empresa._funcionarios._dados[i]);
            }
        }
    }

    else
    {
        printf("\n!!!ERRO: Nao existem Funcionarios registados na Empresa.\n\n");
    }
}

void listarFuncionario(funcionario f)
{
    printf("\nID: %s\nNome: %s\nMorada: %s\nFuncao: %s\nDepartamento: %s\nEducacao: %s\nExperiencia: %s\nDescricao: %s\nSalario: %d$\n\n",
           f._ID, f._nome, f._morada, f._funcao, f._dept, f._educ, f._experiencia, f._descricao, f._salario );
}

empresa apagarFuncionario(empresa _empresa)
{
    char stringaux[30];
    int i, existe;
    existe = 0;

    if(_empresa._funcionarios._quantidade > 0)
    {
        printf("\nNome do Funcionario a Eliminar: ");
        scanf(" %[^\n]s", stringaux);
        printf("\n");

        for(i=0; i<_empresa._funcionarios._last; i++)
        {
            if (strcmp(stringaux, _empresa._funcionarios._dados[i]._nome) == 0)
            {
                strcpy(_empresa._funcionarios._dados[i]._nome, "DELETED");
                existe = 1;
            }
        }

        if (existe == 0)
        {
            printf("\n!!!ERRO: Nao existe um Funcionario com o nome %s.\n\n", stringaux);
        }

        if (existe == 1)
        {
            _empresa._funcionarios._quantidade --;
            printf("\nFuncionario com o nome %s eliminado.\n\n", stringaux);
        }

    }

    else
    {
        printf("\n!!!ERRO: Nao existem Funcionarios registados na Empresa.\n\n");
    }
    return _empresa;
}

void procurarFuncionario(empresa _empresa)
{
    if (_empresa._funcionarios._quantidade > 0)
    {
        char stringaux[30];
        printf("\nNome do Funcionario a Procurar: ");
        scanf(" %[^\n]s", stringaux);
        printf("\n");

        int i, existe, pos;
        existe = 0;

        for(i=0; i<_empresa._funcionarios._last; i++)
        {
            if (strcmp(stringaux, _empresa._funcionarios._dados[i]._nome) == 0)
            {
                pos = i;
                existe = 1;
            }
        }

        if (existe == 0)
        {
            printf("\n!!!ERRO: Nao existe um Funcionario com o nome %s.\n\n", stringaux);
        }

        if (existe == 1)
        {
            printf("\nFuncionario com o nome %s encontrado.\n\n", stringaux);
            questionaListarFuncionario(_empresa._funcionarios._dados[pos]);
        }
    }

    else
    {
        printf("\n!!!ERRO: Nao existem Funcionarios registados na Empresa.\n\n");
    }
}

void questionaListarFuncionario(funcionario f)
{
    char listar[3];

    while ((((strcmp(listar, "S") != 0) && (strcmp(listar, "N") != 0)) && (strcmp(listar, "s") != 0)) && (strcmp(listar, "n") != 0))
    {
        printf("\nPretende abrir a ficha do Funcionario %s ? (S/N): ", f._nome);
        scanf("%s", listar);
        if ((((strcmp(listar, "S") != 0) && (strcmp(listar, "N") != 0)) && (strcmp(listar, "s") != 0)) && (strcmp(listar, "n") != 0))
        {
            printf("\nOpcao Invalida. Formato Invalido. Introduza 'S' / 's' (SIM) ou 'N' / 'n' (NAO).\n\n");
        }
    }

    if ((strcmp(listar, "S") == 0) || (strcmp(listar, "s") == 0))
    {
        listarFuncionario(f);
        printf("\n");
    }
}

/**********************************************************************/
/**********************************************************************/
/**********************************************************************/

empresa gerirAdministradores(empresa _empresa)
{
    int escolha = 5;
    while (escolha != 0)
    {
        escolha = mostrarMenuAdministradores(escolha);
        switch(escolha)
        {
        case 1 :
        {
            _empresa = inserirAdministrador(_empresa);
            escolha = 0;
            break;
        }

        case 2 :
        {
            listarAdministradores(_empresa);
            escolha = 0;
            break;
        }

        case 3 :
        {
            _empresa = apagarAdministrador(_empresa);
            escolha = 0;
            break;
        }

        case 4 :
        {
            procurarAdministrador(_empresa);
            escolha = 0;
            break;
        }
        }
    }
    return _empresa;
}

int mostrarMenuAdministradores(int escolha)
{
    char s[30];
    int valid = 0;
    int i;

    while ((escolha < 0) || (escolha > 4))
    {
        printf("\n1) Inserir Administrador\n");
        printf("2) Listar Administradores\n");
        printf("3) Apagar Administrador\n");
        printf("4) Procurar Administrador\n");

        printf("\n0) VOLTAR AO MENU INICIAL\n");


        while ((valid == 0) || ((escolha < 0) || (escolha > 4)))
        {
            printf("\nSeleccione a opcao pretendida (0-4): ");
            scanf("%s", s);
            valid = argumentIsInteger(s);

            if (valid == 1)
            {
                escolha = atoi(s);
            }

            if (valid == 0)
            {
                printf("\nOpcao Invalida. Formato Invalido. Introduza um valor NUMERICO entre 0 e 4.\n\n");
                for (i=0; i<strlen(s); i++)
                {
                    s[i] = "";
                }
            }

            else
            {
                if ((escolha < 0) || (escolha > 4))
                {
                    printf("\nOpcao Invalida. Formato Invalido. Introduza um valor entre 0 e 4.\n\n");
                    for (i=0; i<strlen(s); i++)
                    {
                        s[i] = "";
                    }

                    valid = 0;
                }
            }
        }
    }
    return escolha;
}

empresa inserirAdministrador(empresa _empresa)
{
    printf("\nID: ");
    scanf(" %[^\n]s", _empresa._administradores._dados[_empresa._administradores._last]._ID);
    printf("\n");
    printf("Nome: ");
    scanf(" %[^\n]s", _empresa._administradores._dados[_empresa._administradores._last]._nome);
    printf("\n");
    printf("Morada: ");
    scanf(" %[^\n]s", _empresa._administradores._dados[_empresa._administradores._last]._morada);
    printf("\n");
    printf("Funcao: ");
    scanf(" %[^\n]s", _empresa._administradores._dados[_empresa._administradores._last]._funcao);
    printf("\n");
    printf("Departamento: ");
    scanf(" %[^\n]s", _empresa._administradores._dados[_empresa._administradores._last]._dept);
    printf("\n");
    printf("Educacao: ");
    scanf(" %[^\n]s", _empresa._administradores._dados[_empresa._administradores._last]._educ);
    printf("\n");
    printf("Experiencia: ");
    scanf(" %[^\n]s", _empresa._administradores._dados[_empresa._administradores._last]._experiencia);
    printf("\n");
    printf("Descricao: ");
    scanf(" %[^\n]s", _empresa._administradores._dados[_empresa._administradores._last]._descricao);
    printf("\n");
    printf("Salario: ");
    scanf("%d", &_empresa._administradores._dados[_empresa._administradores._last]._salario);
    printf("\n");

    printf("\nAdministrador %s inserido com sucesso.\n\n", _empresa._administradores._dados[_empresa._administradores._last]._nome);

    _empresa._administradores._last ++;
    _empresa._administradores._quantidade ++;
    return _empresa;
}

void listarAdministradores(empresa _empresa)
{
    int i;

    if (_empresa._administradores._quantidade > 0)
    {
        for (i=0; i<_empresa._administradores._last; i++)
        {
            if (strcmp(_empresa._administradores._dados[i]._nome, "DELETED") != 0)
            {
                listarAdministrador(_empresa._administradores._dados[i]);
            }
        }
    }

    else
    {
        printf("\n!!!ERRO: Nao existem Administradores registados na Empresa.\n\n");
    }
}

void listarAdministrador(funcionario f)
{
    printf("\nID: %s\nNome: %s\nMorada: %s\nFuncao: %s\nDepartamento: %s\nEducacao: %s\nExperiencia: %s\nDescricao: %s\nSalario: %d$\n\n",
           f._ID, f._nome, f._morada, f._funcao, f._dept, f._educ, f._experiencia, f._descricao, f._salario );
}

empresa apagarAdministrador(empresa _empresa)
{
    char stringaux[30];
    int i, existe;
    existe = 0;

    if (_empresa._administradores._quantidade > 0)
    {
        printf("\nNome do Administrador a Eliminar: ");
        scanf(" %[^\n]s", stringaux);
        printf("\n");

        for(i=0; i<_empresa._administradores._last; i++)
        {
            if (strcmp(stringaux, _empresa._administradores._dados[i]._nome) == 0)
            {
                strcpy(_empresa._administradores._dados[i]._nome, "DELETED");
                existe = 1;
            }
        }

        if (existe == 0)
        {
            printf("\n!!!ERRO: Nao existe um Administrador com o nome %s.\n\n", stringaux);
        }

        if (existe == 1)
        {
            _empresa._administradores._quantidade --;
            printf("\nAdministrador com o nome %s eliminado.\n\n", stringaux);
        }

    }

    else
    {
        printf("\n!!!ERRO: Nao existem Administradores registados na Empresa.\n\n");
    }
    return _empresa;
}

void procurarAdministrador(empresa _empresa)
{
    if (_empresa._administradores._quantidade > 0)
    {
        char stringaux[30];
        printf("\nNome do Administrador a Procurar: ");
        scanf(" %[^\n]s", stringaux);
        printf("\n");

        int i, existe, pos;
        existe = 0;

        for(i=0; i<_empresa._administradores._last; i++)
        {
            if (strcmp(stringaux, _empresa._administradores._dados[i]._nome) == 0)
            {
                pos = i;
                existe = 1;
            }
        }

        if (existe == 0)
        {
            printf("\n!!!ERRO: Nao existe um Administrador com o nome %s.\n\n", stringaux);
        }

        if (existe == 1)
        {
            printf("\nAdministrador com o nome %s encontrado.\n\n", stringaux);
            questionaListarFuncionario(_empresa._administradores._dados[pos]);
        }
    }
    else
    {
        printf("\n!!!ERRO: Nao existem Administradores registados na Empresa.\n\n");
    }
}

void questionaListarAdministrador(funcionario f)
{
    char listar[3];

    while ((((strcmp(listar, "S") != 0) && (strcmp(listar, "N") != 0)) && (strcmp(listar, "s") != 0)) && (strcmp(listar, "n") != 0))
    {
        printf("\nPretende abrir a ficha do Administrador %s ? (S/N): ", f._nome);
        scanf("%s", listar);
        if ((((strcmp(listar, "S") != 0) && (strcmp(listar, "N") != 0)) && (strcmp(listar, "s") != 0)) && (strcmp(listar, "n") != 0))
        {
            printf("\nOpcao Invalida. Formato Invalido. Introduza 'S' / 's' (SIM) ou 'N' / 'n' (NAO).\n\n");
        }
    }

    if ((strcmp(listar, "S") == 0) || (strcmp(listar, "s") == 0))
    {
        listarAdministrador(f);
        printf("\n");
    }
}

/**********************************************************************/
/**********************************************************************/
/**********************************************************************/

empresa gerirProjetos(empresa _empresa)
{
    int escolha = 5;
    while (escolha != 0)
    {
        escolha = mostrarMenuProjetos(escolha);
        switch(escolha)
        {
        case 1 :
        {
            _empresa = inserirProjeto(_empresa);
            escolha = 0;
            break;
        }

        case 2 :
        {
            listarProjetos(_empresa);
            escolha = 0;
            break;
        }

        case 3 :
        {
            _empresa = apagarProjeto(_empresa);
            escolha = 0;
            break;
        }

        case 4 :
        {
            _empresa = procurarProjeto(_empresa);
            escolha = 0;
            break;
        }
        }
    }
    return _empresa;
}

int mostrarMenuProjetos(int escolha)
{
    char s[30];
    int valid = 0;
    int i;

    while ((escolha < 0) || (escolha > 4))
    {
        printf("\n1) Inserir Projeto\n");
        printf("2) Listar Projetos\n");
        printf("3) Apagar Projeto\n");
        printf("4) Abrir Menu de um Projeto\n");

        printf("\n0) VOLTAR AO MENU INICIAL\n");


        while ((valid == 0) || ((escolha < 0) || (escolha > 4)))
        {
            printf("\nSeleccione a opcao pretendida (0-4): ");
            scanf("%s", s);
            valid = argumentIsInteger(s);

            if (valid == 1)
            {
                escolha = atoi(s);
            }

            if (valid == 0)
            {
                printf("\nOpcao Invalida. Formato Invalido. Introduza um valor NUMERICO entre 0 e 4.\n\n");
                for (i=0; i<strlen(s); i++)
                {
                    s[i] = "";
                }
            }

            else
            {
                if ((escolha < 0) || (escolha > 4))
                {
                    printf("\nOpcao Invalida. Formato Invalido. Introduza um valor entre 0 e 4.\n\n");
                    for (i=0; i<strlen(s); i++)
                    {
                        s[i] = "";
                    }

                    valid = 0;
                }
            }
        }
    }
    return escolha;
}


empresa inserirProjeto(empresa _empresa)
{
    printf("\nID: ");
    scanf(" %[^\n]s", _empresa._projetos[_empresa._last]._ID);
    printf("\n");
    printf("Designacao: ");
    scanf(" %[^\n]s", _empresa._projetos[_empresa._last]._desgn);
    printf("\n");
    printf("Localizacao: ");
    scanf(" %[^\n]s", _empresa._projetos[_empresa._last]._local);
    printf("\n");
    printf("Data de Criacao (dia, mes, ano)\n");
    printf("Dia: ");
    scanf("%d", &_empresa._projetos[_empresa._last]._data._dia);
    printf("Mes: ");
    scanf("%d", &_empresa._projetos[_empresa._last]._data._mes);
    printf("Ano: ");
    scanf("%d", &_empresa._projetos[_empresa._last]._data._ano);
    printf("\n");
    printf("Tipo: ");
    scanf(" %[^\n]s", _empresa._projetos[_empresa._last]._tipo);
    printf("\n");
    printf("Condicao: ");
    scanf(" %[^\n]s", _empresa._projetos[_empresa._last]._cond);
    printf("\n");
    printf("Observacoes: ");
    scanf(" %[^\n]s", _empresa._projetos[_empresa._last]._obs);
    printf("\n");

    printf("\nProjeto %s criado com sucesso.\n\n", _empresa._projetos[_empresa._last]._ID);

    _empresa = questionaAtribuirLider(_empresa, _empresa._projetos[_empresa._last]);

    _empresa._last ++;
    _empresa._quantidade ++;
    return _empresa;
}

empresa questionaAtribuirLider(empresa _empresa, projeto p)
{
    char listar[3];

    while ((((strcmp(listar, "S") != 0) && (strcmp(listar, "N") != 0)) && (strcmp(listar, "s") != 0)) && (strcmp(listar, "n") != 0))
    {
        printf("\nPretende atribuir um Lider ao Projeto %s ? (S/N): ", p._ID);
        scanf("%s", listar);
        if ((((strcmp(listar, "S") != 0) && (strcmp(listar, "N") != 0)) && (strcmp(listar, "s") != 0)) && (strcmp(listar, "n") != 0))
        {
            printf("\nOpcao Invalida. Formato Invalido. Introduza 'S' / 's' (SIM) ou 'N' / 'n' (NAO).\n\n");
        }
    }

    if ((strcmp(listar, "S") == 0) || (strcmp(listar, "s") == 0))
    {
        _empresa = atribuirLider(_empresa, p);
        printf("\n");
    }

    else
    {
        strcpy(_empresa._projetos[_empresa._last]._liderID, "'DESCONHECIDO'");
        printf("\nLider 'DESCONHECIDO' atribuido.\n\n");
    }

    return _empresa;
}

empresa atribuirLider(empresa _empresa, projeto p)
{
    char stringaux[30];
    printf("\nNome do Administrador que pretende que seja o Lider: ");
    scanf(" %[^\n]s", stringaux);
    printf("\n");

    int i, pos, existe;
    existe = 0;

    for(i=0; i<_empresa._administradores._last; i++)
    {
        if (strcmp(stringaux, _empresa._administradores._dados[i]._nome) == 0)
        {
            pos = i;
            existe = 1;
        }
    }

    if (existe == 0)
    {
        printf("\n!!!ERRO: Nao existe um Administrador com o nome %s.\n", stringaux);
        printf("Lider 'DESCONHECIDO' atribuido.\n\n");
    }

    if (existe == 1)
    {
        printf("\nAdministrador com o nome %s encontrado.\n", stringaux);

        strcpy(_empresa._projetos[_empresa._last]._liderID, stringaux);
        printf("Projeto %s atribuido ao Administrador %s.\n\n", p._ID, stringaux);
    }

    else
    {
        printf("\n!!!ERRO: Nao existem Projetos registados na Empresa.\n\n");
    }

    return _empresa;
}

void listarProjetos(empresa _empresa)
{
    int i;

    if (_empresa._quantidade > 0)
    {
        for (i=0; i<_empresa._last; i++)
        {
            if (strcmp(_empresa._projetos[i]._ID, "DELETED") != 0)
            {
                listarProjeto(_empresa._projetos[i]);
            }
        }
    }

    else
    {
        printf("\n!!!ERRO: Nao existem Projetos registados na Empresa.\n\n");
    }
}

void listarProjeto(projeto f)
{
    printf("\nID: %s\nDesignacao: %s\nLocalizacao: %s\n", f._ID, f._desgn, f._local);
    printf("Data de Criacao: ");
    displayData(f._data);
    printf("\nID do Lider: %s\nTipo: %s\nCondicoes: %s\nObservacoes: %s\n\n", f._liderID, f._tipo, f._cond, f._obs);
}

displayData(data d)
{
    printf("%d/%d/%d", d._dia, d._mes, d._ano);
}

empresa apagarProjeto(empresa _empresa)
{
    char stringaux[30];
    int i, existe;
    existe = 0;

    if (_empresa._quantidade > 0)
    {
        printf("\nID do Projeto a Eliminar: ");
        scanf(" %[^\n]s", stringaux);
        printf("\n");

        for(i=0; i<_empresa._last; i++)
        {
            if (strcmp(stringaux, _empresa._projetos[i]._ID) == 0)
            {
                strcpy(_empresa._projetos[i]._ID, "DELETED");
                existe = 1;
            }
        }

        if (existe == 0)
        {
            printf("\n!!!ERRO: Nao existe um Projeto com o ID %s.\n\n", stringaux);
        }

        if (existe == 1)
        {
            _empresa._quantidade --;
            printf("\nProjeto com o ID %s eliminado.\n\n", stringaux);
        }

    }

    else
    {
        printf("\n!!!ERRO: Nao existem Projetos registados na Empresa.\n\n");
    }
    return _empresa;
}

empresa abrirMenuProjeto(empresa _empresa, int pos)
{
    printf("vMenu do Projeto %s Seleccionado.\n\n", _empresa._projetos[pos]._ID);
    int escolha = 17;
    while (escolha != 0)
    {
        escolha = mostrarMenuUMProjeto(escolha);
        switch(escolha)
        {
        case 1 :
        {
            _empresa = inserirDoacao(_empresa, pos);
            escolha = 0;
            break;
        }

        case 2 :
        {
            _empresa = inserirDoador(_empresa, pos);
            escolha = 0;
            break;
        }

        case 3 :
        {
            _empresa = inserirVoluntario(_empresa, pos);
            escolha = 0;
            break;
        }

        case 4 :
        {
            _empresa = afiliarFuncionario(_empresa, pos);
            escolha = 0;
            break;
        }

        case 5 :
        {
            _empresa = alterarFuncao(_empresa, pos);
            escolha = 0;
            break;
        }

        case 6 :
        {
            _empresa = apagarDoacao(_empresa, pos);
            escolha = 0;
            break;
        }

        case 7 :
        {
            _empresa = apagarDoador(_empresa, pos);
            escolha = 0;
            break;
        }

        case 8 :
        {
            _empresa = apagarVoluntario(_empresa, pos);
            escolha = 0;
            break;
        }

        case 9 :
        {
            procurarDoacao(_empresa, pos);
            escolha = 0;
            break;
        }

        case 10 :
        {
            procurarDoador(_empresa, pos);
            escolha = 0;
            break;
        }

        case 11 :
        {
            procurarVoluntario(_empresa, pos);
            escolha = 0;
            break;
        }

        case 12 :
        {
            procurarFuncionarioNumProjeto(_empresa, pos);
            escolha = 0;
            break;
        }

        case 13 :
        {
            listarDoacoes(_empresa, pos);
            escolha = 0;
            break;
        }

        case 14 :
        {
            listarDoadores(_empresa, pos);
            escolha = 0;
            break;
        }

        case 15 :
        {
            listarVoluntarios(_empresa, pos);
            escolha = 0;
            break;
        }

        case 16 :
        {
            listarFuncionariosNumProjeto(_empresa, pos);
            escolha = 0;
            break;
        }
        }
    }
    return _empresa;
}

int mostrarMenuUMProjeto(int escolha)
{
    char s[30];
    int valid = 0;
    int i;

    while ((escolha < 0) || (escolha > 16))
    {
        printf("\n1) Registar Doacao\n");
        printf("2) Registar Doador\n");
        printf("3) Registar Voluntario\n");
        printf("4) Afiliar Funcionario ao Projeto\n");
        printf("5) Alterar Posicao de um Funcionario no Projeto\n");
        printf("6) Remover Doacao\n");
        printf("7) Remover Doador\n");
        printf("8) Remover Voluntario\n");
        printf("9) Procurar Doacao\n");
        printf("10) Procurar Doador\n");
        printf("11) Procurar Voluntario\n");
        printf("12) Procurar Funcionario (no projeto)\n");
        printf("13) Listar Doacoes\n");
        printf("14) Listar Doadores\n");
        printf("15) Listar Voluntarios\n");
        printf("16) Listar Funcionarios\n");

        printf("\n0) VOLTAR AO MENU INICIAL\n");


        while ((valid == 0) || ((escolha < 0) || (escolha > 16)))
        {
            printf("\nSeleccione a opcao pretendida (0-16): ");
            scanf("%s", s);
            valid = argumentIsInteger(s);

            if (valid == 1)
            {
                escolha = atoi(s);
            }

            if (valid == 0)
            {
                printf("\nOpcao Invalida. Formato Invalido. Introduza um valor NUMERICO entre 0 e 15.\n\n");
                for (i=0; i<strlen(s); i++)
                {
                    s[i] = "";
                }
            }

            else
            {
                if ((escolha < 0) || (escolha > 16))
                {
                    printf("\nOpcao Invalida. Formato Invalido. Introduza um valor entre 0 e 15.\n\n");
                    for (i=0; i<strlen(s); i++)
                    {
                        s[i] = "";
                    }

                    valid = 0;
                }
            }
        }
    }
    return escolha;
}

empresa procurarProjeto(empresa _empresa)
{
    if(_empresa._quantidade > 0)
    {
        char stringaux[30];
        printf("\nID do Projeto a Abrir: ");
        scanf(" %[^\n]s", stringaux);
        printf("\n");

        int i, existe, pos;
        existe = 0;

        for(i=0; i<_empresa._last; i++)
        {
            if (strcmp(stringaux, _empresa._projetos[i]._ID) == 0)
            {
                pos = i;
                existe = 1;
            }
        }

        if (existe == 0)
        {
            printf("\n!!!ERRO: Nao existe um Projeto com o ID %s.\n\n", stringaux);
        }

        if (existe == 1)
        {
            printf("\nProjeto com ID %s encontrado.\n\n", stringaux);
            _empresa = questionaAbrirProjeto(_empresa, _empresa._projetos[pos], pos);
        }
    }

    else
    {
        printf("\n!!!ERRO: Nao existem Projetos registados na Empresa.\n\n");
    }
    return _empresa;
}

empresa questionaAbrirProjeto(empresa _empresa, projeto p, int pos)
{
    char listar[3];

    while ((((strcmp(listar, "S") != 0) && (strcmp(listar, "N") != 0)) && (strcmp(listar, "s") != 0)) && (strcmp(listar, "n") != 0))
    {
        printf("\nPretende abrir a ficha do Projeto %s ? (S/N): ", p._ID);
        scanf("%s", listar);
        if ((((strcmp(listar, "S") != 0) && (strcmp(listar, "N") != 0)) && (strcmp(listar, "s") != 0)) && (strcmp(listar, "n") != 0))
        {
            printf("\nOpcao Invalida. Formato Invalido. Introduza 'S' / 's' (SIM) ou 'N' / 'n' (NAO).\n\n");
        }
    }

    if ((strcmp(listar, "S") == 0) || (strcmp(listar, "s") == 0))
    {
        _empresa = abrirMenuProjeto(_empresa, pos);
    }
    return _empresa;
}

/**********************************************************************/
/**********************************************************************/
/**********************************************************************/

empresa inserirDoacao(empresa _empresa, int pos)
{
    printf("\nID: ");
    scanf(" %[^\n]s", _empresa._projetos[pos]._doacoes._dados[_empresa._projetos[pos]._doacoes._last]._ID);
    printf("\n");
    printf("Data da Doacao (dia, mes, ano)\n");
    printf("Dia: ");
    scanf("%d", &_empresa._projetos[pos]._doacoes._dados[_empresa._projetos[pos]._doacoes._last]._data._dia);
    printf("Mes: ");
    scanf("%d", &_empresa._projetos[pos]._doacoes._dados[_empresa._projetos[pos]._doacoes._last]._data._mes);
    printf("Ano: ");
    scanf("%d", &_empresa._projetos[pos]._doacoes._dados[_empresa._projetos[pos]._doacoes._last]._data._ano);
    printf("\n");
    printf("Quantia: ");
    scanf("%d", &_empresa._projetos[pos]._doacoes._dados[_empresa._projetos[pos]._doacoes._last]._quantia);
    printf("\n");

    strcpy(_empresa._projetos[pos]._doacoes._dados[_empresa._projetos[pos]._doacoes._last]._projetoID, _empresa._projetos[pos]._ID);
    printf("\nDoacao %s inserido com sucesso.\n\n", _empresa._projetos[pos]._doacoes._dados[_empresa._projetos[pos]._doacoes._last]._ID);

    _empresa = questionaAtribuirDoador(pos, _empresa, _empresa._projetos[pos]._doacoes._dados[_empresa._projetos[pos]._doacoes._last]);
    printf("\n");
    _empresa = questionaAtribuirResponsavel(pos, _empresa, _empresa._projetos[pos]._doacoes._dados[_empresa._projetos[pos]._doacoes._last]);

    _empresa._projetos[pos]._doadores._last ++;
    _empresa._projetos[pos]._doadores._quantidade ++;
    return _empresa;
}

empresa questionaAtribuirDoador(int pos, empresa _empresa, doacao p)
{
    char listar[3];

    while ((((strcmp(listar, "S") != 0) && (strcmp(listar, "N") != 0)) && (strcmp(listar, "s") != 0)) && (strcmp(listar, "n") != 0))
    {
        printf("\nPretende associar um Doador a Doacao %s ? (S/N): ", p._ID);
        scanf(" %[^\n]s", listar);
        if ((((strcmp(listar, "S") != 0) && (strcmp(listar, "N") != 0)) && (strcmp(listar, "s") != 0)) && (strcmp(listar, "n") != 0))
        {
            printf("\nOpcao Invalida. Formato Invalido. Introduza 'S' / 's' (SIM) ou 'N' / 'n' (NAO).\n\n");
        }
    }

    if ((strcmp(listar, "S") == 0) || (strcmp(listar, "s") == 0))
    {
        _empresa = atribuirDoador(pos, _empresa, p);
        printf("\n");
    }

    else
    {
        strcpy(_empresa._projetos[pos]._doacoes._dados[_empresa._projetos[pos]._doacoes._last]._doadorID, "'DESCONHECIDO'");
        printf("\nDoador 'DESCONHECIDO' atribuido.\n\n");
    }

    return _empresa;
}

empresa atribuirDoador(int proj, empresa _empresa, doacao p)
{
    char stringaux[30];
    printf("\nID do Doador a associar: ");
    scanf(" %[^\n]s", stringaux);
    printf("\n");

    int i, pos, existe;
    existe = 0;

    for(i=0; i<_empresa._projetos[proj]._doadores._quantidade; i++)
    {
        if (strcmp(_empresa._projetos[proj]._doadores._dados[i]._ID, stringaux) == 0)
        {
            pos = i;
            existe = 1;
        }
    }

    if (existe == 0)
    {
        printf("\n!!!ERRO: Nao existe um Doador com o ID %s.\n", stringaux);
        printf("Doador 'DESCONHECIDO' atribuido.\n\n");
    }

    if (existe == 1)
    {
        printf("\nDoador com o nome %s encontrado.\n", stringaux);

        strcpy(_empresa._projetos[proj]._doacoes._dados[_empresa._projetos[proj]._doacoes._last]._doadorID, stringaux);
        printf("Doacao %s atribuida ao Doador %s.\n\n", p._ID, stringaux);
    }

    else
    {
        printf("\n!!!ERRO: Nao existem Doadores registados no Projeto.\n\n");
    }

    return _empresa;
}

empresa questionaAtribuirResponsavel(int pos, empresa _empresa, doacao p)
{
    char listar[3];

    while ((((strcmp(listar, "S") != 0) && (strcmp(listar, "N") != 0)) && (strcmp(listar, "s") != 0)) && (strcmp(listar, "n") != 0))
    {
        printf("\nPretende associar um Funcionario Responsavel a Doacao %s ? (S/N): ", p._ID);
        scanf(" %[^\n]s", listar);
        if ((((strcmp(listar, "S") != 0) && (strcmp(listar, "N") != 0)) && (strcmp(listar, "s") != 0)) && (strcmp(listar, "n") != 0))
        {
            printf("\nOpcao Invalida. Formato Invalido. Introduza 'S' / 's' (SIM) ou 'N' / 'n' (NAO).\n\n");
        }
    }

    if ((strcmp(listar, "S") == 0) || (strcmp(listar, "s") == 0))
    {
        _empresa = atribuirResponsavel(pos, _empresa, p);
        printf("\n");
    }

    else
    {
        strcpy(_empresa._projetos[pos]._doacoes._dados[_empresa._projetos[pos]._doacoes._last]._funcionarioID, "'DESCONHECIDO'");
        printf("\nFuncionario 'DESCONHECIDO' atribuido.\n\n");
    }

    return _empresa;
}

empresa atribuirResponsavel(int proj, empresa _empresa, doacao p)
{
    char stringaux[30];
    printf("\nID do Funcionario Responsavel a associar: ");
    scanf(" %[^\n]s", stringaux);
    printf("\n");

    int i, pos, existe;
    existe = 0;

    for(i=0; i<_empresa._funcionarios._quantidade; i++)
    {
        if (strcmp(_empresa._funcionarios._dados[i]._ID, stringaux) == 0)
        {
            pos = i;
            existe = 1;
        }
    }

    if (existe == 0)
    {
        printf("\n!!!ERRO: Nao existe um Funcionario com o ID %s.\n", stringaux);
        printf("Funcionario 'DESCONHECIDO' atribuido.\n\n");
    }

    if (existe == 1)
    {
        printf("\nFuncionario com o nome %s encontrado.\n", stringaux);

        strcpy(_empresa._projetos[proj]._doacoes._dados[_empresa._projetos[proj]._doacoes._last]._funcionarioID, stringaux);
        printf("Funcionario %s fica responsavel pela Doacao %s.\n\n", stringaux, p._ID);
    }

    else
    {
        printf("\n!!!ERRO: Nao existem Funcionarios registados.\n\n");
    }

    return _empresa;
}


void listarDoacoes(empresa _empresa, int pos)
{
    int i;

    if (_empresa._projetos[pos]._doacoes._quantidade > 0)
    {
        for (i=0; i<_empresa._projetos[pos]._doacoes._last; i++)
        {
            if (strcmp(_empresa._projetos[pos]._doacoes._dados[i]._ID, "DELETED") != 0)
            {
                listarDoacao(_empresa._projetos[pos]._doacoes._dados[i]);
            }
        }
    }

    else
    {
        printf("\n!!!ERRO: Nao existem Doacoes registados neste Projeto.\n\n");
    }
}

void listarDoacao(doacao f)
{
    printf("\nID: %s\nID do Doador: %s\nID do Funcionario Responsavel: %s\nID do Projeto: %s\n", f._ID, f._doadorID, f._funcionarioID, f._projetoID);
    printf("Data de Doacao: ");
    displayData(f._data);
    printf("\nQuantia: %d$", f._quantia);

}

empresa apagarDoacao(empresa _empresa, int pos)
{
    char stringaux[30];
    int i, existe;
    existe = 0;

    if (_empresa._projetos[pos]._doacoes._quantidade > 0)
    {
        printf("\nID da Doacao a Eliminar: ");
        scanf(" %[^\n]s", stringaux);
        printf("\n");

        for(i=0; i<_empresa._projetos[pos]._doacoes._last; i++)
        {
            if (strcmp(_empresa._projetos[pos]._doacoes._dados[i]._ID, stringaux) == 0)
            {
                strcpy(_empresa._projetos[pos]._doacoes._dados[i]._ID, "DELETED");
                existe = 1;
            }
        }

        if (existe == 0)
        {
            printf("\n!!!ERRO: Nao existe uma Doacao com o ID %s neste Projeto.\n\n", stringaux);
        }

        if (existe == 1)
        {
            _empresa._projetos[pos]._doacoes._quantidade --;
            printf("\nDoacao com o ID %s eliminado.\n\n", stringaux);
        }

    }

    else
    {
        printf("\n!!!ERRO: Nao existem Doacoes registadas neste Projeto.\n\n");
    }
    return _empresa;
}

void procurarDoacao(empresa _empresa, int proj)
{
    if (_empresa._projetos[proj]._doacoes._quantidade > 0)
    {
        char stringaux[30];
        printf("\nID da Doacao a Procurar: ");
        scanf(" %[^\n]s", stringaux);
        printf("\n");

        int i, existe, pos;
        existe = 0;

        for(i=0; i<_empresa._projetos[proj]._doacoes._last; i++)
        {
            if (strcmp(stringaux, _empresa._projetos[proj]._doacoes._dados[i]._ID) == 0)
            {
                pos = i;
                existe = 1;
            }
        }

        if (existe == 0)
        {
            printf("\n!!!ERRO: Nao existe uma Doacao com o ID %s neste Projeto.\n\n", stringaux);
        }

        if (existe == 1)
        {
            printf("\nDoacao com o ID %s encontrado.\n\n", stringaux);
            questionaListarDoacao(_empresa._projetos[proj]._doacoes._dados[pos]);
        }
    }
    else
    {
        printf("\n!!!ERRO: Nao existem Doacoes registadas neste Projeto.\n\n");
    }
}

void questionaListarDoacao(doacao f)
{
    char listar[3];

    while ((((strcmp(listar, "S") != 0) && (strcmp(listar, "N") != 0)) && (strcmp(listar, "s") != 0)) && (strcmp(listar, "n") != 0))
    {
        printf("\nPretende abrir a ficha da Doacao %s ? (S/N): ", f._ID);
        scanf("%s", listar);
        if ((((strcmp(listar, "S") != 0) && (strcmp(listar, "N") != 0)) && (strcmp(listar, "s") != 0)) && (strcmp(listar, "n") != 0))
        {
            printf("\nOpcao Invalida. Formato Invalido. Introduza 'S' / 's' (SIM) ou 'N' / 'n' (NAO).\n\n");
        }
    }

    if ((strcmp(listar, "S") == 0) || (strcmp(listar, "s") == 0))
    {
        listarDoacao(f);
        printf("\n");
    }
}

/**********************************************************************/
/**********************************************************************/
/**********************************************************************/

empresa inserirDoador(empresa _empresa, int pos)
{
    printf("\nID: ");
    scanf(" %[^\n]s", _empresa._projetos[pos]._doadores._dados[_empresa._projetos[pos]._doadores._last]._ID);
    printf("\n");
    printf("Nome: ");
    scanf(" %[^\n]s", _empresa._projetos[pos]._doadores._dados[_empresa._projetos[pos]._doadores._last]._nome);
    printf("\n");
    printf("Local: ");
    scanf(" %[^\n]s", _empresa._projetos[pos]._doadores._dados[_empresa._projetos[pos]._doadores._last]._local);
    printf("\n");
    printf("Intencao: ");
    scanf(" %[^\n]s", _empresa._projetos[pos]._doadores._dados[_empresa._projetos[pos]._doadores._last]._intencao);
    printf("\n");

    printf("\nDoador %s inserido com sucesso.\n\n",  _empresa._projetos[pos]._doadores._dados[_empresa._projetos[pos]._doadores._last]._nome);

    _empresa._projetos[pos]._doadores._last ++;
    _empresa._projetos[pos]._doadores._quantidade ++;
    return _empresa;
}

void listarDoadores(empresa _empresa, int pos)
{
    int i;

    if (_empresa._projetos[pos]._doadores._quantidade > 0)
    {
        for (i=0; i<_empresa._projetos[pos]._doadores._last; i++)
        {
            if (strcmp(_empresa._projetos[pos]._doadores._dados[i]._nome, "DELETED") != 0)
            {
                listarDoador(_empresa._projetos[pos]._doadores._dados[i]);
            }
        }
    }

    else
    {
        printf("\n!!!ERRO: Nao existem Doadores registados neste Projeto.\n\n");
    }
}

void listarDoador(doador f)
{
    printf("\nID: %s\nNome: %s\nLocal: %s\nIntencao: %s\n\n", f._ID, f._nome, f._local, f._intencao);
}

empresa apagarDoador(empresa _empresa, int pos)
{
    char stringaux[30];
    int i, existe;
    existe = 0;

    if (_empresa._projetos[pos]._doadores._quantidade > 0)
    {
        printf("\nNome do Doador a Eliminar: ");
        scanf(" %[^\n]s", stringaux);
        printf("\n");

        for(i=0; i<_empresa._projetos[pos]._doadores._last; i++)
        {
            if (strcmp(_empresa._projetos[pos]._doadores._dados[i]._nome, stringaux) == 0)
            {
                strcpy(_empresa._projetos[pos]._doadores._dados[i]._nome, "DELETED");
                existe = 1;
            }
        }

        if (existe == 0)
        {
            printf("\n!!!ERRO: Nao existe um Doador com o nome %s neste Projeto.\n\n", stringaux);
        }

        if (existe == 1)
        {
            _empresa._projetos[pos]._doadores._quantidade --;
            printf("\nDoador com o nome %s eliminado.\n\n", stringaux);
        }

    }

    else
    {
        printf("\n!!!ERRO: Nao existem Doadores registados neste Projeto.\n\n");
    }
    return _empresa;
}

void procurarDoador(empresa _empresa, int proj)
{
    if (_empresa._projetos[proj]._doadores._quantidade > 0)
    {
        char stringaux[30];
        printf("\nNome do Doador a Procurar: ");
        scanf(" %[^\n]s", stringaux);
        printf("\n");

        int i, existe, pos;
        existe = 0;

        for(i=0; i<_empresa._projetos[proj]._doadores._last; i++)
        {
            if (strcmp(stringaux, _empresa._projetos[proj]._doadores._dados[i]._nome) == 0)
            {
                pos = i;
                existe = 1;
            }
        }

        if (existe == 0)
        {
            printf("\n!!!ERRO: Nao existe um Doador com o nome %s neste Projeto.\n\n", stringaux);
        }

        if (existe == 1)
        {
            printf("\nDoador com o nome %s encontrado.\n\n", stringaux);
            questionaListarDoador(_empresa._projetos[proj]._doadores._dados[pos]);
        }
    }
    else
    {
        printf("\n!!!ERRO: Nao existem Doadores registados neste Projeto.\n\n");
    }
}

void questionaListarDoador(doador f)
{
    char listar[3];

    while ((((strcmp(listar, "S") != 0) && (strcmp(listar, "N") != 0)) && (strcmp(listar, "s") != 0)) && (strcmp(listar, "n") != 0))
    {
        printf("\nPretende abrir a ficha do Doador %s ? (S/N): ", f._nome);
        scanf("%s", listar);
        if ((((strcmp(listar, "S") != 0) && (strcmp(listar, "N") != 0)) && (strcmp(listar, "s") != 0)) && (strcmp(listar, "n") != 0))
        {
            printf("\nOpcao Invalida. Formato Invalido. Introduza 'S' / 's' (SIM) ou 'N' / 'n' (NAO).\n\n");
        }
    }

    if ((strcmp(listar, "S") == 0) || (strcmp(listar, "s") == 0))
    {
        listarDoador(f);
        printf("\n");
    }
}

/**********************************************************************/
/**********************************************************************/
/**********************************************************************/

empresa inserirVoluntario(empresa _empresa, int pos)
{
    printf("\nID: ");
    scanf(" %[^\n]s", _empresa._projetos[pos]._voluntarios._dados[_empresa._projetos[pos]._voluntarios._last]._ID);
    printf("\n");
    printf("Nome: ");
    scanf(" %[^\n]s", _empresa._projetos[pos]._voluntarios._dados[_empresa._projetos[pos]._voluntarios._last]._nome);
    printf("\n");
    printf("Morada: ");
    scanf(" %[^\n]s", _empresa._projetos[pos]._voluntarios._dados[_empresa._projetos[pos]._voluntarios._last]._morada);
    printf("\n");
    printf("Funcao: ");
    scanf(" %[^\n]s", _empresa._projetos[pos]._voluntarios._dados[_empresa._projetos[pos]._voluntarios._last]._funcao);
    printf("\n");
    printf("Educacao: ");
    scanf(" %[^\n]s", _empresa._projetos[pos]._voluntarios._dados[_empresa._projetos[pos]._voluntarios._last]._educ);
    printf("\n");
    printf("Experiencia: ");
    scanf(" %[^\n]s", _empresa._projetos[pos]._voluntarios._dados[_empresa._projetos[pos]._voluntarios._last]._experiencia);
    printf("\n");
    printf("Descricao: ");
    scanf(" %[^\n]s", _empresa._projetos[pos]._voluntarios._dados[_empresa._projetos[pos]._voluntarios._last]._descricao);
    printf("\n");

    _empresa._projetos[pos]._voluntarios._dados[_empresa._projetos[pos]._voluntarios._last]._ISvoluntario = 1;

    printf("\nVoluntario %s inserido com sucesso.\n\n",  _empresa._projetos[pos]._voluntarios._dados[_empresa._projetos[pos]._voluntarios._last]._nome);

    _empresa._projetos[pos]._voluntarios._last ++;
    _empresa._projetos[pos]._voluntarios._quantidade ++;
    return _empresa;
}

void listarVoluntarios(empresa _empresa, int pos)
{
    int i;

    if (_empresa._projetos[pos]._voluntarios._quantidade > 0)
    {
        for (i=0; i<_empresa._projetos[pos]._voluntarios._last; i++)
        {
            if (strcmp(_empresa._projetos[pos]._voluntarios._dados[i]._nome, "DELETED") != 0)
            {
                listarVoluntario(_empresa._projetos[pos]._voluntarios._dados[i]);
            }
        }
    }

    else
    {
        printf("\n!!!ERRO: Nao existem Voluntarios registados neste Projeto.\n\n");
    }
}

void listarVoluntario(funcionario f)
{
    printf("\nID: %s\nNome: %s\nMorada: %s\nFuncao: %s\nEducacao: %s\nExperiencia: %s\nDescricao: %s\n\n",
           f._ID, f._nome, f._morada, f._funcao, f._educ, f._experiencia, f._descricao);
}

empresa apagarVoluntario(empresa _empresa, int pos)
{
    char stringaux[30];
    int i, existe;
    existe = 0;

    if (_empresa._projetos[pos]._voluntarios._quantidade > 0)
    {
        printf("\nNome do Voluntario a Eliminar: ");
        scanf(" %[^\n]s", stringaux);
        printf("\n");

        for(i=0; i<_empresa._projetos[pos]._voluntarios._last; i++)
        {
            if (strcmp(_empresa._projetos[pos]._voluntarios._dados[i]._nome, stringaux) == 0)
            {
                strcpy(_empresa._projetos[pos]._voluntarios._dados[i]._nome, "DELETED");
                existe = 1;
            }
        }

        if (existe == 0)
        {
            printf("\n!!!ERRO: Nao existe um Voluntario com o nome %s neste Projeto.\n\n", stringaux);
        }

        if (existe == 1)
        {
            _empresa._projetos[pos]._voluntarios._quantidade --;
            printf("\nVoluntario com o nome %s eliminado.\n\n", stringaux);
        }

    }

    else
    {
        printf("\n!!!ERRO: Nao existem Voluntarios registados neste Projeto.\n\n");
    }
    return _empresa;
}

void procurarVoluntario(empresa _empresa, int proj)
{
    if (_empresa._projetos[proj]._voluntarios._quantidade > 0)
    {
        char stringaux[30];
        printf("\nNome do Voluntario a Procurar: ");
        scanf(" %[^\n]s", stringaux);
        printf("\n");

        int i, existe, pos;
        existe = 0;

        for(i=0; i<_empresa._projetos[proj]._voluntarios._last; i++)
        {
            if (strcmp(stringaux, _empresa._projetos[proj]._voluntarios._dados[i]._nome) == 0)
            {
                pos = i;
                existe = 1;
            }
        }

        if (existe == 0)
        {
            printf("\n!!!ERRO: Nao existe um Voluntario com o nome %s neste Projeto.\n\n", stringaux);
        }

        if (existe == 1)
        {
            printf("\nVoluntario com o nome %s encontrado.\n\n", stringaux);
            questionaListarVoluntario(_empresa._projetos[proj]._voluntarios._dados[pos]);
        }
    }
    else
    {
        printf("\n!!!ERRO: Nao existem Voluntarios registados neste Projeto.\n\n");
    }
}

void questionaListarVoluntario(funcionario f)
{
    char listar[3];

    while ((((strcmp(listar, "S") != 0) && (strcmp(listar, "N") != 0)) && (strcmp(listar, "s") != 0)) && (strcmp(listar, "n") != 0))
    {
        printf("\nPretende abrir a ficha do Voluntario %s ? (S/N): ", f._nome);
        scanf("%s", listar);
        if ((((strcmp(listar, "S") != 0) && (strcmp(listar, "N") != 0)) && (strcmp(listar, "s") != 0)) && (strcmp(listar, "n") != 0))
        {
            printf("\nOpcao Invalida. Formato Invalido. Introduza 'S' / 's' (SIM) ou 'N' / 'n' (NAO).\n\n");
        }
    }

    if ((strcmp(listar, "S") == 0) || (strcmp(listar, "s") == 0))
    {
        listarVoluntario(f);
        printf("\n");
    }
}

/**********************************************************************/
/**********************************************************************/
/**********************************************************************/

empresa afiliarFuncionario(empresa _empresa, int pos)
{
    int i;

    if (_empresa._funcionarios._quantidade > 0)
    {
        char stringaux[30];
        printf("\nNome do Funcionario a associar: ");
        scanf(" %[^\n]s", stringaux);
        printf("\n");

        int i, existe, pos;
        existe = 0;

        for(i=0; i<_empresa._funcionarios._last; i++)
        {
            if (strcmp(stringaux, _empresa._funcionarios._dados[i]._nome) == 0)
            {
                pos = i;
                existe = 1;
            }
        }

        if (existe == 0)
        {
            printf("\n!!!ERRO: Nao existe um Funcionario com o nome %s na Empresa.\n\n", stringaux);
        }

        if (existe == 1)
        {
            printf("\nFuncionario com o nome %s encontrado.\n", stringaux);

            _empresa = acrescentarFuncionarioaProjeto(_empresa, pos, _empresa._funcionarios._dados[pos]);
            printf("Funcionario com o nome %s associado ao projeto.\n", stringaux);

            _empresa._projetos[pos]._funcionarios._last ++;
            _empresa._projetos[pos]._funcionarios._quantidade ++;
        }
    }

    else
    {
        printf("\n!!!ERRO: Nao existem Funcionarios registados na Empresa.\n\n");
    }

    return _empresa;
}

empresa acrescentarFuncionarioaProjeto(empresa _empresa, int pos, funcionario f)
{
    strcpy(_empresa._projetos[pos]._funcionarios._dados[_empresa._projetos[pos]._funcionarios._last]._ID, f._ID);
    strcpy(_empresa._projetos[pos]._funcionarios._dados[_empresa._projetos[pos]._funcionarios._last]._nome, f._nome);
    strcpy(_empresa._projetos[pos]._funcionarios._dados[_empresa._projetos[pos]._funcionarios._last]._morada, f._morada);
    strcpy(_empresa._projetos[pos]._funcionarios._dados[_empresa._projetos[pos]._funcionarios._last]._dept, f._dept);
    strcpy(_empresa._projetos[pos]._funcionarios._dados[_empresa._projetos[pos]._funcionarios._last]._educ, f._educ);
    strcpy(_empresa._projetos[pos]._funcionarios._dados[_empresa._projetos[pos]._funcionarios._last]._experiencia, f._experiencia);
    strcpy(_empresa._projetos[pos]._funcionarios._dados[_empresa._projetos[pos]._funcionarios._last]._descricao, f._descricao);
    strcpy(_empresa._projetos[pos]._funcionarios._dados[_empresa._projetos[pos]._funcionarios._last]._posicao, f._posicao);
    _empresa._projetos[pos]._funcionarios._dados[_empresa._projetos[pos]._funcionarios._last]._salario = f._salario;
    _empresa._projetos[pos]._funcionarios._dados[_empresa._projetos[pos]._funcionarios._last]._ISvoluntario = f._ISvoluntario;

    char stringaux2[30];
    printf("\nFuncao a atribuir ao Funcionario %s no projeto: ", f._nome);
    scanf(" %[^\n]s", stringaux2);
    printf("\n");

    strcpy(_empresa._projetos[pos]._funcionarios._dados[_empresa._projetos[pos]._funcionarios._last]._funcao, stringaux2);

    return _empresa;
}

void procurarFuncionarioNumProjeto(empresa _empresa, int proj)
{
    if (_empresa._projetos[proj]._funcionarios._quantidade > 0)
    {
        char stringaux[30];
        printf("\nNome do Funcionario a Procurar: ");
        scanf(" %[^\n]s", stringaux);
        printf("\n");

        int i, existe, pos;
        existe = 0;

        for(i=0; i<_empresa._projetos[proj]._funcionarios._last; i++)
        {
            if (strcmp(stringaux, _empresa._projetos[proj]._funcionarios._dados[i]._nome) == 0)
            {
                pos = i;
                existe = 1;
            }
        }

        if (existe == 0)
        {
            printf("\n!!!ERRO: Nao existe um Funcionario com o nome %s associado a este Projeto.\n\n", stringaux);
        }

        if (existe == 1)
        {
            printf("\nFuncionario com o nome %s encontrado.\n\n", stringaux);
            questionaListarFuncionarioNumProjeto(_empresa._projetos[proj]._funcionarios._dados[pos]);
        }
    }
    else
    {
        printf("\n!!!ERRO: Nao existem Funcionarios associados a este Projeto.\n\n");
    }
}

void questionaListarFuncionarioNumProjeto(funcionario f)
{
    char listar[3];

    while ((((strcmp(listar, "S") != 0) && (strcmp(listar, "N") != 0)) && (strcmp(listar, "s") != 0)) && (strcmp(listar, "n") != 0))
    {
        printf("\nPretende abrir a ficha do Funcionario %s ? (S/N): ", f._nome);
        scanf("%s", listar);
        if ((((strcmp(listar, "S") != 0) && (strcmp(listar, "N") != 0)) && (strcmp(listar, "s") != 0)) && (strcmp(listar, "n") != 0))
        {
            printf("\nOpcao Invalida. Formato Invalido. Introduza 'S' / 's' (SIM) ou 'N' / 'n' (NAO).\n\n");
        }
    }

    if ((strcmp(listar, "S") == 0) || (strcmp(listar, "s") == 0))
    {
        listarFuncionarioNumProjeto(f);
        printf("\n");
    }
}

void listarFuncionariosNumProjeto(empresa _empresa, int pos)
{
    int i;

    if (_empresa._projetos[pos]._funcionarios._quantidade > 0)
    {
        for (i=0; i<_empresa._projetos[pos]._funcionarios._last; i++)
        {
            if (strcmp(_empresa._projetos[pos]._funcionarios._dados[i]._nome, "DELETED") != 0)
            {
                listarFuncionario(_empresa._projetos[pos]._funcionarios._dados[i]);
            }
        }
    }

    else
    {
        printf("\n!!!ERRO: Nao existem Funcionarios associados a este Projeto.\n\n");
    }
}

void listarFuncionarioNumProjeto(funcionario f)
{
        printf("\nID: %s\nNome: %s\nMorada: %s\nFuncao: %s\nDepartamento: %s\nEducacao: %s\nExperiencia: %s\nDescricao: %s\nSalario: %d$\n\nPosicao: %s\n\n",
           f._ID, f._nome, f._morada, f._funcao, f._dept, f._educ, f._experiencia, f._descricao, f._salario, f._posicao);
}

empresa alterarFuncao(empresa _empresa, int proj)
{
    if (_empresa._projetos[proj]._funcionarios._quantidade > 0)
    {
        char stringaux[30];
        printf("\nNome do Funcionario a quem pretende alterar a Funcao: ");
        scanf(" %[^\n]s", stringaux);
        printf("\n");

        int i, existe, pos;
        existe = 0;

        for(i=0; i<_empresa._projetos[proj]._funcionarios._last; i++)
        {
            if (strcmp(stringaux, _empresa._projetos[proj]._funcionarios._dados[i]._nome) == 0)
            {
                pos = i;
                existe = 1;
            }
        }

        if (existe == 0)
        {
            printf("\n!!!ERRO: Nao existe um Funcionario com o nome %s associado a este Projeto.\n\n", stringaux);
        }

        if (existe == 1)
        {
            printf("\nFuncionario com o nome %s encontrado.\n\n", stringaux);

            char stringaux2[30];
            printf("Funcao a atribuir ao Funcionario %s no projeto: ", stringaux);
            scanf(" %[^\n]s", stringaux2);
            printf("\n");

            strcpy(_empresa._projetos[proj]._funcionarios._dados[pos]._funcao, stringaux2);

            printf("Nova Funcao atribuida com sucesso.\n\n", stringaux);
        }
    }
    else
    {
        printf("\n!!!ERRO: Nao existem Funcionarios associados a este Projeto.\n\n");
    }

    return _empresa;
}

/**********************************************************************/
/**********************************************************************/
/**********************************************************************/

int argumentIsInteger(char arg[]) /** Verifica se uma dada cadeia de caracteres é constituida somente por digitos. Função auxiliar para validar os inputs de numeros.*/
{
    int j = 0;
    int valid = 1;
    for (j=0; j<strlen(arg); j++)
    {
        if (!isdigit(arg[j]))
        {
            valid = 0;
        }
    }
    return valid;
}
