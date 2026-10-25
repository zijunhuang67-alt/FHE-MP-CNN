#include <iostream>
#include <numeric>
#include <vector>

#include "seal/seal.h"

int main()
{
    using namespace seal;

    constexpr long logN = 16;
    constexpr int logp = 46;
    constexpr int logq = 51;
    constexpr int log_special_prime = 51;
    constexpr int remaining_level = 16;
    constexpr int boot_level = 14;
    constexpr std::size_t secret_key_hamming_weight = 192;

    std::vector<int> requested_bits;
    requested_bits.push_back(logq);
    requested_bits.insert(requested_bits.end(), remaining_level, logp);
    requested_bits.insert(requested_bits.end(), boot_level, logq);
    requested_bits.push_back(log_special_prime);

    EncryptionParameters parms(scheme_type::ckks);
    const std::size_t degree = std::size_t{ 1 } << logN;
    parms.set_poly_modulus_degree(degree);
    parms.set_coeff_modulus(CoeffModulus::Create(degree, requested_bits));
    parms.set_secret_key_hamming_weight(secret_key_hamming_weight);

    SEALContext context(parms, true, sec_level_type::tc128);
    const auto &key_data = *context.key_context_data();
    const auto &qualifiers = key_data.qualifiers();
    CKKSEncoder encoder(context);

    std::cout << "parameters_set=" << std::boolalpha << context.parameters_set() << '\n';
    std::cout << "parameter_error=" << context.parameter_error_name() << '\n';
    std::cout << "poly_modulus_degree=" << degree << '\n';
    std::cout << "coeff_modulus_prime_count=" << parms.coeff_modulus().size() << '\n';
    std::cout << "requested_coeff_modulus_bits="
              << std::accumulate(requested_bits.begin(), requested_bits.end(), 0) << '\n';
    std::cout << "actual_coeff_modulus_bits=" << key_data.total_coeff_modulus_bit_count() << '\n';
    std::cout << "tc128_max_coeff_modulus_bits="
              << CoeffModulus::MaxBitCount(degree, sec_level_type::tc128) << '\n';
    std::cout << "qualifier_sec_level=" << static_cast<int>(qualifiers.sec_level) << '\n';
    std::cout << "slot_count=" << encoder.slot_count() << '\n';
    std::cout << "secret_key_hamming_weight=" << parms.secret_key_hamming_weight() << '\n';

    return context.parameters_set() && qualifiers.sec_level == sec_level_type::tc128 ? 0 : 1;
}
