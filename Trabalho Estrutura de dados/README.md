Trabalho Estrutura de Dados

Eduardo Souza Arrigoni
Felipe Soeiro Accioly


A ideia é a criação de um sistema, programado em C, voltado para a consulta de pacientes de uma clínica, com a leitura de arquivos CSV.
Para que a execução seja feita de forma correta, é aconselhável que os arquivos(makefile, main.c, bd_paciente.c e bd_paciente.h) do sistema sejam colocados em uma pasta com o nome de sua preferência. Após isso, a execução é feita utilizando o ambiente Linux Ubuntu, em que deve-se escrever o caminho em que a pasta está, exemplo: cd /mnt/d/Documents/sistema_pacientes -> exemplo do caminho em que a pasta vai estar. Em seguida, deve-se digitar make para compilar e executar o programa. Então, o programa irá pedir para que insira o nome do arquivo csv que vai rodar no sistema, exemplo: bancodedados.csv. O programa estará pronto para rodar.

Principais TADs: struct paciente, com o objetivo de representar as informações de um paciente, struct bdpaciente, com o objetivo de representar a base de dados que armazena todos pacientes

Tornam o código jmais modular e para uma manutenção mais fácil