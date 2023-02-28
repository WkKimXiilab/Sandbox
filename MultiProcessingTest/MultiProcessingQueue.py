
import torch

import sys
sys.path.insert(1, '/root/xaiva-media/lib/')
import XaivaDecoder

from multiprocessing import Process, Manager
from multiprocessing.managers import BaseManager
import time

class SharedXaivaDecoder(object):
    xaivaDecoder = XaivaDecoder.XaivaDecoderManager()

    def __init__(self):
        strUrl = "/root/xaiva-media/TestVideo/0001_compressed.mp4"
        self.strChannel = "0"
        
        logPath = "logs/xaiva_decoder.log"
        self.xaivaDecoder.SetLog(0, logPath, 10, 0, 0)
    
        self.xaivaDecoder.CreateXaivaDecoder(self.strChannel, False, 0)
        self.xaivaDecoder.SetFrameInterval(self.strChannel, 1)
        self.xaivaDecoder.SetDecodeQueueSize(self.strChannel, 1500)
        self.xaivaDecoder.MediaOpen(self.strChannel, strUrl)
    
        self.xaivaDecoder.RunDemuxAndDecode(self.strChannel)

        # time.sleep(60)

    def GetAddress(self):
        return id(self.xaivaDecoder)

    def processing_test(self, processType):
        global startTime
        global endTime
        print("Sub Thread Version : ", self.xaivaDecoder.GetVersion())

        while True:
            pTensor, nFrameNumber, nTimeStamp = self.xaivaDecoder.GetTensorinQueue(self.strChannel)

            nState = self.xaivaDecoder.GetStreamState(self.strChannel)
            if (nState == -3) :
                print("End of Decoding.")
                break

            # 전달된 Tensor가 없으면 다시 반복
            if pTensor == None:
                time.sleep(0)
                continue

            del(pTensor)

            if nFrameNumber == 2:
                startTime = time.time()
            if nFrameNumber == 1201:
                endTime = time.time()
                print("Time : ", endTime - startTime)
            
            print("[{}] {} Check FrameNumber : {}".format(self.strChannel, processType, nFrameNumber))
            time.sleep(0)

        return 0


def Proc(inst):
    print("Sub Thread Address : ", id(inst))

    inst.processing_test('sub ')


def main():
    BaseManager.register('SharedXaivaDecoder', SharedXaivaDecoder)
    manager = BaseManager()
    manager.start()

    inst = manager.SharedXaivaDecoder()
    print("Main Thread Address : ", id(inst))

    p = Process(target=Proc, args=[inst])

    p.start()

    inst.processing_test('main')

    p.join()    


if __name__ == '__main__':
    main()
