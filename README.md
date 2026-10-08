# HTTP server in C

## Main components

| Layer no. | Layer Name   | Component      | Desc                                  |
| :-------- | :----------- | :------------- | :------------------------------------ |
| 7         | App          | HTTP protocol  | Req parsing + Res gen                 |
| 6         | Session      |                |                                       |
| 5         | Presentation |                |                                       |
| 4         | Transport    | TCP Networking | socket/bind/listen - accept/recv/send |
| 3         | Network      |                |                                       |
| 2         | Data Link    |                |                                       |
| 1         | Phy          |                |                                       |
