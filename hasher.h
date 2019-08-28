#ifndef HASHER_H
#define HASHER_H

#include <iostream>
#include <openssl/sha.h>
#include <openssl/md5.h>
#include <string>
#include <sstream>
#include <vector>

class HashStrategy
{
public:
  virtual ~HashStrategy() { }
  virtual void toHash(std::vector<uint16_t>& dest, const std::string& src) = 0;
};

class Sha1 : public HashStrategy
{
public:
  ~Sha1() { }
  void toHash(std::vector<uint16_t>& dest, const std::string& src)
  {
    SHA_CTX ctx;
    SHA1_Init(&ctx);
    SHA1_Update(&ctx, src.c_str(), src.length());
    SHA1_Final(reinterpret_cast<unsigned char*>(dest.data()), &ctx);    
  }
};

class Sha256 : public HashStrategy
{
public:
  ~Sha256() { }
  void toHash(std::vector<uint16_t>& dest, const std::string& src)
  {
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, src.c_str(), src.length());
    SHA256_Final(reinterpret_cast<unsigned char*>(dest.data()), &ctx);    
  }
};

class MD5 : public HashStrategy
{
public:
  ~MD5() { }
  void toHash(std::vector<uint16_t>& dest, const std::string& src)
  {
    MD5_CTX ctx;
    MD5_Init(&ctx);
    MD5_Update(&ctx, src.c_str(), src.length());
    MD5_Final(reinterpret_cast<unsigned char*>(dest.data()), &ctx);    
  }
};

class Hasher
{
public:
  Hasher( HashStrategy* const s ) : strategy( s ) {}
  ~Hasher()
  {
    delete strategy;
  }
  void toHash(std::vector<uint16_t>& dest, const std::string& src)
  {
    strategy->toHash(dest, src);
  }

private:
  HashStrategy *strategy;
};

#endif
