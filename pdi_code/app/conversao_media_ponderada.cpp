#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    std::cout << "Processamento de Imagens - Conversao para Escala de Cinza (Media Ponderada)" << std::endl;

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

    // 2. Criar uma imagem de saida com as mesmas dimensoes e 3 canais
    cv::Mat resultImage = cv::Mat::zeros(originalImage.rows, originalImage.cols, CV_8UC3);

    // 3. Processar cada pixel com media ponderada
    std::cout << "Processando pixels usando Media Ponderada..." << std::endl;

    for (int y = 0; y < originalImage.rows; y++) {
        for (int x = 0; x < originalImage.cols; x++) {
            // Obter valores BGR
            cv::Vec3b pixel = originalImage.at<cv::Vec3b>(y, x);
            uchar blue = pixel[0];
            uchar green = pixel[1];
            uchar red = pixel[2];

            // Media ponderada: Gray = 0.299*R + 0.587*G + 0.114*B
            uchar grayValue = static_cast<uchar>(
                0.114f * blue + 0.587f * green + 0.299f * red
            );

            // Preencher todos os canais com o valor de cinza
            resultImage.at<cv::Vec3b>(y, x) = cv::Vec3b(grayValue, grayValue, grayValue);
        }
    }

    std::cout << "Processamento concluido!" << std::endl;

    // 4. Salvar imagens para depuracao (opcional)
    cv::imwrite("debug_saida.jpg", resultImage);

    // 5. Mostrar as duas imagens
    try {
        cv::namedWindow("Imagem Original", cv::WINDOW_AUTOSIZE);
        cv::namedWindow("Imagem em Escala de Cinza (Media Ponderada)", cv::WINDOW_AUTOSIZE);

        cv::imshow("Imagem Original", originalImage);
        cv::imshow("Imagem em Escala de Cinza (Media Ponderada)", resultImage);

        std::cout << "Pressione qualquer tecla para continuar..." << std::endl;

        int key = 0;
        while (key != 27 && key != 13 && key != 32) { // ESC, Enter ou Espaco
            key = cv::waitKey(30) & 0xFF;
            if (key != 255) break; // Qualquer tecla pressionada
        }
    } catch (const cv::Exception& e) {
        std::cerr << "Erro ao exibir janelas: " << e.what() << std::endl;
    }

    // 6. Salvar a imagem processada
    std::string grayOutputPath = "../data/gray_output_media_ponderada.jpg";
    bool graySaved = cv::imwrite(grayOutputPath, resultImage);

    if (graySaved) {
        std::cout << "Imagem processada salva com sucesso!" << std::endl;
        std::cout << "Imagem em escala de cinza salva em: " << grayOutputPath << std::endl;
    } else {
        std::cerr << "Erro ao salvar a imagem processada." << std::endl;
    }

    // 7. Fechar todas as janelas
    cv::destroyAllWindows();

    return 0;
}
