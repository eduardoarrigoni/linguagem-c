# Trabalho de Estrutura de Dados

# Desenvolvido por:
- Eduardo Souza Arrigoni


# Sistema de Gerenciamento de Pacientes em C

Este projeto é um sistema em linguagem C para o gerenciamento de pacientes. Ele permite cadastrar, consultar, atualizar, remover e listar registros de pacientes, dando maior praticidade aos usuários.


# Funcionalidades

- Cadastro de novos pacientes;
- Consulta de pacientes por ID;
- Atualização de dados dos pacientes;
- Remoção de pacientes cadastrados;
- Listagem de todos pacientes.


# Estrutura do Projeto

- main.c;
- bd_paciente.c;
- bd_paciente.h;
- Makefile.


# Como funciona o programa

Para que a execução seja feita de forma correta, é aconselhável que os arquivos(makefile, main.c, bd_paciente.c e bd_paciente.h) do sistema, sejam colocados em uma pasta com o nome de sua preferência. Após isso, a execução é feita utilizando o ambiente Linux Ubuntu, onde deve-se escrever o caminho em que a pasta está, exemplo: cd /mnt/d/Documents/sistema_pacientes -> exemplo do caminho em que a pasta vai estar. Em seguida, deve-se digitar make para compilar e executar o programa. Então, o programa irá pedir para que insira o nome do arquivo csv que vai rodar no sistema, exemplo: bancodedados.csv. O programa estará pronto para rodar.

Passo a passo: 
- 1. Guardar arquivos (makefile, main.c, bd_paciente.c e bd_paciente.h) em uma pasta;
- 2. Executar no ambiente Linux Ubuntu;
- 3. Escrever caminho da pasta;
- 4. Digitar make para compilar e executar o programa;
- 5. Inserir nome do arquivo .csv.


# Principais TADs

- Struct paciente: com o objetivo de representar as informações de um paciente;
- Struct bdpaciente: com o objetivo de representar a base de dados que armazena todos pacientes.
- Utilização de estruturas de fila.

Tornam o código mais modular e para uma manutenção mais fácil.
