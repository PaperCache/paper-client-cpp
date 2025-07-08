# paper-client-cpp
The C++ [PaperCache](https://papercache.io) client. The client supports all commands described in the wire protocol on the homepage.

## Example
```cpp
#include <paper_client_cpp/client.hpp>

paper::client client ("paper://127.0.0.1:3145");

client.set("hello", "world");
auto got = client.get("hello");
```
