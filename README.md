# GET_NEXT_LINE
fd 를 매개변수로 받으면, 해당 fd 에서 들어온 입력을 읽고 한 줄을 return 해주는 함수 ft_gnl 구현

## ft_gnl의 Prototype

```c
char*  ft_gnl(int fd);
```

- fd 에 들어온 입력을 '\n' 전 까지 끊어서 char* 에 담아 반환한다.
- 입력에 '\n'이 없다면 들어온 입력 전부를 char* 에 담아 반환한다.
- 입력이 없거나 오류 발생시 NULL 포인터를 반환한다.

## ft_gnl의 내부 구현 특징

### 각 fd 들을 구조체 s_list 로 구성된 연결 리스트로 관리한다.
  
  ```c
  typedef struct s_list
  {
    int             fd;
    char            buffer[BUFFER_SIZE + 1];
    struct s_list  *next;
  }   
  ```
  - fd     : 구조체가 관리하는 fd
  - buffer : '\n' 까지 반환 후 남은 입력을 저장하는 버퍼
  - next : 다른 fd 를 관리하는 구조체를 가리키는 포인터


### fd 에서 입력을 읽어 반환하는 방법
 1. fd 를 읽어 구조체 buffer 에 담는다.
 2. buffer 내부에 '\n'이 있을 경우, '\n' 까지 반환할 char* 에 담고 반환한다.
 3. '\n'이 없다면 buffer 에 있는 값을 전부 반환할 char* 에 담는다.
 4. 입력이 더 있는 경우 1번부터 다시 반복하고, 없는 경우 char* 를 반환한다.


### 연결리스트 관리
  - 연결리스트는 static 으로 선언되어 buffer의 데이터를 유지할 수 있다.
  - ft_gnl의 인자로 받은 fd 에 대한 구조체를 생성한다.
  - 다 읽어서 buffer 가 비어있는 구조체는 삭제한다.

---

<img width="221" alt="스크린샷 2024-06-23 오후 10 30 20" src="https://github.com/seonjo1/GET_NEXT_LINE/assets/127729846/4d3eab81-a3b5-4cdf-9016-9827b82341f6">
