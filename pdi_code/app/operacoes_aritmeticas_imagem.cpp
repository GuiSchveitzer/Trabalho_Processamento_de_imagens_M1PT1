#include <iostream>
#include <opencv2/opencv.hpp>
#include "utils.hpp"

int main() {
    std::cout << "Processamento de Imagens - Operacoes Aritmeticas entre Imagens" << std::endl;
    
    // 1. Abrir a primeira imagem
    std::string imagePath1 = "../data/blobs-image.jpg";
    cv::Mat image1 = cv::imread(imagePath1, cv::IMREAD_COLOR);
    
    if (image1.empty()) {
        std::cerr << "Erro: Nao foi possivel carregar a primeira imagem: " << imagePath1 << std::endl;
        return -1;
    }
    
    // 2. Abrir a segunda imagem
    std::string imagePath2 = "../data/blobs-image-2.jpg";
    cv::Mat image2 = cv::imread(imagePath2, cv::IMREAD_COLOR);
    
    if (image2.empty()) {
        std::cerr << "Erro: Nao foi possivel carregar a segunda imagem: " << imagePath2 << std::endl;
        return -1;
    }
    
    // Verificar se as imagens tem as mesmas dimensoes
    if (image1.size() != image2.size()) {
        std::cout << "Redimensionando a segunda imagem para coincidir com a primeira..." << std::endl;
        resizeImage(image2, image2, image1.size());
    }
    
    std::cout << "Imagens carregadas com sucesso!" << std::endl;
    std::cout << "Dimensoes da Imagem 1: " << image1.cols << "x" << image1.rows << std::endl;
    std::cout << "Dimensoes da Imagem 2: " << image2.cols << "x" << image2.rows << std::endl;
    
    // Criar imagens resultado
    cv::Mat somaResult = cv::Mat::zeros(image1.size(), CV_8UC3);
    cv::Mat subtracaoResult = cv::Mat::zeros(image1.size(), CV_8UC3);
    cv::Mat multiplicacaoResult = cv::Mat::zeros(image1.size(), CV_8UC3);
    cv::Mat divisaoResult = cv::Mat::zeros(image1.size(), CV_8UC3);
    
    std::cout << "Processando operacoes aritmeticas entre imagens..." << std::endl;
    
    // Percorrer pixel a pixel
    for (int y = 0; y < image1.rows; y++) {
        for (int x = 0; x < image1.cols; x++) {
            // Obter os valores BGR dos pixels das duas imagens
            cv::Vec3b pixel1 = image1.at<cv::Vec3b>(y, x);
            cv::Vec3b pixel2 = image2.at<cv::Vec3b>(y, x);
            
            // SOMA (com promocao de tipos)
            cv::Vec3b somaPixel;
            somaPixel[0] = saturate_uchar(static_cast<int>(pixel1[0]) + static_cast<int>(pixel2[0]));
            somaPixel[1] = saturate_uchar(static_cast<int>(pixel1[1]) + static_cast<int>(pixel2[1]));
            somaPixel[2] = saturate_uchar(static_cast<int>(pixel1[2]) + static_cast<int>(pixel2[2]));
            somaResult.at<cv::Vec3b>(y, x) = somaPixel;
            
            // SUBTRACAO (diferenca absoluta com promocao de tipos)
            cv::Vec3b subPixel;
            subPixel[0] = saturate_uchar(abs(static_cast<int>(pixel1[0]) - static_cast<int>(pixel2[0])));
            subPixel[1] = saturate_uchar(abs(static_cast<int>(pixel1[1]) - static_cast<int>(pixel2[1])));
            subPixel[2] = saturate_uchar(abs(static_cast<int>(pixel1[2]) - static_cast<int>(pixel2[2])));
            subtracaoResult.at<cv::Vec3b>(y, x) = subPixel;
            
            // MULTIPLICACAO (normalizada com float para evitar overflow)
            cv::Vec3b multPixel;
            multPixel[0] = saturate_uchar((static_cast<float>(pixel1[0]) * static_cast<float>(pixel2[0])) / 255.0f);
            multPixel[1] = saturate_uchar((static_cast<float>(pixel1[1]) * static_cast<float>(pixel2[1])) / 255.0f);
            multPixel[2] = saturate_uchar((static_cast<float>(pixel1[2]) * static_cast<float>(pixel2[2])) / 255.0f);
            multiplicacaoResult.at<cv::Vec3b>(y, x) = multPixel;
            
            // DIVISAO (com protecao contra divisao por zero e promocao de tipos)
            cv::Vec3b divPixel;
            divPixel[0] = pixel2[0] == 0 ? 0 : saturate_uchar((static_cast<float>(pixel1[0]) * 255.0f) / static_cast<float>(pixel2[0]));
            divPixel[1] = pixel2[1] == 0 ? 0 : saturate_uchar((static_cast<float>(pixel1[1]) * 255.0f) / static_cast<float>(pixel2[1]));
            divPixel[2] = pixel2[2] == 0 ? 0 : saturate_uchar((static_cast<float>(pixel1[2]) * 255.0f) / static_cast<float>(pixel2[2]));
            divisaoResult.at<cv::Vec3b>(y, x) = divPixel;
        }
    }
    
    std::cout << "Processamento concluido!" << std::endl;
    
    // Exibir as imagens
    cv::namedWindow("Imagem 1", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Imagem 2", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Soma das Imagens", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Subtracao das Imagens", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Multiplicacao das Imagens", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Divisao das Imagens", cv::WINDOW_AUTOSIZE);
    
    cv::imshow("Imagem 1", image1);
    cv::imshow("Imagem 2", image2);
    cv::imshow("Soma das Imagens", somaResult);
    cv::imshow("Subtracao das Imagens", subtracaoResult);
    cv::imshow("Multiplicacao das Imagens", multiplicacaoResult);
    cv::imshow("Divisao das Imagens", divisaoResult);
    
    std::cout << "Pressione qualquer tecla para continuar..." << std::endl;
    cv::waitKey(0);
    
    // Salvar as imagens processadas
    cv::imwrite("../data/soma_imagens.jpg", somaResult);
    cv::imwrite("../data/subtracao_imagens.jpg", subtracaoResult);
    cv::imwrite("../data/multiplicacao_imagens.jpg", multiplicacaoResult);
    cv::imwrite("../data/divisao_imagens.jpg", divisaoResult);
    
    std::cout << "Imagens salvas com sucesso!" << std::endl;
    
    // Fechar todas as janelas
    cv::destroyAllWindows();
    
    return 0;
}