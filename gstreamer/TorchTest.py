import torch
import time

shape = (3, 1920, 1080)

start = time.time()
loopCount = 100
for i in range(0, loopCount):
    x = torch.rand(shape, device=torch.device('cpu'))
    # x.cuda()
    # x = torch.rand(shape, device=torch.device('cuda:0'))
    # x.cpu()
end = time.time()

print("[{}]GPU-CPU Converting : {}".format(loopCount, end-start))