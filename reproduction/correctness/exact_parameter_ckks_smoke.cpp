#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

#include "seal/seal.h"

int main()
{
    using namespace seal;

    constexpr long logN = 16;
    constexpr int logp = 46;
    constexpr int logq = 51;
    constexpr int remaining_level = 16;
    constexpr int boot_level = 14;

    std::vector<int> coeff_bits{ logq };
    coeff_bits.insert(coeff_bits.end(), remaining_level, logp);
    coeff_bits.insert(coeff_bits.end(), boot_level, logq);
    coeff_bits.push_back(logq);

    EncryptionParameters parms(scheme_type::ckks);
    parms.set_poly_modulus_degree(std::size_t{ 1 } << logN);
    parms.set_coeff_modulus(CoeffModulus::Create(std::size_t{ 1 } << logN, coeff_bits));
    parms.set_secret_key_hamming_weight(192);

    SEALContext context(parms);
    if (!context.parameters_set())
    {
        std::cerr << context.parameter_error_name() << '\n';
        return 1;
    }

    KeyGenerator keygen(context);
    PublicKey public_key;
    keygen.create_public_key(public_key);
    RelinKeys relin_keys;
    keygen.create_relin_keys(relin_keys);
    GaloisKeys one_step_galois_keys;
    keygen.create_galois_keys(std::vector<int>{ 1 }, one_step_galois_keys);
    CKKSEncoder encoder(context);
    Encryptor encryptor(context, public_key);
    Evaluator evaluator(context, encoder);
    Decryptor decryptor(context, keygen.secret_key());

    const std::vector<double> input{ -1.0, -0.5, 0.0, 0.25, 0.5, 1.0 };
    const std::vector<double> addend(input.size(), 0.125);
    const double scale = std::pow(2.0, logp);

    Plaintext plain_input, plain_addend, plain_output;
    encoder.encode(input, scale, plain_input);
    encoder.encode(addend, scale, plain_addend);
    Ciphertext encrypted;
    encryptor.encrypt(plain_input, encrypted);
    evaluator.add_plain_inplace(encrypted, plain_addend);
    decryptor.decrypt(encrypted, plain_output);

    std::vector<double> decoded;
    encoder.decode(plain_output, decoded);
    double max_abs_error = 0.0;
    for (std::size_t i = 0; i < input.size(); ++i)
    {
        max_abs_error = std::max(max_abs_error, std::abs(decoded[i] - (input[i] + addend[i])));
    }

    std::cout << std::scientific << std::setprecision(8)
              << "max_abs_error=" << max_abs_error << '\n'
              << "checked_values=" << input.size() << '\n'
              << "security_qualifier="
              << static_cast<int>(context.key_context_data()->qualifiers().sec_level) << '\n'
              << "ciphertext_bytes_uncompressed="
              << encrypted.save_size(compr_mode_type::none) << '\n'
              << "public_key_bytes_uncompressed="
              << public_key.save_size(compr_mode_type::none) << '\n'
              << "secret_key_bytes_uncompressed="
              << keygen.secret_key().save_size(compr_mode_type::none) << '\n'
              << "relin_keys_bytes_uncompressed="
              << relin_keys.save_size(compr_mode_type::none) << '\n'
              << "one_step_galois_keys_bytes_uncompressed="
              << one_step_galois_keys.save_size(compr_mode_type::none) << '\n';
    return max_abs_error < 1e-6 ? 0 : 1;
}
