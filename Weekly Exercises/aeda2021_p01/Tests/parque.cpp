#include "parque.h"
#include <iterator>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned lot, unsigned nMaxCli) : lotacao(lot), numMaximoClientes(nMaxCli){
    vagas = lotacao;
}

unsigned ParqueEstacionamento::getNumLugares() const
{
    return lotacao;
}

unsigned ParqueEstacionamento::getNumMaximoClientes() const
{
    return numMaximoClientes;
}

int ParqueEstacionamento::posicaoCliente(const string & nome) const{
    for (auto iter = clientes.begin(); iter != clientes.end(); ++iter) {
        if (iter->nome==nome)
            return iter - clientes.begin();
    }
    return -1;
}

bool ParqueEstacionamento::adicionaCliente(const string & nome){
    if (clientes.size()<numMaximoClientes){
        InfoCartao cliente;
        cliente.nome=nome;
        cliente.presente=false;
        clientes.push_back(cliente);
        return true;
    }
    return false;
}

bool ParqueEstacionamento::entrar(const string & nome){
    int index=posicaoCliente(nome);
    if (index==-1||vagas==0)return false;
    else{
        if(clientes[index].presente)return false;
        clientes[index].presente=true;
        vagas--;
        return true;
    }
}

bool ParqueEstacionamento::retiraCliente(const string & nome){
    int index=posicaoCliente(nome);
    if (index==-1||clientes[index].presente)return false;
    else{
        clientes.erase(clientes.begin()+index);
        return true;
    }
}

bool ParqueEstacionamento::sair(const string & nome){
    int index=posicaoCliente(nome);
    if (index==-1||!clientes[index].presente)return false;
    else{clientes[index].presente=false;
    return true;
    }
}

unsigned ParqueEstacionamento::getNumLugaresOcupados() const{return lotacao-vagas;}

unsigned ParqueEstacionamento::getNumClientesAtuais() const{return clientes.size();}

