# Classe Manager

A classe `Manager` representa o controlador principal para gerenciar a execução e interação entre os componentes do sistema.

### Atributos

- **lifeState**: Estado atual da execução do sistema, definido pelo enum `LifeState`.
- **newReader**: Ponteiro para um objeto da classe `Reader` utilizado para leitura de dados.
- **newLife**: Ponteiro para um objeto da classe `Life` responsável pela simulação do Jogo da Vida.
- **newCanva**: Ponteiro para um objeto da classe `Canvas` utilizado para renderização visual.
- **Rows**: Número de linhas na grade de simulação.
- **Columns**: Número de colunas na grade de simulação.
- **image_out**: Flag indicando se a saída de imagem está habilitada.
- **end_flag**: Flag indicando o término da execução.
- **cell_color**: Cor das células para visualização.
- **bkg_color**: Cor de fundo para visualização.
- **block_size**: Tamanho do bloco (célula) em pixels.
- **output_path**: Caminho para o arquivo de saída.
- **fps**: Frames por segundo para animação.

### Construtor

- **Manager()**: Construtor padrão que inicializa os atributos e cria instâncias dos objetos `Reader`, `Life` e `Canvas`.

### Métodos

- **process()**: Método responsável por coordenar o processamento da simulação e interação com o usuário.
- **update()**: Método para atualizar o estado da simulação e dos elementos visuais.
- **render()**: Método para renderizar a visualização da simulação.
- **quit()**: Método que verifica se a execução deve ser encerrada (retorna true se `lifeState` for `END`).

### Destrutor

- **~Manager()**: Destrutor responsável por liberar a memória alocada dinamicamente para os objetos `Reader`, `Life` e `Canvas`.

### Observações

- A classe `Manager` integra os elementos essenciais para controlar o ciclo de vida da simulação do Jogo da Vida, incluindo leitura de dados, processamento da simulação, visualização e gerenciamento do estado de execução.

