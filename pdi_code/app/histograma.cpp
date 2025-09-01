#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>

// Funcao para computar histograma manualmente
std::vector<int> computeHistogram(const cv::Mat& image, int channel = 0) {
    std::vector<int> histogram(256, 0);
    
    for (int y = 0; y < image.rows; y++) {
        for (int x = 0; x < image.cols; x++) {
            if (image.channels() == 1) {
                // Imagem em escala de cinza
                uchar intensity = image.at<uchar>(y, x);
                histogram[intensity]++;
            } else {
                // Imagem colorida
                cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);
                histogram[pixel[channel]]++;
            }
        }
    }
    
    return histogram;
}

// Funcao para desenhar histograma
cv::Mat drawHistogram(const std::vector<int>& histogram, const cv::Scalar& color, const std::string& title) {
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double) hist_w / 256);
    
    cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar(0, 0, 0));
    
    // Encontrar valor maximo para normalizar
    int max_val = *std::max_element(histogram.begin(), histogram.end());
    
    // Desenhar as barras do histograma
    for (int i = 1; i < 256; i++) {
        cv::line(histImage,
                cv::Point(bin_w * (i-1), hist_h - cvRound(((double)histogram[i-1] / max_val) * hist_h)),
                cv::Point(bin_w * i, hist_h - cvRound(((double)histogram[i] / max_val) * hist_h)),
                color, 2, 8, 0);
    }
    
    // Adicionar titulo
    cv::putText(histImage, title, cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(255, 255, 255), 2);
    
    return histImage;
}

int main() {
    std::cout << "Processamento de Imagens - Computacao e Visualizacao de Histogramas" << std::endl;

    // 1. Carregar a imagem colorida
    std::string imagePath = "../data/blobs-image-2.jpg";
    cv::Mat originalImage = cv::imread(imagePath, cv::IMREAD_COLOR);

    if (originalImage.empty()) {
        std::cerr << "Erro: Nao foi possivel carregar a imagem: " << imagePath << std::endl;
        return -1;
    }

    std::cout << "Imagem carregada com sucesso!" << std::endl;
    std::cout << "Dimensoes: " << originalImage.cols << "x" << originalImage.rows << std::endl;

    // 2. Converter para escala de cinza
    cv::Mat grayImage;
    cv::cvtColor(originalImage, grayImage, cv::COLOR_BGR2GRAY);

    std::cout << "Computando histogramas..." << std::endl;

    // 3. Computar histogramas manualmente
    
    // Histograma da imagem em escala de cinza
    std::vector<int> grayHistogram = computeHistogram(grayImage);
    
    // Histogramas dos canais RGB da imagem colorida
    std::vector<int> blueHistogram = computeHistogram(originalImage, 0);   // Canal B
    std::vector<int> greenHistogram = computeHistogram(originalImage, 1);  // Canal G
    std::vector<int> redHistogram = computeHistogram(originalImage, 2);    // Canal R

    std::cout << "Histogramas computados com sucesso!" << std::endl;

    // 4. Criar visualizacoes dos histogramas
    cv::Mat grayHistImage = drawHistogram(grayHistogram, cv::Scalar(255, 255, 255), "Histograma - Escala de Cinza");
    cv::Mat blueHistImage = drawHistogram(blueHistogram, cv::Scalar(255, 0, 0), "Histograma - Canal Azul");
    cv::Mat greenHistImage = drawHistogram(greenHistogram, cv::Scalar(0, 255, 0), "Histograma - Canal Verde");
    cv::Mat redHistImage = drawHistogram(redHistogram, cv::Scalar(0, 0, 255), "Histograma - Canal Vermelho");

    // 5. Criar histograma combinado RGB
    cv::Mat combinedHistImage(400, 512, CV_8UC3, cv::Scalar(0, 0, 0));
    int bin_w = cvRound((double) 512 / 256);
    
    // Encontrar valor maximo para normalizar
    int max_blue = *std::max_element(blueHistogram.begin(), blueHistogram.end());
    int max_green = *std::max_element(greenHistogram.begin(), greenHistogram.end());
    int max_red = *std::max_element(redHistogram.begin(), redHistogram.end());
    int max_combined = std::max({max_blue, max_green, max_red});
    
    // Desenhar histogramas combinados
    for (int i = 1; i < 256; i++) {
        // Canal Azul
        cv::line(combinedHistImage,
                cv::Point(bin_w * (i-1), 400 - cvRound(((double)blueHistogram[i-1] / max_combined) * 400)),
                cv::Point(bin_w * i, 400 - cvRound(((double)blueHistogram[i] / max_combined) * 400)),
                cv::Scalar(255, 0, 0), 1, 8, 0);
        
        // Canal Verde
        cv::line(combinedHistImage,
                cv::Point(bin_w * (i-1), 400 - cvRound(((double)greenHistogram[i-1] / max_combined) * 400)),
                cv::Point(bin_w * i, 400 - cvRound(((double)greenHistogram[i] / max_combined) * 400)),
                cv::Scalar(0, 255, 0), 1, 8, 0);
        
        // Canal Vermelho
        cv::line(combinedHistImage,
                cv::Point(bin_w * (i-1), 400 - cvRound(((double)redHistogram[i-1] / max_combined) * 400)),
                cv::Point(bin_w * i, 400 - cvRound(((double)redHistogram[i] / max_combined) * 400)),
                cv::Scalar(0, 0, 255), 1, 8, 0);
    }
    
    cv::putText(combinedHistImage, "Histograma RGB Combinado", cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(255, 255, 255), 2);

    std::cout << "Visualizacoes dos histogramas criadas!" << std::endl;

    // 6. SALVAR PRIMEIRO - antes de qualquer visualizacao
    std::string grayHistPath = "../data/histograma_escala_cinza.jpg";
    std::string blueHistPath = "../data/histograma_canal_azul.jpg";
    std::string greenHistPath = "../data/histograma_canal_verde.jpg";
    std::string redHistPath = "../data/histograma_canal_vermelho.jpg";
    std::string combinedHistPath = "../data/histograma_rgb_combinado.jpg";
    std::string grayImagePath = "../data/imagem_escala_cinza.jpg";

    std::cout << "Salvando histogramas e imagens..." << std::endl;
    
    bool grayHistSaved = cv::imwrite(grayHistPath, grayHistImage);
    bool blueHistSaved = cv::imwrite(blueHistPath, blueHistImage);
    bool greenHistSaved = cv::imwrite(greenHistPath, greenHistImage);
    bool redHistSaved = cv::imwrite(redHistPath, redHistImage);
    bool combinedHistSaved = cv::imwrite(combinedHistPath, combinedHistImage);
    bool grayImageSaved = cv::imwrite(grayImagePath, grayImage);

    if (grayHistSaved && blueHistSaved && greenHistSaved && redHistSaved && combinedHistSaved && grayImageSaved) {
        std::cout << "Histogramas e imagens salvos com sucesso!" << std::endl;
        std::cout << "Histograma escala de cinza: " << grayHistPath << std::endl;
        std::cout << "Histograma canal azul: " << blueHistPath << std::endl;
        std::cout << "Histograma canal verde: " << greenHistPath << std::endl;
        std::cout << "Histograma canal vermelho: " << redHistPath << std::endl;
        std::cout << "Histograma RGB combinado: " << combinedHistPath << std::endl;
        std::cout << "Imagem em escala de cinza: " << grayImagePath << std::endl;
    } else {
        std::cerr << "Erro ao salvar alguns arquivos." << std::endl;
    }

    // 7. Salvar imagens de debug
    cv::imwrite("debug_hist_gray.jpg", grayHistImage);
    cv::imwrite("debug_hist_combined.jpg", combinedHistImage);
    cv::imwrite("debug_gray_image.jpg", grayImage);
    std::cout << "Imagens de debug salvas no diretorio atual" << std::endl;

    // 8. AGORA mostrar as imagens (ja que salvamento foi feito)
    try {
        cv::namedWindow("Imagem Original", cv::WINDOW_AUTOSIZE);
        cv::namedWindow("Imagem Escala de Cinza", cv::WINDOW_AUTOSIZE);
        cv::namedWindow("Histograma - Escala de Cinza", cv::WINDOW_AUTOSIZE);
        cv::namedWindow("Histograma - Canal Azul", cv::WINDOW_AUTOSIZE);
        cv::namedWindow("Histograma - Canal Verde", cv::WINDOW_AUTOSIZE);
        cv::namedWindow("Histograma - Canal Vermelho", cv::WINDOW_AUTOSIZE);
        cv::namedWindow("Histograma RGB Combinado", cv::WINDOW_AUTOSIZE);

        cv::imshow("Imagem Original", originalImage);
        cv::imshow("Imagem Escala de Cinza", grayImage);
        cv::imshow("Histograma - Escala de Cinza", grayHistImage);
        cv::imshow("Histograma - Canal Azul", blueHistImage);
        cv::imshow("Histograma - Canal Verde", greenHistImage);
        cv::imshow("Histograma - Canal Vermelho", redHistImage);
        cv::imshow("Histograma RGB Combinado", combinedHistImage);

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