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
│   ├── Base1.png, Base2.png              # Imagens para operações entre imagens
│   ├── [imagens_coloridas]               # Resultados em cores
│   ├── [imagens_cinza]                   # Resultados em tons de cinza
│   └── [imagens_geradas]                 # Todos os resultados dos algoritmos
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
- **Operações:** Soma, subtração, multiplicação e divisão com valores escalares
- **Implementação:** Funciona tanto em imagens coloridas quanto em tons de cinza
- **Saídas Coloridas:** `data/soma_escalar.jpg`, `data/subtracao_escalar.jpg`, `data/multiplicacao_escalar.jpg`, `data/divisao_escalar.jpg`
- **Saídas Tons de Cinza:** `data/soma_escalar_cinza.jpg`, `data/subtracao_escalar_cinza.jpg`, `data/multiplicacao_escalar_cinza.jpg`, `data/divisao_escalar_cinza.jpg`

### 4. Operações Aritméticas entre Imagens
- **Operações:** Soma, subtração, multiplicação e divisão pixel a pixel entre duas imagens
- **Implementação:** Funciona tanto em imagens coloridas quanto em tons de cinza
- **Saídas Coloridas:** `data/soma_imagens.jpg`, `data/subtracao_imagens.jpg`, `data/multiplicacao_imagens.jpg`, `data/divisao_imagens.jpg`
- **Saídas Tons de Cinza:** `data/soma_imagens_cinza.jpg`, `data/subtracao_imagens_cinza.jpg`, `data/multiplicacao_imagens_cinza.jpg`, `data/divisao_imagens_cinza.jpg`

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
- **Suporte completo a tons de cinza:** Operações aritméticas funcionam tanto em imagens coloridas quanto em tons de cinza
- **Operações aritméticas abrangentes:** Implementa todas as 4 operações básicas (+, -, *, /) para escalar e entre imagens
- **Executáveis separados:** Cada algoritmo é um programa independente
- **Menu centralizado:** Interface única para acessar todos os algoritmos
- **Visualização interativa:** Janelas do OpenCV mostram resultados lado a lado (colorido vs tons de cinza)
- **Tratamento de erros:** Verificação de arquivos e execução
- **Múltiplas saídas:** Cada operação aritmética gera versões coloridas e em tons de cinza

## ✅ Requisitos Atendidos da M1

O projeto implementa **TODOS** os algoritmos solicitados no Trabalho M1:

### ✓ Conversão para Tons de Cinza (somente imagem colorida)
- [x] **Média Aritmética** - `conversao_media_aritmetica.cpp`
- [x] **Média Ponderada** - `conversao_media_ponderada.cpp`

### ✓ Operações Aritméticas (+ - * /)
- [x] **Coloridas e tons de cinza** - Implementação completa
- [x] **Imagem com Imagem** - `operacoes_aritmeticas_imagem.cpp`
- [x] **Imagem com Valor Escalar** - `operacoes_aritmeticas_escalar.cpp`

### ✓ Limiarização
- [x] **Tons de cinza** - Binária e binária inversa
- [x] **Colorida** - Por intensidade e por canal

### ✓ Isolar Canais de Cores (colorida)
- [x] **Canal R** - Vermelho isolado
- [x] **Canal G** - Verde isolado  
- [x] **Canal B** - Azul isolado

### ✓ Histograma (colorida e tons de cinza)
- [x] **Computação** - Implementação manual pixel por pixel
- [x] **Visualização** - Gráficos individuais e combinados

### ✓ Inverso da imagem
- [x] **Colorida** - Negativo de imagem colorida
- [x] **Tons de cinza** - Negativo de imagem em cinza

---

## 🎨 Detalhes das Operações Aritméticas

### Operações com Escalar (Algoritmo 3)
- **Entrada:** Uma imagem colorida (`blobs-image.jpg`)
- **Processamento:** 
  1. Aplica operações (+50, -50, ×1.5, ÷2) na imagem colorida
  2. Converte a imagem para tons de cinza
  3. Aplica as mesmas operações na versão em tons de cinza
- **Visualização:** 10 janelas (5 coloridas + 5 tons de cinza)
- **Salvamento:** 9 arquivos (4 coloridos + 4 tons de cinza + 1 original cinza)

### Operações entre Imagens (Algoritmo 4)
- **Entrada:** Duas imagens coloridas (`Base1.png` e `Base2.png`)
- **Processamento:**
  1. Aplica operações (+, -, ×, ÷) entre as imagens coloridas
  2. Converte ambas as imagens para tons de cinza
  3. Aplica as mesmas operações nas versões em tons de cinza
- **Visualização:** 12 janelas (6 coloridas + 6 tons de cinza)
- **Salvamento:** 10 arquivos (4 coloridos + 4 tons de cinza + 2 originais cinza)

---

**Autor:** 
**Disciplina:** Processamento Digital de Imagens  
**Semestre:** 6º Semestre
