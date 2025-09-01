cmake_minimum_required(VERSION 3.16)
project(pdi_code)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

include_directories(
    ${OpenCV_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/include
)

# Arquivos fonte da biblioteca
file(GLOB LIB_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Executavel principal (run.cpp)
add_executable(pdi_code 
    ${PROJECT_SOURCE_DIR}/app/run.cpp
    ${LIB_FILES}
)
target_link_libraries(pdi_code ${OpenCV_LIBS})

# Executavel para conversao por media aritmetica
add_executable(conversao_media_aritmetica 
    ${PROJECT_SOURCE_DIR}/app/conversao_media_aritmetica.cpp
    ${LIB_FILES}
)
target_link_libraries(conversao_media_aritmetica ${OpenCV_LIBS})

# Executavel para conversao por media ponderada
add_executable(conversao_media_ponderada 
    ${PROJECT_SOURCE_DIR}/app/conversao_media_ponderada.cpp
    ${LIB_FILES}
)
target_link_libraries(conversao_media_ponderada ${OpenCV_LIBS})

# Executavel para operacoes aritmeticas com escalar
add_executable(operacoes_aritmeticas_escalar 
    ${PROJECT_SOURCE_DIR}/app/operacoes_aritmeticas_escalar.cpp
    ${LIB_FILES}
)
target_link_libraries(operacoes_aritmeticas_escalar ${OpenCV_LIBS})

# Executavel para operacoes aritmeticas entre imagens
add_executable(operacoes_aritmeticas_imagem 
    ${PROJECT_SOURCE_DIR}/app/operacoes_aritmeticas_imagem.cpp
    ${LIB_FILES}
)
target_link_libraries(operacoes_aritmeticas_imagem ${OpenCV_LIBS})

# Executavel para limiarizacao
add_executable(limiarizacao 
    ${PROJECT_SOURCE_DIR}/app/limiarizacao.cpp
    ${LIB_FILES}
)
target_link_libraries(limiarizacao ${OpenCV_LIBS})

# Executavel para isolamento de canais
add_executable(isolamento_canais 
    ${PROJECT_SOURCE_DIR}/app/isolamento_canais.cpp
    ${LIB_FILES}
)
target_link_libraries(isolamento_canais ${OpenCV_LIBS})

# Executavel para histograma
add_executable(histograma 
    ${PROJECT_SOURCE_DIR}/app/histograma.cpp
    ${LIB_FILES}
)
target_link_libraries(histograma ${OpenCV_LIBS})

# Executavel para inverso da imagem
add_executable(inverso_imagem 
    ${PROJECT_SOURCE_DIR}/app/inverso_imagem.cpp
    ${LIB_FILES}
)
target_link_libraries(inverso_imagem ${OpenCV_LIBS})
