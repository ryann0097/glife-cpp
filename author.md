=======================================================
## Conway's Game of Life - PL1 Version
=======================================================

Autor: Ryan Silvestre 
Email: ryan.silvestre.718@ufrn.edu.br 

1. Introdução:
   O "Game of Life" criado por John Horton Conway é um autômato de células e funciona com uma matriz de células. O jogo começa com uma configuração inicial, e essa matriz vai evoluindo de acordo com regras pré-determinadas. As células vivas permanecem vivas se tiverem 2 ou 3 vizinhos vivos e podem morrer em duas ocasiões: se tiverem 1 ou menos vizinhos ao seu redor; se tiverem 4 ou mais vizinhos ao seu redor. As células mortas podem voltar à vida caso tenham EXATAMENTE 3 vizinhos vivos. O jogo para quando a configuração da matriz for estável ou for extinta.

2. Componentes:
   - `arquivo1.cpp`: Descrição do que faz e como se integra ao projeto.
   - `arquivo2.h`: Detalhes sobre a sua função no sistema.

3. Estrutura do Projeto:
   - `src/`: Contém todos os arquivos fonte.
   - `ext_lib/`: Bibliotecas relacionadas à criação de imagens para a opção de geração de imagens pelo usuário.
   - `examples/`: Alguns templates prontos para o usuário colocar no arquivo de configuração "glife.ini".
   - ´tests-pics/´: Algumas fotos de gerações anteriores.

4. Compilação e como rodar:
   - Na pasta "src", execute o comando ´cmake -S . -B build´
   - Vá para a pasta "build" e execute o comando ´make´.
   - Mova o arquivo ´glife´ gerado para ´/src´.
   - Ajuste as configurações da maneira orientada ao abrir o arquivo ´glife.ini´.
   - Na pasta ´/src´, execute o comando ´./glife´.

