/*************************************************
* PBKDF/EMSA/EME/KDF/MGF Retrieval Source File   *
* (C) 1999-2007 Jack Lloyd                       *
*************************************************/

#include <botan/lookup.h>
#include <botan/libstate.h>
#include <botan/scan_name.h>

#if defined(BOTAN_HAS_PBKDF1)
  #include <botan/pbkdf1.h>
#endif

#if defined(BOTAN_HAS_PBKDF2)
  #include <botan/pbkdf2.h>
  #include <botan/hmac.h>
#endif

#if defined(BOTAN_HAS_PGPS2K)
  #include <botan/pgp_s2k.h>
#endif

#if defined(BOTAN_HAS_MGF1)
  #include <botan/mgf1.h>
#endif

#if defined(BOTAN_HAS_EMSA1)
  #include <botan/emsa1.h>
#endif

#if defined(BOTAN_HAS_EMSA1_BSI)
  #include <botan/emsa1_bsi.h>
#endif

#if defined(BOTAN_HAS_EMSA2)
  #include <botan/emsa2.h>
#endif

#if defined(BOTAN_HAS_EMSA3)
  #include <botan/emsa3.h>
#endif

#if defined(BOTAN_HAS_EMSA4)
  #include <botan/emsa4.h>
#endif

#if defined(BOTAN_HAS_EMSA_RAW)
  #include <botan/emsa_raw.h>
#endif

#if defined(BOTAN_HAS_EME1)
  #include <botan/eme1.h>
#endif

#if defined(BOTAN_HAS_EME_PKCS1v15)
  #include <botan/eme_pkcs.h>
#endif

#if defined(BOTAN_HAS_KDF1)
  #include <botan/kdf1.h>
#endif

#if defined(BOTAN_HAS_KDF2)
  #include <botan/kdf2.h>
#endif

#if defined(BOTAN_HAS_X942_PRF)
  #include <botan/prf_x942.h>
#endif

#if defined(BOTAN_HAS_SSL_V3_PRF)
  #include <botan/prf_ssl3.h>
#endif

#if defined(BOTAN_HAS_TLS_V10_PRF)
  #include <botan/prf_tls.h>
#endif

#if defined(BOTAN_HAS_CIPHER_MODE_PADDING)
  #include <botan/mode_pad.h>
#endif

namespace Botan {

/*************************************************
* Get a S2K algorithm by name                    *
*************************************************/
S2K* get_s2k(const std::string& algo_spec)
   {
   SCAN_Name request(algo_spec);

#if defined(BOTAN_HAS_PBKDF1)
   if(request.algo_name() == "PBKDF1" && request.arg_count() == 1)
      return new PKCS5_PBKDF1(get_hash(request.argument(0)));
#endif

#if defined(BOTAN_HAS_PBKDF2)
   if(request.algo_name() == "PBKDF2" && request.arg_count() == 1)
      return new PKCS5_PBKDF2(new HMAC(get_hash(request.argument(0))));
#endif

#if defined(BOTAN_HAS_PGPS2K)
   if(request.algo_name() == "OpenPGP-S2K" && request.arg_count() == 1)
      return new OpenPGP_S2K(get_hash(request.argument(0)));
#endif

   throw Algorithm_Not_Found(algo_spec);
   }

/*************************************************
* Get a block cipher padding method by name      *
*************************************************/
BlockCipherModePaddingMethod* get_bc_pad(const std::string& algo_spec)
   {
   SCAN_Name request(algo_spec);

#if defined(BOTAN_HAS_CIPHER_MODE_PADDING)
   if(request.algo_name() == "PKCS7")
      return new PKCS7_Padding;

   if(request.algo_name() == "OneAndZeros")
      return new OneAndZeros_Padding;

   if(request.algo_name() == "X9.23")
      return new ANSI_X923_Padding;

   if(request.algo_name() == "NoPadding")
      return new Null_Padding;
#endif

   throw Algorithm_Not_Found(algo_spec);
   }

/*************************************************
* Get an EMSA by name                            *
*************************************************/
EMSA* get_emsa(const std::string& algo_spec)
   {
   SCAN_Name request(algo_spec);

#if defined(BOTAN_HAS_EMSA_RAW)
   if(request.algo_name() == "Raw" && request.arg_count() == 0)
      return new EMSA_Raw;
#endif

#if defined(BOTAN_HAS_EMSA1)
   if(request.algo_name() == "EMSA1" && request.arg_count() == 1)
      return new EMSA1(get_hash(request.argument(0)));
#endif

#if defined(BOTAN_HAS_EMSA1_BSI)
   if(request.algo_name() == "EMSA1_BSI" && request.arg_count() == 1)
      return new EMSA1_BSI(get_hash(request.argument(0)));
#endif

#if defined(BOTAN_HAS_EMSA2)
   if(request.algo_name() == "EMSA2" && request.arg_count() == 1)
      return new EMSA2(get_hash(request.argument(0)));
#endif

#if defined(BOTAN_HAS_EMSA3)
   if(request.algo_name() == "EMSA3" && request.arg_count() == 1)
      return new EMSA3(get_hash(request.argument(0)));
#endif

#if defined(BOTAN_HAS_EMSA4)
   if(request.algo_name() == "EMSA4" && request.arg_count_between(1, 3))
      {
      // 3 args: Hash, MGF, salt size (MGF is hardcoded MGF1 in Botan)
      if(request.arg_count() == 1)
         return new EMSA4(get_hash(request.argument(0)));

      if(request.arg_count() == 2 && request.argument(1) != "MGF1")
         return new EMSA4(get_hash(request.argument(0)));

      if(request.arg_count() == 3)
         return new EMSA4(get_hash(request.argument(0)),
                          request.argument_as_u32bit(2, 0));
      }
#endif

   throw Algorithm_Not_Found(algo_spec);
   }

/*************************************************
* Get an EME by name                             *
*************************************************/
EME* get_eme(const std::string& algo_spec)
   {
   SCAN_Name request(algo_spec);

#if defined(BOTAN_HAS_EME_PKCS1v15)
   if(request.algo_name() == "PKCS1v15" && request.arg_count() == 0)
      return new EME_PKCS1v15;
#endif

#if defined(BOTAN_HAS_EME1)
   if(request.algo_name() == "EME1" && request.arg_count_between(1, 2))
      {
      if(request.arg_count() == 1 ||
         (request.arg_count() == 2 && request.argument(1) == "MGF1"))
         {
         return new EME1(get_hash(request.argument(0)));
         }
      }
#endif

   throw Algorithm_Not_Found(algo_spec);
   }

/*************************************************
* Get an KDF by name                             *
*************************************************/
KDF* get_kdf(const std::string& algo_spec)
   {
   SCAN_Name request(algo_spec);

#if defined(BOTAN_HAS_KDF1)
   if(request.algo_name() == "KDF1" && request.arg_count() == 1)
      return new KDF1(get_hash(request.argument(0)));
#endif

#if defined(BOTAN_HAS_KDF2)
   if(request.algo_name() == "KDF2" && request.arg_count() == 1)
      return new KDF2(get_hash(request.argument(0)));
#endif

#if defined(BOTAN_HAS_X942_PRF)
   if(request.algo_name() == "X9.42-PRF" && request.arg_count() == 1)
      return new X942_PRF(request.argument(0));
#endif

#if defined(BOTAN_HAS_TLS_V10_PRF)
   if(request.algo_name() == "TLS-PRF" && request.arg_count() == 0)
      return new TLS_PRF;
#endif

#if defined(BOTAN_HAS_SSL_V3_PRF)
   if(request.algo_name() == "SSL3-PRF" && request.arg_count() == 0)
      return new SSL3_PRF;
#endif

   throw Algorithm_Not_Found(algo_spec);
   }

}
