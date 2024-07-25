# Classe "Life"

A classe ´Life` é responsável pela matriz de células e pela exibição de saída do jogo.

## Funções (Métodos)

### Construtores

- **Life()**: Construtor padrão.
- **Life(int nRow, int nCol)**: Construtor que inicializa com o número de linhas e colunas.
- **Life(int nRow, int nCol, int numOfGen)**: Construtor que inicializa com linhas, colunas e número de gerações.

### Setters

- **set_bkg_color(const std::string &color)**: Define a cor de fundo.
- **set_cell_color(const std::string &color)**: Define a cor das células.
- **set_block_size(const int &bs)**: Define o tamanho do bloco.
- **set_filename(const std::string &filename)**: Define o nome do arquivo de saída.
- **set_output(const std::string &output)**: Define a configuração de saída.
- **set_fps(const int &f)**: Define os frames por segundo.

### Operadores

- **operator==(const Life& other) const**: Verifica a igualdade com outro objeto `Life` baseado no estado da grade.

### Operações na Matriz

- **fillMatrix(const std::vector<cellCoord>& aliveCellToSet)**: Preenche a matriz com células vivas com base em coordenadas fornecidas.

### Verificação e Contagem de Células Vivas

- **aliveCellVerifier(const int& row, const int& column) const**
- **aliveCellVerifier(const int& row, const int& column, const int& rowOffset, const int& columnOffset) const**
- **aliveCellsCounter(const int& row, const int& column) const**

### Outras Operações

- **stable()**: Verifica se a simulação atingiu estabilidade.
- **extinct()**: Verifica se todas as células na simulação morreram.
- **create_canvas()**: Inicializa um canvas para visualização.

### Funções de Salvamento e Processamento

- **saving(Life &other)**: Função para salvar o estado da simulação.
- **saving_string(Life &other)**: Função para salvar o estado da simulação como string.
- **copying(Life& other)**: Copia o estado de outro objeto `Life`.
- **glife_string(Life &other)**: Converte o estado da grade em uma representação textual.
- **update_glife()**: Atualiza a representação gráfica do estado da simulação.
- **update_glife_string()**: Atualiza a representação textual do estado da simulação.
- **print_glife()**: Imprime a representação textual do estado da simulação.
- **image_glife()**: Gera uma imagem com base no estado da simulação.

### Utilitários

- **endGen()**: Verifica se o número atual de gerações é igual ao número total de gerações a simular.

## Não Funções (Não são Métodos)

- **Atributos Públicos**: Rows, Columns, genCounter, genNum, image_out, Matrix, bkg_color, cell_color, block_size, output, filename, fps, newCanva, no_repeat, no_repeat_string, glife_view, glife_coord são variáveis de instância da classe e não são funções.
  
- **Tipos Especiais**: cellCoord é uma estrutura e std::hash<cellCoord> é uma especialização de hash para cellCoord, não são funções, mas tipos de dados e especializações.

- **Destrutor**: ~Life() é o destrutor da classe, responsável por liberar a memória alocada dinamicamente para a matriz Matrix.
