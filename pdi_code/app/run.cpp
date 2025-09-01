#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <limits>
#include <cstdlib>

void exibir_menu() {
    std::cout << "\n====================================================" << std::endl;
    std::cout << "   PROCESSAMENTO DIGITAL DE IMAGENS - MENU PRINCIPAL" << std::endl;
    std::cout << "====================================================" << std::endl;
    std::cout << "Selecione uma opcao:" << std::endl;
    std::cout << "\n[1] Conversao para Escala de Cinza (Media Aritmetica)" << std::endl;
    std::cout << "[2] Conversao para Escala de Cinza (Media Ponderada)" << std::endl;
    std::cout << "[3] Operacoes Aritmeticas com Escalar" << std::endl;
    std::cout << "[4] Operacoes Aritmeticas entre Imagens" << std::endl;
    std::cout << "[5] Limiarizacao (Thresholding)" << std::endl;
    std::cout << "[6] Isolamento de Canais RGB" << std::endl;
    std::cout << "[7] Histogramas" << std::endl;
    std::cout << "[8] Inverso da Imagem (Negativo)" << std::endl;
    std::cout << "[0] Sair" << std::endl;
    std::cout << "\n====================================================" << std::endl;
    std::cout << "Digite sua opcao: ";
}

int obter_opcao() {
    int opcao;
    while (!(std::cin >> opcao)) {
        std::cout << "Entrada invalida! Digite um numero: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return opcao;
}

void pausar() {
    std::cout << "\nPressione Enter para voltar ao menu...";
    std::cin.get();
}

void executar_programa(const std::string& programa) {
    std::cout << "\n====================================================" << std::endl;
    std::cout << "Executando: " << programa << std::endl;
    std::cout << "====================================================" << std::endl;
    
    std::string comando = "cd /d \"" + std::string("..\\build") + "\" && " + programa + ".exe";
    
    int resultado = system(comando.c_str());
    
    if (resultado != 0) {
        std::cout << "\nErro ao executar o programa. Certifique-se de que foi compilado corretamente." << std::endl;
    }
    
    pausar();
}

int main() {
    std::cout << "Iniciando Sistema de Processamento Digital de Imagens..." << std::endl;
    
    // Verificar se a imagem principal existe
    std::string imagePath = "data/blobs-image.jpg";
    cv::Mat testImage = cv::imread(imagePath, cv::IMREAD_COLOR);
    
    if (testImage.empty()) {
        std::cerr << "\nAVISO: Imagem principal nao encontrada em: " << imagePath << std::endl;
        std::cerr << "Execute o programa na pasta correta (onde esta o diretorio 'data/')" << std::endl;
    } else {
        std::cout << "Imagem principal encontrada! (" << testImage.cols << "x" << testImage.rows << ")" << std::endl;
    }
    
    int opcao;
    do {
        exibir_menu();
        opcao = obter_opcao();
        
        switch (opcao) {
            case 1:
                executar_programa("conversao_media_aritmetica");
                break;
                
            case 2:
                executar_programa("conversao_media_ponderada");
                break;
                
            case 3:
                executar_programa("operacoes_aritmeticas_escalar");
                break;
                
            case 4:
                executar_programa("operacoes_aritmeticas_imagem");
                break;
                
            case 5:
                executar_programa("limiarizacao");
                break;
                
            case 6:
                executar_programa("isolamento_canais");
                break;
                
            case 7:
                executar_programa("histograma");
                break;
                
            case 8:
                executar_programa("inverso_imagem");
                break;
                
            case 0:
                std::cout << "\nEncerrando o programa..." << std::endl;
                break;
                
            default:
                std::cout << "\nOpcao invalida! Tente novamente." << std::endl;
                pausar();
                break;
        }
        
    } while (opcao != 0);
    
    std::cout << "\nPrograma finalizado. Obrigado por usar o sistema PDI!" << std::endl;
    return 0;
}
