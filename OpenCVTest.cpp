#include <iostream>

// #include <opencv2/core/core.hpp>
// #include <opencv2/imgcodecs/imgcodecs.hpp>
// #include <opencv2/imgproc/imgproc.hpp>

// int main()
// {
//     std::cout << "test : " << std::endl;
//     cv::Mat mImage = cv::Mat();

//     // mImage = cv::imread("/root/xaiva_decoder/OutputImage/test_1_.jpg");
//     try 
//     {
//         mImage = cv::imread("/root/xaiva_decoder/test_src.jpg");
//     }
// 	catch (cv::Exception& e)
// 	{
// 		std::string strError = "imread : " + std::string(e.what());
//         std::cout << strError <<  std::endl;
// 	}

//     std::cout << mImage.size() << std::endl;
//     // cv::cvtColor(mImage, mImage, cv::COLOR_BGR2RGB);

//     try 
//     {
//         int nRet = cv::imwrite("/root/xaiva_decoder/OutputImage/test.jpg", mImage);
//     }
// 	catch (cv::Exception& e)
// 	{
// 		std::string strError = "imwrite : " + std::string(e.what());
//         std::cout << strError <<  std::endl;
// 	}

//     // std::cout << nRet << std::endl;

//     return 0;
// }
#include <fstream>
#include <iostream>
#include <errno.h>
#include <string.h>
#include "/root/xaiva_decoder/Third_party/libjpeg-turbo/turbojpeg.h"

int main()
{
    unsigned char *srcBuf; //passed in as a param containing pixel data in RGB pixel interleaved format
    tjhandle handle = tjInitCompress();

    if(handle == NULL)
    {
        const char *err = (const char *) tjGetErrorStr();
        std::cout << "TJ Error: " << err << " UNABLE TO INIT TJ Compressor Object\n";
        return -1;
    }
    int jpegQual =92;
    int width = 1920;
    int height = 1080;
    int nbands = 3;
    int flags = 0;
    unsigned char* jpegBuf = NULL;
    int pitch = width * nbands;
    int pixelFormat = TJPF_GRAY;
    int jpegSubsamp = TJSAMP_GRAY;
    
    if(nbands == 3)
    {
        pixelFormat = TJPF_RGB;
        jpegSubsamp = TJSAMP_411;
    }
    unsigned long jpegSize = 0;

    srcBuf = new unsigned char[width * height * nbands];
    for(int j = 0; j < height; j++)
    {
        for(int i = 0; i < width; i++)
        {
            srcBuf[(j * width + i) * nbands + 0] = (i) % 256;
            srcBuf[(j * width + i) * nbands + 1] = (j) % 256;
            srcBuf[(j * width + i) * nbands + 2] = (j + i) % 256;
        }
    }

    int tj_stat = tjCompress2( handle, srcBuf, width, pitch, height,
        pixelFormat, &(jpegBuf), &jpegSize, jpegSubsamp, jpegQual, flags);
   
    if(tj_stat != 0)
    {
        const char *err = (const char *) tjGetErrorStr();
        std::cout << "TurboJPEG Error: " << err << " UNABLE TO COMPRESS JPEG IMAGE\n";
        tjDestroy(handle);
        handle = NULL;
        return -1;
    }

    FILE *file = fopen("/root/xaiva_decoder/out.jpg", "wb");
    if (!file) {
        std::cout << "Could not open JPEG file: " << strerror(errno);
        return -1;
    }
    if (fwrite(jpegBuf, jpegSize, 1, file) < 1) {
        std::cout << "Could not write JPEG file: " << strerror(errno);
        return -1;
    }
    fclose(file);

    // std::string strFilePath = "/root/xaiva_decoder/out.jpg";

    // std::ofstream ofWriteFile(strFilePath.data(), std::ios::binary);
    // std::cout << "ofWriteFile Create!" <<  std::endl;

    // ofWriteFile.write(reinterpret_cast<const char*>(&jpegBuf), jpegSize);
    // std::cout << "ofWriteFile write! : size " << jpegSize <<  std::endl;

    // ofWriteFile.close();

    tjDestroy(handle);

    //to free the memory allocated by TurboJPEG (either by tjAlloc(), 
    //or by the Compress/Decompress) after you are done working on it:
    tjFree(jpegBuf);

    return 0;
}