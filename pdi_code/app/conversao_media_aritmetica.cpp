#include <iostream>
#include <opencv2/opencv.hpp>

#include "Operation.hpp"

int main() {
    std::cout << "Processamento de Imagens - Conversao para Escala de Cinza (Media Aritimetica)" << std::endl;
    
    // 1. Abrir uma imagem
    std::string imagePath = "../data/blobs-image.jpg";
    cv::Mat originalImage = cv::imread(imagePath, cv::IMREAD_COLOR);
    
    // Verificar se a imagem foi carregada corretamente
    if (originalImage.empty()) {
        std::cerr << "Erro: Nao foi possivel carregar a imagem: " << imagePath << std::endl;
        return -1;
    }
    
    std::cout << "Imagem carregada com sucesso!" << std::endl;
    std::cout << "Dimensoes: " << originalImage.cols << "x" << originalImage.rows << std::endl;
    
    // 2. Criar uma imagem (resultado) com as mesmas dimensoes da original
    cv::Mat resultImage = cv::Mat::zeros(originalImage.rows, originalImage.cols, CV_8UC3);
    
    // 3. Percorrer pixel a pixel a imagem
    std::cout << "Processando pixels..." << std::endl;
    
    for (int y = 0; y < originalImage.rows; y++) {
        for (int x = 0; x < originalImage.cols; x++) {
            // Obter os valores BGR do pixel atual
            cv::Vec3b pixel = originalImage.at<cv::Vec3b>(y, x);
            uchar blue = pixel[0];
            uchar green = pixel[1];
            uchar red = pixel[2];
            
            // 4. Calcular para cada pixel a media de valores r, g e b
            uchar grayValue = static_cast<uchar>((red + green + blue) / 3);
            
            // 5. Salvar o pixel correspondente na imagem de saida
            // Aplicar o valor de cinza nos tres canais para manter a imagem colorida
            resultImage.at<cv::Vec3b>(y, x) = cv::Vec3b(grayValue, grayValue, grayValue);
        }
    }
    
    std::cout << "Processamento concluido!" << std::endl;
    
    // 6. Mostrar as duas imagens
    cv::imshow("Imagem Original", originalImage);
    cv::imshow("Imagem em Escala de Cinza", resultImage);
    
    std::cout << "Pressione qualquer tecla para continuar..." << std::endl;
    cv::waitKey(0);
    
    // 7. Salvar a imagem processada
    std::string grayOutputPath = "../data/gray_output_media_aritimetica.jpg";
    
    bool graySaved = cv::imwrite(grayOutputPath, resultImage);
    
    if (graySaved) {
        std::cout << "Imagem processada salva com sucesso!" << std::endl;
        std::cout << "Imagem em escala de cinza salva em: " << grayOutputPath << std::endl;
    } else {
        std::cerr << "Erro ao salvar a imagem processada." << std::endl;
    }
    
    // Fechar todas as janelas
    cv::destroyAllWindows();
    
    Operation op;
    return 0;
}