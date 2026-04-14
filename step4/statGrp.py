import matplotlib.pyplot as plt
from datetime import datetime
from pathlib import Path

myId=2024128055
name="전성환"
myTime = datetime.now()

#wc, youtube 폴더명
statName=["wcStat","youtubeStat"]

# 리눅스 한글 폰트(없으면 sans-serif로 대체)
plt.rcParams["font.family"] = "NanumGothic"
plt.rcParams["axes.unicode_minus"] = False


for stat in statName:
    #CPU 사용량
    fig, axs = plt.subplots(2,2)
    fig.suptitle(f"{stat} \n 이름: {name} 학번: {myId}\n 현재시각 {myTime}")

    dir = Path(__file__).resolve().parent
    path = dir.parent / "step3" / stat
    cpuUseges=[]
    sec=0
    times=[]
    with open(path / "cpu.txt",'r',encoding="utf-8") as cStat:
        for line in cStat:
            scores = line.split()
            if len(scores)>=4 and scores[1]=='all':
                cpuUseges.append(100.0-float(scores[-1]))
                times.append(sec)
                sec+=1
    axs[0,0].plot(times,cpuUseges)
    axs[0,0].set_title("cpu사용량")

    #메모리 사용량
    memUseges=[]
    sec=0
    times=[]
    with open(path / "memory.txt",'r',encoding='utf-8') as memStat:
        for line in memStat:
            scores = line.split()
            if len(scores) <= 2 or scores[1]=="kbmemfree" or scores[0]=="Linux": continue
            memUseges.append(float(scores[4]))
            times.append(sec)
            sec+=1
    axs[0,1].plot(times,memUseges)
    axs[0,1].set_title("memory사용량")

    #디스크IO사용량
    diskUseges=[]
    sec=0
    times=[]
    with open(path / "disk.txt",'r',encoding="utf-8") as dStat:
        for line in dStat:
            scores=line.split()
            if len(scores)>=2 and scores[1]=="vda":
                diskUseges.append(float(scores[-1]))
                times.append(sec)
                sec+=1
    axs[1,0].plot(times,diskUseges)
    axs[1,0].set_title('disk 사용량')


    rx=[]
    tx=[]
    sec=0
    times=[]
    with open(path / "network.txt",'r',encoding='utf-8') as netStat:
        for line in netStat:
            scores = line.split()
            if len(scores)>=2 and scores[1]=="enp0s1":
                rx.append(float(scores[4]))
                tx.append(float(scores[5]))
                times.append(sec)
                sec+=1
    axs[1,1].plot(times,rx,color="orange")
    axs[1,1].plot(times,tx,color="blue")
    axs[1,1].set_title("네트워크사용량(rx: orange, tx: blue)")

    plt.tight_layout()
    plt.savefig(stat+"결과.pdf")
    plt.close(fig)
    



            


            
            
