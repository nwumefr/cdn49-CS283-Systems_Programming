1. How does the remote client determine when a command's output is fully received from the server, and what techniques can be used to handle partial reads or ensure complete message transmission?

A remote client determines that a command's output is fully received using methods like length prefixing (where the server sends the message length first), delimiter-based framing (using a special character like \n or \0 to mark the end), or connection closure (where the client reads until the server disconnects). Partial reads can be handled by looping recv() until the expected data is received, buffering data, or using non-blocking/asynchronous I/O to avoid indefinite blocking.

2. This week's lecture on TCP explains that it is a reliable stream protocol rather than a message-oriented one. Since TCP does not preserve message boundaries, how should a networked shell protocol define and detect the beginning and end of a command sent over a TCP connection? What challenges arise if this is not handled correctly?

Since TCP is a stream protocol and does not preserve message boundaries, a networked shell protocol must define message boundaries using length prefixing (including message size in a fixed header), delimiter-based framing (using special characters like \n or \0), or fixed-size messages. If not handled correctly, messages may be split across multiple packets or combined, leading to corrupted or incomplete commands being processed.

3. Describe the general differences between stateful and stateless protocols.

Stateful protocols maintain context between client-server interactions (e.g., TCP, where a connection persists), while stateless protocols treat each request independently with no retained memory of past interactions (e.g., HTTP, where each request is self-contained). Stateful protocols enable persistent sessions but require more resources, while stateless protocols are more scalable and fault-tolerant.

4. Our lecture this week stated that UDP is "unreliable". If that is the case, why would we ever use it?

UDP is used despite being "unreliable" because it has lower latency and overhead, making it ideal for real-time applications like video streaming, online gaming, VoIP, and DNS lookups, where occasional packet loss is acceptable and retransmission would introduce unnecessary delays.

5. What interface/abstraction is provided by the operating system to enable applications to use network communications?

The operating system provides the socket interface, which abstracts network communication for applications by allowing them to create, bind, connect, send, and receive data over network protocols like TCP and UDP, enabling reliable or fast communication depending on the use case.