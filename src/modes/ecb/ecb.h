/*************************************************
* ECB Mode Header File                           *
* (C) 1999-2007 Jack Lloyd                       *
*************************************************/

#ifndef BOTAN_ECB_H__
#define BOTAN_ECB_H__

#include <botan/modebase.h>
#include <botan/mode_pad.h>
#include <botan/block_cipher.h>

namespace Botan {

/*************************************************
* ECB                                            *
*************************************************/
class BOTAN_DLL ECB : public BlockCipherMode
   {
   protected:
      ECB(BlockCipher* ciph, const BlockCipherModePaddingMethod* pad) :
         BlockCipherMode(ciph, "ECB", 0), padder(pad) {}
      ~ECB() { delete padder; }

      std::string name() const;
      const BlockCipherModePaddingMethod* padder;
   private:
      bool valid_iv_size(u32bit) const;
   };

/*************************************************
* ECB Encryption                                 *
*************************************************/
class BOTAN_DLL ECB_Encryption : public ECB
   {
   public:
      ECB_Encryption(BlockCipher* ciph,
                     const BlockCipherModePaddingMethod* pad) :
         ECB(ciph, pad) {}

      ECB_Encryption(BlockCipher* ciph,
                     const BlockCipherModePaddingMethod* pad,
                     const SymmetricKey& key) :
         ECB(ciph, pad) { set_key(key); }
   private:
      void write(const byte[], u32bit);
      void end_msg();
   };

/*************************************************
* ECB Decryption                                 *
*************************************************/
class BOTAN_DLL ECB_Decryption : public ECB
   {
   public:
      ECB_Decryption(BlockCipher* ciph,
                     const BlockCipherModePaddingMethod* pad) :
         ECB(ciph, pad) {}

      ECB_Decryption(BlockCipher* ciph,
                     const BlockCipherModePaddingMethod* pad,
                     const SymmetricKey& key) :
         ECB(ciph, pad) { set_key(key); }
   private:
      void write(const byte[], u32bit);
      void end_msg();
   };

}

#endif
