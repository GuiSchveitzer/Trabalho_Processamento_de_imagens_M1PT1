#ifndef UTILS_HPP
#define UTILS_HPP

#include <opencv2/opencv.hpp>
#include <algorithm>

// Funcao para saturar valores (substitui cv::saturate_cast)
inline uchar saturate_uchar(int value) {
    if (value > 255) return 255;
    if (value < 0) return 0;
    return static_cast<uchar>(value);
}

inline uchar saturate_uchar(float value) {
    if (value > 255.0f) return 255;
    if (value < 0.0f) return 0;
    return static_cast<uchar>(value + 0.5f); // Arredondamento
}

// Funcao para converter BGR para tons de cinza (substitui cv::cvtColor)
inline void convertBGRToGray(const cv::Mat& src, cv::Mat& dst) {
    dst = cv::Mat::zeros(src.rows, src.cols, CV_8UC1);
    
    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            cv::Vec3b pixel = src.at<cv::Vec3b>(y, x);
            uchar blue = pixel[0];
            uchar green = pixel[1];
            uchar red = pixel[2];
            
            // Formula padrao de conversao para tons de cinza
            uchar gray = static_cast<uchar>(0.299 * red + 0.587 * green + 0.114 * blue);
            dst.at<uchar>(y, x) = gray;
        }
    }
}

// Funcao para converter tons de cinza para BGR (substitui cv::cvtColor)
inline void convertGrayToBGR(const cv::Mat& src, cv::Mat& dst) {
    dst = cv::Mat::zeros(src.rows, src.cols, CV_8UC3);
    
    for (int y = 0; y < src.rows; y++) {
        for (int x = 0; x < src.cols; x++) {
            uchar grayValue = src.at<uchar>(y, x);
            dst.at<cv::Vec3b>(y, x) = cv::Vec3b(grayValue, grayValue, grayValue);
        }
    }
}

// Funcao para redimensionar imagem (substitui cv::resize - versao simples)
inline void resizeImage(const cv::Mat& src, cv::Mat& dst, cv::Size newSize) {
    dst = cv::Mat::zeros(newSize.height, newSize.width, src.type());
    
    float scaleX = static_cast<float>(src.cols) / newSize.width;
    float scaleY = static_cast<float>(src.rows) / newSize.height;
    
    for (int y = 0; y < newSize.height; y++) {
        for (int x = 0; x < newSize.width; x++) {
            int srcX = static_cast<int>(x * scaleX);
            int srcY = static_cast<int>(y * scaleY);
            
            // Garantir que nao ultrapasse os limites
            srcX = std::min(srcX, src.cols - 1);
            srcY = std::min(srcY, src.rows - 1);
            
            if (src.type() == CV_8UC3) {
                dst.at<cv::Vec3b>(y, x) = src.at<cv::Vec3b>(srcY, srcX);
            } else if (src.type() == CV_8UC1) {
                dst.at<uchar>(y, x) = src.at<uchar>(srcY, srcX);
            }
        }
    }
}

#endif // UTILS_HPP
