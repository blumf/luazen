

/*

This is directly extracted from the Monocypher library by Loup Vaillant.
http://loup-vaillant.fr/projects/monocypher/   (version 0.2)

All the Monocypher functions are included, except Chacha20 and Poly1305 
which are replaced with NORX.

The code below is copyrighted by Loup Vaillant, 2017. See LICENSE-monocypher.

20170319  - updated to Monocypher v0.6

*/

#ifndef MONOCYPHER_H
#define MONOCYPHER_H

#include <inttypes.h>
#include <stddef.h>

// Constant time equality verification
// returns 0 if it matches, -1 otherwise.
int crypto_memcmp(const uint8_t *p1, const uint8_t *p2, size_t n);

// constant time zero comparison.
// returns 0 if the input is all zero, -1 otherwise.
int crypto_zerocmp(const uint8_t *p, size_t n);

////////////////
/// Chacha20 ///  REMOVED
////////////////

/////////////////
/// Poly 1305 ///  REMOVED
/////////////////


////////////////
/// Blake2 b ///
////////////////
typedef struct {
    uint8_t  buf[128];      // input buffer
    uint64_t hash[8];       // chained state
    uint64_t input_size[2]; // total number of bytes
    uint8_t  c;             // pointer for buf[]
    uint8_t  output_size;   // digest size
} crypto_blake2b_ctx;

void crypto_blake2b_general_init(crypto_blake2b_ctx *ctx, size_t out_size,
                                 const uint8_t      *key, size_t key_size);

void crypto_blake2b_init(crypto_blake2b_ctx *ctx);

void crypto_blake2b_update(crypto_blake2b_ctx *ctx,
                           const uint8_t *in, size_t in_size);

void crypto_blake2b_final(crypto_blake2b_ctx *ctx, uint8_t *out);

void crypto_blake2b_general(uint8_t       *out, size_t out_size, // digest
                            const uint8_t *key, size_t key_size, // optional
                            const uint8_t *in , size_t in_size);

void crypto_blake2b(uint8_t out[64], const uint8_t *in, size_t in_size);

////////////////
/// Argon2 i ///
////////////////
void crypto_argon2i(uint8_t       *tag,       uint32_t tag_size,      // >= 4
                    void          *work_area, uint32_t nb_blocks,     // >= 8
                    uint32_t       nb_iterations,
                    const uint8_t *password,  uint32_t password_size,
                    const uint8_t *salt,      uint32_t salt_size,     // >= 8
                    const uint8_t *key,       uint32_t key_size,
                    const uint8_t *ad,        uint32_t ad_size);

///////////////
/// X-25519 ///
///////////////
int crypto_x25519(uint8_t       shared_secret   [32],
                  const uint8_t your_secret_key [32],
                  const uint8_t their_public_key[32]);

void crypto_x25519_public_key(uint8_t       public_key[32],
                              const uint8_t secret_key[32]);


///////////////
/// Ed25519 ///
///////////////
void crypto_sign_public_key(uint8_t        public_key[32],
                            const uint8_t  secret_key[32]);

void crypto_sign(uint8_t        signature[64],
                 const uint8_t  secret_key[32],
                 const uint8_t  public_key[32], // optional, may be 0
                 const uint8_t *message, size_t message_size);

int crypto_check(const uint8_t  signature[64],
                 const uint8_t  public_key[32],
                 const uint8_t *message, size_t message_size);

////////////////////
/// Key exchange ///
////////////////////
int crypto_key_exchange(uint8_t       shared_key      [32],
                        const uint8_t your_secret_key [32],
                        const uint8_t their_public_key[32]);

////////////////////////////////
/// Authenticated encryption ///  REMOVED
////////////////////////////////

#endif // MONOCYPHER_H
