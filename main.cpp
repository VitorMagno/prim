#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>
#include<queue>
#include<algorithm>
#include<climits>
#include<array>

using namespace std;

bool naoEhDoMesmoConjunto(int paiDoVerticeVizinho, int paiDoVerticeAtual){
  if(paiDoVerticeVizinho != paiDoVerticeAtual){
    return false;
  }
  return true;
}

bool existeCaminho(int valor){
  if(valor == INT_MAX){
    return false;
  }
  return true;
}
bool atualizarDistancia(int custo, int pesoDoAtual, int pesoVizinho){
  if(custo < pesoVizinho + pesoDoAtual){
    return false;
  }
  return true;
}
void prim(int s, int t, int n, int** G, int *distAcumulada, int *paiDe)
{
  // inicializa d e p
    int distIndividual[t];
    for (int i = s; i <= t; i++)
    {
        distAcumulada[i] = 100000;
        paiDe[i]= i;
        //cout << dist.at(i) << paiDe.at(i) <<endl;
    }
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> fila;
    fila.push({0,s});
    while(!fila.empty()){
      pair<int,int> primeiroElementoDaFila = fila.top();
      fila.pop();
      int verticeAtual = primeiroElementoDaFila.second;
      int pesoVerticeAtual = primeiroElementoDaFila.first;
      for(int i = 1; i < t; i++){
        int vizinhoVerticeAtual = i;
        int pesoDoVizinhoPeloVerticeAtual = G[verticeAtual][vizinhoVerticeAtual];
        if(existeCaminho(pesoDoVizinhoPeloVerticeAtual)){
          if(atualizarDistancia(distAcumulada[vizinhoVerticeAtual], pesoVerticeAtual, pesoDoVizinhoPeloVerticeAtual)){
            if(naoEhDoMesmoConjunto(paiDe[vizinhoVerticeAtual], paiDe[verticeAtual])){
              distAcumulada[vizinhoVerticeAtual] = pesoDoVizinhoPeloVerticeAtual + pesoVerticeAtual;
              distIndividual[vizinhoVerticeAtual] = pesoVerticeAtual;
              paiDe[vizinhoVerticeAtual] = verticeAtual;
            }
          }
        }
      }
    }
    
    return;
}


void solutions(bool saida, string nomeSaida, bool solucao, int s, int t, int** G, int n){
    int dist[t];
    int pais[t];
    //vector<int> *ptrDist = &dist;
    //vector<int> *ptrPais = &pais;
    prim(s, t, n, G, &dist[0], &pais[0]);
    string resposta="";
    if (saida && solucao){
    // escreve a saida das distancias ordenadas num arquivo txt
        ofstream out;
        out.open(nomeSaida, ofstream::out);
        for (int i = t; i > s; i--)
        {
          if(i == s){
            resposta = "raiz\n " + resposta;
          }else if (pais[i] == i){
            resposta = "nao existe caminho\n" + resposta;
          }else{
            resposta = pais[pais[i]] + '->' + pais[i] + ' : ' + (dist[i] - dist[i-1]) +"\n" + resposta;
          }
          out << resposta << endl;
        }
        out.close();
        return;
    }else{
    // exibe no terminal as distancias ordenadas de cada aresta
      for (int i = t; i > s; i--)
        {
          if(i == s){
            resposta = "raiz\n " + resposta;
          }else if (pais[i] == i){
            resposta = "nao existe caminho\n" + resposta;
          }else{
            resposta = pais[pais[i]] + '->' + pais[i] + ' : ' + (dist[i] - dist[i-1]) +"\n" + resposta;
          }
          cout << resposta << endl;
        }
    return;
    }
    //if(saida){
    // escreve o peso do menor caminho num arquivo txt
        cout << "nao implementado nesse algoritmo" <<endl;
       /* ofstream out;
        out.open(nomeSaida, ofstream::out);
        int sumCaminho;
        for(int i = s; i <= t; i++){
          if(dist[i] == 100000){
            continue;
          }else{
            sumCaminho = dist[i];
          }
        }
        out << "peso do menor caminho: "<< sumCaminho << endl;
        out.close();
        return;*/
    //}
    
    // exibe no terminal o peso do menor caminho
    /*int sumCaminho=0;
    for(int i = s; i <= t; i++){
      if(dist[i] == 100000){
        continue;
      }else{
        //cout<< "v: " << i << " distancia " << dist[i]<<endl;
        sumCaminho = dist[i];
      }
    }
    
    cout << "peso do menor caminho: "<< sumCaminho << endl;*/
    //return;
}

int main(int argc, char const *argv[]){

  const int BUFFER_LENGTH = 8;      // Tamanho do buffer de leitura das linhas dos arquivos de entrada.
  char buffer[BUFFER_LENGTH];       // Buffer de leitura mencionado.

  string opReadFile = "-f";
  bool read = false;
  string opHelp = "-h";
  string opInicial = "-i";
  string opSolucao = "-s";
  bool solucao = false;
  bool inicial = false;
  string opFinal = "-l";
  bool final = false;
  string opSaida = "-o";
  string nomeSaida;
  bool saida = false;
  int s = 1;
  int t = 999;
  int** G;
  int n;

  for (int i = 1; i < argc; i++){
    if (argv[i] == opReadFile){
      // Input File Stream pra abrir o arquivo de entrada.
      ifstream file_input;

      // Tenta abrir arquivo informado.
      file_input = ifstream(argv[i+1], ios::binary);

      // Encerra se houve erro ao abrir arquivo com a lista de vitórias.
      if (!file_input.is_open()) {
        cout << "Erro ao abrir arquivo " << argv[i+1] << '\n';
        return 1;
      }
      
      // Pega primeira linha para dentro do buffer.
      file_input.getline(buffer, BUFFER_LENGTH);
      
      int qtd_vert = atoi(&buffer[0]);  // Ordem do grafo
      int qtd_ares = atoi(&buffer[2]);  // Tamanho do grafo
      
      // Usamos +1 pra acessar os vértices pelos seus números. Deixaremos a primeira linha e primeira colunas sem usar.
      G = new int* [qtd_ares+1];
      n = qtd_ares+1;
      t = qtd_vert+1;
      for (int y = 0; y <qtd_ares+1; y++){
        G[y] = new int [qtd_ares+1];
      }
      
      // Inicializa pesos no máximo.
      for (int j=0; j < qtd_ares+1; j++)
      {
        for (int i=0; i < qtd_ares+1; i++)
        	G[i][j] = INT_MAX;
            //cout<<G[i][j]<<endl;
      }
      
      // Lê até atingir o final do arquivo.
      while(!file_input.fail())
      {
        // Puxa linha pro buffer
        file_input.getline(buffer, BUFFER_LENGTH);
        if(file_input.fail()) break;
        // Lê e converte os valores desejados.
        int vert_orig = atoi(&buffer[0]);
        int vert_dest = atoi(&buffer[2]);
        int weight = atoi(&buffer[4]);
        //cout<< vert_orig << " " << vert_dest << " " << weight << endl;
        
        // Atualiza o valor do peso da aresta saindo de vert_orig e indo para vert_dest.
        // cout<< "origem: " << vert_orig << "destino: "<< vert_dest << "peso: "<< G[vert_orig][vert_dest] << endl; == sem resposta
        G[vert_orig][vert_dest] = weight;
      }
    }

    if (argv[i] == opHelp){
      // descreve as entradas e o que cada parametro inicial pode fazer
      cout << "Algoritmo de Dijkstra utilizando heapmin" << endl;
      cout << "use -f <arquivo> para entrada de um grafo utilizando uma matriz de incidencia"<< endl;
      cout << "use -o <arquivo> para redirecionar saida para \"arquivo\""<< endl;
      cout << "use -s para exibir solucao ordenada"<< endl;
      cout << "use -i <vertInicial> apos -o ou apos <arquivo> para indicar vertice inicial"<< endl;
      cout << "use -l <vertFinal> apos -o ou apos <arquivo> para indicar vertice final"<< endl;
      return 0;
    }

    if (argv[i] == opInicial){
      inicial = true;
      s = stoi(argv[i+1]);
    }

    if (argv[i] == opFinal){
      final = true;
      t = stoi(argv[i+1]);
    }

    if (argv[i] == opSaida){
    	saida = true;
        nomeSaida = argv[i+1];
    }
    if(argv[i]== opSolucao){
        solucao = true;
    }
  }

  solutions(saida, nomeSaida, solucao, s, t, G, n);
  free(G);
}