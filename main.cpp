#include "thread"
#include "XaivaDecoderManager/XaivaDecoderManager.h"

#include <vector>

// int ThreadTest(std::shared_ptr<XaivaMedia::XaivaDecoderManager> pXaivaDecoderManager, int nChannel, int nGpuNumber, std::string strUrl)
// {
//     pXaivaDecoderManager->CreateXaivaDecoder(nChannel, true, nGpuNumber);

//     pXaivaDecoderManager->SetFrameInterval(nChannel, 1);
//     pXaivaDecoderManager->SetReconnectTimeoutIntervalInSec(nChannel, 30);
//     pXaivaDecoderManager->SetDecodeQueueSize(nChannel, 20);
    
//     pXaivaDecoderManager->MediaOpen(nChannel, strUrl);
    
//     while(1)
//     {
//         int nRet = pXaivaDecoderManager->RunDemuxAndDecode(nChannel);
//         if(nRet != 0)
//         {
//             usleep(100000);
//             continue;
//         }
//         else
//         {
//             break;
//         }
//     }

//     while(1)
//     {
//         int nFrameNumber = 0;
//         long nTimeStamp = 0;
//         auto pTensor = pXaivaDecoderManager->GetTensorinQueue(nChannel, nFrameNumber, nTimeStamp);

//         std::cout << nFrameNumber << ", " << std::endl;
//         // if(pTensor.numel())
//         //     std::cout << pTensor << std::endl;

//         // if( nFrameNumber > 30)
//         //     break;
//     }
//     std::cout << "Thread End : " << nChannel << std::endl;
//     return 0;
// }

// int main(void)
// {
//     std::shared_ptr<XaivaMedia::XaivaDecoderManager> pXaivaDecoderManager = std::make_shared<XaivaMedia::XaivaDecoderManager>();
//     const int nChannelSize = 1;
//     const int nPopCount = 10000;
//     const int nSleepCountInMicro = 2000000;

//     const int nGpuNumber = 2;

//     // while(1)
//     {
//         std::string strVersion;
//         pXaivaDecoderManager->GetVersion(strVersion);
//         std::cout << "Show Version : " << strVersion << std::endl;
            
//         std::string logPath = "logs/ffmpeg_decoder.log";
//         pXaivaDecoderManager->SetLog(2, logPath, 10, 0, 0);
        
//         //Test Stream
//         std::vector<std::thread> vecThread(nChannelSize);
//         for(int i = 1; i <= nChannelSize; i++)
//         {
//             std::string strUrl = "rtsp://192.168.2.44:3082/" + std::to_string(i) + "/high";

//             vecThread[i-1] = std::thread(ThreadTest, pXaivaDecoderManager, i, nGpuNumber, strUrl);
//             vecThread[i-1].detach();
//             // pXaivaDecoderManager->CreateXaivaDecoder(i, true, nGpuNumber);

//             // pXaivaDecoderManager->SetFrameInterval(i, 1);
//             // pXaivaDecoderManager->SetReconnectTimeoutIntervalInSec(i, 30);
//             // pXaivaDecoderManager->SetDecodeQueueSize(i, 20);
            
//             // std::string strUrl = "rtsp://192.168.2.44:9082/" + std::to_string(i) + "/high";
//             // pXaivaDecoderManager->MediaOpen(i, strUrl);
            
//             // while(1)
//             // {
//             //     int nRet = pXaivaDecoderManager->RunDemuxAndDecode(i);
//             //     if(nRet != 0)
//             //     {
//             //         usleep(100000);
//             //         continue;
//             //     }
//             //     else
//             //     {
//             //         break;
//             //     }
//             // }
//         }

//         for(int i = 0; i <= nChannelSize; i++)
//         {
//             while(vecThread[i].joinable())
//                 usleep(1);
//                 continue;
//             vecThread[i].join();
//         }
        
//         // char* szUrl = (char*)"rtsp://xiirtsp:xiirocks12@192.168.10.80/ch4";
//         // char* szUrl = (char*)"./TestSample/street28_1min_conv.mp4";

        
//         // while(1)
//         // {
//         //     // int nWidth = 0;
//         //     // int nHeight = 0;
//         //     // double dFps = 0.0;
//         //     // pXaivaDecoderManager->GetMediaInfo(i, nWidth, nHeight, dFps);

//         //     for(int i = 1; i <= nChannelSize; i++)
//         //     {
//         //         int nState = pXaivaDecoderManager->GetStreamState(i);
//         //         // std::cout << "nState Check : " << nState << std::endl;

//         //         if(nState == -2)
//         //         {
//         //             pXaivaDecoderManager->CreateXaivaDecoder(i, true, nGpuNumber);

//         //             pXaivaDecoderManager->SetFrameInterval(i, 1);
//         //             pXaivaDecoderManager->SetReconnectTimeoutIntervalInSec(i, 30);
//         //             pXaivaDecoderManager->SetDecodeQueueSize(i, 20);
                    
//         //             std::string strUrl = "rtsp://192.168.2.44:9082/" + std::to_string(i) + "/high";
//         //             pXaivaDecoderManager->MediaOpen(i, strUrl);
                    
//         //             while(1)
//         //             {
//         //                 int nRet = pXaivaDecoderManager->RunDemuxAndDecode(i);
//         //                 if(nRet != 0)
//         //                 {
//         //                     usleep(1000000);
//         //                     continue;
//         //                 }
//         //                 else
//         //                 {
//         //                     break;
//         //                 }
//         //             }
//         //         }

//         //         int nFrameNumber = 0;
//         //         long nTimeStamp = 0;
//         //         auto pTensor = pXaivaDecoderManager->GetTensorinQueue(i, nFrameNumber, nTimeStamp);
//         //         // if(pTensor.numel())
//         //         //     std::cout << pTensor << std::endl;

//         //         if(nFrameNumber >= 1)
//         //             std::cout << "[" << i << "]GetFrontAddresInQueue : " << nFrameNumber << ", " << nTimeStamp << std::endl;

//         //         if(nFrameNumber > 90)
//         //             break;
                
//         //         int nCurrentQueueSize = 0;
//         //         int nConstraintQueueSize = 0;
//         //         pXaivaDecoderManager->GetDecodedQueueSize(i, nCurrentQueueSize, nConstraintQueueSize);
//         //         // if(nFrameNumber != 0)
//         //         //     std::cout << "GetDecodedQueueSize : " << nCurrentQueueSize << ", " << nConstraintQueueSize << std::endl;

//         //         // ReleaseFrameData(pFrame);
//         //         // std::cout << "av_freep " <<  std::endl;

//         //         // if (j % 30 == 0)
//         //         {
//         //         }

//         //         usleep(1);
//         //     }

//         //     // pFFmpegDecoder[i*10 + 1]->MediaOpen("rtsp://admin:Xiirocks1@59.10.103.94:19554/trackID=1");
//         //     // pFFmpegDecoder[i*10 + 2]->MediaOpen("rtsp://admin:Xiirocks1@192.168.10.246:554/trackID=1");
//         //     // pFFmpegDecoder[i*10 + 3]->MediaOpen("rtsp://admin:@192.168.10.247:554/trackID=1");
//         //     // pFFmpegDecoder[i*10 + 4]->MediaOpen("rtsp://admin:@192.168.10.248:554/trackID=1");
//         //     // pFFmpegDecoder[i*10 + 5]->MediaOpen("rtsp://admin:Xiirocks1@192.168.10.219:554/trackID=1");
//         //     // pFFmpegDecoder[i*10 + 6]->MediaOpen("rtsp://admin:Xiirocks1@192.168.10.212:554/trackID=1");
//         //     // pFFmpegDecoder[i*10 + 7]->MediaOpen("rtsp://admin:Xiirocks1@192.168.10.213:554/trackID=1");
//         //     // pFFmpegDecoder[i*10 + 8]->MediaOpen("rtsp://admin:Xiirocks1@192.168.10.216:554/trackID=1");
//         //     // pFFmpegDecoder[i*10 + 9]->MediaOpen("rtsp://admin:Xiirocks1@192.168.10.217:554/trackID=1");
//         // }

//         usleep(nSleepCountInMicro);

//         for(int i = 0; i < nChannelSize; i++)
//             pXaivaDecoderManager->DestroyXaivaDecoder(i);
//     }

//     return 0;
// }

// #include "PybindWrapper.h"

// int main()
// {
//     CreateXaivaDecoder(1, true);
//     return 0;
// }

int nWidth = 4;
int nHeight = 3;
int nStep = 3;


int TensorInfo(std::string strFunc, const torch::Tensor& pTensor)
{
    auto pTensorData = pTensor.data_ptr<uint8_t>();
    std::cout << strFunc << " : " << std::endl; 
    std::cout << (void*)pTensorData << std::endl;
    for (int i = 0; i < nWidth * nHeight; i++)
        std::cout << "index" << i << ": (" << 
            static_cast<int>(pTensorData[i*nStep + 0]) << ", " <<
            static_cast<int>(pTensorData[i*nStep + 1]) << ", " <<
            static_cast<int>(pTensorData[i*nStep + 2]) << ")" <<
            std::endl;

    std::cout << pTensor << std::endl;
    
    std::cout << std::endl;

    return 0;
}

int main()
{
    uint8_t* pData = new uint8_t[nWidth * nHeight * nStep]();

    // Clock 90
    // Destination (Tensor)
    // [[(1, 128, 255), (2, 127, 254), (3, 125, 252), (1, 122, 255)] 
    //  [(6, 127, 254), (4, 127, 254), (1, 121, 252), (2, 124, 253)]
    //  [(3, 128, 252), (5, 127, 253), (2, 121, 255), (1, 124, 254)]]

    // [[(3, 128, 252), (6, 127, 254), (1, 128, 255)]
    //  [(5, 127, 253), (4, 127, 254), (2, 127, 254)] 
    //  [(2, 121, 255), (1, 122, 255), (3, 125, 252)]  
    //  [(1, 124, 254), (2, 124, 253), (1, 122, 255)]]
    
    // Destination (Memory)
    // (1, 128, 255), 
    // (2, 127, 254), 
    // (3, 125, 252), 
    // (1, 122, 255), 
    // (6, 127, 254), 
    // (4, 127, 254), 
    // (1, 121, 252), 
    // (2, 124, 253)
    // (3, 128, 252), 
    // (5, 127, 253), 
    // (2, 121, 255), 
    // (1, 124, 254)

    // (3, 128, 252),
    // (6, 127, 254), 
    // (1, 128, 255),
    // (5, 127, 253),  
    // (4, 127, 254), 
    // (2, 127, 254),
    // (2, 121, 255), 
    // (1, 122, 255), 
    // (3, 125, 252),
    // (1, 124, 254),  
    // (2, 124, 253),
    // (1, 122, 255) 

    pData[0] = 1;   pData[1] = 128;     pData[2] = 255;
    pData[3] = 2;   pData[4] = 127;     pData[5] = 254;
    pData[6] = 3;   pData[7] = 125;     pData[8] = 252;
    pData[9] = 1;   pData[10] = 122;    pData[11] = 255;

    pData[12] = 6;  pData[13] = 127;    pData[14] = 254;
    pData[15] = 4;  pData[16] = 127;    pData[17] = 254;
    pData[18] = 1;  pData[19] = 121;    pData[20] = 252;
    pData[21] = 2;  pData[22] = 124;    pData[23] = 253;

    pData[24] = 3;  pData[25] = 128;    pData[26] = 252;
    pData[27] = 5;  pData[28] = 127;    pData[29] = 253;
    pData[30] = 2;  pData[31] = 121;    pData[32] = 255;
    pData[33] = 1;  pData[34] = 124;    pData[35] = 254;

    // for (int i = 0; i < nWidth * nHeight; i++)
    //     std::cout << "value " << i << ": (" << 
    //         static_cast<int>(pData[i*nStep + 0]) << ", " <<
    //         static_cast<int>(pData[i*nStep + 1]) << ", " <<
    //         static_cast<int>(pData[i*nStep + 2]) << ")" <<
    //         std::endl;
    // std::cout << std::endl;
    // std::cout << std::endl;

    auto options = torch::TensorOptions()
        .dtype(torch::kUInt8)
        .layout(torch::kStrided)
        .device(torch::kCPU);
    
    torch::Tensor pTensor;
    pTensor = torch::from_blob(pData, {nHeight, nWidth, nStep}, options).clone();
    TensorInfo("from_blob", pTensor);

    pTensor = pTensor.permute({2, 0, 1});
    TensorInfo("permute 1", pTensor);

    pTensor = pTensor.rot90(-1, {1, 2});
    TensorInfo("rot90", pTensor);

    pTensor = pTensor.permute({1, 2, 0});
    TensorInfo("permute 2", pTensor);

    pTensor = pTensor.contiguous();
    TensorInfo("Contiguous", pTensor);
    return 0;
}