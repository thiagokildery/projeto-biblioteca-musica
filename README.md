   Documentação da Aplicação: Sistema de Gerenciamento de Discos

  Descrição
A aplicação é um sistema simples para gerenciar uma lista de discos (como álbuns de música). Utiliza uma lista encadeada para armazenar os dados e permite realizar operações básicas, como adicionar, remover, exibir os discos e salvar as informações em um arquivo. Os dados são persistidos para que possam ser carregados em execuções futuras.

---

  Funcionalidades:

1. Inserir Disco 
   - Permite adicionar um novo disco à lista, incluindo:
     - Nome do disco.
     - Nota de avaliação (de 0.0 a 5.0).
   - Os dados são armazenados em memória e podem ser persistidos no arquivo.

2. Remover Disco 
   - Permite excluir um disco da lista pelo nome.
   - Caso o disco não seja encontrado, exibe uma mensagem de erro.

3. Exibir Lista de Discos
   - Mostra todos os discos cadastrados, com suas respectivas notas de avaliação.

4. Persistência de Dados
   - Os discos são carregados automaticamente de um arquivo de texto (`discos.txt`) na inicialização do programa.
   - Ao finalizar o programa, a lista é salva novamente no mesmo arquivo, garantindo que nenhuma alteração seja perdida.

5. Menu Interativo
   - Exibe opções claras para o usuário:
     - Adicionar disco.
     - Remover disco.
     - Visualizar todos os discos.
     - Sair da aplicação.
   - A interface é simples e amigável, ideal para interações rápidas.

---

  Formato do Arquivo de Dados:
- Os dados são armazenados no arquivo `discos.txt` no seguinte formato:
  ```
  <nome do disco>|<nota>
  ```
      Exemplo:
  ```
  Dark Side of the Moon|4.9
  Abbey Road|5.0
  Thriller|4.8
  ```

---

  Objetivo:
A aplicação é ideal para uso pessoal ou educacional, permitindo organizar e avaliar uma coleção de discos de maneira prática. Ela demonstra conceitos de estruturas de dados, manipulação de arquivos e interação com o usuário em C.
