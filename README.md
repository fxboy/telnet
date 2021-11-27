The Mac OS uses socket to judge whether the port on the server is being monitored, and the port scanning and blasting function does not support sending and receiving messages directly on the console.

> be careful

It is recommended to modify the project name to avoid conflict with the telnet command

> usage method
```shell
PROJECTNAME <IP> <PORT1> <PORT2> <VIEW>  
```
  * IP: Host address   *
  
  * PORT1: Specify port *
  
  * PORT2: Burst scan end port
    
  * VIEW: Show only successful connections 1. Yes (default) 0. No, only valid for blasting
