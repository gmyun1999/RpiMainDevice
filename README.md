## Project description
- This is the main Raspberry Pi code for smart gardening.
- This Raspberry Pi can select the type and number of plants.
- It uses a raspberry pi, lcd and button actuator.
- Receive and process socket communication from multiple client Raspberry Pi synchronously.
  
## Project struct

- We used service dir to separate business logic from infrastructure logic.
- We didn't necessarily separate domain logic from business logic.
- In config.txt, we have the button gpio pin number and pr.

```bash
main_device/
├── include/                      # 헤더 파일 디렉터리
│   ├── config.h
│   ├── gpio.h
│   ├── LCD1602.h
│   ├── socket.h
│   ├── button.h
│   └── services/
│       ├── button_service.h
│       ├── communication_service.h
│       ├── lcd1602_service.h
│       ├── plant.h
│       └── step.h
├── src/                          # 소스 파일 디렉터리
│   ├── config.c
│   ├── gpio.c
│   ├── LCD1602.c
│   ├── socket.c
│   ├── button.c
│   └── services/
│       ├── button_service.c
│       ├── communication_service.c
│       ├── lcd1602_service.c
│       ├── plant.c
│       └── step.c
├── config.txt                   # 버튼 스레드 pr 및 gpio 핀번호
├── Makefile
├── README.md
└── main.c
```

## Requirements

To build and run, you will need the following libraries
- `gcc` (GNU Compiler Collection)
- `make`
- `pthread` (POSIX thread)
- `i2c` 
- `cjson` 

### install (linux)

You can install the required libraries using the following command

   ```bash
   sudo apt update
   sudo apt install build-essential make libi2c-dev libcjson-dev
   ```

1. **execute**

   ```sh
   sudo ./[project dir]
   
2. **compile**

   ```sh
   make

3. **remove the compiled object files and executables**

   ```sh
   make clean
