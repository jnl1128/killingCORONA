# killingCORONA

### 게임제작 배경
코로나-19가 빨리 종식되길 바라는 마음으로 세균을 닦아 죽여버리는 게임을 제작했습니다! 

### 게임 설명
1. 없앨 세균의 개수를 입력한다. 
    - how many viruses do you want to kill? 이라는 질문에 숫자를 입력한다.
2. 시작 버튼을 누르고 랜덤하게 생성되는 세균을 손 모양의 아이콘을 움직여 닦는다.
![bubble3](https://user-images.githubusercontent.com/64057843/96365005-b710a080-1178-11eb-9f4c-933bf8677728.png)
3. 게임 한 판당 10초의 제한시간이 있다.
4. 제한시간을 넘으면 수명 하나가 없어진다.
![heart](https://user-images.githubusercontent.com/64057843/96364678-c0007280-1176-11eb-8ad1-0540d5a301cf.png)
![heart](https://user-images.githubusercontent.com/64057843/96364678-c0007280-1176-11eb-8ad1-0540d5a301cf.png)
![heart](https://user-images.githubusercontent.com/64057843/96364678-c0007280-1176-11eb-8ad1-0540d5a301cf.png)
5. 수명은 총 3개로, 3개가 모두 끝나면 게임이 자동으로 종료된다.
6. 게임 한 판이 끝나고 계속 게임을 진행할지 여부를 go 버튼과 stop 버튼으로 결정할 수 있다.
![stop](https://user-images.githubusercontent.com/64057843/96364986-9cd6c280-1178-11eb-9848-d2e2631077f1.png) ![go-up](https://user-images.githubusercontent.com/64057843/96364988-9d6f5900-1178-11eb-8657-c6df6edf2ae7.png)

### 게임제작에 사용한 개념
1. 동적 할당
    - 게임 한 판당, 없앨 세균의 개수를 직접 입력하도록 배열의 크기를 동적으로 바꿀 수 있도록 했다.
    - 35 이내로 입력해야 하고, 그 이상의 수를 입력했을 경우 새로 입력을 받는다.
2. 클래스
    - 랜덤하게 생성되는 여러개의 세균의 위치를 파악하기 위해서 클래스 개념을 사용한다.
3. 랜덤 생성
    - 중복 없이 세균을 랜덤하게 생성한다.
    - 즉, 입력받은 수 만큼 세균이 랜덤한 이미지와 위치에 생성되도록 한다.
