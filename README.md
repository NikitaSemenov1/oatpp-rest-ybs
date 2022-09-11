# oatpp-starter
Starter project of oat++ (AKA oatpp) application. Based on oatpp Multithreaded (Simple) API.

## Overview

### Project layout

```
|- CMakeLists.txt                        // projects CMakeLists.txt
|- src/
|    |
|    |- controller/                      // Folder containing MyController where all endpoints are declared
|    |- dto/                             // DTOs are declared here
|    |- AppComponent.hpp                 // Service config
|    |- App.cpp                          // main() is here
|
|- test/                                 // test folder
|- utility/install-oatpp-modules.sh      // utility script to install required oatpp-modules.  
```

---

### Build and Run

#### Using CMake

**Requires** 

- `oatpp` module installed. You may run `utility/install-oatpp-modules.sh` 
script to install required oatpp modules.

```
$ mkdir build && cd build
$ cmake ..
$ make 
$ ./oatpp-rest-ybs-exe  # - run application.

```

[//]: # (#### In Docker)

[//]: # ()
[//]: # (```)

[//]: # ($ docker build -t oatpp-starter .)

[//]: # ($ docker run -p 8000:8000 -t oatpp-starter)

[//]: # (```)
