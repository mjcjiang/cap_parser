# Prerequisite
g++ >= std11

cmake >= 3.12

# Compile and Link
```
mkdir build
cd build
cmake ..
make
```
# Run
```
cd apps
./test_cap_parser
```

# Trouble Shooting
when make the project, you may encounter message like this:
```
warning: libibverbs.so.1, needed by /home/hjiang/craft/cap_parser/build/lib/libpcap.so, not found (try using -rpath or -rpath-link)
```
just install libibverbs-dev (debian or ubuntu as example)
```
sudo apt-get install libibverbs-dev
```