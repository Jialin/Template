/**
 * Subset iteration.
 */
for (int subMask = mask; subMask >= 0; subMask = (subMask - 1) & mask) {
  // ... deal with <subMask> of <mask>
  if (!subMask) break;
}
