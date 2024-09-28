CRUD'S PIZZARIA

DESCRIÇÃO:

Este projeto implementa um sistema CRUD (Criar, Ler, Atualizar e Deletar) para a gestão de cardápio de uma pizzaria, desenvolvido em C.

DEPENDÊNCIAS:

Este projeto utiliza a biblioteca termios.h, que é específica para sistemas baseados em Unix, como Linux e macOS.

Uso da Biblioteca termios.h:

A biblioteca termios.h é usada para manipular o comportamento do terminal, permitindo a captura de entrada do usuário sem a necessidade de pressionar a tecla Enter. Essa funcionalidade é crucial para melhorar a experiência de usuário em sistemas de menu, onde as interações precisam ser mais diretas.

Compatibilidade:

Sistemas Operacionais Compatíveis: Linux, macOS, e outros sistemas baseados em Unix.
Sistemas Não Compatíveis: Windows. Se você deseja executar este projeto no Windows, será necessário portar as funcionalidades específicas do terminal utilizando APIs equivalentes como windows.h.

AVISOS:

Para salvar os dados, saia do programa corretamente (botão sair).
O arquivo "cardapio.bin" guarda os dados do programa, portanto não modifique ou exclua ele.
Ao utilizar a função de imprimir cardápio, será criado um novo arquivo de texto na pasta com as informações do cardápio.