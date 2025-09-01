#include <iostream>
#include <opencv2/opencv.hpp>
#include "utils.hpp"

int main() {
    std::cout << "Processamento de Imagens - Limiarizacao (Thresholding)" << std::endl;

    // 1. Abrir a imagem
    std::string imagePath = "../data/blobs-image.jpg";
    cv::Mat originalImage = cv::imread(imagePath, cv::IMREAD_COLOR);

    if (originalImage.empty()) {
        std::cerr << "Erro: Nao foi possivel carregar a imagem: " << imagePath << std::endl;
        return -1;
    }

    std::cout << "Imagem carregada com sucesso!" << std::endl;
    std::cout << "Dimensoes: " << originalImage.cols << "x" << originalImage.rows << std::endl;

    // 2. Definir valor de limiar (threshold)
    int limiar = 128; // Valor tipico (0-255)
    std::cout << "Valor de limiar utilizado: " << limiar << std::endl;

    // 3. Converter para tons de cinza para limiarizacao em escala de cinza
    cv::Mat grayImage;
    convertBGRToGray(originalImage, grayImage);

    // 4. Criar imagens de resultado
    cv::Mat binaryResult = cv::Mat::zeros(originalImage.size(), CV_8UC1);           // Binaria (tons de cinza)
    cv::Mat binaryInverseResult = cv::Mat::zeros(originalImage.size(), CV_8UC1);    // Binaria inversa
    cv::Mat colorBinaryResult = cv::Mat::zeros(originalImage.size(), CV_8UC3);      // Limiarizacao colorida
    cv::Mat colorThresholdResult = cv::Mat::zeros(originalImage.size(), CV_8UC3);   // Limiarizacao por canal

    std::cout << "Processando limiarizacao..." << std::endl;

    // 5. Limiarizacao em tons de cinza
    for (int y = 0; y < grayImage.rows; y++) {
        for (int x = 0; x < grayImage.cols; x++) {
            uchar grayPixel = grayImage.at<uchar>(y, x);
            
            // Limiarizacao binaria: pixel >= limiar = 255, senao = 0
            if (grayPixel >= limiar) {
                binaryResult.at<uchar>(y, x) = 255;
                binaryInverseResult.at<uchar>(y, x) = 0;
            } else {
                binaryResult.at<uchar>(y, x) = 0;
                binaryInverseResult.at<uchar>(y, x) = 255;
            }
        }
    }

    // 6. Limiarizacao colorida (metodo 1: por intensidade media)
    for (int y = 0; y < originalImage.rows; y++) {
        for (int x = 0; x < originalImage.cols; x++) {
            cv::Vec3b pixel = originalImage.at<cv::Vec3b>(y, x);
            
            // Calcular intensidade media do pixel
            int intensidadeMedia = static_cast<int>((pixel[0] + pixel[1] + pixel[2]) / 3);
            
            // Aplicar limiarizacao baseada na intensidade media
            if (intensidadeMedia >= limiar) {
                colorBinaryResult.at<cv::Vec3b>(y, x) = cv::Vec3b(255, 255, 255); // Branco
            } else {
                colorBinaryResult.at<cv::Vec3b>(y, x) = cv::Vec3b(0, 0, 0); // Preto
            }
        }
    }

    // 7. Limiarizacao colorida (metodo 2: por canal individual)
    for (int y = 0; y < originalImage.rows; y++) {
        for (int x = 0; x < originalImage.cols; x++) {
            cv::Vec3b pixel = originalImage.at<cv::Vec3b>(y, x);
            cv::Vec3b thresholdPixel;
            
            // Aplicar limiarizacao em cada canal separadamente
            for (int c = 0; c < 3; c++) {
                if (pixel[c] >= limiar) {
                    thresholdPixel[c] = 255;
                } else {
                    thresholdPixel[c] = 0;
                }
            }
            
            colorThresholdResult.at<cv::Vec3b>(y, x) = thresholdPixel;
        }
    }

    std::cout << "Processamento concluído!" << std::endl;

    // 8. Converter resultado binário para visualização colorida
    cv::Mat binaryColorDisplay, binaryInverseColorDisplay;
    convertGrayToBGR(binaryResult, binaryColorDisplay);
    convertGrayToBGR(binaryInverseResult, binaryInverseColorDisplay);

    // 9. Exibir as imagens
    cv::namedWindow("Imagem Original", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Tons de Cinza", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Limiarizacao Binaria", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Limiarizacao Binaria Inversa", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Limiarizacao Colorida (Intensidade)", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Limiarizacao Colorida (Por Canal)", cv::WINDOW_AUTOSIZE);

    cv::imshow("Imagem Original", originalImage);
    cv::imshow("Tons de Cinza", grayImage);
    cv::imshow("Limiarizacao Binaria", binaryColorDisplay);
    cv::imshow("Limiarizacao Binaria Inversa", binaryInverseColorDisplay);
    cv::imshow("Limiarizacao Colorida (Intensidade)", colorBinaryResult);
    cv::imshow("Limiarizacao Colorida (Por Canal)", colorThresholdResult);

    std::cout << "Pressione qualquer tecla para continuar..." << std::endl;
    cv::waitKey(0);

    // 10. Salvar resultados
    cv::imwrite("../data/limiarizacao_binaria.jpg", binaryResult);
    cv::imwrite("../data/limiarizacao_binaria_inversa.jpg", binaryInverseResult);
    cv::imwrite("../data/limiarizacao_colorida_intensidade.jpg", colorBinaryResult);
    cv::imwrite("../data/limiarizacao_colorida_canais.jpg", colorThresholdResult);
    cv::imwrite("../data/tons_cinza.jpg", grayImage);

    std::cout << "Imagens salvas com sucesso!" << std::endl;

    // 11. Fechar janelas
    cv::destroyAllWindows();

    return 0;
}