
import torch

import sys
sys.path.insert(1, '/root/xaiva-media/lib/')
import XaivaDecoder

from multiprocessing import Process, Manager, Lock
from multiprocessing.managers import BaseManager

import time
import random

class SharedXaivaDecoder(object):
    xaivaDecoder = XaivaDecoder.XaivaDecoderManager()

    def __init__(self):
        strUrl = "/root/xaiva-media/TestVideo/0001_compressed.mp4"
        # strUrl = "/root/xaiva-media/TestVideo/Next_Level_HD.mp4"
        self.strChannel = "0"
        
        logPath = "logs/xaiva_decoder.log"
        self.xaivaDecoder.SetLog(1, logPath, 10, 0, 0)
    
        self.xaivaDecoder.CreateXaivaDecoder(self.strChannel, False, 0)
        self.xaivaDecoder.SetFrameInterval(self.strChannel, 1)
        self.xaivaDecoder.SetDecodeQueueSize(self.strChannel, 7000)
        self.xaivaDecoder.MediaOpen(self.strChannel, strUrl)
    
        self.xaivaDecoder.RunDemuxAndDecode(self.strChannel)

    def GetAddress(self):
        return id(self.xaivaDecoder)

    def ReadTensor(self, strChannel, i):
        pTensor = self.xaivaDecoder.ReadTensor(strChannel, i)
        return pTensor
    
    def RemoveTensor(self, strChannel, i):
        nRet = self.xaivaDecoder.RemoveTensor(strChannel, i)
        return nRet
    
    def PopFrameIndex(self, strChannel):
        nIndex = self.xaivaDecoder.PopFrameIndex(strChannel)
        return nIndex

    def processing_test(self, processType):
        global startTime
        global endTime

        while True:
            i = random.randrange(1, 7000)

            pTensor = self.xaivaDecoder.ReadTensor(self.strChannel, i)
            
            if pTensor == None:
                time.sleep(0)
                continue

            pTensor = self.xaivaDecoder.ReadTensor(self.strChannel, i)
            pTensor = self.xaivaDecoder.ReadTensor(self.strChannel, i)
            pTensor = self.xaivaDecoder.ReadTensor(self.strChannel, i)
            # nRet = self.xaivaDecoder.RemoveTensor(self.strChannel, i)
            pTensor = self.xaivaDecoder.ReadTensor(self.strChannel, i)
            nRet = self.xaivaDecoder.RemoveTensor(self.strChannel, i)

            nCurrentQueueSize, nConstraintQueueSize = self.xaivaDecoder.GetDecodedQueueSize(self.strChannel)
            print("[{}] Queue Size : ".format(i), nCurrentQueueSize, "/",  nConstraintQueueSize)

            if i == 2:
                startTime = time.time()
            if i == 1200:
                endTime = time.time()
                print("Time : ", endTime - startTime)
            
            print("[{}] {} Check FrameNumber : {}/{}".format(self.strChannel, processType, i, 0))
            
            time.sleep(0)

        return 0


# def Proc(inst, processType):
#     print("Sub Thread Address : ", id(inst))

#     inst.processing_test(processType)

if __name__ == '__main__':
    BaseManager.register('SharedXaivaDecoder', SharedXaivaDecoder)
    manager = BaseManager()
    manager.start()

    inst = manager.SharedXaivaDecoder()
    print("Main Thread Address : ", id(inst))

    pn = list()
    processNumSize = 8
    for i in range(processNumSize):
        # pn.append(Process(target=Proc, args=[inst, 'sub{}'.format(i)]))
        pn.append(Process(target=inst.processing_test, args=['sub{}'.format(i)]))
        pn[i].start()

    inst.processing_test('main')

    for i in range(processNumSize):
        pn[i].join()

    while True :
        time.sleep(0)


