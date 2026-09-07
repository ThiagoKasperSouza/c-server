# C-Server
Um servidor HTTP simples e nativo escrito em C puro, projetado para receber e processar requisições GraphQL no formato JSON sem a necessidade de bibliotecas externas (como cJSON ou frameworks de rede).

## 📌 Visão Geral
O projeto consiste em um servidor de conexões TCP utilizando Sockets de Berkeley no POSIX Linux/macOS. Ele escuta requisições HTTP do tipo POST, faz o parse manual do corpo (payload JSON) para extrair a query GraphQL desejada e devolve uma resposta estruturada em JSON no padrão da especificação GraphQL.

## 🚀 Funcionalidades
Zero Dependências de Terceiros: Desenvolvido exclusivamente com bibliotecas padrão C (<sys/socket.h>, <arpa/inet.h>, etc.).

Suporte a GraphQL Nátivo: Extração e resolução manual de queries do payload HTTP.

Reuso de Porta: Configurado com SO_REUSEADDR para evitar erros de porta bloqueada ao reiniciar a aplicação.

Arquitetura Modular: Separação clara entre inicialização de rede, recepção de conexões e execução da lógica de negócios.


## 📋 Pré-requisitos
Para compilar e executar o servidor, você precisa apenas de:

- Sistema Operacional baseado em Unix (Linux ou macOS).

- Compilador C (como gcc ou clang).
  
- CMake

- Utilitário curl para realização de testes (opcional).

## 🛠️ Compilação e Execução
Compile o arquivo com o CMake:

```Bash
mkdir build && cd build && cmake .. 
```
Construa o executável
```Bash
cmake --build . 
```

Execute o servidor:

```Bash
./program
```
O servidor estará escutando na porta 8080.


## 🧪 Como Testar
Você pode enviar requisições GraphQL usando o curl no seu terminal:

1. Testando a Query hello
```Bash
curl -X POST http://localhost:8080/graphql \
  -H "Content-Type: application/json" \
  -d '{"query": "{ hello }"}'
```

2. Testando a Query usuario
Comando:

```Bash
curl -X POST http://localhost:8080/graphql \
  -H "Content-Type: application/json" \
  -d '{"query": "{ usuario { id nome } }"}'
```

3. Testando Query Inválida
Comando:

```Bash
curl -X POST http://localhost:8080/graphql \
  -H "Content-Type: application/json" \
  -d '{"query": "{ produtos }"}'
```

⚙️ Configurações
Para alterar a porta padrão, modifique a diretiva de pré-processador no início do código:

```C
#define PORT 8080
#define BUFFER_SIZE 4096
```
