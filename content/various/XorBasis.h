/**
 * Author: Alex Li
 * License: CC0
 * Source: https://algorithms.alexli.ca/xor-basis/
 * Description: An XOR basis is the analog of a vector space basis for integers under the bitwise XOR operation
 * Time: O(B) \text{($B$ is the number of bits)}
 * Status: stress-tested
 */
#pragma once

struct XorBasis {
  static const ll MASK_BITS = 62;
  // basis[i] != 0 has its highest set bit at bit i.
  array<ll, MASK_BITS> basis{};
  int basis_size = 0;
  bool insert(ll x) {
    for (int i = MASK_BITS - 1; i >= 0; i--) {
      if (!((x >> i) & 1)) {
        continue;
      }
      if (basis[i] == 0) {
        basis[i] = x;
        basis_size++;
        return true;
      }
      x ^= basis[i];
    }
    return false;
  }
  bool contains(ll x) const {
    for (int i = MASK_BITS - 1; i >= 0; i--) {
      if (((x >> i) & 1) && basis[i] != 0)
        x ^= basis[i];
    }
    return x == 0;
  }
  ll maxXor(ll base = 0) const {
    for (int i = MASK_BITS - 1; i >= 0; i--) {
      if ((base ^ basis[i]) > base)
        base ^= basis[i];
    }
    return base;
  }
  int size() const { return basis_size; }
};