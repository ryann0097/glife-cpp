## Classe Reader

A classe `Reader` é responsável por realizar a leitura de dados de entrada e configurar os atributos necessários para a simulação do Jogo da Vida.

### Atributos

- **inputFile**: Objeto `std::ifstream` utilizado para ler o arquivo de entrada.
- **filename**: Nome do arquivo de entrada.
- **generations**: Número de gerações a simular.
- **rows**: Número de linhas na grade de simulação.
- **columns**: Número de colunas na grade de simulação.
- **aliveCellChar**: Caractere que representa uma célula viva no arquivo de entrada.
- **image_out**: Flag indicando se a saída de imagem está habilitada.
- **alive_color**: Cor das células vivas para visualização.
- **bkg_color**: Cor de fundo para visualização.
- **block_size**: Tamanho do bloco (célula) em pixels.
- **output_path**: Caminho para o arquivo de saída.
- **fps**: Frames por segundo para animação.
- **aliveCellToSet**: Vetor de `cellCoord` contendo as coordenadas das células vivas inicialmente.

### Construtor

- **Reader()**: Construtor padrão que inicializa os atributos.

### Métodos

- **is_empty() const**: Verifica se o arquivo de entrada está vazio.
- **is_empty_output() const**: Verifica se os atributos de saída estão vazios ou não configurados.
- **processINI()**: Processa configurações iniciais ou pré-configuradas.
- **processFile()**: Processa o arquivo de entrada para configurar os atributos da simulação.

### Métodos de Acesso (Getters)

- **getGenerations() const**: Retorna o número de gerações.
- **getRows() const**: Retorna o número de linhas.
- **getColumns() const**: Retorna o número de colunas.
- **getOutput() const**: Retorna true se a saída de imagem está habilitada.
- **getAliveColor() const**: Retorna a cor das células vivas.
- **getBkgColor() const**: Retorna a cor de fundo.
- **getBlockSize() const**: Retorna o tamanho do bloco.
- **getFileName() const**: Retorna o nome do arquivo de entrada.
- **getOutputPath() const**: Retorna o caminho do arquivo de saída.
- **getFps() const**: Retorna os frames por segundo.

### Destrutor

- **~Reader()**: Destrutor padrão.

### Observações

- A classe `Reader` encapsula a lógica de leitura e configuração dos parâmetros iniciais da simulação do Jogo da Vida, permitindo inicializações a partir de arquivos ou configurações pré-definidas.

