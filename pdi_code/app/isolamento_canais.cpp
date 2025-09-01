#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

int main() {
    std::cout << "Processamento de Imagens - Isolamento de Canais de Cores" << std::endl;

    // 1. Carregar a imagem colorida
    std::string imagePath = "../data/blobs-image.jpg";
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

    // 3. Criar matrizes para cada canal isolado
    cv::Mat redChannel = cv::Mat::zeros(height, width, CV_8UC3);    // Canal R isolado
    cv::Mat greenChannel = cv::Mat::zeros(height, width, CV_8UC3);  // Canal G isolado
    cv::Mat blueChannel = cv::Mat::zeros(height, width, CV_8UC3);   // Canal B isolado

    std::cout << "Processando pixels para isolar canais..." << std::endl;

    // 4. Processar cada pixel para isolar os canais
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // OpenCV usa formato BGR (Blue, Green, Red)
            cv::Vec3b pixel = originalImage.at<cv::Vec3b>(y, x);
            
            uchar blue = pixel[0];   // Canal B
            uchar green = pixel[1];  // Canal G  
            uchar red = pixel[2];    // Canal R

            // Canal R isolado: apenas o vermelho, outros zerados
            redChannel.at<cv::Vec3b>(y, x) = cv::Vec3b(0, 0, red);
            
            // Canal G isolado: apenas o verde, outros zerados
            greenChannel.at<cv::Vec3b>(y, x) = cv::Vec3b(0, green, 0);
            
            // Canal B isolado: apenas o azul, outros zerados
            blueChannel.at<cv::Vec3b>(y, x) = cv::Vec3b(blue, 0, 0);
        }
    }

    std::cout << "Processamento concluido!" << std::endl;

    // 5. SALVAR PRIMEIRO - antes de qualquer visualizacao
    std::string redOutputPath = "../data/canal_red_isolado.jpg";
    std::string greenOutputPath = "../data/canal_green_isolado.jpg";
    std::string blueOutputPath = "../data/canal_blue_isolado.jpg";

    std::cout << "Salvando canais isolados..." << std::endl;
    
    bool redSaved = cv::imwrite(redOutputPath, redChannel);
    bool greenSaved = cv::imwrite(greenOutputPath, greenChannel);
    bool blueSaved = cv::imwrite(blueOutputPath, blueChannel);

    if (redSaved && greenSaved && blueSaved) {
        std::cout << "Canais isolados salvos com sucesso!" << std::endl;
        std::cout << "Canal R salvo em: " << redOutputPath << std::endl;
        std::cout << "Canal G salvo em: " << greenOutputPath << std::endl;
        std::cout << "Canal B salvo em: " << blueOutputPath << std::endl;
    } else {
        std::cerr << "Erro ao salvar alguns canais." << std::endl;
    }

    // 6. Salvar imagens de debug
    cv::imwrite("debug_canal_red.jpg", redChannel);
    cv::imwrite("debug_canal_green.jpg", greenChannel);
    cv::imwrite("debug_canal_blue.jpg", blueChannel);
    std::cout << "Imagens de debug salvas no diretorio atual" << std::endl;

    // 7. AGORA mostrar as imagens (ja que salvamento foi feito)
    try {
        cv::namedWindow("Imagem Original", cv::WINDOW_AUTOSIZE);
        cv::namedWindow("Canal R (Vermelho)", cv::WINDOW_AUTOSIZE);
        cv::namedWindow("Canal G (Verde)", cv::WINDOW_AUTOSIZE);
        cv::namedWindow("Canal B (Azul)", cv::WINDOW_AUTOSIZE);

        cv::imshow("Imagem Original", originalImage);
        cv::imshow("Canal R (Vermelho)", redChannel);
        cv::imshow("Canal G (Verde)", greenChannel);
        cv::imshow("Canal B (Azul)", blueChannel);

        std::cout << "Pressione qualquer tecla para continuar..." << std::endl;

        int key = 0;
        while (key != 27 && key != 13 && key != 32) { // ESC, Enter ou Espaco
            key = cv::waitKey(30) & 0xFF;
            if (key != 255) break; // Qualquer tecla pressionada
        }
    } catch (const cv::Exception& e) {
        std::cerr << "Erro ao exibir janelas: " << e.what() << std::endl;
    }

    // 8. Fechar todas as janelas
    cv::destroyAllWindows();

    std::cout << "Programa finalizado com sucesso!" << std::endl;
    return 0;
}