#include <opencv2/opencv.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/cudaarithm.hpp>
#include <opencv2/cudafilters.hpp>

int main(int argc, char** argv)
{
    std::cout << "test!" << std::endl;
    cv::Mat src = cv::imread("/root/Sandbox/0.jpg", cv::IMREAD_COLOR); // 이미지 로드
    cv::cuda::GpuMat d_src, d_dst; // GPU에서 사용할 GpuMat 생성

    d_src.upload(src); // CPU에서 GPU로 이미지 업로드

    cv::Ptr<cv::cuda::Filter> filter = cv::cuda::createGaussianFilter(d_src.type(), d_src.type(), cv::Size(31, 31), 0);
    filter->apply(d_src, d_dst);

    cv::Mat dst;
    d_dst.download(dst); // GPU에서 CPU로 이미지 다운로드

    cv::imwrite("test.jpg", dst);

    // cv::imshow("Source", src);
    // cv::imshow("Result", dst);

    // cv::waitKey();

    return 0;
}