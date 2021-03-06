/**
 *  @file
 *  @copyright defined in eos/LICENSE
 */
#pragma once

#include "crypto.h"
#include "fixed_bytes.hpp"
#include "varint.hpp"
#include "serialize.hpp"

#include <array>
#include <memory>
#include <string_view>
#include <vector>

#warning "<eosiolib/crypto.hpp> is deprecated use <eosio/crypto.hpp>"

namespace eosio {

   /**
   *  @defgroup public_key Public Key Type
   *  @ingroup types
   *  @brief Specifies public key type
   *
   *  @{
   */

   /**
    * EOSIO Public Key
    * @brief EOSIO Public Key
    */
   struct public_key {
      /**
       * Type of the public key, could be either K1 or R1
       * @brief Type of the public key
       */
      unsigned_int        type;

      /**
       * Bytes of the public key
       *
       * @brief Bytes of the public key
       */
      std::array<char,33> data;

      friend bool operator == ( const public_key& a, const public_key& b ) {
        return std::tie(a.type,a.data) == std::tie(b.type,b.data);
      }
      friend bool operator != ( const public_key& a, const public_key& b ) {
        return std::tie(a.type,a.data) != std::tie(b.type,b.data);
      }
      EOSLIB_SERIALIZE( public_key, (type)(data) )
   };

   /// @} publickeytype

   /**
   *  @defgroup signature Signature type
   *  @ingroup types
   *  @brief Specifies signature type
   *
   *  @{
   */

   /**
    * EOSIO Signature
    * @brief EOSIO Signature
    */
   struct signature {
      /**
       * Type of the signature, could be either K1 or R1
       * @brief Type of the signature
       */
      unsigned_int        type;

      /**
       * Bytes of the signature
       *
       * @brief Bytes of the signature
       */
      std::array<char,65> data;

      friend bool operator == ( const signature& a, const signature& b ) {
        return std::tie(a.type,a.data) == std::tie(b.type,b.data);
      }
      friend bool operator != ( const signature& a, const signature& b ) {
        return std::tie(a.type,a.data) != std::tie(b.type,b.data);
      }
      EOSLIB_SERIALIZE( signature, (type)(data) )
   };

   /// @} signaturetype

   /**
    *  @defgroup crypto Chain API
    *  @ingroup core
    *  @brief Defines API for calculating and checking hashes
    *  @{
    */

   /**
    *  Tests if the SHA256 hash generated from data matches the provided digest.
    *  This method is optimized to a NO-OP when in fast evaluation mode.
    *  @brief Tests if the sha256 hash generated from data matches the provided digest.
    *
    *  @param data - Data you want to hash
    *  @param length - Data length
    *  @param hash - digest to compare to
    */
   void assert_sha256( const char* data, uint32_t length, const eosio::checksum256& hash );

   /**
    *  Tests if the SHA1 hash generated from data matches the provided digest.
    *  This method is optimized to a NO-OP when in fast evaluation mode.
    *  @brief Tests if the sha1 hash generated from data matches the provided digest.
    *
    *  @param data - Data you want to hash
    *  @param length - Data length
    *  @param hash - digest to compare to
    */
   void assert_sha1( const char* data, uint32_t length, const eosio::checksum160& hash );

   /**
    *  Tests if the SHA512 hash generated from data matches the provided digest.
    *  This method is optimized to a NO-OP when in fast evaluation mode.
    *  @brief Tests if the sha512 hash generated from data matches the provided digest.
    *
    *  @param data - Data you want to hash
    *  @param length - Data length
    *  @param hash - digest to compare to
    */
   void assert_sha512( const char* data, uint32_t length, const eosio::checksum512& hash );

   /**
    *  Tests if the RIPEMD160 hash generated from data matches the provided digest.
    *  @brief Tests if the ripemd160 hash generated from data matches the provided digest.
    *
    *  @param data - Data you want to hash
    *  @param length - Data length
    *  @param hash - digest to compare to
    */
   void assert_ripemd160( const char* data, uint32_t length, const eosio::checksum160& hash );

   /**
    *  Hashes `data` using SHA256.
    *  @brief Hashes `data` using SHA256.
    *
    *  @param data - Data you want to hash
    *  @param length - Data length
    *  @return eosio::checksum256 - Computed digest
    */
   eosio::checksum256 sha256( const char* data, uint32_t length );

   /**
    *  Hashes `data` using SHA1.
    *  @brief Hashes `data` using SHA1.
    *
    *  @param data - Data you want to hash
    *  @param length - Data length
    *  @return eosio::checksum160 - Computed digest
    */
   eosio::checksum160 sha1( const char* data, uint32_t length );

   /**
    *  Hashes `data` using SHA512.
    *  @brief Hashes `data` using SHA512.
    *
    *  @param data - Data you want to hash
    *  @param length - Data length
    *  @return eosio::checksum512 - Computed digest
    */
   eosio::checksum512 sha512( const char* data, uint32_t length );

   /**
    *  Hashes `data` using RIPEMD160.
    *  @brief Hashes `data` using RIPEMD160.
    *
    *  @param data - Data you want to hash
    *  @param length - Data length
    *  @return eosio::checksum160 - Computed digest
    */
   eosio::checksum160 ripemd160( const char* data, uint32_t length );

   /**
    *  Calculates the public key used for a given signature on a given digest.
    *  @brief Calculates the public key used for a given signature on a given digest.
    *
    *  @param digest - Digest of the message that was signed
    *  @param sig - Signature
    *  @return eosio::public_key - Recovered public key
    */
   eosio::public_key recover_key( const eosio::checksum256& digest, const eosio::signature& sig );

   /**
    *  Tests a given public key with the recovered public key from digest and signature.
    *  @brief Tests a given public key with the recovered public key from digest and signature.
    *
    *  @param digest - Digest of the message that was signed
    *  @param sig - Signature
    *  @param pubkey - Public key
    */
   void assert_recover_key( const eosio::checksum256& digest, const eosio::signature& sig, const eosio::public_key& pubkey );

   /// }@cryptoapi


   /**
    *  @defgroup wax WAX Chain C++ extension API
    *  @brief Defines WAX C++ extension API
    *  @ingroup core
    *  @{
    */


    /**
    * Verifies an RSA signed message
    *
    * @warning WAX specific
    *
    * @param message - message buffer to verify
    * @param message_len - message buffer length
    * @param signature - signature as hex string
    * @param exponent - public key exponent as hex string
    * @param modulus - modulus as hex string (a leading zero is not allowed)
    *
    * @return false if validation has failed, true if everything is Ok
    *
    * @sa https://www.emc.com/collateral/white-papers/h11300-pkcs-1v2-2-rsa-cryptography-standard-wp.pdf
    *
    * @todo Check if this function must be removed (due to the old style message buffer)
    */
    inline bool verify_rsa_sha256_sig(const void* message,
                                      uint32_t message_len,
                                      std::string_view signature,
                                      std::string_view exponent,
                                      std::string_view modulus) {
        return ::verify_rsa_sha256_sig(
            message, message_len,
            signature.data(), signature.size(), 
            exponent.data(), exponent.size(),
            modulus.data(), modulus.size());
    }

   /**
    * Verifies an RSA signed message
    *
    * @warning WAX specific
    *
    * @param message - message to verify
    * @param signature - signature as hex string
    * @param exponent - public key exponent as hex string
    * @param modulus - modulus as hex string (a leading zero is not allowed)
    *
    * @return false if validation has failed, true if everything is Ok
    *
    * @sa https://www.emc.com/collateral/white-papers/h11300-pkcs-1v2-2-rsa-cryptography-standard-wp.pdf
    */
    inline bool verify_rsa_sha256_sig(std::string_view message,
                                      std::string_view signature,
                                      std::string_view exponent,
                                      std::string_view modulus) {
        return verify_rsa_sha256_sig(
            message.data(), message.size(), signature, exponent, modulus);
    }

   /**
    * Verifies an RSA signed message
    *
    * @warning WAX specific
    *
    * @param message - message to verify
    * @param signature - signature as hex string
    * @param exponent - public key exponent as hex string
    * @param modulus - modulus as hex string (a leading zero is not allowed)
    *
    * @return false if validation has failed, true if everything is Ok
    *
    * @sa https://www.emc.com/collateral/white-papers/h11300-pkcs-1v2-2-rsa-cryptography-standard-wp.pdf
    */
    template<typename T, typename A = std::allocator<T>>
    bool verify_rsa_sha256_sig(const std::vector<T, A>& message,
                               std::string_view signature,
                               std::string_view exponent,
                               std::string_view modulus) {
        return verify_rsa_sha256_sig(
            message.data(), message.size()*sizeof(T), signature, exponent, modulus);
    }

   /**
    * Verifies an RSA signed message
    *
    * @warning WAX specific
    *
    * @param message - message to verify
    * @param signature - signature as hex string
    * @param exponent - public key exponent as hex string
    * @param modulus - modulus as hex string (a leading zero is not allowed)
    *
    * @return false if validation has failed, true if everything is Ok
    *
    * @sa https://www.emc.com/collateral/white-papers/h11300-pkcs-1v2-2-rsa-cryptography-standard-wp.pdf
    */
    template<typename T, std::size_t N>
    bool verify_rsa_sha256_sig(const std::array<T, N>& message,
                               std::string_view signature,
                               std::string_view exponent,
                               std::string_view modulus) {
        return verify_rsa_sha256_sig(
            message.data(), message.size()*sizeof(T), signature, exponent, modulus);
    }

    /// }@wax

} // namespace eosio
