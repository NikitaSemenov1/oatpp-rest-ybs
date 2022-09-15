# Yandex backend school test project

## Overview

### Project layout

```
|- CMakeLists.txt                        // projects CMakeLists.txt
|- src/
|    |- service/                         // business logic
|    |- controller/                      // Folder containing MyController where all endpoints are declared
|    |- dto/                             // DTOs are declared here
|    |- AppComponent.hpp                 // Service components
|    |- App.cpp                          // main() is here
|    |- DabaseComponent.hpp              // Database components
|    |- ErrorHandler.hpp                 // Custom error handler. Responds json
|    |- Serializers.hpp                  // DTO serializer
|- sql/                                  // migrations
|- utility/install-oatpp-modules.sh      // utility script to install required oatpp-modules.
|- resources/config.json                 // configuration file with configuration profiles
|- Dockerfile                            // Dockerfile
|- docker-compose.yaml                   // Docker-compose with this service and postgresql 
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