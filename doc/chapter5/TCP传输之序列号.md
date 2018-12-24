
示例代码：
- tcp_serv_1.cc 
- tcp_cli_1.cc 

上述代码实现字符串的回传，客户端发送什么字符串给服务器，服务器就转发该字符串给客户端。

TCP建立连接后，就可以传输数据了，TCP工作在全双工模式，它可以同时进行双向数据传输。

运行上述代码，服务器客户端成功建立连接后，在客户端输入`a`发送给服务器，结果如下：
```c 
// 客户端：
$ ./tcp_cli_1 127.0.0.1
Client is running...
a
Received from server: a

// 服务器：
$ ./tcp_serv_1
Server is running...
Received from client: a

```

`Wireshark`抓包如下：
![]()

其中序号967-969是TCP三次握手内容，这里不做分析。
会看到，在客户端服务器传输字符串`a\n`的过程中，产生了4个TCP报文。这里看到的序号为**975-978**

序号975报文内容：
```c 
Transmission Control Protocol, Src Port: 60383 (60383), Dst Port: sd (9876), Seq: 1181120994, Ack: 2786360474, Len: 2
    Source Port: 60383 (60383)
    Destination Port: sd (9876)
    [Stream index: 30]
    [TCP Segment Len: 2]
    Sequence number: 1181120994
    [Next sequence number: 1181120996]
    Acknowledgment number: 2786360474
    1000 .... = Header Length: 32 bytes (8)
    Flags: 0x018 (PSH, ACK)
    Window size value: 6379
    [Calculated window size: 408256]
    [Window size scaling factor: 64]
    Checksum: 0xfe2a [unverified]
    [Checksum Status: Unverified]
    Urgent pointer: 0
    Options: (12 bytes), No-Operation (NOP), No-Operation (NOP), Timestamps
    TCP payload (2 bytes)
Data (2 bytes)
    Data: 610a
    Text: a\n
    [Payload MD5 hash: 60b725f10c9c85c70d97880dfe8191b3]
    [Length: 2]
```

报文内容，客户端发送`PSH=1`和`ACK=1`，`PSH`表示当前传输数据，我们会看到`Data`部分是有内容的，字符串`a\n`，占两个字节，`TCP Segment Len=2`：
- PSH=1
- ACK=1
- TCP Segment Len 2
- Seq_Num(Cli)=1181120994
- Ack_Num(Cli)=2786360474

服务器收到客户端传来的字符串后，返回一个确认报文，序号为`976`：
- ACK=1
- Seq_Num(Srv)=2786360474
- Ack_Num(Srv)=1181120996 

可以看到，**Ack_Num(Srv) = Seq_Num(Cli) + TCP_Segment_Len**

序号977的内容则是服务器向客户端发送字符串`a\n`：
- PSH=1
- ACK=1
- Seq_Num(Srv)=2786360474
- Ack_num(Srv)=1181120996

会看到序号的值和976报文一样。这是因为，序号的值只有再下面两种情况才有意义：
- 数据字段至少包含一个字节
- 这是一个`SYN`段，或者`FIN`段，或者是`RST`段

TCP中对无携带资料的`ACK`区段，视为序列号无效，并且不消耗任何序列号。

我们可以继续传输字符串`aaa`来验证序列号的计算：
如下图：
![tcp_sequence_number_2]()

序号91948-91951在客户端和服务器之间传输字符串`aaa\n`，序号94243-94246传输一大串内容，会看到序列号的计算还是按照此规则。
