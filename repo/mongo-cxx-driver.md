1. pre-install

```
dnf install mongo-c-driver
```

2. download 

```
curl -OL https://github.com/mongodb/mongo-cxx-driver/releases/download/r3.7.0/mongo-cxx-driver-r3.7.0.tar.gz
tar -xzf mongo-cxx-driver-r3.7.0.tar.gz
cd mongo-cxx-driver-r3.7.0/build
```

3. config
```
cmake .. 
-DCMAKE_BUILD_TYPE=Debug 
-DCMAKE_CXX_STANDARD=17 
-DMONGOCXX_OVERRIDE_DEFAULT_INSTALL_PREFIX=OFF 
-DBUILD_VERSION=3.10.1

```

4. build&install

```
sudo cmake --build .
sudo cmake --build . --target install
```

5. compile 

```
make
c++ --std=c++17 main.cpp -o main \
    -I/usr/local/include/mongocxx/v_noabi \
    -I/usr/local/include/bsoncxx/v_noabi \
    -L/usr/local/lib -lmongocxx -lbsoncxx

cmake
include_directories(/usr/local/include/ /usr/local/include/mongocxx/v_noabi /usr/local/include/bsoncxx/v_noabi)
link_directories(/usr/local/lib/)
target_link_libraries(try_mongo libmongocxx.dylib libbsoncxx.dylib)

```