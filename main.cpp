#include <iostream>
#include <clocale>
#include "header.h"
#include "record.h"
#include "dbtree.h"
#include "serialChar.h"
#include "node.h"

using namespace std;

int main() {
   setlocale(LC_ALL, "Portuguese");
   int op, i;
   char c;
   serialChar r('a');
   node<serialChar,3> noq;
   cout<<sizeof(noq)<<endl;
   dbtree<serialChar, 3> arq("teste.dat", "TPG", 1);
   cout<<"teste"<<noq.tamVet()<<endl;
   record<node<serialChar, 3>> aux;

   if (arq.isOpen()) {
      cout << "Arquivo aberto com sucesso!\n\n";

      do {
         cout << "Selecione uma opção:\n\n"
              << "1. Inserir um registro\n"
              << "2. Excluir um registro\n"
              << "3. Pesquisar um registro\n"
              << "4. Listar todos os registros\n"
              << "5. Sair\n\n"
              << "Sua opção: ";
         cin >> op;
         switch (op) {
            case 1:
               cout << "Digite um número inteiro: ";
               cin >> c;
               
               r.setValue(c);
               
               if (arq.insert(r))
                  cout << "Valor " << c << " inserido com sucesso.\n" << endl;

               break;
            case 2:
               cout << "Digite valor deseja remover do arquivo: ";
               cin >> c;
               i = arq.search(serialChar(c));
               if (i != 0) {
                  if (arq.deleteRecord(i))
                     cout << "Valor " << c << " removido do arquivo.\n" << endl;
               } else {
                  cout << "Valor " << c << " não encontrado no arquivo\n" << endl;
               }
               break;
            case 3:
               cout << "Digite o valor a ser pesquisado: ";
               cin >> c;
               i = arq.search(serialChar(c));

               if (i != 0)
                  cout << "Valor " << c << " encontrado no registro " << i << ".\n" << endl;
               else
                  cout << "Valor " << c << " não encontrado.\n" << endl;

               break;
            case 4:
               cout << "Listando todos os registros válidos do arquivo: " << endl;
               i = arq.getFirstValid();

               if (i == 0) {
                  cout << "Não existem registros no arquivo.\n" << endl;
               } else {
                  while (i != 0) {
                     arq.readRecord(aux, i);
                     noq=aux.getData();
                     cout<<"[";
                     for(int i=0;i<noq.sizeN();i++){
                        cout<<noq.getKey(i).getValue()<<",";
                     }
                     cout<<"]";
                     i = aux.getNext();
                  }
                  cout << endl;
               }

               break;
            case 5:
               cout << "Encerrando o programa... ";
               arq.close();
               cout << "concluído." << endl;
               return 0;
               break;
            default:
               cout << "Opção inválida! Tente novamente..." << endl;
               break;
         }
      } while (true);
   } else {
      cout << "Não foi possível abrir o arquivo!" << endl;
      return 1;
   }
   return 0;
}
