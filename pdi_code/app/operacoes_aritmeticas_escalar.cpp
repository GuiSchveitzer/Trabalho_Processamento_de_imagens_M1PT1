#include <iostream>
#include <opencv2/opencv.hpp>
#include "utils.hpp"

int main() {
    std::cout << "Processamento de Imagens - Operacoes Aritmeticas com Escalar" << std::endl;

    // 1. Abrir a imagem
    std::string imagePath = "../data/blobs-image.jpg";
    cv::Mat originalImage = cv::imread(imagePath, cv::IMREAD_COLOR);

    if (originalImage.empty()) {
        std::cerr << "Erro: Nao foi possivel carregar a imagem: " << imagePath << std::endl;
        return -1;
    }

    std::cout << "Imagem carregada com sucesso!" << std::endl;
    std::cout << "Dimensoes: " << originalImage.cols << "x" << originalImage.rows << std::endl;

    // 2. Escalar usado
    int valorEscalar = 50;
    float fatorMultiplicacao = 1.5f;
    float fatorDivisao = 2.0f;

    std::cout << "Valor escalar utilizado: " << valorEscalar << std::endl;

    // 3. Criar imagens de resultado
    cv::Mat somaResult = cv::Mat::zeros(originalImage.size(), CV_8UC3);
    cv::Mat subtracaoResult = cv::Mat::zeros(originalImage.size(), CV_8UC3);
    cv::Mat multiplicacaoResult = cv::Mat::zeros(originalImage.size(), CV_8UC3);
    cv::Mat divisaoResult = cv::Mat::zeros(originalImage.size(), CV_8UC3);

    std::cout << "Processando operacoes aritmeticas..." << std::endl;

    // 4. Percorrer pixels
    for (int y = 0; y < originalImage.rows; y++) {
        for (int x = 0; x < originalImage.cols; x++) {
            cv::Vec3b pixel = originalImage.at<cv::Vec3b>(y, x);

            // SOMA
            cv::Vec3b somaPixel;
            somaPixel[0] = saturate_uchar(static_cast<int>(pixel[0]) + valorEscalar);
            somaPixel[1] = saturate_uchar(static_cast<int>(pixel[1]) + valorEscalar);
            somaPixel[2] = saturate_uchar(static_cast<int>(pixel[2]) + valorEscalar);
            somaResult.at<cv::Vec3b>(y, x) = somaPixel;

            // SUBTRACAO
            cv::Vec3b subPixel;
            subPixel[0] = saturate_uchar(static_cast<int>(pixel[0]) - valorEscalar);
            subPixel[1] = saturate_uchar(static_cast<int>(pixel[1]) - valorEscalar);
            subPixel[2] = saturate_uchar(static_cast<int>(pixel[2]) - valorEscalar);
            subtracaoResult.at<cv::Vec3b>(y, x) = subPixel;

            // MULTIPLICACAO
            cv::Vec3b multPixel;
            multPixel[0] = saturate_uchar(pixel[0] * fatorMultiplicacao);
            multPixel[1] = saturate_uchar(pixel[1] * fatorMultiplicacao);
            multPixel[2] = saturate_uchar(pixel[2] * fatorMultiplicacao);
            multiplicacaoResult.at<cv::Vec3b>(y, x) = multPixel;

            // DIVISAO (evitando divisao por zero — opcional aqui, mas mantido por seguranca)
            cv::Vec3b divPixel;
            divPixel[0] = saturate_uchar(pixel[0] / fatorDivisao);
            divPixel[1] = saturate_uchar(pixel[1] / fatorDivisao);
            divPixel[2] = saturate_uchar(pixel[2] / fatorDivisao);
            divisaoResult.at<cv::Vec3b>(y, x) = divPixel;
        }
    }

    std::cout << "Processamento concluido!" << std::endl;

    // 5. Exibir as imagens
    cv::namedWindow("Imagem Original", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Soma (+50)", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Subtracao (-50)", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Multiplicacao (x1.5)", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Divisao (/2)", cv::WINDOW_AUTOSIZE);

    cv::imshow("Imagem Original", originalImage);
    cv::imshow("Soma (+50)", somaResult);
    cv::imshow("Subtracao (-50)", subtracaoResult);
    cv::imshow("Multiplicacao (x1.5)", multiplicacaoResult);
    cv::imshow("Divisao (/2)", divisaoResult);

    std::cout << "Pressione qualquer tecla para continuar..." << std::endl;
    cv::waitKey(0);

    // 6. Salvar resultados
    cv::imwrite("../data/soma_escalar.jpg", somaResult);
    cv::imwrite("../data/subtracao_escalar.jpg", subtracaoResult);
    cv::imwrite("../data/multiplicacao_escalar.jpg", multiplicacaoResult);
    cv::imwrite("../data/divisao_escalar.jpg", divisaoResult);

    std::cout << "Imagens salvas com sucesso!" << std::endl;

    // 7. Fechar janelas
    cv::destroyAllWindows();

    return 0;
}
