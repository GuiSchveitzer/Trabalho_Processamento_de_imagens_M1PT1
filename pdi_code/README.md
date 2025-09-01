# Processamento Digital de Imagens (PDI) - Trabalho M1

Este projeto implementa algoritmos fundamentais de Processamento Digital de Imagens usando C++ e OpenCV, com implementações manuais pixel por pixel para fins educacionais.

### Teste Rápido
1. Vá para a pasta build: `cd build`
2. Execute: `./pdi_code.exe`  
3. Digite `1` para testar conversão para escala de cinza
4. Verifique se a imagem foi salva em `../data/`

## 🖼️ Interface do Sistema

O programa possui um menu interativo que permite selecionar qual algoritmo executar:

```
====================================================
   PROCESSAMENTO DIGITAL DE IMAGENS - MENU PRINCIPAL
====================================================
Selecione uma opcao:

[1] Conversao para Escala de Cinza (Media Aritmetica)
[2] Conversao para Escala de Cinza (Media Ponderada)
[3] Operacoes Aritmeticas com Escalar
[4] Operacoes Aritmeticas entre Imagens
[5] Limiarizacao (Thresholding)
[6] Isolamento de Canais RGB
[7] Histogramas
[8] Inverso da Imagem (Negativo)
[0] Sair

====================================================
Digite sua opcao: 
```

## 📦 Estrutura do Projeto

```
pdi_code/
├── app/
│   ├── run.cpp                           # Menu principal 
│   ├── conversao_media_aritmetica.cpp    # Algoritmo 1
│   ├── conversao_media_ponderada.cpp     # Algoritmo 2  
│   ├── operacoes_aritmeticas_escalar.cpp # Algoritmo 3
│   ├── operacoes_aritmeticas_imagem.cpp  # Algoritmo 4
│   ├── limiarizacao.cpp                  # Algoritmo 5
│   ├── isolamento_canais.cpp             # Algoritmo 6
│   ├── histograma.cpp                    # Algoritmo 7
│   └── inverso_imagem.cpp                # Algoritmo 8
├── include/
│   ├── Operation.hpp                     # Classe base para operações
│   └── utils.hpp                         # Funções utilitárias
├── src/
│   └── Operation.cpp                     # Implementação da classe Operation
├── data/
│   ├── blobs-image.jpg                   # Imagem de entrada principal
│   └── [imagens_geradas]                 # Resultados dos algoritmos
├── build/                                # Executáveis compilados
├── CMakeLists.txt                        # Configuração do CMake
└── README.md                             # Esta documentação
```

## 🎯 Algoritmos Implementados

### 1. Conversão para Escala de Cinza (Média Aritmética)
- **Fórmula:** `Cinza = (R + G + B) / 3`
- **Saída:** `data/gray_output_media_aritmetica.jpg`

### 2. Conversão para Escala de Cinza (Média Ponderada) 
- **Fórmula:** `Cinza = 0.299*R + 0.587*G + 0.114*B`
- **Saída:** `data/gray_output_media_ponderada.jpg`

### 3. Operações Aritméticas com Escalar
- **Operações:** Soma e multiplicação com valores escalares
- **Saídas:** `data/soma_escalar.jpg`, `data/multiplicacao_escalar.jpg`

### 4. Operações Aritméticas entre Imagens
- **Operação:** Soma pixel a pixel entre duas imagens
- **Saída:** `data/soma_imagens.jpg`

### 5. Limiarização (Thresholding)
- **Operação:** Conversão para imagem binária usando threshold
- **Saída:** `data/limiarizacao_binaria.jpg`

### 6. Isolamento de Canais RGB
- **Operação:** Separação dos canais vermelho, verde e azul
- **Saídas:** `data/canal_red_isolado.jpg`, `data/canal_green_isolado.jpg`, `data/canal_blue_isolado.jpg`

### 7. Histogramas
- **Operação:** Computação e visualização do histograma em tons de cinza
- **Saída:** `data/histograma_escala_cinza.jpg`

### 8. Inverso da Imagem (Negativo)
- **Fórmula:** `novo_valor = 255 - valor_original`
- **Saída:** `data/imagem_invertida_colorida.jpg`

## 📁 Como Funciona

1. **Execute o menu principal:** `./pdi_code`
2. **Escolha uma opção** (1-8) para executar um algoritmo específico
3. **O programa chama automaticamente** o executável correspondente no diretório `build/`
4. **Visualize os resultados** nas janelas que se abrem e na pasta `data/`
5. **Pressione Enter** para voltar ao menu principal

## 🔧 Dependências

- **OpenCV 4.x:** Para carregamento, exibição e salvamento de imagens
- **CMake 3.x:** Para gerenciamento de compilação  
- **Compilador C++11 ou superior:** GCC, Clang ou MSVC

## 💡 Características Técnicas

- **Implementações manuais:** Todos os algoritmos são feitos pixel por pixel
- **Executáveis separados:** Cada algoritmo é um programa independente
- **Menu centralizado:** Interface única para acessar todos os algoritmos
- **Visualização interativa:** Janelas do OpenCV mostram resultados
- **Tratamento de erros:** Verificação de arquivos e execução

---

**Autor:** 
**Disciplina:** Processamento Digital de Imagens  
**Semestre:** 6º Semestre