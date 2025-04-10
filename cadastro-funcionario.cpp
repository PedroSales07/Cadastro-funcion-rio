/*
//------------// Créditos //----------//
Desenvolvedor:   Pedro Paulo Dias Sales
Data de Criação: 05/11/2024 
Contatos: 
Email    -       pedrosalesmcd@gmail.com
Github   -       github.com/PedroSales07
Wpp      -       (21) 96865-6996
Descrição:
	        Este programa em C++ permite o cadastro, consulta e exibição
			de funcionários, com cálculo automático do salário líquido 
			com base no valor/hora e nas horas trabalhadas, aplicando as
			faixas de desconto do INSS. É possível salvar e carregar os 
			dados de um arquivo externo, bem como exibir funcionários por
		    diferentes faixas salariais.
	
			Funcionalidades:
			- Cadastro de até 50 funcionários com CPF único.
		    - Cálculo do salário líquido com desconto do INSS.
		    - Busca e exibição de funcionários cadastrados.
		    - Filtros por faixa salarial.
		    - Salvamento e carregamento de dados via arquivo externo.
*/
#include<stdio.h>                            
#include<stdlib.h>
#include<iostream>                            //bibliotecas 
#include<locale.h>
using namespace std;
typedef struct{
	int cpf;
	char nome[50];
	char sexo;                            
	int idade;                                //conjunto de variáveis de diferentes tipos
	float horasTrabalhadas;
	float valorhora;
	float salarioLiquido;
}Pessoa;
Pessoa funcionario[50];
int total = 0;                                                       
void pesquisarFuncionario();
    
    
    
    bool existeCpf(int pesq_cpf) { //verificar se o cpf já está matriculado
    for (int i = 0; i < total; i++) {                           
        if (funcionario[i].cpf == pesq_cpf)
		return true;
        }
    return false;
    }

    void calcularLiquido(){ //cálculo de desconto do inss
    	float aux = funcionario[total].horasTrabalhadas * funcionario[total].valorhora;
    	float desconto_inss =  aux;
    	if(aux < 1751.81){
    	aux = aux / 100;
    	aux = aux * 8;
		}else if(aux >= 1751.81 && aux < 2919.72 ){
		aux = aux / 100;                                        
    	aux = aux * 9;
		}else if(aux >= 2919.73 && aux < 5839.45){
    	aux = aux / 100;
    	aux = aux * 11;
        }
        desconto_inss = (desconto_inss) - (aux);
        funcionario[total].salarioLiquido = desconto_inss;
    }
    
    void adicionar(){  //adicionar um funcionário
	int pesq_cpf;
     	system("cls");
        cout<<"_________ADICIONAR__________"<<endl<<endl;
	    cout<<"**DADOS PRINCIPAIS**"<<endl;
        if(total<=50){
            cout<<"FUNCIONARIO "<<total<<endl;                          
            cout<<"CPF: "; cin>>funcionario[total].cpf;
            for(int i=0; i<total; i++){
            	while(funcionario[total].cpf==funcionario[i].cpf){ //verifica se o cpf já está matriculado 
            		system("cls");
            		system("color 04");
            		cout<<"FUNCIONÁRIO JA CADASTRADO!"<<endl;
            		system("pause");
            		system("color 0A");
            		return pesquisarFuncionario();                       
				}
				
			}
		cout<<"NOME: "; cin>>funcionario[total].nome;	
		cout<<"SEXO[M/F]: "; cin>>funcionario[total].sexo;
        cout<<"IDADE: "; cin>>funcionario[total].idade;
        cout<<"HORAS TRABALHADAS: "; cin>>funcionario[total].horasTrabalhadas;
        cout<<"VALOR DA HORA: "; cin>>funcionario[total].valorhora;
		}else{    			    
            system("color");
    	    cout<<"SISTEMA LOTADO"<<endl;
    	    system("pause");  	    
        }
        calcularLiquido();
	    total++;
    }

    void exibirFuncionario(int i){ //exibe o funcionário da posição [i] do vetor
        cout<<endl<<"_____FUNCIONÁRIO "<<i<<"_____"<<endl;
        cout<<"CPF..............: "<<funcionario[i].cpf<<endl;
        cout<<"NOME.............: "<<funcionario[i].nome<<endl;                 
        cout<<"IDADE............: "<<funcionario[i].idade<<endl;
        cout<<"SEXO.............: "<<funcionario[i].sexo<<endl;
        cout<<"SALÁRIO LÍQUIDO..: "<<funcionario[i].salarioLiquido<<endl;
	    cout<<"_________________"<<endl;	    
    }

    void buscarFuncionario(){ //verifica se o funcionário está matriculado e exibe ou adiciona um novo funcionário
    	int resposta;
    	char opcao;
    	system("cls");
    	cout<<"BUSCAR"<<endl;
    	cout<<"cpf: "; cin>>resposta;                            
    	for (int i = 0; i < total; i++) {
        if (funcionario[i].cpf == resposta) {
            exibirFuncionario(i);
            system("pause");
            return; 
            }
        }
        system("color 04");
        cout<<endl<<"FUNCIONÁRIO NÃO CADASTRADO!"<<endl;
        system("pause");
        system("cls");
        system("color 0A");
        cout<<"DESEJA ADICIONAR NO SISTEMA? (S/N): "; cin>>opcao;
        if (opcao == 'S' || opcao == 's') {
        adicionar();
        system("cls");
        cout<<"FUNCIONÁRIO ADICIONADO COM SUCESSO!"<<endl;
        system("pause");
        }
	}

    void pesquisarFuncionario(){ //verifica se o funcionário está matriculado e exibe ou retorna a função: adicionar();
    	int pesq_cpf;
    	char resposta;
     	system("cls");
    	cout<<"PESQUISAR CPF: "; cin>>pesq_cpf;		
	    if(existeCpf(pesq_cpf)){
	 	system("color 04");
	 	cout<<endl<<"FUNCIONÁRIO JÁ CADASTRADO!"<<endl;
	 	system("pause");
        }else{
        	system("color 04");
        cout<<endl<<"FUNCIONÁRIO NÃO CADASTRADO!"<<endl;
        system("pause");
        system("cls");
        system("color 0A");
     	cout<<"DESEJA ADICIONAR NO SISTEMA? (S/N): "; cin>>resposta;
        if (resposta == 'S' || resposta == 's'){
            adicionar();
            cout<<"FUNCIONÁRIO ADICIONADO COM SUCESSO!"<<endl;
        }else{
        	system("cls");
        	system("color 04");
            cout<<"OPERAÇÃO CANCELADA!"<< endl;
            system("pause");
          }
        } 
    }

    void exibirFuncionarios_salario500(){ //exibi funcionários com salário inferior a R$ 500
    	system("cls");
	    if(total <= 0){
        system("color 04");
        cout<<"SISTEMA VAZIO"<<endl;
        system("pause");
        return;
        }
	    cout<<endl<<"FUNCIONÁRIOS COM SALÁRIO INFERIOR A R$ 500:"<<endl;
	    bool encontrouFuncionario = false; 
        for(int i = 0; i < total; i++){
	        if(funcionario[i].salarioLiquido < 500){
	            exibirFuncionario(i);
	            encontrouFuncionario = true;
            }
        }
	    if (!encontrouFuncionario) { 
	        system("color 04");
	        cout<<"SISTEMA VAZIO"<<endl;
        }
        system("pause"); 
    }
    
    void exibirFuncionarios_salario1000(){ //exibi funcionários com salário inferior a R$ 1.000
    	system("cls");
	    if(total <= 0){
        system("color 04");
        cout<<"SISTEMA VAZIO"<<endl;
        system("pause");
        return;
        }
	    cout<<endl<<"FUNCIONÁRIOS COM SALÁRIO INFERIOR A R$ 1.000:"<<endl;
	    bool encontrouFuncionario = false; 
        for(int i = 0; i < total; i++){
	        if(funcionario[i].salarioLiquido < 1000){
	            exibirFuncionario(i);
	            encontrouFuncionario = true;
            }
        }
	    if(!encontrouFuncionario){ 
	        system("color 04");
	        cout<<"SISTEMA VAZIO"<<endl;
        }
        system("pause"); 
    }
    
    void exibirFuncionarios_salario4000(){ //exibi funcionários com salário superior a R$ 4.000
    	system("cls");
	    if(total <= 0){
        system("color 04");
        cout<<"SISTEMA VAZIO"<<endl;
        system("pause");
        return;
        }
	    cout<<endl<<"FUNCIONÁRIOS COM SALÁRIO SUPERIOR OU IGUAL A R$ 4.000:"<<endl;
	    bool encontrouFuncionario = false; 
        for(int i = 0; i < total; i++){
	        if(funcionario[i].salarioLiquido >= 4.000){
	            exibirFuncionario(i);
	            encontrouFuncionario = true;
            }
        }
	    if(!encontrouFuncionario){ 
	        system("color 04");
	        cout<<"SISTEMA VAZIO"<<endl;
        }
        system("pause"); 
    }
    
    void exibirFuncionarios_salario5000(){ //exibi funcionários com salário superior ou igual a R$ 5.000
    	system("cls");
	    if(total <= 0){
        system("color 04");
        cout<<"SISTEMA VAZIO"<<endl;
        system("pause");
        return;
        }
	    cout<<endl<<"FUNCIONÁRIOS COM SALÁRIO SUPERIOR OU IGUAL A R$ 5.000:"<<endl;
	    bool encontrouFuncionario = false; 
        for(int i = 0; i < total; i++){
	        if(funcionario[i].salarioLiquido >= 5000){
	            exibirFuncionario(i);
	            encontrouFuncionario = true;
            }
        }
	    if(!encontrouFuncionario){ 
	        system("color 04");
	        cout<<"SISTEMA VAZIO"<<endl;
        }
        system("pause"); 
    }
    
    void exibirFuncionarios_salario7000(){ //exibi funcionários com salário superior ou igual a R$ 7.000
    	system("cls");
	    if(total <= 0){
        system("color 04");
        cout<<"SISTEMA VAZIO"<<endl;
        system("pause");
        return;
        }
	    cout<<endl<<"FUNCIONÁRIOS COM SALÁRIO SUPERIOR OU IGUAL A R$ 7.000:"<<endl;
	    bool encontrouFuncionario = false; 
        for(int i = 0; i < total; i++){
	        if(funcionario[i].salarioLiquido >= 7000){
	            exibirFuncionario(i);
	            encontrouFuncionario = true;
            }
        }
	    if(!encontrouFuncionario){ 
	        system("color 04");
	        cout<<"SISTEMA VAZIO"<<endl;
        }
        system("pause"); 
    }
    
    void exibirFuncionarios_salario10000(){ // exibe funcionários com salário superior ou igual a R$ 10.000
	    system("cls");
	    if(total <= 0){
        system("color 04");
        cout<<"SISTEMA VAZIO"<<endl;
        system("pause");
        return; 
        }
	    cout<<endl<<"FUNCIONÁRIOS COM SALÁRIO SUPERIOR OU IGUAL A R$ 10.000:"<<endl;
	    bool encontrouFuncionario = false; 
        for(int i = 0; i < total; i++){
	        if(funcionario[i].salarioLiquido >= 10000){
	            exibirFuncionario(i);
	            encontrouFuncionario = true;
            }
        }
	    if(!encontrouFuncionario){ 
	        system("color 04");
	        cout<<"SISTEMA VAZIO"<<endl;
        }
        system("pause"); 
    }
    
    void exibirTodosOsFuncionarios(){ //exibi todos os funcionários 
    	system("cls");
    	if(total<=0){
		system("color 04");
		cout<<"SISTEMA VAZIO"<<endl;
	    }else{
	     cout<<"_________EXIBIR_________"<<endl<<endl;
        for(int i=0; i<total; i++){
        exibirFuncionario(i);
      }
    }
    system("pause"); 
    }

    void exibir(){ //menu de exibição, com chamada para as respectivas funções
	int op_2;
	system("cls");
    cout<<"_________EXIBIR FUNCIONARIOS_________"<<endl<<endl;
	cout<<"[1]FUNCIONÁRIOS COM SALÁRIO INFERIOR A R$ 500"<<endl;
    cout<<"[2]FUNCIONÁRIOS COM SALÁRIO INFERIOR A R$ 1000"<<endl;
	cout<<"[3]FUNCIONÁRIOS COM SALÁRIO SUPERIOR A R$ 4000"<<endl;
	cout<<"[4]FUNCIONÁRIOS COM SALÁRIO SUPERIOR OU IGUAL A R$ 5000"<<endl;
	cout<<"[5]FUNCIONÁRIOS COM SALÁRIO SUPERIOR OU IGUAL A R$ 7000"<<endl;
	cout<<"[6]FUNCIONÁRIOS COM SALÁRIO SUPERIOR OU IGUAL A ?R$ 10000"<<endl;
	cout<<"[7]TODOS OS FUNCIONÁRIOS "<<endl<<endl;
	cout<<"OPÇÃO: "; cin>>op_2;
	switch(op_2){
		case 1: exibirFuncionarios_salario500();    break;
		case 2: exibirFuncionarios_salario1000();   break;
		case 3: exibirFuncionarios_salario4000();   break;
		case 4: exibirFuncionarios_salario5000();   break;
		case 5: exibirFuncionarios_salario7000();   break;
		case 6: exibirFuncionarios_salario10000();  break;
		case 7: exibirTodosOsFuncionarios();        break;
	}
   }

    void salvarDados(){ //salvar os dados no arquivo externo
        char nome_arq[50];
		FILE *arq;
		system("cls");
	    cout<<"___SALVAR PROGRAMA ARQUIVO EXTERNO___"<<endl;
	    cout<<"Nome do arquivo externo: "; cin>>nome_arq;
	    arq=fopen(nome_arq, "w");
	        if(arq==NULL){
	        system("color 04");
		    cout<<"ERRO DURANTE O SALVAMENTO!"<<endl;
	        }else{
		        fprintf(arq,"TOTAL = %d\n", total);
		        for(int i=0; i<total; i++){
		        fprintf(arq,"\nFUNCIONÁRIO %d", i);
			    fprintf(arq,"\nCPF = %d", funcionario[i].cpf);
			    fprintf(arq,"\nNOME = %s", funcionario[i].nome);
			    fprintf(arq,"\nIDADE = %d", funcionario[i].idade);
			    fprintf(arq,"\nSEXO = %c", funcionario[i].sexo);
			    fprintf(arq,"\nLÍQUIDO = %.1f", funcionario[i].salarioLiquido);
			    fprintf(arq,"__________________________");
	            }
	            fclose(arq);
	        }
	    system("pause");   
    }

    void carregarDados(){ //mostar os dados salvos no arquivo externo
    char nome_arq[50];
    FILE *arq;
    system("cls");
    cout<<"___CARREGAR PROGRAMA ARQUIVO EXTERNO___"<<endl;
    cout<<"Nome do arquivo externo: "; cin>>nome_arq;
    arq = fopen(nome_arq, "r");
    if (arq == NULL) {
        system("color 04");
        cout << "ERRO AO CARREGAR O ARQUIVO!" << endl;
        system("pause");
        return;
    }else{
        fscanf(arq, "TOTAL = %d\n", &total);
        cout<<endl<<"TOTAL = "<<total<<endl<<endl;
    for (int i = 0; i < total; i++) {
    	fscanf(arq, "\nALUNO %d", &i);
        fscanf(arq, "\nCPF = %d", &funcionario[i].cpf);
        fscanf(arq, "\nNOME = %s", funcionario[i].nome);  
        fscanf(arq, "\nIDADE = %d", &funcionario[i].idade);
        fscanf(arq, "\nSEXO = %c", &funcionario[i].sexo);
        fscanf(arq, "\nLÍQUIDO = %f", &funcionario[i].salarioLiquido);
       
        cout<<"ALUNO "<<i<<endl;
        cout<<"CPF = "<<funcionario[i].cpf<<endl;
        cout<<"NOME = "<<funcionario[i].nome<<endl;
        cout<<"IDADE = "<<funcionario[i].idade<<endl;
        cout<<"SEXO = "<<funcionario[i].sexo<<endl;
        cout<<"LÍQUIDO = "<<funcionario[i].salarioLiquido<<endl;
        cout<<"_____________________"<<endl;
    }
    fclose(arq);
    system("color 0A");
    cout << "DADOS CARREGADOS COM SUCESSO!" << endl;
    system("pause");
       }
    }

    void salvar_carregar(){ //menu de salvar/carregar os dados 
        int aux;
    	system("cls");
    	cout<<"___SALVAR OU CARREGAR DADOS____"<<endl;
    	cout<<endl<<"  [1]SALVAR"<<endl;
    	cout<<"  [2]CARREGAR"<<endl<<endl;
    	cout<<"  OPÇÃO: "; cin>>aux;
    	
    	switch(aux){
    		case 1: 
    		    salvarDados();   
	            break;
	    	case 2: 
	    	    carregarDados();
		            break;
			default: 
			system("cls");
			system("color 04");
			cout<<"OPÇÃO INVALIDA, TENTE NOVAMENTE!"<<endl; 
			system("pause"); 
			        break;			     
	    }
	}
	
int main(){ //função principal
	setlocale(LC_ALL, "portuguese");
	int op;
	do{
		system("cls");
		system("color 0A");
		cout<<"_______MENU PRINCIPAL_______"<<endl<<endl;
		cout<<"[1]ADICIONAR"<<endl;
		cout<<"[2]BUSCAR"<<endl;
		cout<<"[3]EXIBIR"<<endl;
		cout<<"[4]SALVAR/CARREGAR"<<endl;
		cout<<"[0]SAIR"<<endl<<endl;
		cout<<"OPÇÃO: "; cin>>op;
		
		switch(op){
			
			case 1: pesquisarFuncionario();
			    break; 
			case 2: buscarFuncionario();
			    break;
			case 3: exibir();
			    break;
			case 4: salvar_carregar();
			    break;    
		}
	}while(op!=0);
}