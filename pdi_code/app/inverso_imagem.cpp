#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

int main() {
    std::cout << "Processamento de Imagens - Inverso da Imagem (Negativo)" << std::endl;

    // 1. Carregar a imagem colorida
    std::string imagePath = "../data/blobs-image-2.jpg";
    cv::Mat originalImage = cv::imread(imagePath, cv::IMREAD_COLOR);

    if (originalImage.empty()) {
        std::cerr << "Erro: Nao foi possivel carregar a imagem: " << imagePath << std::endl;
        return -1;
    }

    std::cout << "Imagem carregada com sucesso!" << std::endl;
    std::cout << "Dimensoes: " << originalImage.cols << "x" << originalImage.rows << std::endl;

    // 2. Obter dimensoes da imagem
    int height = originalImage.rows;
    int width = originalImage.cols;
    int channels = originalImage.channels();

    // 3. Criar matriz para a imagem invertida
    cv::Mat invertedImage = cv::Mat::zeros(height, width, originalImage.type());

    std::cout << "Processando pixels para inverter a imagem..." << std::endl;

    // 4. Processar cada pixel para fazer o inverso (negativo)
    if (channels == 3) {
        // Imagem colorida (BGR)
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                cv::Vec3b pixel = originalImage.at<cv::Vec3b>(y, x);
                
                // Inverso: novo_valor = 255 - valor_original
                uchar blue = 255 - pixel[0];   // Inverter canal B
                uchar green = 255 - pixel[1];  // Inverter canal G
                uchar red = 255 - pixel[2];    // Inverter canal R

                invertedImage.at<cv::Vec3b>(y, x) = cv::Vec3b(blue, green, red);
            }
        }
    } else if (channels == 1) {
        // Imagem em escala de cinza
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                uchar pixel = originalImage.at<uchar>(y, x);
                
                // Inverso: novo_valor = 255 - valor_original
                uchar invertedPixel = 255 - pixel;
                
                invertedImage.at<uchar>(y, x) = invertedPixel;
            }
        }
    }

    std::cout << "Processamento concluido!" << std::endl;

    // 5. Criar tambem versao em escala de cinza e seu inverso
    cv::Mat grayOriginal, grayInverted;
    cv::cvtColor(originalImage, grayOriginal, cv::COLOR_BGR2GRAY);
    
    // Inverter a imagem em escala de cinza
    grayInverted = cv::Mat::zeros(height, width, CV_8UC1);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            uchar pixel = grayOriginal.at<uchar>(y, x);
            grayInverted.at<uchar>(y, x) = 255 - pixel;
        }
    }

    // 6. SALVAR PRIMEIRO - antes de qualquer visualizacao
    std::string invertedColorPath = "../data/imagem_invertida_colorida.jpg";
    std::string invertedGrayPath = "../data/imagem_invertida_cinza.jpg";
    std::string grayOriginalPath = "../data/imagem_original_cinza.jpg";

    std::cout << "Salvando imagens processadas..." << std::endl;
    
    bool invertedColorSaved = cv::imwrite(invertedColorPath, invertedImage);
    bool invertedGraySaved = cv::imwrite(invertedGrayPath, grayInverted);
    bool grayOriginalSaved = cv::imwrite(grayOriginalPath, grayOriginal);

    if (invertedColorSaved && invertedGraySaved && grayOriginalSaved) {
        std::cout << "Imagens processadas salvas com sucesso!" << std::endl;
        std::cout << "Imagem invertida colorida: " << invertedColorPath << std::endl;
        std::cout << "Imagem invertida cinza: " << invertedGrayPath << std::endl;
        std::cout << "Imagem original cinza: " << grayOriginalPath << std::endl;
    } else {
        std::cerr << "Erro ao salvar algumas imagens." << std::endl;
    }

    // 7. Salvar imagens de debug
    cv::imwrite("debug_invertida_colorida.jpg", invertedImage);
    cv::imwrite("debug_invertida_cinza.jpg", grayInverted);
    cv::imwrite("debug_original_cinza.jpg", grayOriginal);
    std::cout << "Imagens de debug salvas no diretorio atual" << std::endl;

    // 8. AGORA mostrar as imagens (ja que salvamento foi feito)
    try {
        cv::namedWindow("Imagem Original (Colorida)", cv::WINDOW_AUTOSIZE);
        cv::namedWindow("Imagem Invertida (Colorida)", cv::WINDOW_AUTOSIZE);
        cv::namedWindow("Imagem Original (Cinza)", cv::WINDOW_AUTOSIZE);
        cv::namedWindow("Imagem Invertida (Cinza)", cv::WINDOW_AUTOSIZE);

        cv::imshow("Imagem Original (Colorida)", originalImage);
        cv::imshow("Imagem Invertida (Colorida)", invertedImage);
        cv::imshow("Imagem Original (Cinza)", grayOriginal);
        cv::imshow("Imagem Invertida (Cinza)", grayInverted);

        std::cout << "Pressione qualquer tecla para continuar..." << std::endl;

        int key = 0;
        while (key != 27 && key != 13 && key != 32) { // ESC, Enter ou Espaco
            key = cv::waitKey(30) & 0xFF;
            if (key != 255) break; // Qualquer tecla pressionada
        }
    } catch (const cv::Exception& e) {
        std::cerr << "Erro ao exibir janelas: " << e.what() << std::endl;
    }

    // 9. Fechar todas as janelas
    cv::destroyAllWindows();

    std::cout << "Programa finalizado com sucesso!" << std::endl;
    return 0;
}