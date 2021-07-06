# Árvore B
Arvore B desenvolvida na disciplina técnicas de programação.

A meta da implementação é a construção do programa seguindo os seguintes critérios:

O programa deve ser corretamente modularizado (dividido em classes, métodos, etc.);
O projeto deve ser criado da seguinte forma: ArvoreB-NomeAluno, sem espaços, acentos ou caracteres especiais, por exemplo, ArvoreB-ChicoAnisio.
No cabeçalho do arquivo, deve constar um comentário com a identificação completa do aluno, incluindo número de matrícula.
Ao término do trabalho, cada aluno deverá:
Selecionar a opção Clean do menu Build, no Code::Blocks;
Compactar a pasta do projeto com todo seu conteúdo, usando o mesmo nome da pasta como nome do arquivo (ex.: ArvoreB-NomeAluno.zip)
A árvore B em disco é um arquivo tipado em que cada página é armazenada como um registro do arquivo. Deve ser implementado um programa que armazene um conjunto de objetos do TAD (tipo abstrato de dados) serialChar em uma árvore B, com o armazenamento de cada página da árvore em um registro de arquivo tipado, conforme visto na disciplina. A árvore de ter um grau mínimo t = 3, especificado na forma de uma constante no cabeçalho da classe.

O tipo serialChar é um tipo de dados serializável, com todos os operadores relacionais implementados, para correto uso como chave de uma árvore. Seu conteúdo é um único caracter. Para efeitos de comparação, ao contrário do tipo char, letras maiúsculas e minúsculas devem ser iguais ('a' == 'A"). Para os demais casos, devem ser consideradas as posições na tabela ASCII, assim como é feito no char.

A implementação deve manter o menor número possível de páginas em memória. A classe header poderá ser alterada, para indicar a raiz da árvore, se for necessário. Cada página da árvore será armazenada em um único registro do arquivo.

O programa deve apresentar um menu que permita ao usuário:
inserir um valor na árvore;
remover um valor da árvore;
imprimir a árvore completa;
buscar um valor em uma árvore;
executar um conjunto de testes padronizados;
o menu deve ser reapresentado após cada ação, exceto quando o usuário solicitar o término da execução.
O conjunto padronizado de testes corresponde à inserção, em ordem, das chaves [')', '6', 'O', 'b', 'L', 'G', 'P', 'C', '3', '%', 'm', '(', 'H', 'W', 'Y', '&', 'k', '1', 'X', '-']. Após inseri-las, devem ser removidas, em ordem, as chaves ['C', 'm', '1', 'O', ')', 'W', 'Y', 'L', 'X', '(']. Cada inserção/remoção deverá imprimir o estado atual da árvore ao terminar.

Durante a inserção e a remoção, deve ocorrer uma única passada na árvore, da raiz até a página em que a operação for realizada. No caso da remoção, a busca pelo maior predecessor ou pelo menor sucessor deve ser feita com uma única passada, já removendo e ajustando a árvore para que a remoção seja concluída.